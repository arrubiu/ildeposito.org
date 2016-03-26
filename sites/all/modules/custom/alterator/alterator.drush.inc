<?php

/**
 * Implements hook_drush_help().
 */
function alterator_drush_help($command) {
  switch ($command) {

    case 'drush:eventi-buffer':
      return dt('Check dates for buffer updates');
      break;
  }
}

/**
 * Implements hook_drush_command().
 */
function alterator_drush_command() {
  $items = array();

  $items['eventi-buffer'] = array(
    'description' => dt('Check dates for buffer updates.'),
    'callback' => 'alterator_eventi_buffer',
    'bootstrap' => DRUSH_BOOTSTRAP_MAX,
  );

  return $items;
}



