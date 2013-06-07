<?php
/**
 * @file
 * ildeposito_ct_articolo.ds_extras.inc
 */

/**
 * Implements hook_ds_vd_info().
 */
function ildeposito_ct_articolo_ds_vd_info() {
  $export = array();

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'contenuti_articoli-page';
  $ds_vd->label = 'Contenuti_articoli: Blog (Views template)';
  $export['contenuti_articoli-page'] = $ds_vd;

  return $export;
}
