<?php
// $Id$

/**
 * @file
 * All non-hook code to prevent unnecessary parsing.
 */

/**
 * Alter the repeating date part of the node edit form.
 *
 * Depeding on configuration this adds:
 * - A number of preset repeat options - e.g. every year, every week, every day,
 *   plus a no repeat option and a custom option. Full flexibility with convenient short cuts.
 *   Optionally, the until date may be hidden if a default is provided.
 * - A single checkbox to apply a single repeat date rule. The custom form is hidden.
 *   Suitable, for example, for events that might include one-offs and anniversaries/birthdays.
 * - Automatic repeat - no custom form and no option. Suitable for birthdays.
 */
function _date_repeat_presets_alter_entity_form(&$element) {
  static $once = FALSE;

  // Find any repeating date fields.
  $instance = field_info_instance($element['#entity_type'], $element['#field_name'], $element['#bundle']);

  // get settings - default or set via widget settings form
  $settings = $instance['widget']['settings']['repeat_presets'];

  if ($settings['type'] == 'selection') {
    $presets = $settings['preset'];

    // Repeat options array
    $options = array();

    // Offer a no repeat option.
    $options['none'] = t('No repeat');

    // Get the parts of the set rule to get and match any X-ID element
    $set_rrule_values = _date_repeat_presets_parse_rrule($element['rrule']['#default_value']);

    // Default preset to none in case no matching rule found
    $default = 'none';
    foreach ($presets as $id => $preset) {
      if ($preset['enabled'] && !empty($preset['rrule']) && !empty($preset['title'])) {
        // Add form element option
        $options[$id] = t($preset['title']);

        // Parse the preset option rrule to see if it has same id as current setting
        $values = _date_repeat_presets_parse_rrule($preset['rrule']);

        // If preset rule matches current rule - make this preset selected.
        if ($preset['rrule'] == $element['rrule']['#default_value']) {
          $default = $id;
        }
        // Otherwise if X-ID of preset rule matches X-ID of current rule - make this preset selected.
        elseif (!empty($set_rrule_values['X-ID']) && !empty($values['X-ID']) && $set_rrule_values['X-ID'][0] == $values['X-ID'][0]) {
          $default = $id;
        }
      }
    }

    $weight = $element['rrule']['#weight'] - .1;

    // Handle custom rrule option.
    if ($settings['allow_custom']) {
      // Add option to form element.
      $options['custom'] = t('Custom');

      // If there is a rule set which does not match any presets then mark the custom option as selected.
      if (!empty($element['rrule']['#default_value']) && $default === 'none')  {
        $default = 'custom';
      }

      // Add javascript to show/hide the custom form when custom option is selected/deselected.
      if (!$once) {
        drupal_add_js(drupal_get_path('module', 'date_repeat_presets') . '/date_repeat_presets.js');
        $once = TRUE;
      }
    }
    else {
      // if custom is not an option then we don't need the fieldset.
      // unset($form[$field_name]['und']['rrule']['#type']);
    }

    // Add preset selection to form either as radios or select box depending on settings.
    $element['rrule']['rrule_presets'] = array(
      '#type' => $settings['preset_ui'],
      '#title' => t('Repeat'),
      '#options' => $options,
      '#default_value' => $default,
      '#weight' => -1,
      '#date_repeat_presets_field' => TRUE,
      '#attributes' => array('class' => array('drp-presets-' . $element['#field_name'], 'drp-presets')),
      '#prefix' => '<div class="rrule-presets">',
      '#suffix' => '</div>',
    );

    // need to do some after build manipulation on the expanded rrule form element.
    $element['#after_build'][] = 'date_repeat_presets_after_build';

    if (!empty($js_settings)) {
      // hide/show custom options
      // drupal_add_js(drupal_get_path('module', 'date_repeat_presets') . '/date_repeat_presets.js');
      // drupal_add_js(array('date_repeat_presets' => array('fields' => $js_settings)), 'setting');
    }
  }
  elseif ($settings['type'] == 'single') {
    // set up the form for single rule with optional apply checkbox
    // $form[$field_name]['rrule']['#type'] = 'hidden';
    // $form[$field_name]['rrule']['#processed'] = TRUE;

    // what is 'und'? Answer: undefined language.
    $weight = $element['rrule']['#weight'] - .1;

    if ($settings['auto']['optional']) {
      $element['rrule']['rrule_apply'] = array(
        '#type' => 'checkbox',
        '#title' => t($settings['auto']['text']),
        '#default_value' => !empty($element['rrule']['#default_value']),
        '#weight' => $weight,
        '#date_repeat_presets_field' => TRUE,
      );
    }

    // need to do some after build manipulation on the expanded rrule form element.
    $element['#after_build'][] = 'date_repeat_presets_after_build';
  }
  else {
    // standard - do nothing
  }

  return $element;
}

/**
 * An after_build callback for the repeat date element.
 */
function _date_repeat_presets_after_build($form, &$form_state) {
  $field_instance = field_info_instance($form['#entity_type'], $form['#field_name'], $form['#bundle']);
  $settings = $field_instance['widget']['settings']['repeat_presets'];

  $form['rrule']['#drp_instance'] = $field_instance;

  if ($settings['type'] == 'selection' && $settings['allow_custom'] == TRUE) {
    // for presets that allow custom rule
    // wrap the rrule form section in an indentifiable div.
    $form['rrule']['#prefix'] = '<div id="date-repeat-presets-custom-'. $form['#field_name'] .'" class="date-repeat-presets-custom">';
    $form['rrule']['#suffix'] = '</div>';
    $form['rrule']['#collapsed'] = FALSE;

    // If a preset is selected the custom form elements will be populated with
    // the preset rule which may violate repeat form validation - e.g. years + and -.
    // To avoid validation errors with reset these form elements.
    if (FALSE && $form_state['values'][$form['#field_name']]['rrule']['rrule_presets'] <> 'custom') {
      $form['rrule']['INTERVAL']['#value'] = 0;
      $form['rrule']['FREQ']['#value'] = 'NONE';
      foreach (element_children($form['rrule']['UNTIL']['datetime']) as $datetime_field) {
        $form['rrule']['UNTIL']['datetime'][$datetime_field]['#value'] = '';
        $form['rrule']['UNTIL']['datetime'][$datetime_field]['#default_value'] = '';
      }
      $form['rrule']['UNTIL']['datetime']['#value'] = '';
      $form['rrule']['UNTIL']['datetime']['#default_value'] = '';
    }
  }
  else {
    // for all others (no custom rule required) remove the custom rule form elements
    unset($form['rrule']['#theme_wrappers']);
    foreach (element_children($form['rrule']) as $child) {
      if (!isset($form['rrule'][$child]['#date_repeat_presets_field'])) {
        unset($form['rrule'][$child]);
      }
    }
  }

  // Replace the date widget validation method with our one.
  if ($index = array_search('date_widget_validate', $form['#element_validate'])) {
    $form['#element_validate'][$index] = 'date_repeat_presets_validate';
  }

  // Replace validation to the rrule element.
  $form['rrule']['#element_validate'] = array('date_repeat_presets_rrule_validate');

  return $form;
}

/**
 * Friendly version of date_widget_validate() in date_elements.inc. See the after_build hook above.
 */
function _date_repeat_presets_validate($element, &$form_state) {
  $form_values = $form_state['values'];
  $field_name = $element['#field_name'];

  $exists = FALSE;
  $element_values = drupal_array_get_nested_value($form_values, $element['#parents'], $exists);

  // Replace the widget validation method for all but custom repeat dates.
  if ($exists && array_key_exists('rrule', $element_values) && $element_values['rrule']['rrule_presets'] <> 'custom') {
    return _date_repeat_presets_widget_validate($element, $form_state);
  }
  else {
    require_once('./'. drupal_get_path('module', 'date') .'/date_repeat.inc');
    return _date_repeat_widget_validate($element, $form_state);
  }
}

/**
 * Alternative widget validation that takes all parameters from the rrule.
 */
function _date_repeat_presets_widget_validate($element, &$form_state) {
  require_once('./'. drupal_get_path('module', 'date') .'/date_repeat.inc');
  require_once('./'. drupal_get_path('module', 'date_repeat') .'/date_repeat_form.inc');
  $element_values = drupal_array_get_nested_value($form_state['values'], $element['#parents'], $exists);
  $field_name = $element['#field_name'];
  $field = field_info_field($field_name);

  // set by the rrule element validation function
  $rrule = $element_values['rrule'];

  if (!empty($rrule)) {

    // parse rrule into it's parts: associative array keyed on rrule keywords
    $rrule_parts = _date_repeat_presets_parse_rrule($rrule);

    // If no start date was set, clean up the form and return.
    // If no repeats are set, clean up the form and return.
    if (empty($element_values['value']) || $rrule_parts['FREQ'] == 'NONE') {
    // if (empty($form_values[$field_name]['und']['value'])) {
      $element_values['rrule'] = NULL;
      form_set_value($element, array($element_values), $form_state);
      return;
    }

    // Re-calculate the repeating dates, wipe out the previous values,
    // and populate the field with the new values.
    $item = $element_values;

    // Avoid undefined index problems on dates that don't have all parts.
    $possible_items = array('value', 'value2', 'timezone', 'offset', 'offset2');
    foreach ($possible_items as $key) {
      if (empty($item[$key])) {
        $item[$key] = '';
      }
    }

    // get the repeat dates
    $value = date_repeat_build_dates($rrule, $rrule_parts, $field, $item);
    form_set_value($element, $value, $form_state);
  }
  else {
    // If no changes are needed, move the RRULE back to the zero value
    // item of the field.
    form_set_value(array('#parents' => array($field_name, 0, 'rrule')), $rrule, $form_state);
    form_set_value($element['rrule'], NULL, $form_state);
  }
}

/**
 * Validation for the rrule form element. If a preset has been selected, this
 * sets the rrule to the preset value. If custom is selected the standard
 * validate rule is called.
 */
function _date_repeat_presets_rrule_validate($element, &$form_state) {
  // this is the rrule element - we want the name of the settings of the parent
  $field_name = $element['#parents'][1];
  // retrieve settings previously stored on the form
  $settings = $element['#drp_instance']['widget']['settings']['repeat_presets'];
  $element_values = drupal_array_get_nested_value($form_state['values'], $element['#parents']);

  if ($settings['type'] == 'single') {
    // if not optional then set rrule, or if optional and user has checked the 'rrule_apply' checkbox
    // then set rrule to the configured rule. Otherwise set rrule to a no repeat default.
    if (!$settings['auto']['optional'] || $element_values['rrule_apply']) {
      form_set_value($element, $settings['auto']['rrule'], $form_state);
    }
    else {
      // set rrule to "no repeat" default
      form_set_value($element, 'RRULE:FREQ=NONE;INTERVAL=0', $form_state);
    }
  }
  elseif ($settings['type'] == 'selection') {
    $presets = $settings['preset'];
    if ($element_values['rrule_presets'] == 'none') {
      // Set rrule to "no repeat" default.
      form_set_value($element, 'RRULE:FREQ=NONE;INTERVAL=0', $form_state);
    }
    elseif ($element_values['rrule_presets'] <> 'custom') {
      // Set rrule to selected preset.
      $selected_preset = $presets[$element_values['rrule_presets']];
      form_set_value($element, $selected_preset['rrule'], $form_state);
    }
    else {
      // Call standard rrule element validation to validate the custom form elements
      module_load_include('inc', 'date_repeat', 'date_repeat_form');
      date_repeat_rrule_validate($element, $form_state);
    }
  }
}

/**
 * Default preset for selection option.
 */
function _date_repeat_presets_get_default_presets($field_info = NULL) {
  return array(
    'yearly' => array(
      'enabled' => TRUE,
      'title' => t('Every year'),
      'rrule' => 'RRULE:FREQ=YEARLY;INTERVAL=1;UNTIL=20251216T000000Z;WKST=SU;X-ID=yearly',
    ),
    'monthly' => array(
      'enabled' => TRUE,
      'title' => t('Every month'),
      'rrule' => 'RRULE:FREQ=MONTHLY;INTERVAL=1;UNTIL=20120615T230000Z;WKST=SU;X-ID=monthly',
    ),
    'weekly' => array(
      'enabled' => TRUE,
      'title' => t('Every week'),
      'rrule' => 'RRULE:FREQ=WEEKLY;INTERVAL=1;UNTIL=20110615T230000Z;WKST=SU;X-ID=weekly',
    ),
  );
}

/**
 * Get the default settings for repeat presets.
 */
function _date_repeat_presets_get_default_settings() {
  return array(
    'type' => 'standard',
    'allow_custom' => TRUE,
    'preset' => _date_repeat_presets_get_default_presets(),
    'preset_ui' => 'select',
    'auto' => array(
      'rrule' => 'RRULE:FREQ=YEARLY;INTERVAL=1;UNTIL=20251216T000000Z;WKST=SU',
      'optional' => TRUE,
      'text' => t('Tick if this is an annual event.'),
    ),
  );
}

/**
 * Parse rrule.
 * @return
 *  An associative array of rrule parts of the form KEYWORD => VALUE.
 */
function _date_repeat_presets_parse_rrule($rrule) {
  // split out different bits of rrule and parse - this code borrowed from date_ical_parse
  $matches = array();
  preg_match('/([^;:]+)(?:;([^:]*))?:(.+)/', $rrule, $matches);
  $rr_name = !empty($matches[1]) ? strtoupper(trim($matches[1])) : '';
  $rr_field = !empty($matches[2]) ? $matches[2] : '';
  $rr_data = !empty($matches[3]) ? $matches[3] : '';

  // use this method as date_ical_parse expects an ical file beginning with BEGIN:VCALENDAR
  require_once('./'. drupal_get_path('module', 'date_api') .'/date_api_ical.inc');
  $values = date_ical_parse_rrule($rr_field, $rr_data);
  return $values;
}

