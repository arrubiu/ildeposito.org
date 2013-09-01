<?php
/**
 * @file
 * ildeposito_ct_autore.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ildeposito_ct_autore_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'ds_views|contenuti_autore-autore_singolo|default';
  $ds_fieldsetting->entity_type = 'ds_views';
  $ds_fieldsetting->bundle = 'contenuti_autore-autore_singolo';
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
    'facet_presenza_accordi' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_sezioni' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tematiche' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_node' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['ds_views|contenuti_autore-autore_singolo|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'ds_views|contenuti_autore-elenco_autori|default';
  $ds_fieldsetting->entity_type = 'ds_views';
  $ds_fieldsetting->bundle = 'contenuti_autore-elenco_autori';
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
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_sezioni' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['ds_views|contenuti_autore-elenco_autori|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ildeposito_ct_autore_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'ds_views|contenuti_autore-autore_singolo|default';
  $ds_layout->entity_type = 'ds_views';
  $ds_layout->bundle = 'contenuti_autore-autore_singolo';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'right' => array(
        0 => 'service_links_node',
        5 => 'facet_sezioni',
        6 => 'facet_tematiche',
        7 => 'facet_presenza_accordi',
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
      'service_links_node' => 'right',
      'header' => 'header',
      'current_center_notext' => 'header',
      'rows' => 'left',
      'pager' => 'left',
      'facet_sezioni' => 'right',
      'facet_tematiche' => 'right',
      'facet_presenza_accordi' => 'right',
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
  $export['ds_views|contenuti_autore-autore_singolo|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'ds_views|contenuti_autore-elenco_autori|default';
  $ds_layout->entity_type = 'ds_views';
  $ds_layout->bundle = 'contenuti_autore-elenco_autori';
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
        5 => 'facet_localizzazioni',
        6 => 'facet_sezioni',
      ),
    ),
    'fields' => array(
      'header' => 'header',
      'current_center_notext' => 'header',
      'rows' => 'left',
      'pager' => 'left',
      'service_links_not_node' => 'right',
      'facet_localizzazioni' => 'right',
      'facet_sezioni' => 'right',
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
  $export['ds_views|contenuti_autore-elenco_autori|default'] = $ds_layout;

  return $export;
}
