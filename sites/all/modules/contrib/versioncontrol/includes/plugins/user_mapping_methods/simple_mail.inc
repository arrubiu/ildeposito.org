<?php
/**
 * @file
 *   Defines the simple mail method of locating a user.
 */
$plugin = array(
  'title' => t('Map using Drupal user email'),
  'mapper' => array(
    'class' => 'VersioncontrolUserMapperSimpleMail',
  ),
);
