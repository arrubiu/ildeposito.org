<?php

/**
 * @file
 *   Views integration for Hidden comment
 *   By jcisio
 */

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function hidden_comment_views_handlers() {
  return array(
    'handlers' => array(
      'hidden_comment_views_handler_filter' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
    ),
  );
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function hidden_comment_views_data() {
  $data['comments_hide'] = array(
    'table' => array(
      'group' => t('Comment'),
      'join' => array(
        'comments' => array(
          'left_field' => 'cid',
          'field' => 'cid',
        ),
      ),
    ),
    'cid' => array(
      'title' => 'Hidden',
      'help' => 'Comment is hidden',
      'filter' => array(
        'handler' => 'hidden_comment_views_handler_filter',
      ),
    ),
  );

  return $data;
}
