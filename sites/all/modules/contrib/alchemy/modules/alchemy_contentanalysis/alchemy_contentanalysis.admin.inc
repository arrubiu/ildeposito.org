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
function alchemy_contentanalysis_admin_settings($form, &$form_state) {

  $options = alchemy_contentanalysis_get_types();
  $form['alchemy_contentanalysis_defaulttypes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Default data types'),
    '#options' => $options,
    '#default_value' => variable_get('alchemy_contentanalysis_defaulttypes', alchemy_contentanalysis_get_types(TRUE)),
    '#description' => t('Alchemy provides an array of data it can extract from content. Use the above checkboxes to select which ones you want the content analyzer to perform by default.'),
  );

  $form['alchemy_contentanalysis_defaultusecache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use cached data if available.'),
    '#default_value' => variable_get('alchemy_contentanalysis_defaultusecache', ''),
    '#description' => t('The responses from Alchemy are cached. If you want to enable fetching data from cache rather than fetching from the Alchemy API, check the above box.'),
    '#prefix' => '<div id="alchemy_contentanalysis_cache">',
    '#suffix' => '</div>',
  );

  return system_settings_form($form);
}
