<?php

/**
 * @file
 * Page callbacks contact forms.
 */

function contact_entityform_site_form() {
  $site_form = _contact_entityform_get_site_form();
  if (empty($site_form)) {
    //This shouldn't have happened because contact_entityform_access should have prevented it.
    watchdog('contact_entityform', 'Site-wide form does not exist', WATCHDOG_ERROR);
    drupal_set_message(t('Sorry there has been an error.'), 'warning');
    return '';
  }
  module_load_include('inc', 'entityform', 'entityform.admin');
  return entityform_form_wrapper(entityform_empty_load($site_form));
}

/**
 * Output entityform for account
 * @todo Connect submitted entityform to account being contacted
 * @param $account
 */
function contact_entityform_user_form($account) {
  $enityform_type_name = _contact_entityform_get_form_for_account($account);
  module_load_include('inc', 'entityform', 'entityform.admin');
  drupal_set_message(t('Please fill out the form below to contact') . ' ' . theme('username', array('account' => $account)));
  $entityform = entityform_empty_load($enityform_type_name);
  $entityform->contactee = $account;
  return entityform_form_wrapper($entityform);
}