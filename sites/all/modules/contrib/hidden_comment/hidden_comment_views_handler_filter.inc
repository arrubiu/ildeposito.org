<?php

/**
 * @file
 * Views handler filter for hidden comment
 */

class hidden_comment_views_handler_filter extends views_handler_filter_boolean_operator {
  function query() {
    if ($this->value === 'All') {
      return;
    }

    $this->ensure_my_table();
    $field = "{$this->table_alias}.{$this->real_field}";

    $where = sprintf('%s %s', $field, $this->value ? 'IS NOT NULL' : 'IS NULL');

    $this->query->add_where($this->options['group'], $where);
  }
}
