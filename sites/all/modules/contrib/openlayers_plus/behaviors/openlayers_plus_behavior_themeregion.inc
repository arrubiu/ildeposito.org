<?php

class openlayers_plus_behavior_themeregion extends openlayers_behavior {
  /**
   * Override of options_init().
   */
  function options_init() {
    $options = array(
    );
    return $options;
  }

  /**
   * Override of options_form().
   */
  function options_form($defaults) {
    return array(
      'regions' => array(
        '#type' => 'checkboxes',
        '#title' => t('Select Regions'),
        '#options' => system_region_list(variable_get('theme_default'), REGIONS_ALL),
        '#default_value' => isset($defaults['regions']) ? $defaults['regions'] : array(),
        '#description' => t('Select the region(s) you want to move in the map. You will have to edit the CSS to make this work nicely with more than 1 region.')
      ),
      'prefix' => array(
        '#type' => 'textfield',
        '#title' => t('CSS Prefix'),
        '#default_value' => isset($defaults['prefix']) ? $defaults['prefix'] : '#',
        '#description' => t('Prefix for the CSS identifier of the Regions div in your theme.')
      ),
      'suffix' => array(
        '#type' => 'textfield',
        '#title' => t('CSS Suffix'),
        '#default_value' => isset($defaults['suffix']) ? $defaults['suffix'] : '',
        '#description' => t('Suffix for the CSS identifier of the Regions div in your theme.')
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers_plus')
      . '/behaviors/openlayers_plus_behavior_themeregion.js');
    return $this->options;
  }
}
