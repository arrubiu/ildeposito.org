<?php

class VersioncontrolGitRepository extends VersioncontrolRepository {

  /**
   * The branch name of the default (HEAD) branch or NULL if this information
   * is not available.
   */
  public $defaultBranch = NULL;

  public function build($args = array()) {
    parent::build($args);
    // Map db field to data member.
    if (isset($this->default_branch)) {
      $this->defaultBranch = $this->default_branch;
    }
    unset($this->default_branch);
  }


  protected function backendDelete($options) {
    db_delete('versioncontrol_git_repositories')
      ->condition('repo_id', $this->repo_id)
      ->execute();

    // remove all extended event data. parent method removes the base event data
    $elids = db_select('versioncontrol_event_log', 'vel')
      ->fields('vel', array('elid'))
      ->condition('vel.repo_id', $this->repo_id)
      ->execute()->fetchAll(PDO::FETCH_COLUMN);

    if (!empty($elids)) {
    db_delete('versioncontrol_git_event_data')
      ->condition('elid', $elids)
      ->execute();
    }
  }

  protected function backendUpdate($options) {
    db_update('versioncontrol_git_repositories')
      ->condition('repo_id', $this->repo_id)
      ->fields(array('default_branch' => $this->defaultBranch))
      ->execute();
  }

  protected function backendInsert($options) {
    db_insert('versioncontrol_git_repositories')
      ->fields(array(
        'repo_id' => $this->repo_id,
        'default_branch' => $this->defaultBranch,
      ))
      ->execute();
  }

  /**
   * Returns the corresponding event object.
   *
   * @return VersioncontrolGitEvent
   *
   * @see VersioncontrolRepository::generateCodeArrivalEvent()
   */
  public function generateCodeArrivalEvent($data) {
    // First, let's see if this is an event re-queued for parsing.
    if (!empty($data['elid'])) {
      return $this->loadEvent($data['elid']);
    }
    // Unpack all the post-receive data.
    $all_refdata = explode("\n", $data['data']);
    $refs = array();
    foreach ($all_refdata as $refdata) {
      if (empty($refdata)) {
        continue; // last element is often empty, skip it
      }
      list($start, $end, $refpath) = explode(' ', $refdata);
      // @todo Accommodate to other ref namespaces, such as notes.
      list(, $type, $ref) = explode('/', $refpath);
      // Only store the information we got directly from the hook. E.g. do not
      // extract more information using exec's, that should be done by the
      // reposync plugin.
      $refs[] = array(
        'reftype' => $type == 'tags' ? VERSIONCONTROL_GIT_REFTYPE_TAG : VERSIONCONTROL_GIT_REFTYPE_BRANCH,
        'refname' => $ref,
        'old_sha1' => $start,
        'new_sha1' => $end,
        // Provide defaults to not-directly passed information.
        'label_id' => 0,
        'ff' => 0,
      );
    }

    // Slap together an object that VersioncontrolGitEvent::build() will like.
    $obj = new stdClass();
    $obj->uid = empty($data['uid']) ? 0 : $data['uid'];
    $obj->timestamp = empty($data['timestamp']) ? time() : $data['timestamp'];
    $obj->repository = $data['repository'];
    $obj->refs = $refs;

    return $this->getBackend()->buildEntity('event', $obj);
  }

  public function generateRawData($event) {
    $output = '';
    foreach ($event->refs as $ref) {
      // @todo Accommodate to other ref namespaces, such as notes.
      if ($ref->reftype == VERSIONCONTROL_GIT_REFTYPE_TAG) {
        $ref_namespace = 'tags';
      }
      else {
        $ref_namespace = 'heads';
      }
      $output .= "{$ref->old_sha1} {$ref->new_sha1} refs/$ref_namespace/{$ref->refname}\n";
    }
    return $output;
  }

  public function finalizeEvent(VersioncontrolEvent $event) {
    // Check event, so we process only git events.
    if (!$event instanceof VersioncontrolGitEvent) {
      $msg = t('An incompatible VersioncontrolEvent object (of class @class) was provided to a Git repository synchronizer for event-driven repository synchronization.', array('@class' => get_class($event)));
      throw new InvalidArgumentException($msg, E_ERROR);
    }

    foreach ($event as $ref) {
      // 0. Figure out fast-forward status.
      if (GIT_NULL_REV === $ref->old_sha1 || GIT_NULL_REV === $ref->new_sha1) {
        // Adding or removing refs is considered a ff.
        $ref->ff = 1;
      }
      else {
        $merge_base_logs = $this->exec("merge-base {$ref->old_sha1} {$ref->new_sha1}");
        if (count($merge_base_logs) == 2) {
          $ref->ff = (int)(next($merge_base_logs) == $ref->old_sha1);
        }
        else {
          $ref->ff = 0;
        }
      }

      if (!$ref->eventCreatedMe()) {
        // See if we can attach a label from the db to this refchange.
        $ref->syncLabel();
      }
    }
  }

  /**
   * Get the default (HEAD) branch of the repository.
   *
   * @todo Remove this in the next major version. default branch is now a
   * public data member.
   *
   * @return mixed
   *   The name of the default branch or NULL if there is none.
   */
  public function getDefaultBranch() {
    return $this->defaultBranch;
  }

  /**
   * Changes the default branch. Note that this is an async operation.
   *
   * @param $branch_name
   *   The name of the branch that should be checked out by default, when the
   *   repository is closed.
   *
   * @throws Exception
   *   If the branch doesn't exist.
   */
  public function setDefaultBranch($branch_name) {
    // Ensure the branch exists.
    if (!$this->loadBranches(NULL, array('name' => $branch_name))) {
      throw new Exception(t('The branch %branch_name doesn\'t exist.', array('%branch_name' => $branch_name)));
    }

    // The job to be queued.
    $job = array(
      'operation' => array(
        'setDefaultBranch' => array($branch_name),
        'save' => array(),
      ),
      'repository' => $this,
    );

    // Queue the write operation on the database an the repository.
    $queue = DrupalQueue::get('versioncontrol_repomgr');
    if (!$queue->createItem($job)) {
      watchdog('versioncontrol_git', t('Failed to enqueue a default branch change for the Git repository at %root.', array('%root' => $this->root)));
      throw new Exception(t('An error occured while attempting to enqueue switching the default branch.'), 'error');
    }
  }

  /**
   * State flag indicating whether or not the GIT_DIR variable has been pushed
   * into the environment.
   *
   * Used to prevent multiple unnecessary calls to putenv(). Will be obsoleted
   * by the introduction of a cligit library.
   *
   * @var bool
   */
  public $envSet = FALSE;

  /**
   * Ensure environment variables are set for interaction with the repository on
   * disk.
   *
   * Hopefully temporary, until we can get a proper cligit library written.
   */
  public function setEnv() {
    if (!$this->envSet) {
      $root = escapeshellcmd($this->root);
      putenv("GIT_DIR=$root");
      $this->envSet = TRUE;
    }
  }

  public function purgeData($bypass = TRUE) {
    // disable controller caching, no need to cache all the stuff we're about to
    // delete
    $this->getBackend()->disableControllerCaching();
    if (empty($bypass)) {
      foreach ($this->loadBranches() as $branch) {
        $branch->delete();
      }
      foreach ($this->loadTags() as $tag) {
        $tag->delete();
      }
      foreach ($this->loadCommits() as $commit) {
        $commit->delete();
      }

      // Repo is purged, so set init appropriately.
      $this->init = 1;
      $this->update();
      $this->getBackend()->restoreControllerCachingDefaults();
    }
    else {
      $label_ids = db_select('versioncontrol_labels', 'vl')
        ->fields('vl', array('label_id'))
        ->condition('vl.repo_id', $this->repo_id)
        ->execute()->fetchAll(PDO::FETCH_COLUMN);

      if (!empty($label_ids)) {
        db_delete('versioncontrol_operation_labels')
          ->condition('label_id', $label_ids)
          ->execute();
      }

      $op_ids = db_select('versioncontrol_operations', 'vco')
        ->fields('vco', array('vc_op_id'))
        ->condition('vco.repo_id', $this->repo_id)
        ->execute()->fetchAll(PDO::FETCH_COLUMN);

      if (!empty($op_ids)) {
        db_delete('versioncontrol_git_operations')
          ->condition('vc_op_id', $op_ids)
          ->execute();
      }

      $ir_ids = db_select('versioncontrol_item_revisions', 'vir')
        ->fields('vir', array('item_revision_id'))
        ->condition('vir.repo_id', $this->repo_id)
        ->execute()->fetchAll(PDO::FETCH_COLUMN);

      if (!empty($ir_ids)) {
        db_delete('versioncontrol_git_item_revisions')
          ->condition('item_revision_id', $ir_ids)
          ->execute();
      }

      db_delete('versioncontrol_operations')
        ->condition('repo_id', $this->repo_id)
        ->execute();

      db_delete('versioncontrol_labels')
        ->condition('repo_id', $this->repo_id)
        ->execute();

      db_delete('versioncontrol_item_revisions')
        ->condition('repo_id', $this->repo_id)
        ->execute();

      // Repo is purged, so set init appropriately.
      $this->init = 1;
      $this->update();
      $this->getBackend()->restoreControllerCachingDefaults();

      module_invoke_all('versioncontrol_repository_bypass_purge', $this);
    }
  }

  /**
   * Invoke git to fetch a list of local branches in the repository, including
   * the SHA1 of the current branch tip and the branch name.
   */
  public function fetchBranches() {
    $branches = array();
    $data = array(
      'repo_id' => $this->repo_id,
      'label_id' => NULL,
    );

    $logs = $this->exec('show-ref --heads');
    while (($branchdata = next($logs)) !== FALSE) {
      list($data['tip'], $data['name']) = explode(' ', trim($branchdata));
      $data['name'] = substr($data['name'], 11);
      $branches[$data['name']] = new VersioncontrolBranch($this->backend);
      $branches[$data['name']]->build($data);
    }

    return $branches;
  }

  /**
   * Fetch a single branch ref from the repository and turn it into a
   * versioncontrol entity object.
   *
   * @param string $name
   *   The name of the branch ref to fetch.
   *
   * @return VersioncontrolGitBranch|FALSE
   *    The VersioncontrolGitBranch object representing the requested branch, or
   *    FALSE if no branch was found.
   */
  public function fetchBranch($name) {
    $data = array(
      'repo_id' => $this->repo_id,
      'label_id' => NULL,
    );

    $logs = $this->exec('show-ref heads/' . $name);
    while (($branchdata = next($logs)) !== FALSE) {
      list($data['tip'], $data['name']) = explode(' ', trim($branchdata));
      $data['name'] = substr($data['name'], 11);
      return $this->getBackend()->buildEntity('branch', $data);
    }
    return FALSE;
  }

  /**
   * Invoke git to fetch a list of local tags in the repository, including
   * the SHA1 of the commit to which the tag is attached.
   */
  public function fetchTags() {
    $tags = array();
    $data = array(
      'repo_id' => $this->repo_id,
      'label_id' => NULL,
    );

    $logs = $this->exec('show-ref --tags');
    while (($tagdata = next($logs)) !== FALSE) {
      list($data['tip'], $data['name']) = explode(' ', trim($tagdata));
      $data['name'] = substr($data['name'], 10);
      $tags[$data['name']] = new VersioncontrolTag();
      $tags[$data['name']]->build($data);
    }

    return $tags;
  }

  /**
  * Fetch a single tag ref from the repository and turn it into a
  * versioncontrol entity object.
  *
  * @param string $name
  *   The name of the tag ref to fetch.
  *
  * @return VersioncontrolGitTag|FALSE
  *    The VersioncontrolGitTag object representing the requested tag, or FALSE
  *    if no tag was found.
  */
  public function fetchTag($name) {
    $data = array(
        'repo_id' => $this->repo_id,
        'label_id' => NULL,
    );

    $logs = $this->exec('show-ref tags/' . $name);
    while (($tagdata = next($logs)) !== FALSE) {
      list($data['tip'], $data['name']) = explode(' ', trim($tagdata));
      $data['name'] = substr($data['name'], 10);
      return $this->getBackend()->buildEntity('tag', $data);
    }
    return FALSE;
  }

  public function fetchCommits($branch_name = NULL) {
    $logs = $this->exec('rev-list --reverse ' . (empty($branch_name) ? '--all' : $branch_name));
    $commits = array();
    while (($line = next($logs)) !== FALSE) {
      $commits[] = trim($line);
    }
    return $commits;
  }

  /**
   * Execute a Git command using the root context and the command to be
   * executed.
   *
   * @param string $command
   *   Command to execute.
   * @return mixed
   *  Logged output from the command; an array of either strings or file
   *  pointers.
   */
  public function exec($command) {
    if (!$this->envSet) {
      $this->setEnv();
    }
    $logs = array();
    if ($git_bin = _versioncontrol_git_get_binary_path()) {
      exec(escapeshellcmd("$git_bin $command"), $logs);
      // FIXME doing it this way is just wrong.
      array_unshift($logs, '');
      // Reset the array pointer, so that we can use next().
      reset($logs);
    }
    return $logs;
  }

  /**
   * Verify if the repository root points to a valid Git repository.
   *
   * @return boolean
   *   TRUE if the repository path is a bare Git Repository.
   */
  public function isValidGitRepo() {
    // do not use exec() method to get the shell return code
    if (!$this->envSet) {
      $this->setEnv();
    }
    $logs = array();
    $git_bin = _versioncontrol_git_get_binary_path();
    exec(escapeshellcmd("$git_bin ls-files"), $logs, $shell_return);
    if ($shell_return != 0) {
      return FALSE;
    }
    return TRUE;
  }

}
