<?php

/**
 * @file
 * Provides a content-based caching option for panel panes.
 */

// Plugin definition
$plugin = array(
  'title' => t("Content cache"),
  'description' => t('Content based caching allows panel caches to be expired based on content creation / updates.'),
  'cache get' => 'panels_content_cache_get_cache',
  'cache set' => 'panels_content_cache_set_cache',
  'cache clear' => 'panels_content_cache_clear_cache',
  'settings form' => 'panels_content_cache_settings_form',
  'settings form submit' => 'panels_content_cache_settings_form_submit',
  'defaults' => array(
    'lifetime' => 'none',
    'granularity' => 'none',
  ),
);

/**
 * Get cached content.
 */
function panels_content_cache_get_cache($conf, $display, $args, $contexts, $pane = NULL) {
  $cid = panels_content_cache_get_id($conf, $display, $args, $contexts, $pane);
  $cache = cache_get($cid, 'cache');
  if (!$cache) {
    return FALSE;
  }

  if ($conf['lifetime'] != 'none' && (time() - $cache->created) > $conf['lifetime']) {
    return FALSE;
  }

  return $cache->data;
}

/**
 * Set cached content.
 */
function panels_content_cache_set_cache($conf, $content, $display, $args, $contexts, $pane = NULL) {
  $cid = panels_content_cache_get_id($conf, $display, $args, $contexts, $pane);
  cache_set($cid, $content);
}

/**
 * Clear cached content.
 *
 * Cache clears are always for an entire display, regardless of arguments.
 *
 * Have not altered this function to take into account pane IDs (so we can clear individual panes)
 * because all the other panels caching plugins I looked at did not do this either, so
 * have left this for now as it requires further investigation.
 */
function panels_content_cache_clear_cache($display) {
  $cid = 'panels_content_cache';

  // This is used in case this is an in-code display, which means did will be something like 'new-1'.
  if (isset($display->owner) && isset($display->owner->id)) {
    $cid .= ':' . $display->owner->id;
  }
  $cid .= ':' . $display->did;

  cache_clear_all($cid, 'cache', TRUE);
}

/**
 * Figure out an id for our cache based upon input and settings.
 */
function panels_content_cache_get_id($conf, $display, $args, $contexts, $pane) {
  $id = 'panels_content_cache';

  // This is used in case this is an in-code display, which means did will be something like 'new-1'.
  if (isset($display->owner) && isset($display->owner->id)) {
    $id .= ':' . $display->owner->id;
  }
  $id .= ':' . $display->did;

  if ($pane) {
    $id .= ':' . $pane->pid;
  }

  if (user_access('view pane admin links')) {
    $id .= ':admin';
  }

  switch ($conf['granularity']) {
    case 'args':
      foreach ($args as $arg) {
        $id .= ':' . $arg;
      }
      break;

    case 'context':
      if (!is_array($contexts)) {
        $contexts = array($contexts);
      }
      foreach ($contexts as $context) {
        if (isset($context->argument)) {
          $id .= ':' . $context->argument;
        }
      }
  }
  if (module_exists('locale')) {
    global $language;
    $id .= ':' . $language->language;
  }

  if($pane->configuration['use_pager'] == 1) {
    $id .= ':p' . check_plain($_GET['page']);
  }

  return $id;
}

function panels_content_cache_settings_form($conf, $display, $pid) {
  $options = array_merge(array('none' => 'none'), drupal_map_assoc(array(15, 30, 60, 120, 180, 240, 300, 600, 900, 1200, 1800, 3600, 7200, 14400, 28800, 43200, 86400, 172800, 259200, 345600, 604800), 'format_interval'));
  $form['lifetime'] = array(
    '#title' => t('Lifetime'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => $conf['lifetime'],
    '#description' => t('The cache lifetime is the minimum amount of time that will elapse before the cache is emptied and recreated. If set to none the
    cache will not be recreated unless a content update triggers a rebuild.')
  );

  $form['content_types'] = array(
    '#title' => t('Node types'),
    '#description' => t('Checks for new or updated nodes of any of the selected types.'),
    '#type' => 'checkboxes',
    '#options' => node_type_get_names(),
    '#default_value' => $conf['content_types'],
    '#required' => TRUE,
  );

  $form['granularity'] = array(
    '#title' => t('Granularity'),
    '#type' => 'select',
    '#options' => array(
      'args' => t('Arguments'),
      'context' => t('Context'),
      'none' => t('None'),
    ),
    '#description' => t('If "arguments" are selected, this content will be cached per individual argument to the entire display; if "contexts" are selected, this content will be cached per unique context in the pane or display; if "neither" there will be only one cache for this pane.'),
    '#default_value' => $conf['granularity'],
  );

  return $form;
}
