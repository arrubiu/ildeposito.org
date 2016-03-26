<?php
/**
 * @file
 * ildeposito_ct_customcontent.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_ct_customcontent_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ildeposito_ct_customcontent_node_info() {
  $items = array(
    'custom_content' => array(
      'name' => t('Custom content'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
