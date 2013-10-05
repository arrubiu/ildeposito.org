<?php

/**
 * @file
 * Callbacks and functions for Panels cache flushing.
 */

/**
 * Panels clear cache callback.
 */
function ui_cache_clear_panels_callback($task_name, $handler_name) {
  ctools_include('plugins', 'panels');
  // Load Page Manager task.
  $task = page_manager_get_task($task_name);
  // Load Panels handler.
  // @todo Research what is subtask here.
  $subtask_id = '';
  $handler = page_manager_load_task_handler($task, $subtask_id, $handler_name);
  // Load panels/plugins/task_handlers/panel_context.inc
  ctools_get_plugins('page_manager', 'task_handlers', 'panel_context');

  // Get panel display.
  $display = panels_panel_context_get_display($handler);
  $display->context = array();
  $display->args = array();

  // Set additional data which may be used in cache plugins.
  $display->css_id = $handler->conf['css_id'];
  $task_name_prepared = page_manager_make_task_name($handler->task, $handler->subtask);
  $display->cache_key = 'panel_context:' . $task_name_prepared . ':' . $handler->name;

  // Try to clear with API for Panels cache plugins.
  panels_clear_cached_content($display);
  // Manualy clear caches for cache plugins with known problems.
  _ui_cache_clear_panels_clear_cached_content($display);

  drupal_set_message(t('Panel %panel cache cleared.', array('%panel' => $task['title'])));

  ui_cache_clear_page();
  drupal_goto();
}

/**
 * Collection of hacks for different panels cache plugins known problems.
 */
function _ui_cache_clear_panels_clear_cached_content($display) {
  foreach ($display->content as $pane) {
    if (empty($pane->cache['method'])) {
      continue;
    }

    $cid = '';
    $conf = $pane->cache['settings'];
    $method = $pane->cache['method'];

    if ($method == 'simple' && !is_numeric($display->did)) {
      // Problem solved: Simple cache can't be cleared for in-code displays.
      $cid = panels_simple_cache_get_id($conf, $display, array(), array(), $pane);
      // Trim cid to clear multiple panes and ignore granularity.
      $cid = implode(':', array_slice(explode(':', $cid, 4), 0, 3));
      cache_clear_all($cid, 'cache', TRUE);
    }
    elseif ($method == 'panels_hash_cache') {
      // Problem solved: Panels Hash Cache can't be cleared with API.
      $cid = panels_hash_cache_get_id($conf, $display, array(), array(), $pane);
      // Trim cid to clear multiple panes and ignore granularity.
      $cid = implode('-', array_slice(explode('-', $cid, 5), 0, 4));

      cache_clear_all($cid, 'panels_hash_cache', TRUE);
    }
  }
}
