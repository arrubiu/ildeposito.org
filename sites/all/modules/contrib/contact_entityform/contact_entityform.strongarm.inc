<?php
/**
 * @file
 * contact_entityform.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function contact_entityform_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'contact_entityform_roles';
  $strongarm->value = array(
    2 => 'personal_contact_form',
    3 => '',
  );
  $export['contact_entityform_roles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'contact_entityform_site_form';
  $strongarm->value = 'site_contact_form';
  $export['contact_entityform_site_form'] = $strongarm;

  return $export;
}
