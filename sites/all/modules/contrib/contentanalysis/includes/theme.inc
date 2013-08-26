<?php
// $Id$

/**
 * @file
 * Contains the functions used to theme the outputs of this module.
 *
 * Currently this modules implements two custom form elements. The first
 * is a slider that is used on the configuration page to set the thresholds.
 *
 * The second element is used to display the results of the checks after
 * submitting the node_form.
 */


/**
 * Defines the slider form element and its default values
 */
function contentanalysis_element_info() {
  $type['contentanalysis_slider_value'] = array(
    '#input' => TRUE,
    '#step' => 1,
    '#min' => 0,
    '#max' => 100,
    '#size' => 3,
    '#value_suffix' => '',
    '#theme' => 'contentanalysis_slider_value',
  );
  $type['contentanalysis_slider_range'] = array(
    '#input' => TRUE,
    '#step' => 1,
    '#min' => 0,
    '#max' => 1,
    '#size' => 3,
    '#value_suffix' => '',
    '#theme' => 'contentanalysis_slider_range',
  );
  return $type;
}

/**
 * Implements hook_theme().
 */
function contentanalysis_theme($existing, $type, $theme, $path) {
  return array(
    'contentanalysis_slider_value' => array(
       'render element' => 'element',
       'template' => 'slider-value',
       'path' => "$path/theme",
    ),
    'contentanalysis_slider_range' => array(
       'render element' => 'element',
       'template' => 'slider-range',
       'path' => "$path/theme",
    ),
  );
}