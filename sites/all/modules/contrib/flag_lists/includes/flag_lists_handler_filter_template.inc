<?php
/**
 * @file flag_lists_handler_filter_template.inc
 * Filter by list template
 */
class flag_lists_handler_filter_template extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('List templates');
      $templates = flag_lists_get_templates();
      foreach ($templates as $template) {
        $options[$template->name] = $template->name;
      }
      $this->value_options = $options;
    }
  }
}
