<?php
/**
 * @file
 * Linkit views plugin.
 */

$plugin = array(
  'ui_title' => t("Views"),
  'ui_description' => t('Extend Linkit with views support.'),
  'handler' => array(
      'class' => 'LinkitViewsPlugin',
      'file' => 'linkit_views.class.php',
  ),
);