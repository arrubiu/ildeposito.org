<?php
/**
 * @file * Admin include file.
 */

/**
 * @file
 * Admin include file.
 */

/**
 * Displays the form for the standard settings tab.
 *
 * @return
 *   array A structured array for use with Forms API.
 */
function alchemy_admin_settings($form, &$form_state) {

  $apikey = variable_get('alchemy_apikey', '');
  $form['alchemy_apikey'] = array(
    '#type' => 'textfield',
    '#title' => t('Alchemy API Key'),
    '#default_value' => $apikey,
    '#description' => t('You need an API key to use the Alchemy API service. !alchemy_link.', 
      array(
      '!alchemy_link' => l(t('Get an Alchemy API key here'), 'http://www.alchemyapi.com/api/register.html', array('attributes' => array('target', 'alchemy'))),
    )
    ),
  );
  $form['alchemy_usecurl'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use CURL class'),
    '#default_value' => variable_get('alchemy_usecurl', 0),
    '#description' => t('By default fopen is used to connect to the AlchemyAPI. You can change this to use CURL instead. If you get an "Error making API call" error, try changing this setting.'),
  );

  return system_settings_form($form);
}
