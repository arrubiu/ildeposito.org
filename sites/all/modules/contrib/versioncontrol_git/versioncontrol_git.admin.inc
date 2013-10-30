<?php
/**
 * @file
 * Git backend for Version Control API - Provides Git commit information and
 * account management as a pluggable backend.
 *
 * Copyright 2008 by Jimmy Berry ("boombatower", http://drupal.org/user/214218)
 * Copyright 2009 by Cornelius Riemenschneider ("CorniI", http://drupal.org/user/136353)
 */

/**
 * Implements hook_form_alter(): Add elements to various
 * administrative forms that the Version Control API provides.
 */
function versioncontrol_git_form_alter(&$form, &$form_state, $form_id) {
  if ($form['#id'] == 'versioncontrol-repository-form' && $form['#vcs'] == 'git') {
    versioncontrol_git_repository_admin_form_alter($form, $form_state, $form_id);
  }
}

/**
 * Add Git specific elements to the add/edit repository form.
 */
function versioncontrol_git_repository_admin_form_alter(&$form, &$form_state, $form_id) {
  $repository = isset($form['#repository'])? $form['#repository']: null;

  $form['versioncontrol_git'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );
  $form['repository_information']['root']['#description'] = t('An absolute path to your bare Git repository, e.g: (/home/user/projects/myrepository.git).');
  $form['#validate'][] = 'versioncontrol_git_repository_validate';
}

/**
 * Validation of the repository root.
 */
function versioncontrol_git_repository_validate($form, &$form_state) {
  // create a non-in-db-repo just for the validation
  $repo = new VersioncontrolGitRepository(new VersioncontrolGitBackend());
  $repo->root = $form_state['values']['root'];
  if (!$repo->isValidGitRepo()) {
    form_set_error('root', t('The repository at <code>@root</code> is not a valid Git bare repository.', array('@root' => $form_state['values']['root'])));
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function versioncontrol_git_form_versioncontrol_admin_settings_alter(&$form, &$form_state) {
  $form['versioncontrol_git'] = array(
    '#type' => 'fieldset',
    '#title' => t('Git backend configuration'),
    '#description' => t('Options to modify how Git backend behaves.'),
    '#collapsible' => TRUE,
  );
  $form['versioncontrol_git']['versioncontrol_git_binary_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Git binary path'),
    '#default_value' => variable_get('versioncontrol_git_binary_path', 'git'),
    '#description' => t('Path to the git program to be used. By default it use <code>git</code> as it assumes the binary is on the <code>$PATH</code>.'),
    '#element_validate' => array('versioncontrol_git_form_versioncontrol_admin_settings_validate_path'),
  );
  $form['#submit'][] = 'versioncontrol_git_form_versioncontrol_admin_settings_submit';
}

function versioncontrol_git_form_versioncontrol_admin_settings_validate_path($element) {
  if ($errors = _versioncontrol_git_binary_check_path($element['#value'])) {
    form_set_error($element['#parents'][0], implode('<br />', $errors));
    return FALSE;
  }
  return TRUE;
}

/**
 * Submit function for our alter to versioncontrol_admin_settings form.
 */
function versioncontrol_git_form_versioncontrol_admin_settings_submit(&$form, &$form_state) {
  variable_set('versioncontrol_git_binary_path', $form_state['values']['versioncontrol_git_binary_path']);
}
