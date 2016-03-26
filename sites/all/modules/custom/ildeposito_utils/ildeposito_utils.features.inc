<?php
/**
 * @file
 * ildeposito_utils.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_utils_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "elysia_cron" && $api == "default_elysia_cron_rules") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ildeposito_utils_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
