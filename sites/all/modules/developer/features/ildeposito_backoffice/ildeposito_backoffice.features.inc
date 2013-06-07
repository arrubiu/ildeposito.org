<?php
/**
 * @file
 * ildeposito_backoffice.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_backoffice_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "linkit" && $api == "linkit_profiles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ildeposito_backoffice_views_api() {
  return array("api" => "3.0");
}
