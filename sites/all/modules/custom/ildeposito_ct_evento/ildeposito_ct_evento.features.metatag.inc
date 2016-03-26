<?php
/**
 * @file
 * ildeposito_ct_evento.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ildeposito_ct_evento_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:evento.
  $config['node:evento'] = array(
    'instance' => 'node:evento',
    'config' => array(
      'title' => array(
        'value' => '[current-page:title] - [node:field-percorso] - [node:field-localizzazione] | [site:name]',
      ),
      'description' => array(
        'value' => '[node:field-informazioni:value]. I canti e le canzoni collegati a quest\'evento. Tags: [node:field-tags].',
      ),
      'abstract' => array(
        'value' => '[node:field-informazioni:value]. I canti e le canzoni collegati a quest\'evento. Tags: [node:field-tags].',
      ),
      'keywords' => array(
        'value' => '[node:field-tags], eventi, storia, cantata',
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
