<?php

/** @file
 * Extra stuffs for privileged user
 * By jcisio
 */

/**
 * Menu callback; hide a comment.
 *
 * @param $cid
 *   The comment do be hidden.
 */
function hidden_comment_hide($cid = NULL) {
  $comment = db_query('SELECT * FROM {comment} WHERE cid = :cid', array(':cid' => $cid))->fetchObject();
  $hc = db_query('SELECT * FROM {comment_hide} WHERE cid = :cid', array(':cid' => $cid))->fetchObject();

  $output = '';

  if (is_object($hc)) {
    drupal_set_message(t('Comment already hidden.'));
  }
  else {
    $output = drupal_get_form('hidden_comment_confirm_hide', $comment);
  }

  return $output;
}

/**
 * Form builder; Builds the confirmation form for deleting a single comment.
 */
function hidden_comment_confirm_hide($form, &$form_state, $comment) {
  $form = array();
  drupal_add_js(drupal_get_path('module', 'hidden_comment') . '/hidden_comment.js');
  $default_reasons = array_filter(explode("\n", variable_get('hidden_comment_default_reasons', '')));

  $form['#comment'] = $comment;
  $form['default_reasons'] = array(
    '#type' => 'select',
    '#title' => t('Quick select a reason'),
    '#options' => $default_reasons,
    '#description' => t('Fill the below reason textbox with one of the default reason.'),
  );
  $form['reason'] = array(
    '#type' => 'textfield',
    '#title' => t('Reason'),
    '#default_value' => $default_reasons[0],
    '#size' => 50,
    '#maxlength' => 255,
    '#description' => t('Give a reason for this action'),
  );

  return confirm_form(
    $form,
    t('Are you sure you want to hide the comment %title?', array('%title' => $comment->subject)),
    'node/' . $comment->nid,
    t('This action can be reverted by the unhide functionality. Not be scared!'),
    t('Hide'),
    t('Cancel'),
    'hidden_comment_confirm_hide');
}

/**
 * Process comment_confirm_hide form submissions.
 */
function hidden_comment_confirm_hide_submit($form, &$form_state) {
  global $user;
  $comment = $form['#comment'];

  db_insert('comment_hide')
  ->fields(array(
    'cid' => $comment->cid,
    'nid' => $comment->nid,
    'changed' => REQUEST_TIME,
    'uid' => $user->uid,
    'reason' => $form_state['values']['reason'],
  ))
  ->execute();

  $form_state['redirect'] = "node/$comment->nid";
}

/**
 * Menu callback; hide a comment.
 *
 * @param $cid
 *   The comment do be unhidden.
 */
function hidden_comment_unhide($cid = NULL) {
  $comment = db_query('SELECT * FROM {comment} WHERE cid = :cid', array(':cid' => $cid))->fetchObject();
  $hc = db_query('SELECT * FROM {comment_hide} WHERE cid = :cid', array(':cid' => $cid))->fetchObject();

  $output = '';

  if (is_object($hc)) {
    $output = drupal_get_form('hidden_comment_confirm_unhide', $comment);
  }
  else {
    drupal_set_message(t('Comment is not hidden.'));
  }

  return $output;
}

/**
 * Form builder; Builds the confirmation form for unhideing a single comment.
 */
function hidden_comment_confirm_unhide($form, &$form_state, $comment) {
  $form = array();
  $form['#comment'] = $comment;
  return confirm_form(
    $form,
    t('Are you sure you want to unhide the comment %title?', array('%title' => $comment->subject)),
    'node/' . $comment->nid,
    t('Don\'t be scare!'),
    t('Unhide'),
    t('Cancel'),
    'hidden_comment_confirm_unhide');
}

/**
 * Process comment_confirm_unhide form submissions.
 */
function hidden_comment_confirm_unhide_submit($form, &$form_state) {
  $comment = $form['#comment'];

  db_delete('comment_hide')
  ->condition('cid', $comment->cid)
  ->execute();

  $form_state['redirect'] = "node/$comment->nid";
}

/**
 * Form for configuring the module
 */
function hidden_comment_settings_form($form, &$form_state) {
  $form = array();

  $form['hidden_comment_default_reasons'] = array(
    '#type' => 'textarea',
    '#title' => t('Default reasons'),
    '#default_value' => variable_get('hidden_comment_default_reasons', ''),
    '#description' => t('Enter one reason per line.'),
  );

  return system_settings_form($form);
}
