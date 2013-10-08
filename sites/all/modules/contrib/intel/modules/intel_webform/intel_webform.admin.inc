<?php

/**
 * @file
 * Forms and callbacks for controlling the admin side of intel_webform.
 * 
 * These forms will appear in intel_webform local action of webforms.
 */

function intel_webform_manage($node) {
  $form = array();
  $render_array = array();

  
  $render_array['form'] = drupal_get_form('intel_webform_settings_form', $node);  
  
  return $render_array;
}

function intel_webform_settings_form($form, &$form_state, $node) {
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );
  
  $settings = variable_get('intel_webform_settings_' . $node->nid, array());
    
  $form['field'] = array(
    '#type' => 'fieldset',
    '#title' => t('Field mapping'),
  );
  
  $options = array('' => t('None'));
  if (!empty($node->webform['components'])) {
    foreach ($node->webform['components'] AS $field) {
      if ($field['type'] == 'email') {
        $options[$field['form_key']] = $field['name'];
      }
    }
  }    
  $form['field']['field_visitor_email'] = array(
    '#type' => 'select',
    '#title' => t('Visitor email field'),
    '#default_value' => !empty($settings['field_visitor_email']) ? $settings['field_visitor_email'] : '',
    '#description' => t('If you select an existing email field, that fields input will be used. If not, a field will be shown to the user.'),
    '#options' => $options,
  );
  
  $options = array('' => t('None'));
  if (!empty($node->webform['components'])) {
    foreach ($node->webform['components'] AS $field) {
      if ($field['type'] == 'textfield') {
        $options[$field['form_key']] = $field['name'];
      }
    }
  }    
  $form['field']['field_visitor_name'] = array(
    '#type' => 'select',
    '#title' => t('Visitor name field'),
    '#default_value' => !empty($settings['field_visitor_name']) ? $settings['field_visitor_name'] : '',
    '#description' => t('Select the field that contains the visitors first or full name.'),
    '#options' => $options,
  );
  
  $form['field']['field_visitor_name2'] = array(
    '#type' => 'select',
    '#title' => t('Visitor last name field'),
    '#default_value' => !empty($settings['field_visitor_name2']) ? $settings['field_visitor_name2'] : '',
    '#description' => t('Select the field that contains the visitors last name if there is one.'),
    '#options' => $options,
  );  
  
  $form['settings']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  
  return $form;
}


function intel_webform_settings_form_validate($form, &$form_state) {

}

function intel_webform_settings_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $settings = array(
    'field_visitor_email' => $values['field_visitor_email'],
    'field_visitor_name' => $values['field_visitor_name'],
    'field_visitor_name2' => $values['field_visitor_name2'],
  );
  variable_set('intel_webform_settings_' . $values['nid'], $settings);
}