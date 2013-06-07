<?php
// $I$
/**
 * @file
 * Contains the basic 'list template' field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to a list's template flag.
 */
class flag_lists_handler_field_template extends views_handler_field {
  /**
   * Constructor to provide additional field to add.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['name'] = array('table' => 'flags', 'field' => 'name');
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_template'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Provide link to list option
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['link_to_template'] = array(
      '#title' => t('Link this field to its list template'),
      '#description' => t('This will override any other link you have set.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_template']),
    );
  }

  /**
   * Render whatever the data is as a link to the list.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_template']) && $data !== NULL && $data !== '') {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "admin/build/flags/edit/" . $values->{$this->aliases['name']};
    }
    return $data;
  }

  function render($values) {
    return $this->render_link(check_plain($values->{$this->field_alias}), $values);
  }
}