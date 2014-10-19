<?php

/**
 * @file
 * Admin include file.
 */

/**
 * Define the admin form.
 *
 */
function captcha_free_settings() {
  $form['captcha_free_secret_salt'] = array(
    '#title' => t('Secret Salt'),
    '#type' => 'textfield',
    '#default_value' => variable_get('captcha_free_secret_salt', 'secret salt'),
    '#description' => t('Change this phrase to make your \'hash\' or token unique.<br />
      Use: Any short text string will do under 15 characters.'),
    '#required' => TRUE,
    '#size' => 15,
    '#maxlength' => 15,
  );
  $form['captcha_free_time_out'] = array(
    '#title' => t('Form Timeout'),
    '#type' => 'textfield',
    '#default_value' => variable_get('captcha_free_time_out', 10),
    '#description' => t('The number of minutes on the page that the form will be usable.<br />
      The default is 10 minutes, but I use 3 minutes for testing. It\'s your choice.<br />
      Use: Up to 2 digits allowed here.'),
    '#required' => TRUE,
    '#size' => 2,
    '#maxlength' => 2
  );
  $options = array(
    'contact_site_form' => 'Site-wide Contact Form',
    'contact_personal_form' => 'User Contact Form',
    'user_register_form' => 'User Register Form',
    'comment' => 'All Comment Forms',
    'webform' => 'Webforms (All)',
    'user_pass' => 'Password Request Form',
 );
  $form['protect_forms'] = array(
    '#title' => t('Forms to protect'),
    '#type' => 'checkboxes',
    '#default_value' => variable_get('captcha_free_form_ids', array('user_register_form')),
    '#description' => t('Select one or more from the list. Start with the User Register Form<br /> and add other forms as they start being targeted by bots.<br />If you have multiple forms on a page the module will only protect one,<br />but this is not normally a problem.'),
    '#options' => $options,
    '#weight' => 20,
    '#required' => TRUE,
  );
  $form['#validate'][] = 'captcha_free_admin_validate';
  $form['#submit'][] = 'captcha_free_admin_submit';
  return system_settings_form($form);
}