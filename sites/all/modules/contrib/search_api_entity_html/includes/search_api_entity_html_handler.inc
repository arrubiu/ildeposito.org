<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

class search_api_entity_html_handler_field_txt extends views_handler_field {

  /**
   * Stores the entity type of the result entities.
   */
  public $entity_type;

  /**
   * Stores the result entities' metadata wrappers.
   */
  public $wrappers = array();

  /**
   * Stores the current value when rendering list fields.
   */
  public $current_value;

  /**
   * Overridden to add the field for the entity ID (if necessary).
   */
  public function query() {
    EntityFieldHandlerHelper::query($this);
  }

  /**
   * Adds a click-sort to the query.
   */
  public function click_sort($order) {
    EntityFieldHandlerHelper::click_sort($this, $order);
  }

  /**
   * Load the entities for all rows that are about to be displayed.
   */
  public function pre_render(&$values) {
    parent::pre_render($values);
    EntityFieldHandlerHelper::pre_render($this, $values);
  }

  /**
   * Overridden to use a metadata wrapper.
   */
  public function get_value($values, $field = NULL) {
    return EntityFieldHandlerHelper::get_value($this, $values, $field);
  }

  /**
   * Provide options for this handler.
   */
  public function option_definition() {
    return parent::option_definition() + EntityFieldHandlerHelper::option_definition($this);
  }

  /**
   * Provide a options form for this handler.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    EntityFieldHandlerHelper::options_form($this, $form, $form_state);
  }

  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   */
  public function render($values) {
    return EntityFieldHandlerHelper::render($this, $values);
  }

  /**
   * Render a single field value.
   */
  public function render_single_value($value, $values) {
    if (substr($this->field, 0, 17) == 'search_api_viewed') {
      return $this->sanitize_value($value, 'xss_admin');
    } else {
      return $this->sanitize_value($value, 'xss');
    }
  }

}
