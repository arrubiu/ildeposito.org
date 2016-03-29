<?php
/**
 * @file
 * classy_paragraphs_test.features.inc
 */

/**
 * Implements hook_node_info().
 */
function classy_paragraphs_test_node_info() {
  $items = array(
    'cp_test_landing_page' => array(
      'name' => t('Landing page'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_paragraphs_info().
 */
function classy_paragraphs_test_paragraphs_info() {
  $items = array(
    'cp_test_content' => array(
      'name' => 'Content (test)',
      'bundle' => 'cp_test_content',
      'locked' => '1',
    ),
    'cp_test_content_multiple_classes' => array(
      'name' => 'Content multiple classes (test)',
      'bundle' => 'cp_test_content_multiple_classes',
      'locked' => '1',
    ),
  );
  return $items;
}
