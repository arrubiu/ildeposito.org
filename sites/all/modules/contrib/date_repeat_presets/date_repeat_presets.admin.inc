<?php
// $Id$

// this is needed for ajax callback to work
module_load_include('inc', 'date', 'date_admin');

/**
 * @file
 * Administration of repeat rule presets.
 */

/**
 * Alter the date field admin form to allow configurable presets.
 */
function _date_repeat_presets_admin_form_alter(&$form, &$form_state, $form_id) {
  module_load_include('inc', 'date_repeat_presets', 'date_repeat_presets');
  $widget_settings = $form['#instance']['widget']['settings'];
  $repeat_presets_widget_settings = isset($widget_settings['repeat_presets']) ? $widget_settings['repeat_presets'] : array();
  $default_settings = _date_repeat_presets_get_default_settings();
  $repeat_presets_widget_settings = array_merge($default_settings, $repeat_presets_widget_settings);

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'date_repeat_presets') . '/date_repeat_presets.css',
  );

  // handle ahah callback form state - display options for multiple preset selection or single preset
  if (isset($form_state['values']['instance']['widget']['settings']['repeat_presets']['type'])) {
    $preset_type = $form_state['values']['instance']['widget']['settings']['repeat_presets']['type'];
  }
  else {
    $preset_type = $repeat_presets_widget_settings['type'];
  }

  $form['instance']['widget']['settings']['repeat_presets'] = array(
    '#tree' => TRUE,
    '#prefix' => '<div id="repeat-presets-wrapper">', // This is our wrapper div.
    '#suffix' => '</div>',
    // '#weight' => $form['instance']['settings']['repeat_collapsed']['#weight'] + 1,
    );

  $form['instance']['widget']['settings']['repeat_presets']['type'] = array(
    '#type' => 'radios',
    '#title' => t('Repeat preset type'),
    '#description' => t('Select the type of repeat date entry form that is displayed on the node add/edit form.'),
    '#options' => array(
      'standard' => t('Standard repeat rule form'),
      'selection' => t('Selection of rules (optionally including custom)'),
      'single' => t('Single rule (automatic or optional)')),
      '#ajax'        => array(
        'callback'    => 'date_repeat_presets_admin_ajax_callback',
        'wrapper' => 'repeat-presets-wrapper',
        'event'      => 'change',
      ),
    '#default_value' => $repeat_presets_widget_settings['type'],
  );

  // AHAH helper - provide this for non-js form update
  $form['instance']['widget']['settings']['repeat_presets']['update_type'] = array(
    '#type'  => 'submit',
    '#value' => t('Update type'),
    '#attributes' => array('class' => array('drp-update-type-button')),
    '#prefix' => '<div id="repeat-presets-wrapper">',
    '#suffix' => '</div>',
    '#executes_submit_callback' => FALSE,
  );

  // hide this as we spoof this in the presets ahah bit.
  $form['instance']['settings']['repeat_collapsed']['#type'] = 'hidden';


  if ($preset_type == 'selection') {
    // Allow up to 5 presets
    $presets = $repeat_presets_widget_settings['preset'];

    $preset = current($presets);

    $form['instance']['widget']['settings']['repeat_presets']['preset'] = array(
      '#tree' => TRUE,
      '#theme' => 'date_repeat_presets_presets',
      '#title' => t('Repeat date rule presets'),
    );


    for ($i = 0; $i < 5; $i++) {
      $key = 'preset' . $i;
      if (!isset($preset)) {
        $preset = array('title' => '', 'rrule' => '');
      }
      $form['instance']['widget']['settings']['repeat_presets']['preset'][$key] = array(
        '#type' => 'fieldset',
        '#tree' => TRUE,
      );
      $form['instance']['widget']['settings']['repeat_presets']['preset'][$key]['enabled'] = array(
        '#type' => 'checkbox',
        '#default_value' => $preset['enabled'],
        '#title' => t('Enabled'),
      );
      $form['instance']['widget']['settings']['repeat_presets']['preset'][$key]['title'] = array(
        '#type' => 'textfield',
        '#default_value' => $preset['title'],
        '#title' => t('Title'),
      );
      $form['instance']['widget']['settings']['repeat_presets']['preset'][$key]['rrule'] = array(
        '#type' => 'textfield',
        '#default_value' => $preset['rrule'],
        '#title' => t('Rrule'),
        '#description' => t('Enter valid iCalendar recurrence rules (RRULES) to offer as preset repeat rules on the repeating date field. Include an X-ID in the RRULE to allow updated RRULEs to match to previous versions. For the RRULE specification see !url.', array('!url' => l('RFC-5545', 'http://tools.ietf.org/html/rfc5545#section-3.8.5.3', array('external' => TRUE)))),
        '#size' => 100,
      );
      $preset = next($presets);
    }

    $form['instance']['widget']['settings']['repeat_presets']['allow_custom'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow custom repeat rule entry'),
      '#default_value' => $repeat_presets_widget_settings['allow_custom'],
      '#description' => t('Checking this option will add a "Custom" repeat date option. If the user selects this option the full repeating date option form will be presented to the user.'),
    );

    $form['instance']['widget']['settings']['repeat_presets']['preset_ui'] = array(
      '#type' => 'radios',
      '#options' => array('radios' => t('Radios'), 'select' => t('Select')),
      '#title' => t('Repeat presets display setting'),
      '#default_value' => $repeat_presets_widget_settings['preset_ui'],
      '#description' => t('Display the preset rule options as radios or as a drop-down selection.'),
    );
  }
  elseif ($preset_type == 'single') {
    // optional single rule - different UI for different requirements
    // if not optional then the repeat rule is always applied.
    $form['instance']['widget']['settings']['repeat_presets']['auto'] = array(
      '#title' => t('Auto repeat'),
      '#tree' => TRUE,
    );
    $form['instance']['widget']['settings']['repeat_presets']['auto']['rrule'] = array(
      '#type' => 'textfield',
      '#title' => t('Rule to apply'),
      '#default_value' => $repeat_presets_widget_settings['auto']['rrule'],
      '#description' => t('A valid iCalendar recurrence rule (RRULE). See !url.', array('!url' => l('RFC-5545', 'http://tools.ietf.org/html/rfc5545#section-3.8.5.3', array('external' => TRUE)))),
    );
    $form['instance']['widget']['settings']['repeat_presets']['auto']['optional'] = array(
      '#type' => 'checkbox',
      '#title' => t('Repeat rule is optional'),
      '#description' => t('If optional a checkbox will be shown with the prompt text below.'),
      '#default_value' => $repeat_presets_widget_settings['auto']['optional'],
    );
    $form['instance']['widget']['settings']['repeat_presets']['auto']['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $repeat_presets_widget_settings['auto']['text'],
    );
  }
  else {
    // display the repeat collapsed setting here
    $form['instance']['widget']['settings']['repeat_presets']['repeat_collapsed'] = array(
      '#type' => 'radios',
      '#default_value' => $widget_settings['repeat_collapsed'],
      '#options' => array(0 => t('Expanded'), 1 => t('Collapsed')),
      '#title' => t('Repeat display'),
      '#description' => t("Should the repeat options form start out expanded or collapsed? Set to 'Collapsed' to make those options less obtrusive."),
      '#after_build' => array('date_repeat_presets_admin_repeat_collapsed_after_build'),
    );
  }
}

/**
 * #after_build callback for our spoofed repeat_collapsed element. Sets the
 * element validation callback as it doesn't seem to stick in form_alter.
 */
function _date_repeat_presets_admin_repeat_collapsed_after_build($form, &$form_state) {
  $form['#element_validate'] = array('_date_repeat_presets_admin_repeat_collapsed_validate');
  return $form;
}

/**
 * #element_validate callback for spoofed repeat_collapsed element. Move value
 * into the proper widget form element and remove spoofed value so it doesn't
 * end up in the date_repeat_presets settings.
 */
function _date_repeat_presets_admin_repeat_collapsed_validate($form, &$form_state) {
  if (isset($form_state['values']['instance']['widget']['settings']['repeat_presets']['repeat_collapsed'])) {
    $form_state['values']['instance']['settings']['repeat_collapsed'] = $form_state['values']['instance']['widget']['settings']['repeat_presets']['repeat_collapsed'];
    $form_state['values']['instance']['widget']['settings']['repeat_collapsed'] = $form_state['values']['instance']['widget']['settings']['repeat_presets']['repeat_collapsed'];
    unset($form_state['values']['instance']['widget']['settings']['repeat_presets']['repeat_collapsed']);
  }
}

/**
 * Theme function for presets form element - display in table.
 */
function theme_date_repeat_presets_presets($variables) {
  $rows = array();

  // @d7 - form is in variables array
  $form = $variables['form'];

  $elements = element_children($form);
  $headers = array(t('Title'), t('RRULE'), t('Enabled'));
  $notes = NULL;

  foreach ($elements as $key) {
    if (!$notes) {
      // get field descriptions for table notes
      $notes = array();
      if (!empty($form[$key]['title']['#description'])) {
        $notes[] = $form[$key]['title']['#description'];
      }
      if (!empty($form[$key]['rrule']['#description'])) {
        $notes[] = $form[$key]['rrule']['#description'];
      }
      if (!empty($form[$key]['enabled']['#description'])) {
        $notes[] = $form[$key]['enabled']['#description'];
      }
    }
    // Build the table row.
    unset($form[$key]['title']['#title']);
    unset($form[$key]['rrule']['#title']);
    unset($form[$key]['enabled']['#title']);

    unset($form[$key]['title']['#description']);
    unset($form[$key]['rrule']['#description']);
    unset($form[$key]['enabled']['#description']);

    // Add class for js tabledrag
    $form[$key]['attributes'] = array('class' => 'date-repeat-presets-admin-preset-weight');

    $form[$key]['title']['#size'] = 20;

    $row = array(
      'data' => array(
        array('data' => drupal_render($form[$key]['title'])),
        array('data' => drupal_render($form[$key]['rrule'])),
        array('data' => drupal_render($form[$key]['enabled'])),
      ),
    );

    $rows[] = $row;
  }

  $output = '<div class="form-item"><label>'. $form['#title'] .':</label>';

  // @d7 - new function signature
  $output .= theme('table', array('header' => $headers, 'rows' => $rows, 'attributes' => array('id' => 'date-repeat-presets-admin-presets-table')));

  // add notes pulled from form elements to the end of the table
  if (!empty($notes)) {
    // @d7 - new function signature
    $output .= theme('item_list', array('items' => $notes, 'title' => NULL, 'type' => 'ul', 'attributes' => array('class' => 'description')));
  }
  // end of form-item div.
  $output .= '</div>';


  return $output;
}