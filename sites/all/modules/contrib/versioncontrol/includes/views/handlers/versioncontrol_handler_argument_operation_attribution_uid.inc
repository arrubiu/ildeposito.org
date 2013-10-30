<?php
/**
 * @file
 * Contains the attribution argument handler.
 */

/**
 * Specialized argument handler for repo_id argument.
 */
class versioncontrol_handler_argument_operation_attribution_uid extends views_handler_argument_user_uid {
  function query($group_by = FALSE) {
    $this->ensure_my_table();
    $this->query->add_field($this->table_alias, 'author_uid');
    $this->query->add_field($this->table_alias, 'committer_uid');

    if (!empty($this->options['break_phrase'])) {
      views_break_phrase($this->argument, $this);
    }
    else {
      $this->value = array($this->argument);
    }

    if (count($this->value) > 1) {
      $operator = empty($this->options['not']) ? 'IN' : 'NOT IN';
      $this->query->add_where_expression(0, "$this->table_alias.author_uid $operator (:uids) OR $this->table_alias.committer_uid $operator (:uids)", array(':uids' => $this->value));
    }
    else {
      $placeholder = $this->placeholder();
      $operator = empty($this->options['not']) ? '=' : '!=';
      $this->query->add_where_expression(0, "$this->table_alias.author_uid $operator $placeholder OR $this->table_alias.committer_uid $operator $placeholder", array($placeholder => $this->argument));
    }
  }
}
