<?php
/**
* Implements hook_apps_app_info().
*/
function seotools_apps_app_info() {
  return array(
    'configure form' => 'seotools_apps_app_configure_form',
    //'demo content module' => 'enterprise_blog_content',
  );
}

function seotools_apps_app_configure_form() {
  require_once(drupal_get_path('module', 'seotools') . '/seotools.setup.inc');
  $form = drupal_get_form('seotools_setup_0_form');

  return $form;
}