<?php
/**
 * @file
 * ildeposito_ricerca.ds_extras.inc
 */

/**
 * Implements hook_ds_vd_info().
 */
function ildeposito_ricerca_ds_vd_info() {
  $export = array();

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'ricerca-ricerca_page';
  $ds_vd->label = 'Ricerca: Ricerca (Views template)';
  $export['ricerca-ricerca_page'] = $ds_vd;

  return $export;
}
