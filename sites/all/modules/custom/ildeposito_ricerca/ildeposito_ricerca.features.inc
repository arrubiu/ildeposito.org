<?php
/**
 * @file
 * ildeposito_ricerca.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_ricerca_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "current_search" && $api == "current_search") {
    return array("version" => "1");
  }
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "ds_extras" && $api == "ds_extras") {
    return array("version" => "1");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ildeposito_ricerca_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function ildeposito_ricerca_default_search_api_index() {
  $items = array();
  $items['ildeposito_contenuti'] = entity_import('search_api_index', '{
    "name" : "ilDeposito contenuti",
    "machine_name" : "ildeposito_contenuti",
    "description" : null,
    "server" : "localhost",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [] },
      "index_directly" : 1,
      "cron_limit" : "50"
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}
