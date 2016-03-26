<?php
/**
 * @file
 * Administration code for Dismiss module.
 */

/**
 * Implements hook_admin().
 *
 * Dismiss administration settings
 */
function dismiss_admin() {
  $form = array();

  // Development settings fieldset
  $form['development'] = array(
    '#type' => 'fieldset',
    '#title' => 'Development settings',
  );

  // Scope of JS. Header or footer?
  $form['development']['dismiss_scope'] = array(
    '#type'           => 'select',
    '#title'          => t('Load JS for Dismiss in the footer?'),
    '#description'    => t('This script does not perform immediate actions and does not need to be placed in the &lt;head&gt; of the HTML.'),
    '#options'        => array(
      'footer' => t('footer'),
      'header' => t('header'),
    ),
    '#default_value'  => variable_get('dismiss_scope', DISMISS_SCOPE_DEFAULT),
  );

  // Inline JS or extra HTTP request?
  $form['development']['dismiss_inline'] = array(
    '#type'           => 'select',
    '#title'          => t('Load JS for Dismiss inline?'),
    '#description'    => t('The main JS file for Dismiss is very small, so inlining the script is better for performance.'),
    '#options'        => array(
      'inline' => t('inline'),
      'file' => t('file'),
    ),
    '#default_value'  => variable_get('dismiss_inline', DISMISS_INLINE_DEFAULT),
  );

  // Behavior settings fieldset
  $form['behavior'] = array(
    '#type' => 'fieldset',
    '#title' => 'Behavior settings',
  );

  // Option to fade
  $form['behavior']['dismiss_fadeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Length of fadeout wait time (ms)'),
    '#description' => t('The length of time in milliseconds (max 6-digits) Dismiss should wait to automatically fadeout messages. A value of 0 (zero) disables this behavior.'),
    '#size' => 10,
    '#maxlength' => 6,
    '#required' => TRUE,
    '#default_value' => variable_get('dismiss_fadeout', DISMISS_FADEOUT_DEFAULT),
  );

  $form['#validate'][] = 'dismiss_admin_validate';

  return system_settings_form($form);
}

/**
 * Custom validation function for dismiss_admin().
 */
function dismiss_admin_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['dismiss_fadeout'])) {
    form_set_error('fadeout', t('Fadeout value must be numeric.'));
  }
}
