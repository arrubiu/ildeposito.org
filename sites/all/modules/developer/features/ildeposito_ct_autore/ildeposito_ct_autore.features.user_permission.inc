<?php
/**
 * @file
 * ildeposito_ct_autore.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_ct_autore_user_default_permissions() {
  $permissions = array();

  // Exported permission: create autore content.
  $permissions['create autore content'] = array(
    'name' => 'create autore content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any autore content.
  $permissions['delete any autore content'] = array(
    'name' => 'delete any autore content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own autore content.
  $permissions['delete own autore content'] = array(
    'name' => 'delete own autore content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any autore content.
  $permissions['edit any autore content'] = array(
    'name' => 'edit any autore content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own autore content.
  $permissions['edit own autore content'] = array(
    'name' => 'edit own autore content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: enter autore revision log entry.
  $permissions['enter autore revision log entry'] = array(
    'name' => 'enter autore revision log entry',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override autore authored by option.
  $permissions['override autore authored by option'] = array(
    'name' => 'override autore authored by option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override autore authored on option.
  $permissions['override autore authored on option'] = array(
    'name' => 'override autore authored on option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override autore promote to front page option.
  $permissions['override autore promote to front page option'] = array(
    'name' => 'override autore promote to front page option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override autore published option.
  $permissions['override autore published option'] = array(
    'name' => 'override autore published option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override autore revision option.
  $permissions['override autore revision option'] = array(
    'name' => 'override autore revision option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override autore sticky option.
  $permissions['override autore sticky option'] = array(
    'name' => 'override autore sticky option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  return $permissions;
}
