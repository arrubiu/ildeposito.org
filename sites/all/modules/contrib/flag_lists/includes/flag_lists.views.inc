<?php

/**
 * @file
 * Provides support for the Views module.
 */

/**
 * Implementation of hook_views_handlers().
 */
function flag_lists_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'flag_lists') . '/includes',
    ),
    'handlers' => array(
      'flag_lists_handler_field_list' => array(
        'parent' => 'views_handler_field',
        'file' => 'flag_lists_handler_field_list.inc',
      ),
      'flag_lists_handler_field_template' => array(
        'parent' => 'views_handler_field',
        'file' => 'flag_lists_handler_field_template.inc',
      ),
      'flag_lists_handler_field_list_edit' => array(
        'parent' => 'views_handler_field',
        'file' => 'flag_lists_handler_field_list_edit.inc',
      ),
      'flag_lists_handler_field_list_delete' => array(
        'parent' => 'views_handler_field',
        'file' => 'flag_lists_handler_field_list_delete.inc',
      ),
      'flag_lists_handler_field_template_types' => array(
        'parent' => 'views_handler_field_prerender_list',
        'file' => 'flag_lists_handler_field_template_types.inc',
      ),
      'flag_lists_handler_filter_template' => array(
        'parent' => 'views_handler_filter_in_operator',
        'file' => 'flag_lists_handler_filter_template.inc',
      ),
      'flag_lists_handler_argument_fid' => array(
        'parent' => 'views_handler_argument_numeric',
        'file' => 'flag_lists_handler_argument_fid.inc',
    ),
    ),
  );
}


/**
 * Implementation of hook_views_data_alter().
 */
function flag_lists_views_data_alter(&$data) {

  // We want access to users table fields.
  $data['users']['table']['join']['flag_lists_flags'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
  );

  // We need fid and name form flags' data, and join.
  $data['flags'] = array(
    'table' => array(
      'group' => t('Flag'),
      'join' => array(
        'flag_lists_flags' => array(
          'left_field' => 'pfid',
          'field' => 'fid',
        ),
      ),
    ),
    'fid' => array(
      'title' => t('Flag fid'),
      'help' => t('Flag id'),
      'field' => array(
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'name' => array(
      'title' => t('Template name'),
      'help' => t('The name of the list template flag'),
      'field' => array(
        'handler' => 'flag_lists_handler_field_template',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'flag_lists_handler_filter_template',
        'allow empty' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );

  // Add the checkbox for flagging nodes VBO style, minus batch API
  foreach (entity_get_info() as $entity_type => $info) {
    if (isset($info['base table']) && $info['base table'] == 'node' && isset($data[$info['base table']])) {
      $data[$info['base table']]['flag_lists_ops'] = array(
        'title' => t('Flag lists operations'),
        'help' => t('Provide a checkbox to select the row for flag lists operations.'),
        'real field' => $info['entity keys']['id'],
        'field' => array(
          'handler' => 'flag_lists_handler_field_ops',
          'click sortable' => FALSE,
        ),
      );
      break;
    }
  }
}

/**
 * Implementation of hook_views_data().
 */
function flag_lists_views_data() {
  $data = array();

  // flag_lists_flags data
  $data['flag_lists_flags'] = array(
    'table' => array(
      'base' => array(
        'field' => 'fid',
        'title' => t('Flag lists'),
        'help' => 'User created flag lists',
        'weight' => 10,
        'database' => 'default',
      ),
      'group' => t('Flag lists'),
      'join' => array(
        'node' => array(
          'table' => 'flag_lists_flags',
          'left_table' => 'flag_lists_content',
          'left_field' => 'fid',
          'field' => 'fid',
        ),
      ),
    ),
    'fid' => array(
      'title' => t('fid'),
      'help' => t('Flag list id, required for Flag lists operationis\'s "unflag" action.'),
      'field' => array(
        'handler' => 'flag_lists_handler_field_list',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'flag_lists_handler_argument_fid',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'pfid' => array(
      'title' => t('pfid'),
      'help' => t('Template flag id'),
      'field' => array(
        'handler' => 'flag_lists_handler_field_pfid',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),

    'uid' => array(
      'title' => t('Uid'),
      'help' => t('The list owner\'s uid'), // The help that appears on the UI,
      'field' => array(
        'handler' => 'views_handler_field_user',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_user_uid',
        'name field' => 'name', // display this field in the summary
      ),
      'filter' => array(
        'title' => t('Name'),
        'handler' => 'views_handler_filter_user_name',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'name' => array(
      'title' => t('machine name'),
      'help' => t('Machine name of the list'),
      'field' => array(
        'handler' => 'flag_lists_handler_field_list',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'title' => array(
      'title' => t('List title'),
      'help' => t('Title of the list'),
      'field' => array(
        'click sortable' => TRUE,
        'handler' => 'flag_lists_handler_field_list',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'edit_list' => array(
      'field' => array(
        'title' => t('Edit link'),
        'help' => t('Link to edit the list title'),
        'handler' => 'flag_lists_handler_field_list_edit',
      ),
    ),
    'delete_list' => array(
      'field' => array(
        'title' => t('Delete link'),
        'help' => t('Link to delete the list'),
        'handler' => 'flag_lists_handler_field_list_delete',
      ),
    ),
  );

  // Flag_lists_content data

  $data['flag_lists_content'] = array(
    'table' => array(
      'join' => array(
        'node' => array(
          'left_field' => 'nid',
          'field' => 'content_id',
        ),
      ),
      'group' => t('Flag lists'),
    ),
    'uid' => array(
      'relationship' => array(
        'title' => t('User'),
        'help' => t('The user who listed this node'),
        'base' => 'users',
        'handler' => 'views_handler_relationship',
        'label' => t('List user'),
      ),
    ),
    'content_id' => array(
      'relationship' => array(
        'title' => t('Node'),
        'help' => t('The node that has been listed'),
        'base' => 'node',
        'handler' => 'views_handler_relationship',
        'label' => t('Listed content'),
      ),
    ),
    'timestamp' => array(
      'title' => t('Time listed'),
      'help' => t('The time this node was listed'),
      'field' => array(
      'handler' => 'views_handler_field_date',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
  );

  // Flag_lists_types data

  $data['flag_lists_types'] = array(
    'table' => array(
      'group' => t('Flag lists'),
      'join' => array(
        'flag_lists_flags' => array(
          'table' => 'flag_lists_types',
          'type' => 'INNER',
          'left_table' => 'flags',
          'left_field' => 'name',
          'field' => 'name',
        ),
      ),
    ),
    'type' => array(
      'title' => t('Template types'),
      'help' => t('Node types that can be listed by lists using this template'),
      'field' => array(
        'click sortable' => FALSE,
        'handler' => 'flag_lists_handler_field_template_types',
      ),
    ),
  );
  return $data;
}
