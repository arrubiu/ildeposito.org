<?php

/**
 * @file
 * Provides page callback functions for DrupalGap.
 */

/**
 * Returns the HTML for the DrupalGap module status page.
 */
function drupalgap_status() {
  // Add drupalgap javascript settings to Drupal settings.
  drupal_add_js(array('drupalgap' => array('services_endpoint_default' => base_path() . '?q=drupalgap/')), 'setting');

  // Add drupalgap javascript.
  drupal_add_js(drupal_get_path('module', 'drupalgap') . '/drupalgap.js');

  // Set div id for system connect status message box.
  $div_id = 'drupalgap-system-connect-status-message';

  // Build more info text and help link string.
  $msg = t('Please refer to the <a href="@help_page">DrupalGap Module Help Page</a> for more information.', array('@help_page' => url('admin/help/drupalgap')));

  // Create output fieldsets.
  $output = array(
    'drupalgap_system_connect_status' => array(
      '#theme' => 'fieldset',
      '#title' => t('System Connect Status'),
      '#markup' => '<div id="' . $div_id . '">&nbsp;</div>',
    ),
    'drupalgap_information' => array(
      '#theme' => 'fieldset',
      '#title' => t('More Information'),
      '#markup' => "<p>$msg</p>",
    ),
  );

  return $output;
}
