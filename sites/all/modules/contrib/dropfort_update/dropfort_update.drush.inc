<?php

/**
 * Implementation of hook_drush_command().
 */
function dropfort_update_drush_command() {
  $items = array();

  $items['dropfort-register'] = array(
    'description' => "Prints the Dropfort registration link for this site.",
    'arguments' => array(),
    'options' => array(),
    'aliases' => array('dfr'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  return $items;
}


/**
 * Drush make download method for Dropfort
 *
 * @see https://github.com/drush-ops/drush/blob/6.x/commands/make/make.download.inc
 */
function make_download_dropfort($name, $type, $download, $download_location) {
  $options = drush_get_merged_options();
  $full_project_version = $name;

  if (!empty($download['full_version'])) {
    $full_project_version .= $download['full_version'];
  }

  // Set the default download status url for projects
  $dropfort_url = isset($options['dropfort_url']) ? $options['dropfort_url'] : 'https://app.dropfort.com';

  $download += array(
    'status url' => $dropfort_url . '/fserver/release-history',
  );

  $options = array(
    'destination' => dirname($download_location),
    'yes' => TRUE,
    'package-handler' => 'wget',
    'source' => $download['status url'],
    // This is only relevant for profiles, but we always want the variant to
    // be 'profile-only' so we don't end up with extra copies of core.
    'variant' => $type == 'core' ? 'full' : 'profile-only',
    'cache' => TRUE,
  );
  if ($type == 'core') {
    $options['drupal-project-rename'] = basename($download_location);
  }
  if (drush_get_option('no-cache', FALSE)) {
    unset($options['cache']);
  }

  $backend_options = array();
  if (!drush_get_option(array('verbose', 'debug'), FALSE)) {
    $backend_options['integrate'] = TRUE;
    $backend_options['log'] = FALSE;
  }

  // Perform actual download with `drush pm-download`.
  $return = drush_invoke_process('@none', 'pm-download', array($full_project_version), $options, $backend_options);
  if (empty($return['error_log'])) {
    // @todo Report the URL we used for download. See
    // http://drupal.org/node/1452672.
    drush_log(dt('@project downloaded.', array('@project' => $full_project_version)), 'ok');
  }
}

/**
 * Callback for dropfort-register.
 */
function drush_dropfort_update_dropfort_register() {
  if (module_exists('dropfort_update')) {
    module_load_include('inc', 'dropfort_update');
    drush_print(_dropfort_update_site_registration_link(TRUE));
  }
  else {
    drush_set_error("Dropfort Update not installed", dt('You must enable the dropfort_update module for your site before registering with Dropfort.'));
  }
}

/**
 * Try to avoid duplicate declaration issues with Drush
 */
if (!function_exists('drush_dropfort_update_pre_pm_download')) {
  /**
   * Implements drush_hook_pre_COMMAND().
   */
  function drush_dropfort_update_pre_pm_download() {
    $options = drush_get_merged_options();

    $dropfort_update_url = !empty($options['dropfort_url']) ? $options['dropfort_url'] : 'https://app.dropfort.com';
    $token = '';
    $usertoken = !empty($options['dropfort_userauth_token']) ? $options['dropfort_userauth_token'] : '';

    // Only try to load settings from Drupal if it's present
    if (function_exists('variable_get')) {
      $dropfort_update_url = variable_get('dropfort_update_base_url', $dropfort_update_url);
      $token = variable_get('dropfort_update_site_token', '');
    }

    if ($options['source'] and $options['source'] == $dropfort_update_url . '/fserver/release-history') {
      if (!empty($token)) {
        drush_set_option('source', $dropfort_update_url . '/fserver/release-history-auth/' . $token);
      }
      elseif (!empty($usertoken)) {
        drush_set_option('source', $dropfort_update_url . '/fserver/release-history-userauth/' . $usertoken);
      }
      else {
        drush_set_error('DROPFORT_UPDATE_MISSING_AUTH_TOKEN', dt('Unable to find an authentication token to download projects from !url', array('!url'=> $dropfort_update_url)));
      }
    }
  }
}
