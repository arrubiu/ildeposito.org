<?php
/**
 * @file
 * ildeposito_libreria.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ildeposito_libreria_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:voce_libreria.
  $config['node:voce_libreria'] = array(
    'instance' => 'node:voce_libreria',
    'config' => array(
      'title' => array(
        'value' => '[node:field-tipo-voce:0] - [node:title] | [site:name]',
      ),
      'description' => array(
        'value' => '[node:field-tipo-voce] - [node:title] [node:field-autore] [node:field-editore][node:field-citta][node:field-anno]',
      ),
      'abstract' => array(
        'value' => '[node:field-tipo-voce] - [node:title] [node:field-autore] [node:field-editore][node:field-citta][node:field-anno]',
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
