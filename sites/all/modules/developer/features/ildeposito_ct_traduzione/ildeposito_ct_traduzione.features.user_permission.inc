<?php
/**
 * @file
 * ildeposito_ct_traduzione.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_ct_traduzione_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create traduzione content'.
  $permissions['create traduzione content'] = array(
    'name' => 'create traduzione content',
    'roles' => array(
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any traduzione content'.
  $permissions['delete any traduzione content'] = array(
    'name' => 'delete any traduzione content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own traduzione content'.
  $permissions['delete own traduzione content'] = array(
    'name' => 'delete own traduzione content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any traduzione content'.
  $permissions['edit any traduzione content'] = array(
    'name' => 'edit any traduzione content',
    'roles' => array(
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own traduzione content'.
  $permissions['edit own traduzione content'] = array(
    'name' => 'edit own traduzione content',
    'roles' => array(
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'enter traduzione revision log entry'.
  $permissions['enter traduzione revision log entry'] = array(
    'name' => 'enter traduzione revision log entry',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override traduzione authored by option'.
  $permissions['override traduzione authored by option'] = array(
    'name' => 'override traduzione authored by option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override traduzione authored on option'.
  $permissions['override traduzione authored on option'] = array(
    'name' => 'override traduzione authored on option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override traduzione promote to front page option'.
  $permissions['override traduzione promote to front page option'] = array(
    'name' => 'override traduzione promote to front page option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override traduzione published option'.
  $permissions['override traduzione published option'] = array(
    'name' => 'override traduzione published option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override traduzione revision option'.
  $permissions['override traduzione revision option'] = array(
    'name' => 'override traduzione revision option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override traduzione sticky option'.
  $permissions['override traduzione sticky option'] = array(
    'name' => 'override traduzione sticky option',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'override_node_options',
  );

  return $permissions;
}
