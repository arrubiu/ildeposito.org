<?php
/**
 * @file
 *   Provides a "null" mapping to map vcs users to Drupal users.
 */
$plugin = array(
  'title' => t('None (no mapping)'),
  'mapper' => array(
    'class' => 'VersioncontrolUserMapperNone',
  ),
);
