<?php
/**
 * @file
 * Provide list fid argument handler.
 */

/**
 * Argument handler to accept a list id.
 */
class flag_lists_handler_argument_fid extends views_handler_argument_numeric {
  /**
   * Override the behavior of title(). Get the title of the list.
   */
  function title_query() {
    $titles = array();
    $result = db_select('flag_lists_flags', 'fl')
      ->fields('fl', array('title'))
      ->condition('fl.fid', $this->value, 'IN')
      ->execute();
    foreach ($result as $term) {
      $titles[] = check_plain($term->title);
    }
    return $titles;
  }
}

