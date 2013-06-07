<?php
/**
 * @file
 * ildeposito_ct_evento.ds_extras.inc
 */

/**
 * Implements hook_ds_vd_info().
 */
function ildeposito_ct_evento_ds_vd_info() {
  $export = array();

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'contenuti_eventi-eventi_elenco';
  $ds_vd->label = 'Contenuti_eventi: Elenco (Views template)';
  $export['contenuti_eventi-eventi_elenco'] = $ds_vd;

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'contenuti_eventi-eventi_mappa';
  $ds_vd->label = 'Contenuti_eventi: Mappa (Views template)';
  $export['contenuti_eventi-eventi_mappa'] = $ds_vd;

  return $export;
}
