<?php
/**
 * @file
 * ildeposito_ct_fonte.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_ct_fonte_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create fonte_bibliografica content'.
  $permissions['create fonte_bibliografica content'] = array(
    'name' => 'create fonte_bibliografica content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any fonte_bibliografica content'.
  $permissions['delete any fonte_bibliografica content'] = array(
    'name' => 'delete any fonte_bibliografica content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own fonte_bibliografica content'.
  $permissions['delete own fonte_bibliografica content'] = array(
    'name' => 'delete own fonte_bibliografica content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any fonte_bibliografica content'.
  $permissions['edit any fonte_bibliografica content'] = array(
    'name' => 'edit any fonte_bibliografica content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own fonte_bibliografica content'.
  $permissions['edit own fonte_bibliografica content'] = array(
    'name' => 'edit own fonte_bibliografica content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'enter fonte_bibliografica revision log entry'.
  $permissions['enter fonte_bibliografica revision log entry'] = array(
    'name' => 'enter fonte_bibliografica revision log entry',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override fonte_bibliografica authored by option'.
  $permissions['override fonte_bibliografica authored by option'] = array(
    'name' => 'override fonte_bibliografica authored by option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override fonte_bibliografica authored on option'.
  $permissions['override fonte_bibliografica authored on option'] = array(
    'name' => 'override fonte_bibliografica authored on option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override fonte_bibliografica promote to front page option'.
  $permissions['override fonte_bibliografica promote to front page option'] = array(
    'name' => 'override fonte_bibliografica promote to front page option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override fonte_bibliografica published option'.
  $permissions['override fonte_bibliografica published option'] = array(
    'name' => 'override fonte_bibliografica published option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override fonte_bibliografica revision option'.
  $permissions['override fonte_bibliografica revision option'] = array(
    'name' => 'override fonte_bibliografica revision option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override fonte_bibliografica sticky option'.
  $permissions['override fonte_bibliografica sticky option'] = array(
    'name' => 'override fonte_bibliografica sticky option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  return $permissions;
}
