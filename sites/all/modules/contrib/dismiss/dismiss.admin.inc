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

  return system_settings_form($form);
}
