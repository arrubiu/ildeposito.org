<?php
/**
 * @file
 * ildeposito_utenti.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_utenti_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ildeposito_utenti_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
