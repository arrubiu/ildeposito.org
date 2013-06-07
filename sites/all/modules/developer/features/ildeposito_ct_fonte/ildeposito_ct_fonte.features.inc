<?php
/**
 * @file
 * ildeposito_ct_fonte.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_ct_fonte_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ildeposito_ct_fonte_node_info() {
  $items = array(
    'fonte_bibliografica' => array(
      'name' => t('Fonte bibliografica'),
      'base' => 'node_content',
      'description' => t('Il contenuto per indicare la fonte bibliografica di canti e traduzioni'),
      'has_title' => '1',
      'title_label' => t('Titolo'),
      'help' => '',
    ),
  );
  return $items;
}
