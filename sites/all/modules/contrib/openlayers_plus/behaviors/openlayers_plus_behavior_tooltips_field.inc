<?php

class openlayers_plus_behavior_tooltips_field extends openlayers_behavior {
  /**
   * Override of options_init().
   */
  function options_init() {
    return array('positioned' => FALSE);
  }

  /**
   * Override of options_form().
   */
  function options_form() {
    $form = parent::options_form();
    $form['positioned'] = array(
      '#type' => 'checkbox',
      '#title' => t('Position tooltip over feature displaying specific field'),
      '#default_value' => $this->options['positioned'],
    );
	$form['field_displayed'] = array(
	  '#type' => 'textfield',
      '#title' => t('Field to Display'),
      '#description' => t('Field from openlayers view to be displayed. (usually field_your_special_field)'),
      '#default_value' => isset($this->options['field_displayed'])
        ? $this->options['field_displayed'] : NULL
    );
    return $form;
  }

  /**
   * Render.
   */
  function render(&$map) {
	$settings = array(
      'openlayers_plus_behavior_tooltips_field' => array(
		'field' => "field_category",
      ),
    );
	drupal_add_js($settings, array('type' => 'setting'));
    drupal_add_js(drupal_get_path('module', 'openlayers_plus')
      . '/behaviors/openlayers_plus_behavior_tooltips_field.js');
    return $this->options;
  }
}
