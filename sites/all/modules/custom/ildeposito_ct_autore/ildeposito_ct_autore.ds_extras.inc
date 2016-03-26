<?php
/**
 * @file
 * ildeposito_ct_autore.ds_extras.inc
 */

/**
 * Implements hook_ds_vd_info().
 */
function ildeposito_ct_autore_ds_vd_info() {
  $export = array();

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'contenuti_autore-autore_singolo';
  $ds_vd->label = 'Contenuti_autore: Autore (Views template)';
  $export['contenuti_autore-autore_singolo'] = $ds_vd;

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'contenuti_autore-elenco_autori';
  $ds_vd->label = 'Contenuti_autore: Autori (Views template)';
  $export['contenuti_autore-elenco_autori'] = $ds_vd;

  return $export;
}
