<?php
/**
 * @file
 * ildeposito_canto.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ildeposito_canto_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:canto.
  $config['node:canto'] = array(
    'instance' => 'node:canto',
    'config' => array(
      'title' => array(
        'value' => '[node:title] - [node:field-autore-testo] | Testo, accordi, musica e spartiti | [site:name]',
      ),
      'description' => array(
        'value' => '"[node:field-capoverso]" - Testo, accordi, musica e spartiti di [node:title] - [node:field-autore-testo] - [node:field-sezione] - [node:field-tags] - [node:field-lingua].',
      ),
      'abstract' => array(
        'value' => '"[node:field-capoverso]" - Testo, accordi, musica e spartiti di [node:title] - [node:field-autore-testo] - [node:field-sezione] - [node:field-tags] - [node:field-lingua].',
      ),
      'keywords' => array(
        'value' => '[node:field-tags], testi, accordi, musica, spartiti',
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
