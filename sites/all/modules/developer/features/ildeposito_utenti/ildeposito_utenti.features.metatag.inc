<?php
/**
 * @file
 * ildeposito_utenti.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function ildeposito_utenti_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: user.
  $config['user'] = array(
    'instance' => 'user',
    'config' => array(
      'title' => array(
        'value' => '[user:name] | [site:name]',
      ),
      'og:type' => array(
        'value' => 'profile',
      ),
      'og:title' => array(
        'value' => '[user:name]',
      ),
      'og:image' => array(
        'value' => '[user:picture:url]',
      ),
    ),
  );

  return $config;
}
