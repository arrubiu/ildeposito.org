<?php
/**
 * @file
 * ildeposito_tassonomie.ds_extras.inc
 */

/**
 * Implements hook_ds_vd_info().
 */
function ildeposito_tassonomie_ds_vd_info() {
  $export = array();

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'tassonomie_contenuti-contenuti_lingua';
  $ds_vd->label = 'Tassonomie_contenuti: Lingue (Views template)';
  $export['tassonomie_contenuti-contenuti_lingua'] = $ds_vd;

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'tassonomie_contenuti-contenuti_localizzazioni';
  $ds_vd->label = 'Tassonomie_contenuti: Localizzazioni (Views template)';
  $export['tassonomie_contenuti-contenuti_localizzazioni'] = $ds_vd;

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'tassonomie_contenuti-contenuti_percorsi';
  $ds_vd->label = 'Tassonomie_contenuti: Percorsi (Views template)';
  $export['tassonomie_contenuti-contenuti_percorsi'] = $ds_vd;

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'tassonomie_contenuti-contenuti_sezione';
  $ds_vd->label = 'Tassonomie_contenuti: Sezioni (Views template)';
  $export['tassonomie_contenuti-contenuti_sezione'] = $ds_vd;

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'tassonomie_contenuti-contenuti_tags';
  $ds_vd->label = 'Tassonomie_contenuti: Tags (Views template)';
  $export['tassonomie_contenuti-contenuti_tags'] = $ds_vd;

  $ds_vd = new stdClass();
  $ds_vd->api_version = 1;
  $ds_vd->vd = 'tassonomie_contenuti-contenuti_tematica';
  $ds_vd->label = 'Tassonomie_contenuti: Tematiche (Views template)';
  $export['tassonomie_contenuti-contenuti_tematica'] = $ds_vd;

  return $export;
}
