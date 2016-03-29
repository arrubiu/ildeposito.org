<?php

/**
 * @file
 * API documentation for the classy_paragraphs module.
 */

/**
 * Describe the classes that will be used in the drop-down.
 *
 * @param $options
 * @param $field
 * @param $instance
 *
 * @return array
 *   An associative array of all available classes, keyed by the class name,
 *   and then the human-readable name, with the following keys:
 *   - class: The class name which will be used in HTML.
 *   - class label: The human-readable name of the class.
 *
 * @see classy_paragraphs_get_options()
 */
function hook_classy_paragraphs_list_options($options, $field, $instance) {
  $options['loud'] = t('Loud');
  $options['soft'] = t('Soft');
  return $options;
}

/**
 * Alter the class names used on field.
 *
 * @param array $options
 *   An array of classes, keyed first by class name, then by human-readable
 *   name.
 *
 * @see classy_paragraphs_get_options()
 */
function hook_classy_paragraphs_list_options_alter(&$options) {
  $options['loud'] = t('Call to action: Loud');
}
