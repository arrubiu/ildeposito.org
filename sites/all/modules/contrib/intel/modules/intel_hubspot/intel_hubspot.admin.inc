<?php
/**
 * @file * Admin include file. 
*/

/** 
 * Displays the form for the standard settings tab.
 * 
 * @return array 
 * A structured array for use with Forms API. 
*/ 
function intel_hubspot_admin_config($form, $form_state) {
  $form = array_merge($form, intel_hubspot_admin_config_form());
  return system_settings_form($form);
}

function intel_hubspot_admin_config_form() {
  $form = array();
  $form['intel_hubspot_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => variable_get('intel_hubspot_api_key', ''),
    '#description' => t('Enter your Api key from HubSpot.'),
  );  
  return $form;
}