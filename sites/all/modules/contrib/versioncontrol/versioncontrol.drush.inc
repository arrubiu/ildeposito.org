<?php

/**
 * @file
 *
 * Drush integration for VCAPI.
 */

function versioncontrol_drush_command() {
  $items = array();

  $items['vcapi-sync-repositories'] = array(
    'description' => "Parse the logs from a repository known to Version Control API, fully updating the database with any changes made.",
    'arguments' => array(
      'repositories' => 'A comma-delimited list of repository ids or shortnames. Mixing and matching names and ids is fine.',
    ),
    'examples' => array(
      'drush vc-sync 1,2,repository_name,17' => 'Sequentially fetch repository logs for the the four indicated repositories.',
      'drush vc-sync' => 'Sequentially fetch repository logs for all repositories tracked by the system.',
    ),
    'options' => array(
      'flush' => 'Flush all data prior to performing history synchronization. Useful if something has gone awry in the db data and normal resyncs are failing to correct it.',
      'nobatch' => 'By default, this command operates using batchapi to help with memory management; Passing this option will cause it to execute normally.'
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('vc-sync'),
  );
  $items['vcapi-map-operations'] = array(
    'description' => "Attempt to map author & committer data in tracked commits/operations to Drupal users. By default, only unmapped operations will be attempted.",
    'arguments' => array(
      'repositories' => 'A comma-delimited list of repository ids or shortnames. Mixing and matching names and ids is fine.',
    ),
    'options' => array(
      'discover' => 'Instead of using the repositories explicitly provided as arguments, derive a list of repositories to update by checking to see which ones have unmapped commits.',
      'all' => 'Attempt mapping on all operations, whether or not they have already been mapped. Respects --authors and --committers options.',
      'authors' => 'Only attempt to map authors.',
      'committers' => 'Only attempt to map committers.',
      'nobatch' => 'By default, this command operates using batchapi to help with memory management; Passing this option will cause it to execute normally.'
    ),
  );
  $items['vcapi-enqueue-codearrival'] = array(
    'description' => "Enqueue data from an incoming code arrival event to be processed later by reposync logic. The main data payload is read from stdin.",
    'options' => array(
      'uid' => 'The drupal uid of the user who initiated the code event (pushed/committed).',
      'repo-id' => 'The repository id of the repo that received the event.',
      'timestamp' => 'The UNIX epoch timestamp to assign to the event.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('vc-nq'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function versioncontrol_drush_help($section) {
  switch ($section) {
    case 'drush:vcapi-sync-repositories':
      return dt("This command will fetch all new activity in the repositories listed on the command line. If no repositories are given, log fetching will be triggered on all repositories.");
    case 'drush:vcapi-map-operations':
      return dt("This command will attempt to map raw operation author/committer data to known Drupal accounts.");
    case 'drush:vcapi-enqueue-codearrival':
      return dt("This command will enqueue a code arrival event payload for processing in the default queue.");
  }
}

/**
 * Parse a comma-delimited list of repository arguments and return the
 * corresponding list of repositories.
 *
 * Helper function, since this is a common argument for VCAPI's drush commands.
 *
 * @param string $repository_args
 */
function _drush_versioncontrol_parse_repo_arg_list($repository_args = '') {
  $repo_ids = _convert_csv_to_array($repository_args);

  $repositories = array();
  if (!empty($repo_ids)) {
    $ids = $names = array();
    foreach ($repo_ids as $repository_argument) {
      if (is_numeric($repository_argument)) {
        $ids[] = $repository_argument;
      }
      else {
        $names[] = $repository_argument;
      }
    }

    if (!empty($ids)) {
      $repositories = versioncontrol_repository_load_multiple($ids);
    }
    if (!empty($names)) {
      $repositories = array_merge(versioncontrol_repository_load_multiple(array(), array('name' => $names)), $repositories);
    }
  }
  else {
    $repositories = versioncontrol_repository_load_multiple(FALSE);
  }

  return $repositories;
}

function drush_versioncontrol_vcapi_sync_repositories() {
  $repositories = _drush_versioncontrol_parse_repo_arg_list(func_get_args());

  $flush = drush_get_option('flush', FALSE);
  // Make batching optional, it seems to be screwing with output.
  if (drush_get_option('nobatch', FALSE)) {
    foreach ($repositories as $repository) {
      _drush_versioncontrol_vcapi_sync_repositories($repository->repo_id, $flush);
    }
    return;
  }

  // With the repository list assembled, queue batches to run.
  $operations = array();
  foreach ($repositories as $repository) {
    $operations[] = array('_drush_versioncontrol_vcapi_sync_repositories', array($repository->repo_id), $flush);
  }

  $batch = array(
    'operations' => $operations,
    'title' => 'Synchronizing',
    'init_message' => 'Fetching logs from repositories...',
    'error_message' => 'An error occurred while fetching logs from repositories.',
    // 'finished' => 'drush_versioncontrol_vcapi_parse_logs_finished',
  );

  batch_set($batch);
  $batch =& batch_get();
  $batch['progressive'] = FALSE;
  drush_backend_batch_process();
}

function drush_versioncontrol_vcapi_map_operations() {
  $repositories = array();
  if ($discover = drush_get_option('discover', FALSE)) {
    $ids = db_select('versioncontrol_operations', 'vco')
      ->fields('vco', array('repo_id'))
      ->distinct()
      ->where('vco.author_uid = 0 OR vco.committer_uid = 0')
      ->execute()
      ->fetchCol();

    $repositories = versioncontrol_repository_load_multiple($ids);
  }
  else {
    $repositories = _drush_versioncontrol_parse_repo_arg_list(func_get_args());
  }

  $full_remap = drush_get_option('all', FALSE);
  $only_authors = drush_get_option('authors', FALSE);
  $only_committers = drush_get_option('committers', FALSE);

  foreach ($repositories as $repository) {
    $conditions = array();
    if (!$full_remap) {
      if ($only_authors) {
        $conditions['author_uid'] = 0;
      }
      elseif ($only_committers) {
        $conditions['committer_uid'] = 0;
      }
    }

    // FIXME with the current architecture, this skips tag objects
    $commits = $repository->loadCommits(array(), $conditions);
    foreach ($commits as $commit) {
      $succeeded = FALSE;
      // TODO this logic is really horribly inelegant and if-y, improve it
      if ($full_remap) {
        if ($only_committers || $only_authors) {
          if ($only_authors) {
            $succeeded = $commit->mapAuthor();
          }
          else {
            $succeeded = $commit->mapCommitter();
          }
        }
        else {
          $succeeded = $commit->mapUsers();
        }
      }
      else {
        if ($commit->author_uid == 0 && !$only_committers) {
          $succeeded = $commit->mapAuthor();
        }
        if ($commit->committer_uid == 0 && !$only_authors) {
          $succeeded = $commit->mapCommitter() ? TRUE : $succeeded;
        }
      }

      if ($succeeded) {
        // Save the updated commit.
        $commit->save();
      }
    }
  }
}

function _drush_versioncontrol_vcapi_sync_repositories($repo_id, $flush) {
  $repository = versioncontrol_repository_load($repo_id);
  try {
    drush_log(dt('Beginning synchronization of repository !name', array('!name' => $repository->name)), 'ok');
    $sync_status = $flush ? $repository->reSyncFromScratch() : $repository->sync();
    if ($sync_status) {
      drush_log(dt('Successfully synchronized repository !name', array('!name' => $repository->name)), 'success');
    }
    else {
      drush_log(dt('There was an error during the synchronization, review the sync log table for details.'), 'error');
    }
  }
  catch (Exception $e) {
    // @todo is there a way to end up here? reSyncFromScratch() and sync() should handle the exceptions IIRC.
    drush_set_error('Exception while synchronizing', dt('An error occurred while performing history synchronziation on repository !name. Error info: ' . $e->__toString()), array('!name' => $repository->name));
    // There'll be a stale lock on the repository now, so clear it.
    $repository->updateLock(0);
    $repository->update();
  }
}
function drush_versioncontrol_vcapi_enqueue_codearrival() {
  $payload = array(
    'uid' => drush_get_option('uid', 1),
    'repo_id' => drush_get_option('repo-id', 1),
    'data' => stream_get_contents(STDIN),
    'timestamp' => drush_get_option('timestamp', time()),
  );
  $queue = DrupalQueue::get('versioncontrol_reposync', TRUE);
  $queue->createItem($payload);
}

