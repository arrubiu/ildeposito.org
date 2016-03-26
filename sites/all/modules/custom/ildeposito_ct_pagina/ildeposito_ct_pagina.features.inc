<?php
/**
 * @file
 * ildeposito_ct_pagina.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_ct_pagina_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ildeposito_ct_pagina_node_info() {
  $items = array(
    'pagina' => array(
      'name' => t('Pagina'),
      'base' => 'node_content',
      'description' => t('Pagine informative e "statiche"'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
