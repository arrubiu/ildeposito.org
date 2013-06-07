<?php
/**
 * @file
 * ildeposito_ct_articolo.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_ct_articolo_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "ds_extras" && $api == "ds_extras") {
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
function ildeposito_ct_articolo_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ildeposito_ct_articolo_node_info() {
  $items = array(
    'articolo' => array(
      'name' => t('Articolo'),
      'base' => 'node_content',
      'description' => t('Tipo di contenuto per pubblicare articoli'),
      'has_title' => '1',
      'title_label' => t('Titolo'),
      'help' => '',
    ),
  );
  return $items;
}
