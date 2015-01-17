<?php
/**
 * @file
 * ildeposito_gruppi.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_gruppi_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create gruppi content'.
  $permissions['create gruppi content'] = array(
    'name' => 'create gruppi content',
    'roles' => array(
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'define view for terms in tipi_gruppi'.
  $permissions['define view for terms in tipi_gruppi'] = array(
    'name' => 'define view for terms in tipi_gruppi',
    'roles' => array(),
    'module' => 'tvi',
  );

  // Exported permission: 'define view for vocabulary tipi_gruppi'.
  $permissions['define view for vocabulary tipi_gruppi'] = array(
    'name' => 'define view for vocabulary tipi_gruppi',
    'roles' => array(),
    'module' => 'tvi',
  );

  // Exported permission: 'delete any gruppi content'.
  $permissions['delete any gruppi content'] = array(
    'name' => 'delete any gruppi content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own gruppi content'.
  $permissions['delete own gruppi content'] = array(
    'name' => 'delete own gruppi content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in tipi_gruppi'.
  $permissions['delete terms in tipi_gruppi'] = array(
    'name' => 'delete terms in tipi_gruppi',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any gruppi content'.
  $permissions['edit any gruppi content'] = array(
    'name' => 'edit any gruppi content',
    'roles' => array(
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own gruppi content'.
  $permissions['edit own gruppi content'] = array(
    'name' => 'edit own gruppi content',
    'roles' => array(
      'staff' => 'staff',
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in tipi_gruppi'.
  $permissions['edit terms in tipi_gruppi'] = array(
    'name' => 'edit terms in tipi_gruppi',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'enter gruppi revision log entry'.
  $permissions['enter gruppi revision log entry'] = array(
    'name' => 'enter gruppi revision log entry',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override gruppi authored by option'.
  $permissions['override gruppi authored by option'] = array(
    'name' => 'override gruppi authored by option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override gruppi authored on option'.
  $permissions['override gruppi authored on option'] = array(
    'name' => 'override gruppi authored on option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override gruppi promote to front page option'.
  $permissions['override gruppi promote to front page option'] = array(
    'name' => 'override gruppi promote to front page option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override gruppi published option'.
  $permissions['override gruppi published option'] = array(
    'name' => 'override gruppi published option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override gruppi revision option'.
  $permissions['override gruppi revision option'] = array(
    'name' => 'override gruppi revision option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override gruppi sticky option'.
  $permissions['override gruppi sticky option'] = array(
    'name' => 'override gruppi sticky option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  return $permissions;
}
