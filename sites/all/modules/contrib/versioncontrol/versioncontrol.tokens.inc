<?php
/**
 * @file
 *   Token integration.
 */

/**
 * Implements hook_token_info().
 */
function versioncontrol_token_info() {
  $info = array();

  // Backend.
  $info['types']['versioncontrol-backend'] = array(
    'name' => t('Version Control Backend'),
    'description' => t('Tokens related to backends.'),
    'needs-data' => 'versioncontrol-backend',
  );
  $info['tokens']['versioncontrol-backend'] = array(
    'name' => array(
      'name'=> t('Backend name'),
      'description' => t('The name of the backend'),
    ),
    'type' => array(
      'name'=> t('Backend machine name'),
      'description' => t('The type of the backend'),
    ),
    'description' => array(
      'name'=> t('Backend description'),
      'description' => t('The description of the backend'),
    ),
  );

  // Repository.
  $info['types']['versioncontrol-repository'] = array(
    'name' => t('Version Control Repository'),
    'description' => t('Tokens related to repositories.'),
    'needs-data' => 'versioncontrol-repository',
  );
  $info['tokens']['versioncontrol-repository'] = array(
    'id' => array(
      'name'=> t('Repository ID'),
      'description' => t('The unique identifier for the repository.'),
    ),
    'name' => array(
      'name'=> t('Repository name'),
      'description' => t('User visible name of the repository.'),
    ),
    'backend' => array(
      'name'=> t('Repository backend machine name'),
      'description' => t('The backend machine name this repository uses.'),
      'type' => 'versioncontrol-backend',
    ),
    'viewer' => array(
      'name'=> t('Repository viewer url.'),
      'description' => t('A link to the web viewer associated with this repository.'),
    ),
  );

  // Operation.
  $info['types']['versioncontrol-operation'] = array(
    'name' => t('Version Control Operation'),
    'description' => t('Tokens related to operations.'),
    'needs-data' => 'versioncontrol-operation',
  );
  $info['tokens']['versioncontrol-operation'] = array(
    'id' => array(
      'name' => t('Operation ID'),
      'description' => t('The unique identifier for the operation.'),
    ),
    'repository' => array(
      'name' => t('Operation repository ID'),
      'description' => t('The unique identifier for the repository this operation belongs to.'),
      'type' => 'versioncontrol-repository',
    ),
    'revision' => array(
      'name' => t('Operation revision'),
      'description' => t('Backend internal identifier for the operation.'),
    ),
    'author_date' => array(
      'name' => t('Authored date'),
      'description' => 'Date/time when the operation was created.',
      'type' => 'date',
    ),
    'committer_date' => array(
      'name' => t('Committed date'),
      'description' => 'Date/time when the operation was added to the repository.',
      'type' => 'date',
    ),
    'author' => array(
      'name' => t('Author'),
      'description' => 'VCS specific username of the user who is the original author of this operation.',
      'type' => 'user',
    ),
    'committer' => array(
      'name' => t('Committer'),
      'description' => 'VCS specific username of the user who is the original committer of this operation.',
      'type' => 'user',
    ),
    'message' => array(
      'name' => t('Commit message'),
      'description' => 'Log message from VCS for this operation.',
    ),
  );

  // Branch.
  $info['types']['versioncontrol-branch'] = array(
    'name' => t('Version Control Branch'),
    'description' => t('Tokens related to branches.'),
    'needs-data' => 'versioncontrol-branch',
  );
  $info['tokens']['versioncontrol-branch'] = array(
    'id' => array(
      'name' => t('Branch ID'),
      'description' => t('The unique identifier for the branch.'),
    ),
    'name' => array(
      'name' => t('Branch name'),
      'description' => t('The name of the branch.'),
    ),
    'repository' => array(
      'name' => t('Branch repository ID'),
      'description' => t('The unique identifier for the repository this branch belongs to.'),
      'type' => 'versioncontrol-repository',
    ),
  );

  // Tag.
  $info['types']['versioncontrol-tag'] = array(
    'name' => t('Version Control Tag'),
    'description' => t('Tokens related to tags.'),
    'needs-data' => 'versioncontrol-tag',
  );
  $info['tokens']['versioncontrol-tag'] = array(
    'id' => array(
      'name' => t('Tag ID'),
      'description' => t('The unique identifier for the tag.'),
    ),
    'name' => array(
      'name' => t('Tag name'),
      'description' => t('The name of the tag.'),
    ),
    'repository' => array(
      'name' => t('Tag repository ID'),
      'description' => t('The unique identifier for the repository this tag belongs to.'),
      'type' => 'versioncontrol-repository',
    ),
  );

  // Item revision.
  $info['types']['versioncontrol-item'] = array(
    'name' => t('Version Control Item'),
    'description' => t('Tokens related to item revisions.'),
    'needs-data' => 'versioncontrol-item',
  );
  $info['tokens']['versioncontrol-item'] = array(
    'id' => array(
      'name' => t('Item revision ID'),
      'description' => t('The unique identifier for the item revision.'),
    ),
    'operation' => array(
      'name' => t('Item revision operation ID'),
      'description' => t('The unique identifier for the operation this item revision belongs to.'),
      'type' => 'versioncontrol-operation',
    ),
    'repository' => array(
      'name' => t('Item revision repository ID'),
      'description' => t('The unique identifier for the repository this item revision belongs to.'),
      'type' => 'versioncontrol-repository',
    ),
    'path' => array(
      'name' => t('Item revision path'),
      'description' => t('Path of the item revision, relative to the repository root.'),
    ),
    'revision' => array(
      'name' => t('Item revision revision'),
      'description' => t('File-level revision of the item.'),
    ),
    // @todo type
    'source_item' => array(
      'name' => t('Item revision type'),
      'description' => t('File-level revision of the item.'),
      'type' => 'versioncontrol-item',
    ),
    'action' => array(
      'name' => t('Item revision action'),
      'description' => t('Action that was performed while transforming the source item into the successor item.'),
    ),
    'line_changes_added' => array(
      'name' => t('Item revision added lines count'),
      'description' => t('Number of lines added with this item.'),
    ),
    'line_changes_removed' => array(
      'name' => t('Item revision removed lines count'),
      'description' => t('Number of lines removed with this item.'),
    ),
  );

  // Event.
  $info['types']['versioncontrol-event'] = array(
    'name' => t('Version Control Event'),
    'description' => t('Tokens related to events.'),
    'needs-data' => 'versioncontrol-event',
  );
  $info['tokens']['versioncontrol-event'] = array(
    'id' => array(
      'name' => t('Event ID'),
      'description' => t('The unique identifier for the event.'),
    ),
    'repository' => array(
      'name' => t('Event repository ID'),
      'description' => t('The unique identifier for the repository this event belongs to.'),
      'type' => 'versioncontrol-repository',
    ),
    'actor' => array(
      'name' => t('Event actor user ID'),
      'description' => t('The unique identifier for the user who performed this event.'),
      'type' => 'user',
    ),
    'date' => array(
      'name' => t('Event date'),
      'description' => 'Date/time when the event happened.',
      'type' => 'date',
    ),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function versioncontrol_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);
  $language_code = isset($options['language']) ? $options['language']->language : NULL;

  if (empty($data[$type])) {
    return $replacements;
  }
  $object = $data[$type];

  foreach ($tokens as $name => $original) {
    switch ($type) {
      case 'versioncontrol-backend':
        switch ($name) {
          case 'name':
          case 'type':
          case 'description':
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
        }
        break;
      case 'versioncontrol-repository':
        switch ($name) {
          case 'viewer':
            $replacements[$original] = l($object->name, $object->getUrlHandler()->getRepositoryViewUrl());
            break;
          case 'backend':
            $name = 'vcs';
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
            break;
          case 'id':
            $name = 'repo_id';
          case 'name':
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
        }
        if ($backend_tokens = token_find_with_prefix($tokens, 'backend')) {
          $backend = $object->getBackend();
          $replacements += token_generate('versioncontrol-backend', $backend_tokens, array('versioncontrol-backend' => $backend), $options);
        }
        break;
      case 'versioncontrol-operation':
        switch ($name) {
          case 'type':
            $operation_types = versioncontrol_operation_types();
            $replacements[$original] = $operation_types[$object->type];
            break;
          case 'author_date':
          case 'committer_date':
            $replacements[$original] = format_date($object->$name, 'medium', '', NULL, $language_code);
            break;
          case 'repository':
            $name = 'repo_id';
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
            break;
          case 'id':
            $name = 'vc_op_id';
          case 'revision':
          case 'author':
          case 'committer':
          case 'message':
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
        }
        if ($author_date_tokens = token_find_with_prefix($tokens, 'author_date')) {
          $replacements += token_generate('date', $author_date_tokens, array('date' => $object->author_date), $options);
        }
        if ($committer_date_tokens = token_find_with_prefix($tokens, 'committer_date')) {
          $replacements += token_generate('date', $committer_date_tokens, array('date' => $object->committer_date), $options);
        }
        if ($author_tokens = token_find_with_prefix($tokens, 'author')) {
          $author = user_load($object->author_uid);
          $replacements += token_generate('user', $author_tokens, array('user' => $author), $options);
        }
        if ($committer_tokens = token_find_with_prefix($tokens, 'committer')) {
          $committer = user_load($object->committer_uid);
          $replacements += token_generate('user', $author_tokens, array('user' => $committer), $options);
        }
        if ($repository_tokens = token_find_with_prefix($tokens, 'repository')) {
          //$repository = $object->getRepository();
          $repository = versioncontrol_repository_load($object->repo_id);
          $replacements += token_generate('versioncontrol-repository', $repository_tokens, array('versioncontrol-repository' => $repository), $options);
        }
        break;
      case 'versioncontrol-branch':
      case 'versioncontrol-tag':
        switch ($name) {
          case 'repository':
            $name = 'repo_id';
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
            break;
          case 'id':
            $name = 'label_id';
          case 'name':
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
        }
        if ($repository_tokens = token_find_with_prefix($tokens, 'repository')) {
          $repository = $object->getRepository();
          $replacements += token_generate('versioncontrol-repository', $repository_tokens, array('versioncontrol-repository' => $repository), $options);
        }
        break;
      case 'versioncontrol-item':
        switch ($name) {
          case 'repository':
            $name = 'repo_id';
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
            break;
          case 'operation':
            $name = 'vc_op_id';
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
            break;
          case 'action':
            $item_revision_actions = versioncontrol_revision_actions();
            $replacements[$original] = $item_revision_actions[$object->action];
            break;
          case 'source_item':
            $name = 'source_item_revision_id';
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
            break;
          //@todo add a successor_item if possible
          case 'id':
            $name = 'item_revision_id';
          case 'path':
          case 'revision':
          case 'line_changes_added':
          case 'line_changes_removed':
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
        }
        if ($repository_tokens = token_find_with_prefix($tokens, 'repository')) {
          $repository = $object->getRepository();
          $replacements += token_generate('versioncontrol-repository', $repository_tokens, array('versioncontrol-repository' => $repository), $options);
        }
        if ($operation_tokens = token_find_with_prefix($tokens, 'operation')) {
          $operation = $object->getBackend()->loadEntity('operation', array($object->vc_op_id));
          $replacements += token_generate('versioncontrol-operation', $operation_tokens, array('versioncontrol-operation' => $operation), $options);
        }
        if ($source_item_tokens = token_find_with_prefix($tokens, 'source_item')) {
          $source_item = $object->getSourceItem();
          $replacements += token_generate('versioncontrol-item', $source_item_tokens, array('versioncontrol-item' => $source_item), $options);
        }
        break;
      case 'versioncontrol-event':
        switch ($name) {
          case 'repository':
            $name = 'repo_id';
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
            break;
          case 'date':
            $replacements[$original] = format_date($object->timestamp, 'medium', '', NULL, $language_code);
            break;
          case 'id':
            $name = 'elid';
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
            break;
          case 'actor':
            $name = 'uid';
            $replacements[$original] = $sanitize ? check_plain($object->$name) : $object->$name;
            break;
        }
        if ($repository_tokens = token_find_with_prefix($tokens, 'repository')) {
          $repository = $object->getRepository();
          $replacements += token_generate('versioncontrol-repository', $repository_tokens, array('versioncontrol-repository' => $repository), $options);
        }
        if ($date_tokens = token_find_with_prefix($tokens, 'date')) {
          $replacements += token_generate('date', $date_tokens, array('date' => $object->timestamp), $options);
        }
        if ($actor_tokens = token_find_with_prefix($tokens, 'actor')) {
          $actor = user_load($object->uid);
          $replacements += token_generate('user', $actor_tokens, array('user' => $actor), $options);
        }
        break;
    }
  }

  return $replacements;
}
