<?php

class VersioncontrolGitRepositoryHistorySynchronizerDefault implements VersioncontrolRepositoryHistorySynchronizerInterface {

  protected $repository;

  protected $templateDir;

  protected $built;

  public function setRepository(VersioncontrolRepository $repository) {
    // Additional parameter check to the appropriate Git subclass of that
    // required by the interface itself.
    if (!$repository instanceof VersioncontrolGitRepository) {
      $msg = 'The repository "@name" with repo_id "@repo_id" passed to ' . __METHOD__ . ' was not a VersioncontrolGitRepository instance.' ;
      $vars = array(
        '@name' => $repository->name,
        '@repo_id' => empty($repository->repo_id) ? '[NEW]' : $repository->repo_id,
      );
      watchdog($msg, $vars, WATCHDOG_ERROR);
      throw new Exception(strtr($msg, $vars), E_ERROR);
    }
    $this->repository = $repository;
  }

  protected function loadBranchesKeyed() {
    $branches = array();
    $branches_db = $this->repository->loadBranches(array(), array(), array('may cache' => FALSE));

    foreach ($branches_db as $branch) {
      $branches[$branch->name] = $branch;
    }

    return $branches;
  }

  protected function loadTagsKeyed() {
    $tags = array();
    $tags_db = $this->repository->loadTags(array(), array(), array('may cache' => FALSE));

    foreach ($tags_db as $tag) {
      $tags[$tag->name] = $tag;
    }

    return $tags;
  }

  protected function loadCommitHashes($ids = array(), $conditions = array()) {
    $commits = $this->repository->loadCommits($ids, $conditions, array('may cache' => FALSE));

    $revisions = array();
    foreach ($commits as $commit) {
      $revisions[] = $commit->revision;
    }

    return $revisions;
  }

  public function syncFull($options) {
    if (!$this->verify() || !$this->prepare()) {
      return FALSE;
    }

    // 1. Process branches

    // Fetch branches from the repo and load them from the db.
    $branches_repo = $this->repository->fetchBranches();
    $branches_db = $this->loadBranchesKeyed();

    // Determine whether we've got branch changes to make.

    // Insert new branches in the repository. Later all commits in these new
    // branches will be updated.
    // Unfortunately we can't say anything about the branch author at this time.
    // The post-update hook could do this, though.
    // We also can't insert a VCOperation which adds the branch, because
    // we don't know anything about the branch. This is all stuff a hook could
    // figure out.
    foreach(array_diff_key($branches_repo, $branches_db) as $branch) {
      $branch->insert();
    }

    // Reload branches, after they was inserted.
    $branches_db = $this->loadBranchesKeyed();

    // Deleted branches are removed, commits in them are not!
    foreach(array_diff_key($branches_db, $branches_repo) as $branch) {
      $branch->delete();
    }

    // Set the default branch if needed.
    if (!$this->repository->defaultBranch) {
      $this->repository->defaultBranch = $this->getDefaultBranch();
      $this->repository->save(array('nested' => FALSE));
    }

    // 2. Process tags

    // Fetch tags from the repository and load them from the db.
    $tags_in_repo = $this->repository->fetchTags();
    $tags_in_db_by_name = $this->loadTagsKeyed();

    // Check for new tags.
    $tags_new = array_diff_key($tags_in_repo, $tags_in_db_by_name);
    $tags_deleted = array_diff_key($tags_in_db_by_name, $tags_in_repo);
    if (!empty($tags_new)) {
      // Insert new tags in the database.
      $this->processTags($tags_new);
    }
    // Reload tags, after they was inserted.
    $tags_in_db_by_name = $this->loadTagsKeyed();
    // Delete removed tags.
    foreach($tags_deleted as $tag) {
      $tag->delete();
    }

    // 3. Process commits

    // Fetch commits from the repo and load them from the db.
    $commits_repo_hashes = $this->repository->fetchCommits();
    $commits_db_hashes = $this->loadCommitHashes();

    // Insert new commits in the database.
    foreach (array_diff($commits_repo_hashes, $commits_db_hashes) as $hash) {
      $this->parseAndInsertCommit($hash, $branches_db, $tags_in_db_by_name, $options);
    }

    $this->finalize();

    return TRUE;
  }

  /**
   * Parse the output of 'git log' and insert a commit based on its data.
   *
   * @param VersioncontrolRepository $repository
   * @param array $hash
   *   A valid git commit hash.
   * @param array $branches
   *   A VersioncontrolBranch list keyed by branch name.
   * @param array $tags
   *   A VersioncontrolTag list keyed by tag name.
   * @param array $options
   *   See VersioncontrolRepositoryHistorySynchronizerInterface::options.
   */
  protected function parseAndInsertCommit($hash, $branches, $tags, $options) {
    $command = "show --numstat --summary --pretty=format:\"%H%n%P%n%an%n%ae%n%at%n%cn%n%ce%n%ct%n%B%nENDOFOUTPUTGITMESSAGEHERE\" " . escapeshellarg($hash);
    $logs = $this->execute($command);

    // Get commit hash (vcapi's "revision")
    $revision = trim(next($logs));

    // Get parent commit hash(es)
    $parents = explode(' ', trim(next($logs)));
    if (empty($parents[0])) {
      $parents = array();
    }
    $merge = !empty($parents[1]); // Multiple parents indicates a merge

    // Get author data
    $author_name = iconv("UTF-8", "UTF-8//IGNORE", trim(next($logs)));
    $author_email = iconv("UTF-8", "UTF-8//IGNORE", trim(next($logs)));
    $author_date = trim(next($logs));

    // Get committer data
    $committer_name = iconv("UTF-8", "UTF-8//IGNORE", trim(next($logs)));
    $committer_email = iconv("UTF-8", "UTF-8//IGNORE", trim(next($logs)));
    $committer_date = trim(next($logs));

    // Get revision message.
    // TODO: revisit!
    $message = '';
    $i = 0;
    while (($line = iconv("UTF-8", "UTF-8//IGNORE", trim(next($logs)))) !== FALSE) {
      if ($line == 'ENDOFOUTPUTGITMESSAGEHERE') {
        if (substr($message, -2) === "\n\n") {
          $message = substr($message, 0, strlen($message) - 1);
        }
        break;
      }
      $message .= $line ."\n";
      $i++;
    }

    // This is either a (kind of) diffstat for each modified file or a list of
    // file actions like moved, created, deleted, mode changed.
    $line = next($logs);

    // build the data array to be used for the commit op
    $op_data = array(
      'type' => VERSIONCONTROL_OPERATION_COMMIT,
      'revision' => $revision,
      'author' => $author_email,
      'author_name' => $author_name,
      'committer' => $committer_email,
      'committer_name' => $committer_name,
      'parent_commit' => reset($parents),
      'merge' => $merge,
      'author_date' => $author_date,
      'committer_date' => $committer_date,
      'message' => $message,
      'repository' => $this->repository,
    );

    $op = new VersioncontrolGitOperation($this->repository->getBackend());
    $op->build($op_data);
    $op->labels = $this->getCommitLabels($revision, $branches, $tags, $options);
    $op->insert(array('map users' => TRUE));

    $item_action = $merge ? VERSIONCONTROL_ACTION_MERGED : VERSIONCONTROL_ACTION_MODIFIED;
    // build the data array to be used as default values for the item revision
    $default_item_data = array(
      // pass backend in data array to avoid just another param to parse
      // item function
      'backend' => $this->repository->getBackend(),
      'repository' => $this->repository,
      'vc_op_id' => $op->vc_op_id,
      'type' => VERSIONCONTROL_ITEM_FILE,
      'revision' => $revision,
      'action' => $item_action,
    );

    // Parse in the raw data and create VersioncontrolGitItem objects.
    $op_items = $this->parseItems($logs, $line, $default_item_data, $parents);
    $op->itemRevisions = $op_items;
    $op->save(array('nested' => TRUE));
  }

  /**
   * Returns an array of all branches and tags given commit is in.
   *
   * @param string $revision
   *   Git commit hash.
   * @param array $branch_label_list
   *   A VersioncontrolBranch list keyed by branch name.
   * @param array $tag_label_list
   *   A VersioncontrolTag list keyed by tag name.
   * @param array $options
   *   See VersioncontrolRepositoryHistorySynchronizerInterface::options.
   *
   * @return array
   *   List of labels(VersioncontrolBranch, VersioncontrolTag) associated with
   *   the revision.
   */
  protected function getCommitLabels($revision, $branch_label_list, $tag_label_list, $options) {
    $labels = array();

    // Process branches.
    if ($options['operation_labels_mapping'] & VersioncontrolRepositoryHistorySynchronizerInterface::MAP_COMMIT_BRANCH_RELATIONS) {
      $exec = 'branch --no-color --contains ' . escapeshellarg($revision);
      $logs = $this->execute($exec);
      while (($line = next($logs)) !== FALSE) {
        $line = trim($line);
        if ($line[0] == '*') {
          $line = substr($line, 2);
        }
        if (!empty($branch_label_list[$line])) {
          $labels[] = $branch_label_list[$line];
        }
      }
    }

    // Process tags.
    if ($options['operation_labels_mapping'] & VersioncontrolRepositoryHistorySynchronizerInterface::MAP_COMMIT_TAG_RELATIONS) {
      $exec = 'tag -l --contains ' . escapeshellarg($revision);
      $logs = $this->execute($exec);
      while (($line = next($logs)) !== FALSE) {
        if (!empty($tag_label_list[$line])) {
          $labels[] = $tag_label_list[$line];
        }
      }
    }

    return $labels;
  }

  /**
   * Takes parts of the output of git log and returns all affected OperationItems for a commit.
   * @param array $logs
   * @param string $line
   * @param string $revision
   * @param array $parents The parent commit(s)
   * @param bool $merge
   * @return array All items affected by a commit.
   */
  protected function parseItems(&$logs, &$line, $data, $parents) {
    $op_items = array();

    // Parse the diffstat for the changed files.
    do {
      if (!preg_match('/^(\S+)' . "\t" . '(\S+)' . "\t" . '(.+)$/', $line, $matches)) {
        break;
      }
      $path = '/' . $matches[3];
      $op_items[$path] = new VersioncontrolGitItem($data['backend']);
      $data['path'] = $path;
      $op_items[$path]->build($data);
      unset($data['path']);

      if (is_numeric($matches[1]) && is_numeric($matches[2])) {
        $op_items[$path]->line_changes_added = $matches[1];
        $op_items[$path]->line_changes_removed = $matches[2];
      }

      // extract blob
      $command = 'ls-tree -r ' . escapeshellarg($data['revision']) . ' ' . escapeshellarg($matches[3]);
      $lstree_lines = $this->execute($command);
      $blob_hash = $this->parseItemBlob($lstree_lines);
      $op_items[$path]->blob_hash = $blob_hash;
    } while (($line = next($logs)) !== FALSE);

    // Parse file actions.
    do {
      if (!preg_match('/^ (\S+) (\S+) (\S+) (.+)$/', $line, $matches)) {
        break;
      }
      // We also can get 'mode' here if someone changes the file permissions.
      if ($matches[1] == 'create') {
        $op_items['/' . $matches[4]]->action = VERSIONCONTROL_ACTION_ADDED;
        // extract blob
        $command = 'ls-tree -r ' . escapeshellarg($data['revision']) . ' ' . escapeshellarg($matches[4]);
        $lstree_lines = $this->execute($command);
        $blob_hash = $this->parseItemBlob($lstree_lines);
        $op_items['/' . $matches[4]]->blob_hash = $blob_hash;
      }
      else if ($matches[1] == 'delete') {
        $op_items['/' . $matches[4]]->action = VERSIONCONTROL_ACTION_DELETED;
        $op_items['/' . $matches[4]]->type = VERSIONCONTROL_ITEM_FILE_DELETED;
      }
    } while (($line = next($logs)) !== FALSE);

    // Fill in the source_items for non-added items
    foreach ($op_items as $path => &$item) {
      if ($item->action != VERSIONCONTROL_ACTION_ADDED) {
        $this->fillSourceItem($item, $parents, $data);
      }
    }
    return $op_items;
  }

 /**
   * Parse ls-tree with one commit hash and one item.
   */
  protected function parseItemBlob($lines) {
    $line = next($lines);
    // output: <mode> SP <type> SP <object> TAB <file>
    $info = explode("\t", $line);
    $info = array_shift($info);
    $info = explode(' ', $info);
    $blob_hash = array_pop($info);
    return $blob_hash;
  }

  /**
   * A function to fill in the source_item for a specific VersioncontrolItem.
   *
   * Now VCS API assumes there is only one source item, so merges can not be
   * tracked propertly there, and we are neither tracking on git backend for
   * now.
   * For merges we are choosing the first parent git-log  show.
   *
   * @param VersioncontrolItem &$item
   * @param array $parents The parent commit(s)
   * @return none
   */
  protected function fillSourceItem(&$item, $parents, $inc_data) {
    $data = array(
      'type' => VERSIONCONTROL_ITEM_FILE,
      'repository' => $inc_data['repository'],
      'path' => $item->path,
    );

    $path_stripped = substr($item->path, 1);
    // using -5 to let detect merges until 4 parents, merging more than 4 parents in one operation is insane!
    // use also --first-parent to retrieve only one parent for the current support of VCS API
    $cmd = 'log --first-parent --follow --pretty=format:"%H" -5 ' . escapeshellarg($item->revision) . ' -- ' . escapeshellarg($path_stripped);
    $prev_revisions = $this->execute($cmd);

    next($prev_revisions); // grab our hash out
    if (($parent_hash = next($prev_revisions)) !== FALSE) { // get the first parent hash
      $data['revision'] = trim($parent_hash);
      // just fill an object from scratch
      $source_item = new VersioncontrolGitItem($item->getBackend());
      $source_item->build($data);
      $item->setSourceItem($source_item);
    }
    //TODO unify the way to fail
  }

  /**
   * Does all processing to insert the tags in $tags_new in the database.
   *
   * @param VersioncontrolGitRepository $repository
   * @param array $tags_new
   *   All new tags.
   *
   * @return
   *   None.
   */
  function processTags($tags_new) {
    if (empty($tags_new)) {
      return;
    }

    // get a list of all tag names with the corresponding commit.
    $tag_commit_list = $this->getTagCommitList($tags_new);
    $format = '%(objecttype)%0a%(objectname)%0a%(refname)%0a%(taggername)%20%(taggeremail)%0a%(taggerdate)%0a%(contents)ENDOFGITTAGOUTPUTMESAGEHERE';
    foreach ($tag_commit_list as $tag_name => $tag_commit) {
      $exec = 'for-each-ref --format=' . $format . ' refs/tags/' . escapeshellarg($tag_name);
      $logs_tag_msg = $this->execute($exec);

      // Get the specific tag data for annotated vs not annotated tags.
      if ($logs_tag_msg[1] == 'commit') {
        // simple tag
        // [2] is tagged commit [3] tagname [4] and [5] empty [6] commit log
        // message.
        // We get the tagger, the tag_date and the tag_message from the tagged
        // commit.
        $command = 'rev-list -1 --pretty=format:"%an%n%at%n%BENDOFGITTAGOUTPUTMESAGEHERE" ' . escapeshellarg($tag_commit);
        $logs = $this->execute($command);
        $line = next($logs);
        $commits[] = trim($line);
        $tagger = next($logs);
        $tag_date = next($logs);
        $message = '';
        $body_start = TRUE;
        while (($line = next($logs)) !== FALSE) {
          if ($line == 'ENDOFGITTAGOUTPUTMESAGEHERE') {
            break;
          }
          if ($body_start) {
            $message .= "$line";
            $body_start = FALSE;
          }
          else {
            $message .= "\n$line";
          }
        }
      }
      elseif ($logs_tag_msg[1] == 'tag') {
        // annotated tag
        // [2] is the tagged commit [3] tag name
        $tagger = $logs_tag_msg[4];
        $tag_date = strtotime($logs_tag_msg[5]);
        // Get the tag message
        $message = '';
        $i = 0;
        while (true) {
          $line = $logs_tag_msg[$i + 6];
          if($logs_tag_msg[$i + 7] == 'ENDOFGITTAGOUTPUTMESAGEHERE') {
            $message .= $line;
            break;
          }
          $message .= $line ."\n";
          $i++;
        }
      }
      else {
        watchdog('versioncontrol_git', 'Serious problem in tag parsing, please check that you\'re using a supported version of git!');
      }

      $tag_data = array(
        'name' => $tag_name,
        'repository' => $this->repository,
        'repo_id' => $this->repository->repo_id,
      );

      $tag = $this->repository->getBackend()->buildEntity('tag', $tag_data + array('action' => VERSIONCONTROL_ACTION_ADDED));
      $tag->insert();
    }
  }

  /**
   * Returns a list of tag names with the tagged commits.
   * Handles annotated tags.
   * @param array $tags An array of tag names
   * @return array A list of all tags with the respective tagged commit.
   */
  function getTagCommitList($tags) {
    if(empty($tags)) {
      return array();
    }
    $tag_string = $this->getTagString($tags);
    $exec = "show-ref -d $tag_string";
    $tag_commit_list_raw = $this->execute($exec);
    $tag_commit_list = array();
    $tags_annotated = array();
    foreach($tag_commit_list_raw as $tag_commit_line) {
      if($tag_commit_line == '') {
        continue;
      }
      $tag_commit = substr($tag_commit_line, 0, 40);
      // annotated tag mark
      // 9c70f55549d3f4e70aaaf30c0697f704d02e9249 refs/tags/tag^{}
      if (substr($tag_commit_line, -3, 3) == '^{}') {
        $tag_name = substr($tag_commit_line, 51, -3);
        $tags_annotated[$tag_name] = $tag_commit;
      }
      // Simple tags
      // 9c70f55549d3f4e70aaaf30c0697f704d02e9249 refs/tags/tag
      else {
        $tag_name = substr($tag_commit_line, 51);
      }
      $tag_commit_list[$tag_name] = $tag_commit;
    }
    // Because annotated tags show up twice in the output of git show-ref, once
    // with a 'tag' object and once with a commit-id we will go through them and
    // adjust the array so we just keep the commits.
    foreach($tags_annotated as $tag_name => $tag_commit) {
      $tag_commit_list[$tag_name] = $tag_commit;
    }
    return $tag_commit_list;
  }

  /**
   * Returns a string with fully qualified tag names from an array of tag names.
   * @param array $tags
   * @return string
   */
  function getTagString($tags) {
    $tag_string = '';
    // $tag_string is a list of fully qualified tag names
    foreach ($tags as $tag) {
      $tag_string .= escapeshellarg("refs/tags/{$tag->name}") . ' ';
    }
    return $tag_string;
  }

  /**
   * Runs a command through the repository object.
   */
  protected function execute($command) {
    return $this->repository->exec($command);
  }

  public function syncInitial($options) {
    // @todo halstead's optimized fast-export-based parser goes here. But for
    // now, just use the same old crap.
    $sync_options = $this->repository->getSynchronizerOptions();
    return $this->syncFull($sync_options);
  }

  protected function getCommitInterval($start, $end) {
    if ($start == GIT_NULL_REV) {
      // Start as null rev is the same as saying "all revs back to the root"
      $range = $end;
    }
    elseif ($end == GIT_NULL_REV) {
      // null rev as the end of a rev list makes no sense.
      throw new VersioncontrolSynchronizationException("Attempted to git rev-list with the null rev as the end commit.", E_RECOVERABLE_ERROR);
    }
    else {
      $range = "$start..$end";
    }

    $command = "rev-list --reverse $range";
    $logs = $this->execute($command);

    $commit_hashes = array();
    while (($line = next($logs)) !== FALSE) {
      if (($line = trim($line)) && (strlen($line) == 40)) {
        $commit_hashes[] = $line;
      }
    }
    return $commit_hashes;
  }

  public function syncEvent(VersioncontrolEvent $event, $options) {
    if (!$this->verify() || !$this->prepare()) {
      return FALSE;
    }

    // Check event, so we process only git events.
    if (!$event instanceof VersioncontrolGitEvent) {
      $msg = t('An incompatible VersioncontrolEvent object (of class @class) was provided to a Git repository synchronizer for event-driven repository synchronization.', array('@class' => get_class($event)));
      throw new VersioncontrolSynchronizationException($msg, E_ERROR);
    }

    $this->repository->finalizeEvent($event);

    foreach ($event as &$ref) {
      // 1. Process this label.
      $label_db = $ref->getLabel();

      switch ($ref->reftype) {
        case VERSIONCONTROL_GIT_REFTYPE_BRANCH:
          $label_repo = $this->repository->fetchBranch($ref->refname);
          break;
        case VERSIONCONTROL_GIT_REFTYPE_TAG:
          $label_repo = $this->repository->fetchTag($ref->refname);
          break;
      }

      if ($ref->eventCreatedMe() && empty($label_db) && ($label = $label_repo)) {
        $label->insert();
        $ref->label_id = $label->label_id;
      }
      elseif ($ref->eventDeletedMe() && empty($label_repo) && ($label = $label_db)) {
        $label->delete();
      }
      elseif ($label = $label_db) {
        $label->update();
      }
      else {
        $msg = t("Ref '@ref' on repository '@name' indicated it was updated by a push, but there was no record of the ref in the database.", array('@ref' => $ref->refname, '@name' => $this->repository->name));
        throw new VersioncontrolNeedsFullSynchronizationException($msg, E_RECOVERABLE_ERROR);
      }

      unset($label_db);
      unset($label_repo);

      // 2. Process commits.

      if (VERSIONCONTROL_LABEL_BRANCH == $label->type && !$ref->eventDeletedMe()) {
        // TODO replace this with a targeted load based on the $event
        $branches_db = $this->loadBranchesKeyed();
        $tags_db = $this->loadTagsKeyed();
        $commit_hashes = $this->getCommitInterval($ref->old_sha1, $ref->new_sha1);

        if (empty($commit_hashes)) {
          // Apart from the new-branch-same-as-HEAD case above, this should NOT
          // happen. So we error out if it does; allowing it to continue would
          // instead result in an arcane PDO select query error.
          throw new VersioncontrolSynchronizationException("Zero-item commit interval of potential commits not in the database.", E_RECOVERABLE_ERROR);
        }

        $interval_operations_in_db = $this->repository->loadCommits(array(), array('revision' => $commit_hashes), array('may cache' => FALSE));

        $interval_revisions_in_db = array();
        foreach ($interval_operations_in_db as $interval_operation_in_db) {
          $interval_revisions_in_db[] = $interval_operation_in_db->revision;
          // Update labels for known operations.
          $label_is_new = TRUE;
          foreach ($interval_operation_in_db->labels as $stored_label) {
            if ($stored_label->label_id == $label->label_id) {
              $label_is_new = FALSE;
              break;
            }
          }
          if ($label_is_new) {
            $interval_operation_in_db->labels[] = $label;
            $interval_operation_in_db->updateLabels();
          }
        }
        // Add commits not in DB yet.
        foreach (array_diff($commit_hashes, $interval_revisions_in_db) as $hash) {
          $this->parseAndInsertCommit($hash, $branches_db, $tags_db, $options);
        }

        // Only on non-fast-forward, we look for commits not anymore related
        // with the label and remove them.
        if ($ref->ff == 0) {
          $label_commit_hashes = $this->repository->fetchCommits($label->name);

          $label_commit_hashes_removed = array_diff($interval_revisions_in_db, $label_commit_hashes);
          $label_operations_removed = $this->repository->loadCommits(array(), array('revision' => $label_commit_hashes));
          foreach ($label_operations_removed as $label_operation_removed) {
            if (count($label_operation_removed->labels) > 1) {
              // There are other labels that contain this commit, just only
              // remove the connection to the current label.
              foreach ($label_operation_removed->labels as $key => $commit_label) {
                if ($commit_label->label_id == $label->label_id) {
                  unset($label_operation_removed->labels[$key]);
                  break;
                }
              }
              $label_operation_removed->updateLabels();
            }
            else {
              // It's save to completly delete the commit from the database.
              $label_operation_removed->delete();
            }
          }
        }
      }
    }

    $event->update();
    $this->finalize();
    return TRUE;
  }

  public function verifyEvent(VersioncontrolEvent $event) {
    // Check event type, to ensure we only verify git events.
    if (!$event instanceof VersioncontrolGitEvent) {
      $msg = t('An incompatible VersioncontrolEvent object (of class @class) was provided to a Git repository synchronizer for event-driven repository synchronization.', array('@class' => get_class($event)));
      throw new VersioncontrolSynchronizationException($msg, E_ERROR);
    }

    // TODO cache this as an object prop so we don't just do it all again
    foreach ($event as $ref) {
      switch ($ref->reftype) {
        case VERSIONCONTROL_GIT_REFTYPE_BRANCH:
          $label_repo = $this->repository->fetchBranch($ref->refname);
          break;
        case VERSIONCONTROL_GIT_REFTYPE_TAG:
          $label_repo = $this->repository->fetchTag($ref->refname);
          break;
      }

      // If the tips don't match, or the event indicated a deletion but we a
      // FALSE didn't come back instead of a label object, bail.
      if ((GIT_NULL_REV === $ref->new_sha1 && $label_repo != FALSE) ||
          ($label_repo->tip !== $ref->new_sha1)) {
        return FALSE;
      }
    }

    return TRUE;
  }

  public function verifyData() {
    return TRUE;
  }

  /**
   * Prepare the repository for synchronization.
   *
   * Ensure locks are available and sets necessary environment vars.
   *
   * @throws VersioncontrolLockedRepositoryException
   */
  protected function prepare() {
    putenv("GIT_DIR=". escapeshellcmd($this->repository->root));
    return $this->repository->lock();
  }

  protected function finalize() {
    // Update repository updated field. Displayed on administration interface for documentation purposes.
    $this->repository->updated = time();
    $this->repository->unlock();
  }

  protected function verify() {
    if (!$this->repository->isValidGitRepo()) {
      $msg = t('The repository @name at @root is not a valid Git bare repository.', array('@name' => $this->repository->name, '@root' => $this->repository->root));
      throw new VersioncontrolSynchronizationException($msg, E_RECOVERABLE_ERROR);
    }
    return TRUE;
  }

  protected function getDefaultBranch() {
    $exec = 'symbolic-ref --quiet HEAD';
    $logs = $this->execute($exec);
    $default_branch = next($logs);

    if (empty($default_branch)) {
      return NULL;
    }

    // Stdout should be refs/heads/<branchname>.
    if (!preg_match('/^refs\/heads\/(.*)$/', $default_branch, $match)) {
      return NULL;
    }

    return $match[1];
  }
}
