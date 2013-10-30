<?php
/**
 * @file
 *   Defines a plugin synchronizer for use in tests.
 */
$plugin = array(
  'title' => t('Test synchronizer'),
  'worker' => array(
    'class' => 'VersioncontrolTestRepositoryHistorySynchronizerDefault',
  ),
);
