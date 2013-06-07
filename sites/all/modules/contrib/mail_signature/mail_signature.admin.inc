<?php

/**
 * @file
 * Admin callbacks for Mail Signature module.
 */

/**
 * Form builder; Configure the Mail Signature settings.
 */
function mail_signature_settings_form($form) {
  module_load_include('inc', 'mail_signature');

  $form['#validate'][] = 'mail_signature_settings_form_validate';

  $form['mail_signature_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable mail signature'),
    '#default_value' => variable_get('mail_signature_enabled'),
    '#description' => t('Check to add signature to every mail.'),
  );

  $form['mail_signature_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Text signature'),
    '#default_value' => variable_get('mail_signature_text'),
    '#description' => t("The system will add automatically the separator '--' before the signature,
      so don't add it here or it will added two times."),
  );

  if (module_exists('token')) {
    $form['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['token_help']['help'] = array(
      '#theme' => 'token_tree',      
      '#token_types' => array('site'),
    );
  }  

  if (variable_get('mail_signature_mail') != '') {
    variable_del('mail_signature_mail');
  }

  $form['mail_signature_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Send mail to test signature'),
    '#default_value' => variable_get('mail_signature_mail'),
    '#description' => t('If you want to try the signature add here an email address to send a message.'),
  );

  return system_settings_form($form);
}

/**
 * Function to validate values from the settings form.
 */
function mail_signature_settings_form_validate($form, &$form_state) {
  module_load_include('inc', 'mail_signature');

  if (substr($form_state['values']['mail_signature_text'], 0, 2) == '--') {
    drupal_set_message(t('Attenction, the signature starts with "--". This module automatically adds the separator to every mail, so please remove it from the text.'), 'warning');
  }

  // Perform a basic check for HTML characters in the strings to remove field.
  if ($form_state['values']['mail_signature_enabled'] == 1 && $form_state['values']['mail_signature_text'] == '') {
    form_set_error('mail_signature_text', t('To enable signature you have to add a signature text.'));
  }

  elseif ($form_state['values']['mail_signature_enabled'] == 1 && $form_state['values']['mail_signature_text'] != '') {
    drupal_set_message(t('Now signature will be added to every mail.'));

    // Validation control to check test mail.
    if ($form_state['values']['mail_signature_mail'] != '') {
      if (valid_email_address($form_state['values']['mail_signature_mail'])) {
        global $language;
        $message['subject'] = t('Mail signature - Test mail');
        $message['body'] = array(t('This is a test mail to show how your signature is renderd on an email message.'));
        drupal_mail('mail_signature', 'mail-test', $form_state['values']['mail_signature_mail'], $language, $message);
        drupal_set_message(t('The message have  been sent to @email.', array('@email' => $form_state['values']['mail_signature_mail'])));
      }

      else {
        drupal_set_message(t('The email address is not valid: @email.', array('@email' => $form_state['values']['mail_signature_mail'])), 'warning');
      }
    }
  }
}
