<?php
/**
 * @file
 * ildeposito_canto.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_canto_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create canto content'.
  $permissions['create canto content'] = array(
    'name' => 'create canto content',
    'roles' => array(
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any canto content'.
  $permissions['delete any canto content'] = array(
    'name' => 'delete any canto content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own canto content'.
  $permissions['delete own canto content'] = array(
    'name' => 'delete own canto content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any canto content'.
  $permissions['edit any canto content'] = array(
    'name' => 'edit any canto content',
    'roles' => array(
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own canto content'.
  $permissions['edit own canto content'] = array(
    'name' => 'edit own canto content',
    'roles' => array(
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'enter canto revision log entry'.
  $permissions['enter canto revision log entry'] = array(
    'name' => 'enter canto revision log entry',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override canto authored by option'.
  $permissions['override canto authored by option'] = array(
    'name' => 'override canto authored by option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override canto authored on option'.
  $permissions['override canto authored on option'] = array(
    'name' => 'override canto authored on option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override canto promote to front page option'.
  $permissions['override canto promote to front page option'] = array(
    'name' => 'override canto promote to front page option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override canto published option'.
  $permissions['override canto published option'] = array(
    'name' => 'override canto published option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override canto revision option'.
  $permissions['override canto revision option'] = array(
    'name' => 'override canto revision option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override canto sticky option'.
  $permissions['override canto sticky option'] = array(
    'name' => 'override canto sticky option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  return $permissions;
}
