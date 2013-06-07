<?php
/**
 * @file
 * ildeposito_ricerca.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ildeposito_ricerca_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_ds_views__ricerca-ricerca_page';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(
        'title' => array(
          'default' => array(
            'weight' => '28',
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_ds_views__ricerca-ricerca_page'] = $strongarm;

  return $export;
}
