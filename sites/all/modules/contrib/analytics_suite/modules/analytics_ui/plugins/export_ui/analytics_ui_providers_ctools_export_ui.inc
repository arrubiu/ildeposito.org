<?php

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'analytics_provider',  // As defined in hook_schema().
  'access' => 'configure analytics',  // Define a permission users must have to access these pages.

  // Define the menu item.
  'menu' => array(
    'menu prefix' => 'admin/config/search/analytics',
    'menu item' => 'providers',
    'menu title' => 'Providers',
    'menu description' => 'Administer analytics providers.',
  ),
    
  'handler' => 'analytics_ui_providers_ctools_export_ui',

  // Define user interface texts.
  'title singular' => t('provider'),
  'title plural' => t('providers'),
  'title singular proper' => t('Analytics provider'),
  'title plural proper' => t('Analytics providers'),

  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'analytics_ui_provider_form',
    'validate' => 'analytics_ui_provider_form_validate',
    'submit' => 'analytics_ui_provider_form_submit',
  ),
);