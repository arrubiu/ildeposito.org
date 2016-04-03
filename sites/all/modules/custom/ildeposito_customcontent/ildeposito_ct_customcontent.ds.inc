<?php
/**
 * @file
 * ildeposito_customcontent.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function ildeposito_customcontent_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|custom_content|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'custom_content';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'body',
      ),
    ),
    'fields' => array(
      'body' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => TRUE,
  );
  $export['node|custom_content|default'] = $ds_layout;

  return $export;
}
