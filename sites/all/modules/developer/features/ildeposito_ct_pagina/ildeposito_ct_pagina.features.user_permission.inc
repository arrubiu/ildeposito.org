<?php
/**
 * @file
 * ildeposito_ct_pagina.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_ct_pagina_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pagina content'.
  $permissions['create pagina content'] = array(
    'name' => 'create pagina content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pagina content'.
  $permissions['delete any pagina content'] = array(
    'name' => 'delete any pagina content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pagina content'.
  $permissions['delete own pagina content'] = array(
    'name' => 'delete own pagina content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pagina content'.
  $permissions['edit any pagina content'] = array(
    'name' => 'edit any pagina content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pagina content'.
  $permissions['edit own pagina content'] = array(
    'name' => 'edit own pagina content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'enter pagina revision log entry'.
  $permissions['enter pagina revision log entry'] = array(
    'name' => 'enter pagina revision log entry',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override pagina authored by option'.
  $permissions['override pagina authored by option'] = array(
    'name' => 'override pagina authored by option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override pagina authored on option'.
  $permissions['override pagina authored on option'] = array(
    'name' => 'override pagina authored on option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override pagina promote to front page option'.
  $permissions['override pagina promote to front page option'] = array(
    'name' => 'override pagina promote to front page option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override pagina published option'.
  $permissions['override pagina published option'] = array(
    'name' => 'override pagina published option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override pagina revision option'.
  $permissions['override pagina revision option'] = array(
    'name' => 'override pagina revision option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override pagina sticky option'.
  $permissions['override pagina sticky option'] = array(
    'name' => 'override pagina sticky option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  return $permissions;
}
