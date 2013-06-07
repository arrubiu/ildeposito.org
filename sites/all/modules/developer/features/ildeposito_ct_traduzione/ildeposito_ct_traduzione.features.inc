<?php
/**
 * @file
 * ildeposito_ct_traduzione.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_ct_traduzione_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "ds_extras" && $api == "ds_extras") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ildeposito_ct_traduzione_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ildeposito_ct_traduzione_node_info() {
  $items = array(
    'traduzione' => array(
      'name' => t('Traduzione'),
      'base' => 'node_content',
      'description' => t('Crea una traduzione di un canto esistente'),
      'has_title' => '1',
      'title_label' => t('Titolo'),
      'help' => '',
    ),
  );
  return $items;
}
