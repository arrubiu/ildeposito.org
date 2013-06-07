<?php

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'analytics_tag',  // As defined in hook_schema().
  'access' => 'configure analytics',  // Define a permission users must have to access these pages.

  // Define the menu item.
  'menu' => array(
    'menu prefix' => 'admin/config/search/analytics',
    'menu item' => 'tags',
    'menu title' => 'Tags',
    'menu description' => 'Administer analytics tags.',
  ),
    
  'handler' => 'analytics_ui_tags_ctools_export_ui',

  // Define user interface texts.
  'title singular' => t('tag'),
  'title plural' => t('tags'),
  'title singular proper' => t('Analytics tag'),
  'title plural proper' => t('Analytics tags'),

  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'analytics_ui_tag_form',
    'validate' => 'analytics_ui_tag_form_validate',
    'submit' => 'analytics_ui_tag_form_submit',
  ),
);