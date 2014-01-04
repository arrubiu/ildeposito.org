<?php

// Drush aliases
$options['shell-aliases']['pull'] = '!git pull';

// Add tables to structure-only list
// Set default if it doesn't exist. Copied from example.drushrc.php
if (!isset($options['structure-tables']['common'])) {
  $options['structure-tables']['common'] = array('cache', 'cache_filter', 'cache_menu', 'cache_page', 'history', 'sessions', 'watchdog');
}
 
/**
 * These are the defaults for the majority of projects at Metal Toad. Add or
 * remove tables as needed.
 */
$options['structure-tables']['common'] = array_merge($options['structure-tables']['common'], array(
'advagg_aggregates',
'advagg_aggregates_hashes',
'advagg_aggregates_versions',
'advagg_files',
'alchemy_cache',
'cache_advagg_aggregates',
'cache_advagg_info',
'cache_bootstrap',
'cache_entity_comment',
'cache_entity_file',
'cache_entity_node',
'cache_entity_taxonomy_term',
'cache_entity_taxonomy_vocabulary',
'cache_entity_user',
'cache_field',
'cache_filter',
'cache_form',
'cache_htmlpurifier',
'cache_image',
'cache_l10n_update',
'cache_libraries',
'cache_menu',
'cache_metatag',
'cache_page',
'cache_path',
'cache_rules',
'cache_search_api_solr',
'cache_token',
'cache_update',
'cache_variable',
'cache_views',
'cache_views_data',
'cache_widgets',
  'cache_admin_menu',
  'cache_block',
  'cache_field',
  'cache_form',
  'cache_path',
  'cache_token',
  'cache_update',
  'cache_views',
  'cache_views_data',
  'ctools_css_cache',
  'ctools_object_cache',
  'watchdog',
'sessions',
));
