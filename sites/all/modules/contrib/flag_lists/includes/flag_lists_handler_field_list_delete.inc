<?php
// $I$
/**
 * @file
 * Contains the basic 'list delete' field handler.
 */

/**
 * Field handler to provide simple renderer that links to the list edit page.
 */
class flag_lists_handler_field_list_delete extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['fid'] = 'fid';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $fid = $values->{$this->aliases['fid']};

    // Check delete access.
    if (!flag_lists_is_owner('delete', $fid)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    return l($text, "flags/lists/delete/" . $fid,  array('query' => drupal_get_destination()));
  }
}