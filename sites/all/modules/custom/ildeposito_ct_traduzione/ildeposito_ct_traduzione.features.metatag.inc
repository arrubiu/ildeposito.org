<?php
/**
 * @file
 * ildeposito_ct_traduzione.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ildeposito_ct_traduzione_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:traduzione.
  $config['node:traduzione'] = array(
    'instance' => 'node:traduzione',
    'config' => array(
      'title' => array(
        'value' => '[node:title], traduzione in [node:field-lingua] di "[node:field-canto-riferimento]" | [site:name]',
      ),
      'description' => array(
        'value' => 'La traduzione in [node:field-lingua] del testo di "[node:field-canto-riferimento]". [node:field-testo].',
      ),
      'abstract' => array(
        'value' => 'La traduzione in [node:field-lingua] del testo di "[node:field-canto-riferimento]". [node:field-testo].',
      ),
      'keywords' => array(
        'value' => '[node:field-tags], testi, accordi, traduzioni, [node:field-lingua]',
      ),
      'publisher' => array(
        'value' => 'https://plus.google.com/b/113629455468042353975/',
      ),
      'author' => array(
        'value' => 'https://plus.google.com/b/113629455468042353975/',
      ),
    ),
  );

  return $config;
}
