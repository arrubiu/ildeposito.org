<?php
/**
 * @file
 * ildeposito_ct_canto.ds_extras.inc
 */

/**
 * Implements hook_ds_vd_info().
 */
function ildeposito_ct_canto_ds_vd_info() {
  $export = array();

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'contenuti_canti-eventi_elenco';
  $ds_vd->label = 'Contenuti_canti: Elenco (Views template)';
  $export['contenuti_canti-eventi_elenco'] = $ds_vd;

  return $export;
}
