<?php
/**
 * @file
 * ildeposito_ct_libreria.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_ct_libreria_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'clear libreria feeds'.
  $permissions['clear libreria feeds'] = array(
    'name' => 'clear libreria feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: 'create voce_libreria content'.
  $permissions['create voce_libreria content'] = array(
    'name' => 'create voce_libreria content',
    'roles' => array(
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'define view for terms in tipo_libreria'.
  $permissions['define view for terms in tipo_libreria'] = array(
    'name' => 'define view for terms in tipo_libreria',
    'roles' => array(),
    'module' => 'tvi',
  );

  // Exported permission: 'define view for vocabulary tipo_libreria'.
  $permissions['define view for vocabulary tipo_libreria'] = array(
    'name' => 'define view for vocabulary tipo_libreria',
    'roles' => array(),
    'module' => 'tvi',
  );

  // Exported permission: 'delete any voce_libreria content'.
  $permissions['delete any voce_libreria content'] = array(
    'name' => 'delete any voce_libreria content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own voce_libreria content'.
  $permissions['delete own voce_libreria content'] = array(
    'name' => 'delete own voce_libreria content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in tipo_libreria'.
  $permissions['delete terms in tipo_libreria'] = array(
    'name' => 'delete terms in tipo_libreria',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any voce_libreria content'.
  $permissions['edit any voce_libreria content'] = array(
    'name' => 'edit any voce_libreria content',
    'roles' => array(
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own voce_libreria content'.
  $permissions['edit own voce_libreria content'] = array(
    'name' => 'edit own voce_libreria content',
    'roles' => array(
      'utente registrato' => 'utente registrato',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in tipo_libreria'.
  $permissions['edit terms in tipo_libreria'] = array(
    'name' => 'edit terms in tipo_libreria',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'enter voce_libreria revision log entry'.
  $permissions['enter voce_libreria revision log entry'] = array(
    'name' => 'enter voce_libreria revision log entry',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'import libreria feeds'.
  $permissions['import libreria feeds'] = array(
    'name' => 'import libreria feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  // Exported permission: 'override voce_libreria authored by option'.
  $permissions['override voce_libreria authored by option'] = array(
    'name' => 'override voce_libreria authored by option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override voce_libreria authored on option'.
  $permissions['override voce_libreria authored on option'] = array(
    'name' => 'override voce_libreria authored on option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override voce_libreria promote to front page option'.
  $permissions['override voce_libreria promote to front page option'] = array(
    'name' => 'override voce_libreria promote to front page option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override voce_libreria published option'.
  $permissions['override voce_libreria published option'] = array(
    'name' => 'override voce_libreria published option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override voce_libreria revision option'.
  $permissions['override voce_libreria revision option'] = array(
    'name' => 'override voce_libreria revision option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override voce_libreria sticky option'.
  $permissions['override voce_libreria sticky option'] = array(
    'name' => 'override voce_libreria sticky option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'tamper libreria'.
  $permissions['tamper libreria'] = array(
    'name' => 'tamper libreria',
    'roles' => array(),
    'module' => 'feeds_tamper',
  );

  // Exported permission: 'unlock libreria feeds'.
  $permissions['unlock libreria feeds'] = array(
    'name' => 'unlock libreria feeds',
    'roles' => array(),
    'module' => 'feeds',
  );

  return $permissions;
}
