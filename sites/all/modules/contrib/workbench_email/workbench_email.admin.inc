<?php
/**
 * @file
 * Administrative forms for Workbench Email Module.
 */

/**
 * Form for administering the email content.
 *
 * Administrators can use this form to add, update, delete emails.
 *
 * @param array $form
 *   The form array
 *
 * @param array $form_state
 *   The form_state array
 *
 * @return form
 *   Returns the form array
 */
function workbench_email_form($form, &$form_state) {
  $workbench_emails = workbench_email_get();
  $state_labels = workbench_moderation_state_labels();
  foreach ($workbench_emails as $transition_label => $email_transition_set) {
    $state_label = $email_transition_set;
    $transition = array_shift($state_label);
    $transition_title = t(ucwords($state_labels[$transition->from_name] .' To '.$state_labels[$transition->to_name]));
    $form[$transition_label] = array(
      '#type' => 'fieldset',
      '#title' => check_plain($transition_title),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    foreach ($email_transition_set as $rid => $email_transition) {
      $subject = $email_transition->subject;
      $message = $email_transition->message;
      $role = user_role_load($rid);
      $params['rid'] = $rid;
      $params['role'] = $role->name;
      $params['from_state'] = $email_transition->from_name;
      $params['to_state'] = $email_transition->to_name;

      $form[$transition_label][$rid] = array(
        '#type' => 'fieldset',
        '#title' => check_plain(t("Email @role_name",
                                  array('@role_name' => ucwords($role->name)))),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      $form[$transition_label][$rid]['subject'] = array(
        '#type' => 'textfield',
        '#default_value' => $subject,
        '#title' => t('Subject'),
        '#maxlength' => 255,
      );

      $form[$transition_label][$rid]['message'] = array(
        '#type' => 'textarea',
        '#default_value' => $message,
        '#title' => t('Message'),
        '#size' => 30,
      );
    }
  }

  if ($workbench_emails) {
    $form['#tree'] = TRUE;

    $form['token_set'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available Tokens'),
      '#collapsible' => TRUE,
    );

    $form['token_set']['tokens'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('node', 'user'),
      '#click_insert' => TRUE,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save Configuration'),
    );
  }
  else {
    drupal_set_message(t('No email transitions have been defined yet. Visit the
                         <a href="@url"> email transition configuration page</a>',
                      array(
                        '@url' =>
                        url('admin/config/workbench/moderation/email-transitions'))), 'warning');
    $form['#disabled'] = TRUE;
  }

  return $form;
}

/**
 * Validates the form values.
 *
 * Validates if the user has entered a valid subject / message for the emails.
 *
 * @param array $form
 *   The form array
 *
 * @param array $form_state
 *   The form_state array
 */
function workbench_email_form_validate($form, &$form_state) {
  $workbench_emails = workbench_email_get();
  foreach ($workbench_emails as $transition_label => $email_transition_set) {
    foreach ($email_transition_set as $rid => $email_transition) {
      if (isset($form_state['values'][$transition_label])) {
        // Determine if subject is set with no message.
        if ($form_state['values'][$transition_label][$rid]['subject'] != NULL
            && $form_state['values'][$transition_label][$rid]['message'] == NULL) {
          form_set_error("$transition_label][$rid][message",
                         t('You must add an email message if a subject is provided'));
        }
        // Determine if message is set with no subject.
        if ($form_state['values'][$transition_label][$rid]['subject'] == NULL
            && $form_state['values'][$transition_label][$rid]['message'] != NULL) {
          form_set_error("$transition_label][$rid][subject",
                         t('You must add a subject if an email message is provided'));
        }
      }
    }
  }
}

/**
 * Submit function for the form, saves or deletes emails.
 *
 * @param array $form
 *   The form array
 *
 * @param array $form_state
 *   The form_state array
 */
function workbench_email_form_submit($form, &$form_state) {
  $workbench_emails = workbench_email_get();
  foreach ($workbench_emails as $transition_label => $email_transition_set) {
    foreach ($email_transition_set as $rid => $email_transition) {
      $subject = $form_state['values'][$transition_label][$rid]['subject'];
      $message = $form_state['values'][$transition_label][$rid]['message'];
      workbench_email_save($email_transition, $rid, $subject, $message);
    }
  }
  drupal_set_message(t("Email's have been updated"));
}

/**
 * Administration form to create and delete email transitions.
 *
 * @param array $form
 *   The form array
 *
 * @param array $form_state
 *   The form_state array
 *
 * @return form
 *   A ready form array
 */
function workbench_email_transitions_form($form, &$form_state) {
  // List existing states.
  $types = drupal_map_assoc(workbench_moderation_moderate_node_types());
  $transitions = workbench_moderation_transitions();
  $roles = workbench_email_determine_valid_roles();

  if (!$types) {
    drupal_set_message(t('Moderation is not enabled for any content types. Visit
                         the <a href="@url"> content type administration
                         page</a> to enable moderation for one or more types.',
                         array('@url' => url('admin/structure/types'))), 'warning');
    $form['#disabled'] = TRUE;
  }
  elseif (!$roles) {
    drupal_set_message(t('Moderation is not enabled for any roles. Visit the
                         <a href="@url"> user permissions page</a> to enable moderation
                         for one or more roles.',
                         array('@url' => url('admin/people/permissions', array('fragment' => 'module-workbench_moderation')))), 'warning');
    $form['#disabled'] = TRUE;
  }
  else {
    $form['transitions'] = array(
      '#tree' => TRUE,
    );
  }

  foreach ($transitions as $transition) {
    $element = array();

    $element['transition'] = array(
      '#type' => 'value',
      '#value' => $transition,
    );
    $element['from_name'] = array(
      '#markup' => check_plain(workbench_moderation_state_label($transition->from_name)),
    );
    $element['to_name'] = array(
      '#markup' => check_plain(workbench_moderation_state_label($transition->to_name)),
    );

    foreach ($roles as $rid => $role) {
      $workbench_email = workbench_email_get($transition, $rid);
      $element[$role] = array(
        '#type' => 'checkbox',
        '#title' => check_plain(t(ucwords($role))),
        '#title_display' => 'invisible',
        '#default_value' => $workbench_email ? TRUE : FALSE,
      );
    }

    $form['transitions'][] = $element;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Transforms the email transitions administration form into a table.
 *
 * @param array $variables
 *   The form array to render into a table
 *
 * @return output
 *   A rendered form in table structure
 */
function theme_workbench_email_transitions_form($variables) {
  $form = $variables['form'];

  $header = array(
    t('From'),
    '',
    t('To'),
  );

  $roles = workbench_email_determine_valid_roles();
  $role_names = array();
  foreach ($roles as $rid => $role) {
    $role_names[$rid] = ucwords($role);
    $header[] = t("@role", array('@role' => ucwords($role)));
  }

  $rows = array();
  foreach (element_children($form['transitions']) as $key) {
    $element = &$form['transitions'][$key];
    $row = array('data' => array());
    $row['data']['from'] = drupal_render($element['from_name']);
    $row['data'][] = '--&gt;';
    $row['data']['to'] = drupal_render($element['to_name']);
    foreach ($roles as $rid => $role) {
      $row['data'][$role] = drupal_render($element[$role]);
    }
    $rows[] = $row;
  }
  $output = theme('table', array(
                                 'header' => $header,
                                 'rows' => $rows,
                                 'attributes' => array('class' => array('width-auto'))));
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Form submit handler for email transitions.
 *
 * Adds or deletes email transitions depending on user input.
 *
 * @param array $form
 *   The form array
 *
 * @param array $form_state
 *   The form_state array
 */
function workbench_email_transitions_form_submit($form, &$form_state) {
  $roles = workbench_email_determine_valid_roles();
  foreach ($form_state['values']['transitions'] as $transition) {
    foreach ($roles as $rid => $role) {
      if ($transition[$role]) {
        workbench_email_save($transition['transition'], $rid);
      }
      else {
        workbench_email_delete($transition['transition'], $rid);
      }
    }
  }
  drupal_set_message(t('Email transitions have been updated'));
}
