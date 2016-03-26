<?php
/**
 * @file
 * ildeposito_gruppi.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_gruppi_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "custom_formatters" && $api == "custom_formatters") {
    return array("version" => "2");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "openlayers" && $api == "openlayers_maps") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ildeposito_gruppi_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ildeposito_gruppi_node_info() {
  $items = array(
    'gruppi' => array(
      'name' => t('Gruppi'),
      'base' => 'node_content',
      'description' => t('Crea un nuovo gruppo da visualizzare nell\'elenco.'),
      'has_title' => '1',
      'title_label' => t('Nome del gruppo'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
