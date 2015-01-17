<?php
/**
 * @file
 * Variable module integration for the HybridAuth module.
 */

/**
 * Implements hook_variable_info().
 */
function hybridauth_variable_info($options = array()) {
  $variables['hybridauth_widget_title'] = array(
    'type' => 'string',
    'title' => t('HybridAuth widget title', array(), $options),
    'description' => t('Title of the HybridAuth login widget.', array(), $options),
    'default' => 'Or log in with...',
    'localize' => TRUE,
  );
  return $variables;
}
