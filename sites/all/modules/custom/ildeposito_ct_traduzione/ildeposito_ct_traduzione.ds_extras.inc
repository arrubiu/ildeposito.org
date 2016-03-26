<?php
/**
 * @file
 * ildeposito_ct_traduzione.ds_extras.inc
 */

/**
 * Implements hook_ds_vd_info().
 */
function ildeposito_ct_traduzione_ds_vd_info() {
  $export = array();

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'contenuti_traduzioni-traduzioni_elenco';
  $ds_vd->label = 'Contenuti_traduzioni: Elenco (Views template)';
  $export['contenuti_traduzioni-traduzioni_elenco'] = $ds_vd;

  return $export;
}
