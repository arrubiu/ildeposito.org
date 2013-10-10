<?php
/**
 * @file
 * ildeposito_newsletter.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_newsletter_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer newsletters'.
  $permissions['administer newsletters'] = array(
    'name' => 'administer newsletters',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: 'administer simplenews settings'.
  $permissions['administer simplenews settings'] = array(
    'name' => 'administer simplenews settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: 'administer simplenews subscriptions'.
  $permissions['administer simplenews subscriptions'] = array(
    'name' => 'administer simplenews subscriptions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: 'create simplenews content'.
  $permissions['create simplenews content'] = array(
    'name' => 'create simplenews content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any simplenews content'.
  $permissions['delete any simplenews content'] = array(
    'name' => 'delete any simplenews content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own simplenews content'.
  $permissions['delete own simplenews content'] = array(
    'name' => 'delete own simplenews content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any simplenews content'.
  $permissions['edit any simplenews content'] = array(
    'name' => 'edit any simplenews content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own simplenews content'.
  $permissions['edit own simplenews content'] = array(
    'name' => 'edit own simplenews content',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'enter simplenews revision log entry'.
  $permissions['enter simplenews revision log entry'] = array(
    'name' => 'enter simplenews revision log entry',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override simplenews authored by option'.
  $permissions['override simplenews authored by option'] = array(
    'name' => 'override simplenews authored by option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override simplenews authored on option'.
  $permissions['override simplenews authored on option'] = array(
    'name' => 'override simplenews authored on option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override simplenews promote to front page option'.
  $permissions['override simplenews promote to front page option'] = array(
    'name' => 'override simplenews promote to front page option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override simplenews published option'.
  $permissions['override simplenews published option'] = array(
    'name' => 'override simplenews published option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override simplenews revision option'.
  $permissions['override simplenews revision option'] = array(
    'name' => 'override simplenews revision option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'override simplenews sticky option'.
  $permissions['override simplenews sticky option'] = array(
    'name' => 'override simplenews sticky option',
    'roles' => array(),
    'module' => 'override_node_options',
  );

  // Exported permission: 'send newsletter'.
  $permissions['send newsletter'] = array(
    'name' => 'send newsletter',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'simplenews',
  );

  // Exported permission: 'subscribe to newsletters'.
  $permissions['subscribe to newsletters'] = array(
    'name' => 'subscribe to newsletters',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'simplenews',
  );

  return $permissions;
}
