<?php

class flag_lists_handler_field_ops extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    $options['flo'] = array(
      'contains' => array(
        'force_single' => array('default' => FALSE),
        'operation' => array('default' => 'flag'),
      ),
    );

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['flo'] = array(
      '#type' => 'fieldset',
      '#title' => t('Flag lists operations'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    $form['flo']['force_single'] = array(
      '#type' => 'checkbox',
      '#title' => t('Force single'),
      '#default_value' => $this->options['flo']['force_single'],
      '#description' => t('Check this box to restrict selection to a single value.'),
    );
    $form['flo']['operation'] = array(
      '#type' => 'radios',
      '#title' => t('Operation'),
      '#default_value' => $this->options['flo']['operation'],
      '#description' => t('The flag lists operation for this selection.'),
      '#options' => array(
        'flag' => 'Add to list',
        'unflag' => 'Remove from list',
      ),
      '#required' => TRUE,
    );
  }

  /**
   * If the view is using a table style, provide a
   * placeholder for a "select all" checkbox.
   */
  function label() {
    if ($this->view->style_plugin instanceof views_plugin_style_table && !$this->options['flo']['force_single']) {
      return '<!--flag-lists-ops-select-all-->';
    }
    else {
      return parent::label();
    }
  }

  function render($values) {
    return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
  }

  function views_form(&$form, &$form_state) {
    // The view is empty, abort.
    if (empty($this->view->result)) {
      return;
    }

    $form[$this->options['id']] = array(
      '#tree' => TRUE,
    );

    // At this point, the query has already been run, so we can access the results
    // in order to get the base key value (for example, nid for nodes).
    foreach ($this->view->result as $row_index => $row) {
      $entity_id = $this->get_value($row);

      if ($this->options['flo']['force_single']) {
        $form[$this->options['id']][$row_index] = array(
          '#type' => 'radio',
          '#parents' => array($this->options['id']),
          '#return_value' => $entity_id,
        );
      }
      else {
        $form[$this->options['id']][$row_index] = array(
          '#type' => 'checkbox',
          '#return_value' => $entity_id . (isset($row->flag_lists_flags_fid) ? ('-' . $row->flag_lists_flags_fid) : ''),
          '#default_value' => FALSE,
          '#attributes' => array('class' => array('flo-select')),
        );
      }
    }
  }
}