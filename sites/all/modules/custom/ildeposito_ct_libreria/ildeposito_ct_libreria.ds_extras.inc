<?php
/**
 * @file
 * ildeposito_ct_libreria.ds_extras.inc
 */

/**
 * Implements hook_ds_vd_info().
 */
function ildeposito_ct_libreria_ds_vd_info() {
  $export = array();

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'tassonomie_contenuti-contenuti_libreria';
  $ds_vd->label = 'Tassonomie_contenuti: Libreria (Views template)';
  $export['tassonomie_contenuti-contenuti_libreria'] = $ds_vd;

  return $export;
}
