<?php
/**
 * @file
 * ildeposito_customcontent.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_customcontent_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create custom_content content'.
  $permissions['create custom_content content'] = array(
    'name' => 'create custom_content content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any custom_content content'.
  $permissions['delete any custom_content content'] = array(
    'name' => 'delete any custom_content content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own custom_content content'.
  $permissions['delete own custom_content content'] = array(
    'name' => 'delete own custom_content content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any custom_content content'.
  $permissions['edit any custom_content content'] = array(
    'name' => 'edit any custom_content content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own custom_content content'.
  $permissions['edit own custom_content content'] = array(
    'name' => 'edit own custom_content content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'enter custom_content revision log entry'.
  $permissions['enter custom_content revision log entry'] = array(
    'name' => 'enter custom_content revision log entry',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override custom_content authored by option'.
  $permissions['override custom_content authored by option'] = array(
    'name' => 'override custom_content authored by option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override custom_content authored on option'.
  $permissions['override custom_content authored on option'] = array(
    'name' => 'override custom_content authored on option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override custom_content promote to front page option'.
  $permissions['override custom_content promote to front page option'] = array(
    'name' => 'override custom_content promote to front page option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override custom_content published option'.
  $permissions['override custom_content published option'] = array(
    'name' => 'override custom_content published option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override custom_content revision option'.
  $permissions['override custom_content revision option'] = array(
    'name' => 'override custom_content revision option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override custom_content sticky option'.
  $permissions['override custom_content sticky option'] = array(
    'name' => 'override custom_content sticky option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  return $permissions;
}
