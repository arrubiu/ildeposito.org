<?php
/**
 * @file
 * ildeposito_ct_evento.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_ct_evento_user_default_permissions() {
  $permissions = array();

  // Exported permission: create evento content.
  $permissions['create evento content'] = array(
    'name' => 'create evento content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any evento content.
  $permissions['delete any evento content'] = array(
    'name' => 'delete any evento content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own evento content.
  $permissions['delete own evento content'] = array(
    'name' => 'delete own evento content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any evento content.
  $permissions['edit any evento content'] = array(
    'name' => 'edit any evento content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own evento content.
  $permissions['edit own evento content'] = array(
    'name' => 'edit own evento content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: enter evento revision log entry.
  $permissions['enter evento revision log entry'] = array(
    'name' => 'enter evento revision log entry',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override evento authored by option.
  $permissions['override evento authored by option'] = array(
    'name' => 'override evento authored by option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override evento authored on option.
  $permissions['override evento authored on option'] = array(
    'name' => 'override evento authored on option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override evento promote to front page option.
  $permissions['override evento promote to front page option'] = array(
    'name' => 'override evento promote to front page option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override evento published option.
  $permissions['override evento published option'] = array(
    'name' => 'override evento published option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override evento revision option.
  $permissions['override evento revision option'] = array(
    'name' => 'override evento revision option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: override evento sticky option.
  $permissions['override evento sticky option'] = array(
    'name' => 'override evento sticky option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  return $permissions;
}
