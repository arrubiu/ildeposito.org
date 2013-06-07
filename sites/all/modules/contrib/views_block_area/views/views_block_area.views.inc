<?php
/**
 * @file
 * Provide views data and handlers for views_block_area.module
 */

/**
 * Implements hook_views_data()
 */
function views_block_area_views_data() {

  $data['views']['block'] = array(
    'title' => t('Block area'),
    'help' => t('Insert a block inside an area.'),
    'area' => array(
      'handler' => 'views_handler_area_block',
    ),
  );

  return $data;

}