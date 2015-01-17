<?php
/**
 * @file
 * This plugin contains the main documentation of how to make an event
 * processor plugin.
 * It does not really provide any functionallity.
 */

$plugin = array(

  // The versioncontrol system machine name as the backend declares.
  'vcs' => VERSIONCONTROL_PLUGIN_VCS_AGNOSTIC,

  // This title is going to be shown on the repository edition, for the
  // user to identify the plugin.
  'title' => t('Empty event processor'),

  'handler' => array(
    'class' => 'VersioncontrolEventProcessorNone',
    'file' => 'VersioncontrolEventProcessorNone.inc',
    'path' => drupal_get_path('module', 'versioncontrol') . '/includes/plugins/event_processor',
  ),
);
