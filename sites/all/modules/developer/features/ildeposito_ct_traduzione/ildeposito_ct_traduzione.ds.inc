<?php
/**
 * @file
 * ildeposito_ct_traduzione.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ildeposito_ct_traduzione_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'ds_views|contenuti_traduzioni-traduzioni_elenco|default';
  $ds_fieldsetting->entity_type = 'ds_views';
  $ds_fieldsetting->bundle = 'contenuti_traduzioni-traduzioni_elenco';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'header' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'rows' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'pager' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'current_center_notext' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_lingua_originale' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_lingue' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_sezioni' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['ds_views|contenuti_traduzioni-traduzioni_elenco|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ildeposito_ct_traduzione_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'ds_views|contenuti_traduzioni-traduzioni_elenco|default';
  $ds_layout->entity_type = 'ds_views';
  $ds_layout->bundle = 'contenuti_traduzioni-traduzioni_elenco';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'right' => array(
        0 => 'service_links_not_node',
        5 => 'facet_sezioni',
        6 => 'facet_lingue',
        7 => 'facet_lingua_originale',
      ),
      'header' => array(
        1 => 'header',
        2 => 'current_center_notext',
      ),
      'left' => array(
        3 => 'rows',
        4 => 'pager',
      ),
    ),
    'fields' => array(
      'service_links_not_node' => 'right',
      'header' => 'header',
      'current_center_notext' => 'header',
      'rows' => 'left',
      'pager' => 'left',
      'facet_sezioni' => 'right',
      'facet_lingue' => 'right',
      'facet_lingua_originale' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
  );
  $export['ds_views|contenuti_traduzioni-traduzioni_elenco|default'] = $ds_layout;

  return $export;
}
