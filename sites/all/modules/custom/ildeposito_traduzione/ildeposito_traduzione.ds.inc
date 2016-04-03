<?php
/**
 * @file
 * ildeposito_traduzione.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ildeposito_traduzione_ds_field_settings_info() {
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

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|traduzione|rss_app';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'traduzione';
  $ds_fieldsetting->view_mode = 'rss_app';
  $ds_fieldsetting->settings = array(
    'field_lingua_originale' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_minimal',
        ),
      ),
    ),
  );
  $export['node|traduzione|rss_app'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ildeposito_traduzione_ds_layout_settings_info() {
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

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|traduzione|rss_app';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'traduzione';
  $ds_layout->view_mode = 'rss_app';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_sezione',
        1 => 'field_canto_riferimento',
        2 => 'field_lingua_originale',
        3 => 'field_lingua',
        4 => 'field_informazioni',
      ),
    ),
    'fields' => array(
      'field_sezione' => 'ds_content',
      'field_canto_riferimento' => 'ds_content',
      'field_lingua_originale' => 'ds_content',
      'field_lingua' => 'ds_content',
      'field_informazioni' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|traduzione|rss_app'] = $ds_layout;

  return $export;
}
