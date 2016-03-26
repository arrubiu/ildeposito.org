<?php
/**
 * @file
 * ildeposito_tassonomie.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ildeposito_tassonomie_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer rh_taxonomy'.
  $permissions['administer rh_taxonomy'] = array(
    'name' => 'administer rh_taxonomy',
    'roles' => array(),
    'module' => 'rabbit_hole',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer taxonomy display'.
  $permissions['administer taxonomy display'] = array(
    'name' => 'administer taxonomy display',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy_display',
  );

  // Exported permission: 'bypass rh_taxonomy'.
  $permissions['bypass rh_taxonomy'] = array(
    'name' => 'bypass rh_taxonomy',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'rabbit_hole',
  );

  // Exported permission: 'delete terms in forums'.
  $permissions['delete terms in forums'] = array(
    'name' => 'delete terms in forums',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in lingue'.
  $permissions['delete terms in lingue'] = array(
    'name' => 'delete terms in lingue',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in localizzazione'.
  $permissions['delete terms in localizzazione'] = array(
    'name' => 'delete terms in localizzazione',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in newsletter'.
  $permissions['delete terms in newsletter'] = array(
    'name' => 'delete terms in newsletter',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in percorsi'.
  $permissions['delete terms in percorsi'] = array(
    'name' => 'delete terms in percorsi',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in sezioni'.
  $permissions['delete terms in sezioni'] = array(
    'name' => 'delete terms in sezioni',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in tags'.
  $permissions['delete terms in tags'] = array(
    'name' => 'delete terms in tags',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in tematiche'.
  $permissions['delete terms in tematiche'] = array(
    'name' => 'delete terms in tematiche',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in forums'.
  $permissions['edit terms in forums'] = array(
    'name' => 'edit terms in forums',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in lingue'.
  $permissions['edit terms in lingue'] = array(
    'name' => 'edit terms in lingue',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in localizzazione'.
  $permissions['edit terms in localizzazione'] = array(
    'name' => 'edit terms in localizzazione',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in newsletter'.
  $permissions['edit terms in newsletter'] = array(
    'name' => 'edit terms in newsletter',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in percorsi'.
  $permissions['edit terms in percorsi'] = array(
    'name' => 'edit terms in percorsi',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in sezioni'.
  $permissions['edit terms in sezioni'] = array(
    'name' => 'edit terms in sezioni',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in tags'.
  $permissions['edit terms in tags'] = array(
    'name' => 'edit terms in tags',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in tematiche'.
  $permissions['edit terms in tematiche'] = array(
    'name' => 'edit terms in tematiche',
    'roles' => array(
      'staff' => 'staff',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'php redirect rh_taxonomy'.
  $permissions['php redirect rh_taxonomy'] = array(
    'name' => 'php redirect rh_taxonomy',
    'roles' => array(),
    'module' => 'rabbit_hole',
  );

  return $permissions;
}
