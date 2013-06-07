<?php
/**
 * @file
 * ildeposito_book.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_book_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ildeposito_book_node_info() {
  $items = array(
    'book' => array(
      'name' => t('Pagina libro'),
      'base' => 'node_content',
      'description' => t('<em>Books</em> have a built-in hierarchical navigation. Use for handbooks or tutorials.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
