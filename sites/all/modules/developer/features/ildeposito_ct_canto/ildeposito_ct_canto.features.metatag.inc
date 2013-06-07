<?php
/**
 * @file
 * ildeposito_ct_canto.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ildeposito_ct_canto_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:canto.
  $config['node:canto'] = array(
    'instance' => 'node:canto',
    'config' => array(
      'description' => array(
        'value' => '[node:field-capoverso]',
      ),
      'abstract' => array(
        'value' => '[node:field-capoverso]',
      ),
    ),
  );

  return $config;
}
