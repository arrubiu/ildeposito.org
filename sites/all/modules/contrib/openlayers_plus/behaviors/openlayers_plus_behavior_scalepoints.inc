<?php

class openlayers_plus_behavior_scalepoints extends openlayers_behavior {
  /**
   * Override of options_init().
   */
  function options_init() {
    $options['min'] = array(
      'pointRadius' => 5,
      'value' => 0,
    );
    $options['max'] = array(
      'pointRadius' => 20,
      'value' => '50',
    );
    $options['distinct'] = 5;
    $options['min_label'] = -1;
    $options['method'] = 'area';
    // @TODO: This sucks. Get a submission/validation handling into the behaviors base class and fix this.
    $options['fields'] = array('count, weight');
    return $options;
  }

  /**
   * Override of options_form().
   */
  function options_form($defaults = array()) {
    $options = array (
    'min' => array(
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#type' => 'fieldset',
      '#title' => t('Minimum values'),
    ),
    'max' => array(
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#type' => 'fieldset',
      '#title' => t('Maximum values'),
    )
   );
    foreach (array('min', 'max') as $key) {
     $options[$key]['value'] = array(
        '#title' => t('Value'),
        '#description' => t('Enter a fixed value for this field or leave empty to autoscale points.'),
        '#type' => 'textfield',
        '#size' => 4,
        '#default_value' => isset($defaults[$key]['value']) ? $defaults[$key]['value'] : array(),
      );
     $options[$key]['pointRadius'] = array(
        '#title' => t('Radius'),
        '#type' => 'textfield',
        '#size' => 4,
        '#default_value' => isset($defaults[$key]['pointRadius']) ? $defaults[$key]['pointRadius'] : array(),
      );
      $options[$key]['fillOpacity'] = array(
        '#title' => t('Fill opacity'),
        '#type' => 'textfield',
        '#size' => 4,
        '#maxlength' => 4,
        '#default_value' => isset($defaults[$key]['fillOpacity']) ? $defaults[$key]['fillOpacity'] : array(),
      );
      $options[$key]['strokeWidth'] = array(
        '#title' => t('Stroke width'),
        '#type' => 'textfield',
        '#size' => 4,
        '#maxlength' => 4,
        '#default_value' => isset($defaults[$key]['strokeWidth']) ? $defaults[$key]['strokeWidth'] : array(),
      );
      // @TODO: Handle color gradation using API functions in color module
      /*
       $form[$key]['fillColor'] = array(
       '#title' => t('Fill color'),
       '#type' => 'textfield',
       '#size' => 7,
       '#maxlength' => 7,
       '#default_value' => $this->options[$key]['fillColor'],
       );
       $form[$key]['strokeColor'] = array(
       '#title' => t('Stroke color'),
       '#type' => 'textfield',
       '#size' => 7,
       '#maxlength' => 7,
       '#default_value' => $this->options[$key]['strokeColor'],
       );
       */
    };
    $options['method'] = array(
      '#title' => t('Scaling method'),
      '#type' => 'select',
      '#options' => array(
        'area' => t('Circle area'),
        'radius' => t('Circle radius'),
      ),
      '#default_value' => isset($defaults['method']) ? $defaults['method'] : array(),
    );
    $options['distinct'] = array(
      '#title' => t('Number of distinct sizes'),
      '#type' => 'textfield',
      '#default_value' => isset($defaults['distinct']) ? $defaults['distinct'] : array(),
    );
    $options['fields'] = array(
      '#title' => t('Fields'),
      '#description' => t('Enter a comma separated list of attribute fields that can be used for scaling points. The first found attribute will be used.'),
      '#type' => 'textfield',
      '#default_value' => isset($defaults['fields']) ? $defaults['fields'] : array(),
    );
    $options['min_label'] = array(
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#type' => 'textfield',
      '#title' => t('Minimum weight point to label'),
      '#default_value' => isset($defaults['min_label']) ? $defaults['min_label'] : array(),
      '#description' => t('Don\'t show labels below a certain point weight'),
    );
    return $options;
  }

  /**
   * Generate weight segments from the number of distinct values.
   */
  function get_weights() {
    if (!is_numeric($this->options['distinct']) || $this->options['distinct'] < 1) {
      $this->options['distinct'] = 5;
    }
    $size = number_format(1 / $this->options['distinct'], 2);
    $weights = array();
    for ($i = 1; $i < $this->options['distinct']; $i++) {
      $key = (string) ($i * $size);
      $weights[$key] = $i;
    }
    $weights[1] = $this->options['distinct'];
    return $weights;
  }

  /**
   * Generate a weight => pointRadius mapping.
   */
  function get_styles() {
    $weights = array_values($this->get_weights());
    $styles = array();
    foreach (array_keys($this->options['min']) as $key) {
      if ($key != 'value' && (!empty($this->options['min'][$key]) ||  !empty($this->options['max'][$key]))) {
        $pointdiff = ($this->options['max'][$key] - $this->options['min'][$key]) / $this->options['distinct'];
        $pointdiff = number_format($pointdiff, 2);
        
        foreach ($weights as $weight) {
          $styles[$weight][$key] = $this->options['min'][$key] + ($weight - 1) * $pointdiff;
          if ($weight <= $this->options['min_label']) {
            $styles[$weight]['label'] = '';
          }
        }
        $styles[$this->options['distinct']][$key] = $this->options['max'][$key];
      }
    }
    return $styles;
  }

  /**
   * Retrieve the first found usable field from a set of features.
   */
  protected function get_field($features) {
    $fields = explode(',', $this->options['fields']);
    foreach ($fields as $k => $v) {
      $fields[$k] = trim($v);
    }
    foreach ($features as $feature) {
      foreach ($fields as $field) {
        if (isset($feature['attributes'][$field])) {
          return $field;
        }
      }
    }
    return FALSE;
  }

  protected function get_layers($layers) {
    $vector_layers = array();
    foreach ($layers as $key => $layer) {
      // get type == Vector for backwards-compatibility.
      // TODO: After OpenLayers alpha8 it should be removed
      if (((isset($layer['vector']) && $layer['vector'] == 1)) && !empty($layer['features'])) {
        $vector_layers[$key] = $layer;
      }
    }
    return $vector_layers;
  }

  protected function process_weight($ratio, $method) {
    switch ($method) {
      case 'radius':
        return $ratio;
      case 'area':
      default:
        return sqrt($ratio);
    }
  }

  /**
   * Render.
   */
  function render(&$map) {
    // Get the layers we are going to use.
    $layers = $this->get_layers($map['layers']);
    $get_min = $this->options['min']['value'] === '' || !isset($this->options['min']['value']);
    $get_max = $this->options['max']['value'] === '' || !isset($this->options['max']['value']);

    $weights = $this->get_weights();
    
    foreach ($layers as $k => $layer) {
      // Get the field we are going to use.
      if ($field = $this->get_field($layer['features'])) {
        // Get min/max per layer.
        $min = isset($this->options['min']['value']) && is_numeric($this->options['min']['value']) ? $this->options['min']['value'] : 1000000;
        $max = isset($this->options['max']['value']) && is_numeric($this->options['max']['value']) ? $this->options['max']['value'] : 0;
        $count_min = 1000000;
        $count_max = 0;
        if ($get_min || $get_max) {
          foreach ($layer['features'] as $j => $feature) {
            if ($field && isset($feature['attributes'][$field]) && $count = $feature['attributes'][$field]) {
              // Replace the count attribute with the selected one.
              if ($field !== 'count') {
                $map['layers'][$k]['features'][$j]['attributes']['count'] = $count;
              }
              $max = ($count > $max) && $get_max ? $count : $max;
              $min = ($count < $min) && $get_min ? $count : $min;
              $count_max = ($count > $count_max) ? $count : $count_max;
              $count_min = ($count < $count_min) ? $count : $count_min;
            }
          }
        }

        // Sensible defaults code right here: If count_max & count_min are both under 1,
        // assume data source is doing a ratio calc for us. Set max to 1.
        if ($count_max < 1 && $count_min < 1) {
          $max = 1;
        }

        foreach ($layer['features'] as $j => $feature) {
          if ($field && isset($feature['attributes'][$field]) && $count = $feature['attributes'][$field]) {
            // For layers with only a single value always use the smallest weight.
            if ($count_max === $count_min) {
              $map['layers'][$k]['features'][$j]['attributes']['weight'] = 1;
            }
            // Otherwise iterate through to find the right weight.
            else {
              $calculated = $this->process_weight(($count - $min) / ($max - $min), $this->options['method']);
              foreach ($weights as $percentile => $weight) {
                if ($calculated <= $percentile) {
                  $map['layers'][$k]['features'][$j]['attributes']['weight'] = $weight;
                  break;
                }
              }
            }
          }
        }
      }
    }

    drupal_add_js(drupal_get_path('module', 'openlayers_plus') . '/behaviors/openlayers_plus_behavior_scalepoints.js');
    $options = array();
    $options['styles'] = $this->get_styles();
    return $options;
  }
}
