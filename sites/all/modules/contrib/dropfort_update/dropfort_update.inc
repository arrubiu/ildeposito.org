<?php
/**
 * @file
 * Function implementations
 */

/**
 * Track site keys
 *
 * @param string $site_key
 *  Site key to track
 * @param boolean $active [optional]
 *  State of the key
 * @param int $last_used [optional]
 *  Timestamp last used
 */
function _dropfort_update_track_site_keys($site_key, $active = NULL, $last_used = NULL) {
  if (!empty($site_key)){
    $exists = dropfort_update_site_key_exists($site_key);

    $key_data = new stdClass();
    $key_data->site_key = $site_key;
    $key_data->last_used = is_null($last_used) ? time() : $last_used;

    // Only set the active state if specified. Otherwise fallback to the
    // schema default.
    if (is_bool($active)) {
      // Bools don't map to a tinyint field during update
      // so we cast to int
      $key_data->active = (int)$active;
    }

    if ($exists) {
      // Update the last used time
      unset($key_data->site_key);

      // We don't use drupal_write_record here cause it just doesn't work for some stupid reason...
      //drupal_write_record('dropfort_update_site_key', $key_data, array('site_key' => $site_key));
      $update_data = (array) $key_data;

      db_update('dropfort_update_site_key')
        ->fields($update_data)
        ->condition('site_key', $site_key)
        ->execute();
    }
    else {
      drupal_write_record('dropfort_update_site_key', $key_data);
    }
  }
}

/**
 * Try to detect if HTTPS was indeed used to connect
 */
function _dropfort_update_detect_https() {
  global $is_https;
  // This may not be perfect but might be the best possible from within PHP
  if (!empty($_SERVER['HTTPS']) and $_SERVER['HTTPS'] !== 'off' or $_SERVER['SERVER_PORT'] == 443 or $is_https) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Generates a new site key and clears the appropriate caches
 */
function _dropfort_update_generate_new_site_token() {
  // Generate the new key when requested
  variable_set('dropfort_update_site_token', _dropfort_update_random_key(64));
  // Clear update data since it would have stored a cached copy of the old key
  module_load_include('inc', 'update', 'update.compare');
  _update_cache_clear('update_project_projects');
  _update_cache_clear('update_project_data');
}

/**
 * Wrapper function for generating a random key
 */
function _dropfort_update_random_key($byte_count = 32) {
  if (VERSION < 7.24) {
    return drupal_hash_base64(drupal_random_bytes($byte_count));
  }
  else {
    return drupal_random_key($byte_count);
  }
}

/**
 * System status reporting
 *
 * @see system_status().
 */
function _dropfort_update_system_status($check = FALSE) {
  $requirements = &drupal_static(__FUNCTION__);

  if (!isset($requirements) or empty($requirements)) {
    global $base_url;

    // Load .install files
    include_once DRUPAL_ROOT . '/includes/install.inc';
    drupal_load_updates();

    // Check run-time requirements and status information.
    $requirements = module_invoke_all('requirements', 'runtime');
    usort($requirements, '_system_sort_requirements');

    if ($check) {
      $requirements = drupal_requirements_severity($requirements) == REQUIREMENT_ERROR;
    }
    else {
      $time = time();
      // Add the time we checked at
      foreach ($requirements as $key => $requirement) {
        $requirements[$key]['lastchecked'] = $time;
        $requirements[$key] = str_replace('href="/', 'href="' . $base_url . '/', $requirements[$key]);
        $requirements[$key] = str_replace("href='/", "href='/" . $base_url . '/', $requirements[$key]);
      }
    }
    // MySQL import might have set the uid of the anonymous user to autoincrement
    // value. Let's try fixing it. See http://drupal.org/node/204411
    db_update('users')->expression('uid', 'uid - uid')->condition('name', '')->condition('pass', '')->condition('status', 0)->execute();
  }

  return $requirements;
}

/**
 * Update status alter callback
 *
 * @see dropfort_update_update_status_alter().
 * @see hook_update_status_alter().
 */
function _dropfort_update_update_status_alter(&$projects) {
  global $base_url;
  $cache_response = FALSE;
  // List of paths on the site to display a notification to the user.
  $paths = array(
    'admin/reports/updates',
    'admin/reports/updates/update',
    'admin/modules/update',
  );

  if ((in_array(current_path(), $paths) or drupal_is_cli()) and variable_get('dropfort_update_show_moderation_notice', FALSE)) {
    if (user_access('administer dropfort_update')) {
      $site_link = variable_get('dropfort_update_base_url', DROPFORT_UPDATE_BASE_URL) . '/site/' . dropfort_update_get_private_key();
      drupal_set_message(t('Available updates are being moderated. !report', array('!report' => l(t('View release report'), $site_link, array('external' => TRUE)))), 'info');
    }
    else {
      drupal_set_message(t('Available updates are being moderated by a site administrator.'), 'info');
    }
  }

  $cache_key = md5(implode(array_keys($projects)));

  $projects_alter = &drupal_static(__FUNCTION__ . $cache_key);

  if (!isset($projects_alter)) {
    if ($cache = cache_get("dropfort_update_update_status:$cache_key", 'cache')) {
      $projects_alter = $cache->data;
    }
    else {
      cache_clear_all('dropfort_update_update_status:', 'cache', TRUE);
      // Prepare data for the request
      // @see _update_process_fetch_task().
      $site_key   = dropfort_update_get_private_key();
      $site_token = variable_get('dropfort_update_site_token', '');
      $data       = array(
        'projects' => $projects,
        'site_key' => $site_key,
        'site_token' => $site_token,
        'api' => '7.x',
      );
      // Build HTTP request to retrieve filtered status list
      $request = array(
        'headers' => array(
          'Content-Type' => 'application/json',
          'Accept' => 'application/json',
        ),
        'data' => drupal_json_encode($data),
        'method' => 'POST',
        'max_redirects' => 3,
        // We set a lower timeout since we don't want the user waiting for the page too long
        'timeout' => 30,
      );
      $url = variable_get('dropfort_update_base_url', DROPFORT_UPDATE_BASE_URL) . '/updates/list/filter_updatestatus';
      $response = drupal_http_request($url, $request);

      // We don't check if the the data here is empty or not since we want the
      // fallback behavior to be having no update status information at all.
      if (intval($response->code) == 200) {
        $response_projects = drupal_json_decode($response->data);
        if (is_array($response_projects)) {
          $projects_alter = $response_projects;
        }
        // Clean up some variables
        unset($response_projects);
        $cache_response = TRUE;
      }
      elseif (intval($response->code) == 304) {
        // The list is unmodified since last time, use cached value
        // @todo
      }
      else {
        // Set the list of projects to blank
        if ((in_array(current_path(), $paths) or drupal_is_cli()) and variable_get('dropfort_update_show_moderation_notice', FALSE)) {
          drupal_set_message(t('Unable to load moderation data. Update data has been disabled temporarily. See !url settings for details', array('!url' => l('Dropfort Update', 'admin/config/system/dropfort/update'))), 'error');
        }
        watchdog('dropfort_update', 'Failed to load moderation data from @url @code, @status_message', array('@url' => $url, '@code' => $response->code, '@status_message' => $response->status_message), WATCHDOG_ERROR);
        // @todo set the status to 'no updates available' instead of just blanking them
        // @todo set the status for all projects to UPDATE_NOT_FETCHED
        $projects_alter = array();

        // Mark the site key as inactive
        dropfort_update_track_site_keys($site_key, FALSE);
      }

      if ($cache_response) {
        // Cache the result for 1 day
        cache_set("dropfort_update_update_status:$cache_key", $projects_alter, 'cache', variable_get('dropfort_update_cache_lifetime', 86400));
      }
    }
  }

  if (!is_null($projects_alter)) {
    $projects = $projects_alter;
  }
}