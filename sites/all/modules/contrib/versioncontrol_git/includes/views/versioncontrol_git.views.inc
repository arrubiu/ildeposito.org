<?php

/**
 * Implements hook_views_data()
 */
function versioncontrol_git_views_data() {
  $data['versioncontrol_git_operations']['table']['group'] = t("Versioncontrol Git Operations");
  $data['versioncontrol_git_operations']['table']['join'] = array(
    'versioncontrol_operations' => array(
      'left_field' => 'vc_op_id',
      'field' => 'vc_op_id',
      'type' => 'LEFT',
    ),
  );

  $data['versioncontrol_git_operations']['author_name'] = array(
    'title'    => t('Git Author name'),
    'help'     => t("The operation author's full name, as recorded by git."),
    'field'    => array(
      'handler' => 'versioncontrol_handler_field_operation_person',
      'click sortable' => TRUE,
      'additional fields' => array(
        'person_uid' => array('table' => 'versioncontrol_operations', 'field' => 'author_uid'),
      ),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['versioncontrol_git_operations']['author'] = array(
    'real field' => 'author_name',
    'title'    => t('Author (git)'),
    'help'     => t("The Operation Author, it uses operation author's full name as recorded by git if author is not mapped with a user."),
    'field'    => array(
      'handler' => 'versioncontrol_handler_field_operation_person',
      'click sortable' => TRUE,
      'additional fields' => array(
        'person_uid' => array('table' => 'versioncontrol_operations', 'field' => 'author_uid'),
        'person_username' => array('table' => 'users', 'field' => 'name'),
      ),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['versioncontrol_git_operations']['committer_name'] = array(
    'title'    => t('Git committer name'),
    'help'     => t("The operation committer's full name, as recorded by git."),
    'field'    => array(
      'handler' => 'versioncontrol_handler_field_operation_person',
      'click sortable' => TRUE,
      'additional fields' => array(
        'person_uid' => array('table' => 'versioncontrol_operations', 'field' => 'committer_uid'),
      ),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['versioncontrol_git_operations']['committer'] = array(
    'real field' => 'committer_name',
    'title'    => t('Commiter (git)'),
    'help'     => t("The Operation Committer, it uses operation committer's full name as recorded by git if author is not mapped with a user."),
    'field'    => array(
      'handler' => 'versioncontrol_handler_field_operation_person',
      'click sortable' => TRUE,
      'additional fields' => array(
        'person_uid' => array('table' => 'versioncontrol_operations', 'field' => 'committer_uid'),
        'person_username' => array('table' => 'users', 'field' => 'name'),
      ),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['versioncontrol_git_operations']['attribution'] = array(
    'real field' => 'author_name',
    'title'    => t('Attribution (git)'),
    'help'     => t('The operation author (and committer, if different)'),
    'field'    => array(
      'handler' => 'versioncontrol_handler_field_operation_attribution',
      'additional fields' => array(
        'author_uid' => array('table' => 'versioncontrol_operations', 'field' => 'author_uid'),
        'committer_uid' => array('table' => 'versioncontrol_operations', 'field' => 'committer_uid'),
        'committer' => array('table' => 'versioncontrol_git_operations', 'field' => 'committer_name'),
      ),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['versioncontrol_git_operations']['parent_commit'] = array(
    'title'    => t('Parent Commit SHA1'),
    'help'     => t('The SHA1 hash of the parent commit.'),
    'field'    => array(
      'handler' => 'versioncontrol_handler_field_operation_revision',
      'click sortable' => TRUE,
      'additional fields' => array(
        'vcs' => array('table' => 'versioncontrol_repositories', 'field' => 'vcs'),
      ),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  return $data;
}
