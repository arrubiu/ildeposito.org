<?php
/**
 * @file
 * ildeposito_ct_articolo.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_ct_articolo_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create articolo content'.
  $permissions['create articolo content'] = array(
    'name' => 'create articolo content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any articolo content'.
  $permissions['delete any articolo content'] = array(
    'name' => 'delete any articolo content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own articolo content'.
  $permissions['delete own articolo content'] = array(
    'name' => 'delete own articolo content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any articolo content'.
  $permissions['edit any articolo content'] = array(
    'name' => 'edit any articolo content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own articolo content'.
  $permissions['edit own articolo content'] = array(
    'name' => 'edit own articolo content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'enter articolo revision log entry'.
  $permissions['enter articolo revision log entry'] = array(
    'name' => 'enter articolo revision log entry',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override articolo authored by option'.
  $permissions['override articolo authored by option'] = array(
    'name' => 'override articolo authored by option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override articolo authored on option'.
  $permissions['override articolo authored on option'] = array(
    'name' => 'override articolo authored on option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override articolo promote to front page option'.
  $permissions['override articolo promote to front page option'] = array(
    'name' => 'override articolo promote to front page option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override articolo published option'.
  $permissions['override articolo published option'] = array(
    'name' => 'override articolo published option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override articolo revision option'.
  $permissions['override articolo revision option'] = array(
    'name' => 'override articolo revision option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override articolo sticky option'.
  $permissions['override articolo sticky option'] = array(
    'name' => 'override articolo sticky option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  return $permissions;
}
