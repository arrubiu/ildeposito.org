<?php

class openlayers_plus_behavior_blockswitcher extends openlayers_behavior {
  /**
   * Override of options_init().
   */
  function options_init() {
    $options = array(
      'enabled' => FALSE,
      'position' => 'se',
    );
    return $options;
  }

  /**
   * Override of options_form().
   */
  function options_form($defaults) {
    return array(
      'enabled' => array(
        '#type' => 'checkbox',
        '#title' => t('Show blockswitcher in map'),
        '#default_value' => isset($defaults['enabled']) ? $defaults['enabled'] : array(),
      ),
      'open' => array(
        '#type' => 'checkbox',
        '#title' => t('Show blockswitcher open when the map loads'),
        '#default_value' => isset($defaults['open']) ? $defaults['open'] : array(),
      ),
      'overlay_style' => array(
        '#type' => 'select',
        '#title' => t('Show overlay layers as checkboxes or radio buttons'),
        '#options' => array(
          'checkbox' => t('Checkboxes'),
          'radio' => t('Radio Buttons'),
        ),
        '#default_value' => isset($defaults['overlay_style']) ? $defaults['overlay_style'] : array(),
      ),
      'position' => array(
        '#type' => 'select',
        '#title' => t('Position'),
        '#options' => array(
          'ne' => t('Top right'),
          'se' => t('Bottom right'),
          'sw' => t('Bottom left'),
          'nw' => t('Top left'),
        ),
        '#default_value' => isset($defaults['position']) ? $defaults['position'] : array(),
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {

    drupal_add_js(drupal_get_path('module', 'openlayers_plus')
      . '/behaviors/openlayers_plus_behavior_blockswitcher.js');
    if ($this->options['enabled']) {
      $block = module_invoke('openlayers_plus', 'block_view', 'blockswitcher');
      $this->options['block'] = drupal_render($block);
    }
    return $this->options;
  }
}
