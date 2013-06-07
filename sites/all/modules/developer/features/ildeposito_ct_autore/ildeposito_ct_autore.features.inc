<?php
/**
 * @file
 * ildeposito_ct_autore.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_ct_autore_ctools_plugin_api() {
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
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ildeposito_ct_autore_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function ildeposito_ct_autore_node_info() {
  $items = array(
    'autore' => array(
      'name' => t('Autore'),
      'base' => 'node_content',
      'description' => t('Crea un autore (di testo o musica)'),
      'has_title' => '1',
      'title_label' => t('Cognome (o nome del gruppo)'),
      'help' => '',
    ),
  );
  return $items;
}
