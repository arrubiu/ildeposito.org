<?php

/**
 * @file
 * Drush integration with Mail signature module.
 */

/**
 * Implements hook_drush_command().
 */
function mail_signature_drush_command() {
  $items = array();

  $items['mail-signature'] = array(
    'description' => 'Control mail signature.',
    'arguments' => array(
      'action' => 'Action to performe (enable or disable).',
    ),
    'examples' => array(
      'drush mail-signature enable' => 'Enable adding signature to mail.',
      'drush mail-signature disable' => 'Disable adding signature to mail.',
    ),
    'required-arguments' => TRUE,
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function mail_signature_drush_help($section) {
  switch ($section) {
    case 'drush:mail-signature':
      return dt('This command will eanble or disable signature to mails.');
  }
}

/**
 * Callback to drush command.
 */
function drush_mail_signature($action) {
  if ($action != 'enable' && $action != 'disable') {
    drush_set_error('You have to use only \'enable\' or \'disable\' arguments');
  }

  else {
    switch ($action) {
      case 'enable':
        if (variable_get('mail_signature_text') == '') {
          drush_set_error('Signature is empty, please first add it');
        }

        else {
          variable_set('mail_signature_enabled', TRUE);
          drush_log('Mail signature is now enabled', 'ok');
          if (substr(variable_get('mail_signature_text'), 0, 2) == '--') {
            drush_log('The signature starts with \'--\', please check it!', 'warning');
          }
        }
        break;

      case 'disable':
        variable_set('mail_signature_enabled', FALSE);
        drush_log('Mail signature is now disabled', 'ok');
        break;
    }
  }
}
