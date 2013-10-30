<?php
/**
 * @file
 *   Defines account vcs_auth plugin.
 */
$plugin = array(
  'title' => t('Account (restricted write access)'),
  'handler' => array(
    'class' => 'VersioncontrolAuthHandlerMappedAccounts',
  ),
);
