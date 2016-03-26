<?php
/**
 * @file
 * ildeposito_utenti.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function ildeposito_utenti_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: collaboratore.
  $roles['collaboratore'] = array(
    'name' => 'collaboratore',
    'weight' => 5,
  );

  // Exported role: staff.
  $roles['staff'] = array(
    'name' => 'staff',
    'weight' => 3,
  );

  // Exported role: utente registrato.
  $roles['utente registrato'] = array(
    'name' => 'utente registrato',
    'weight' => 4,
  );

  return $roles;
}
