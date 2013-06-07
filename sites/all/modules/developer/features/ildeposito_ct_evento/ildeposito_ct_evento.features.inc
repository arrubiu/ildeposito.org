<?php
/**
 * @file
 * ildeposito_ct_evento.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_ct_evento_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
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
  if ($module == "openlayers" && $api == "openlayers_maps") {
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
function ildeposito_ct_evento_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ildeposito_ct_evento_node_info() {
  $items = array(
    'evento' => array(
      'name' => t('Evento'),
      'base' => 'node_content',
      'description' => t('Utilizzare per la creazione di eventi'),
      'has_title' => '1',
      'title_label' => t('Titolo'),
      'help' => '',
    ),
  );
  return $items;
}
