<?php
/**
 * @file
 *   Provides an "actions" field for item revisions in views.
 */
class versioncontrol_handler_field_item_revision_action extends views_handler_field {

  function render($values) {
    $action = $values->{$this->field_alias};
    $actions = versioncontrol_revision_actions();
    if (isset($actions[$action])) {
      return $actions[$action];
    }
    return '';
  }
}
