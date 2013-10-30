<?php
/**
 * @file
 *   Defines the free for all unrestricted plugin.
 */
$plugin = array(
  'title' => t('Free For All (unrestricted write access)'),
  'handler' => array(
    'class' => 'VersioncontrolAuthHandlerFFA',
  ),
);
