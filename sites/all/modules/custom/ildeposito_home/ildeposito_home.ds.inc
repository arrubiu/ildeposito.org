<?php
/**
 * @file
 * ildeposito_home.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function ildeposito_home_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'sezioni_home';
  $ds_view_mode->label = 'Sezioni home';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['sezioni_home'] = $ds_view_mode;

  return $export;
}
