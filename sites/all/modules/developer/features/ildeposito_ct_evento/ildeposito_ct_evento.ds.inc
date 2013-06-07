<?php
/**
 * @file
 * ildeposito_ct_evento.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ildeposito_ct_evento_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'ds_views|contenuti_eventi-eventi_elenco|default';
  $ds_fieldsetting->entity_type = 'ds_views';
  $ds_fieldsetting->bundle = 'contenuti_eventi-eventi_elenco';
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
    'facet_localizzazioni' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_sezioni' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tags' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['ds_views|contenuti_eventi-eventi_elenco|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'ds_views|contenuti_eventi-eventi_mappa|default';
  $ds_fieldsetting->entity_type = 'ds_views';
  $ds_fieldsetting->bundle = 'contenuti_eventi-eventi_mappa';
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
    'current_search_facet' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_percorsi' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_sezioni' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tags' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['ds_views|contenuti_eventi-eventi_mappa|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ildeposito_ct_evento_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'ds_views|contenuti_eventi-eventi_elenco|default';
  $ds_layout->entity_type = 'ds_views';
  $ds_layout->bundle = 'contenuti_eventi-eventi_elenco';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'header',
        1 => 'current_center_notext',
      ),
      'left' => array(
        2 => 'rows',
        3 => 'pager',
      ),
      'right' => array(
        4 => 'service_links_not_node',
        5 => 'facet_sezioni',
        6 => 'facet_localizzazioni',
        7 => 'facet_tags',
      ),
    ),
    'fields' => array(
      'header' => 'header',
      'current_center_notext' => 'header',
      'rows' => 'left',
      'pager' => 'left',
      'service_links_not_node' => 'right',
      'facet_sezioni' => 'right',
      'facet_localizzazioni' => 'right',
      'facet_tags' => 'right',
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
  $export['ds_views|contenuti_eventi-eventi_elenco|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'ds_views|contenuti_eventi-eventi_mappa|default';
  $ds_layout->entity_type = 'ds_views';
  $ds_layout->bundle = 'contenuti_eventi-eventi_mappa';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'header',
        1 => 'current_search_facet',
      ),
      'left' => array(
        2 => 'rows',
        3 => 'pager',
      ),
      'right' => array(
        4 => 'service_links_not_node',
        5 => 'facet_sezioni',
        6 => 'facet_percorsi',
        7 => 'facet_tags',
      ),
    ),
    'fields' => array(
      'header' => 'header',
      'current_search_facet' => 'header',
      'rows' => 'left',
      'pager' => 'left',
      'service_links_not_node' => 'right',
      'facet_sezioni' => 'right',
      'facet_percorsi' => 'right',
      'facet_tags' => 'right',
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
  $export['ds_views|contenuti_eventi-eventi_mappa|default'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function ildeposito_ct_evento_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'riferimento_evento';
  $ds_view_mode->label = 'Riferimento evento';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['riferimento_evento'] = $ds_view_mode;

  return $export;
}
