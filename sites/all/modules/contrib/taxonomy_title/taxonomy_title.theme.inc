<?php
/**
 * @file taxonomy_title.theme.inc
 * Theme functions for the taxonomy title module.
 */

/**
 * Theme function for admin form, turns into a table.
 */
function theme_taxonomy_title_admin_settings($variables) {
  $form = $variables['form'];

  if (!module_exists('page_title') && !module_exists('metatag')) {
    $title_head = t('Affect title tag');
    dpm('here');
  } 
  else {
    $title_head = t('Affect title tag *');
  }

  $header = array(
    t('Terms in vocabulary'), 
    array('data' => t('Affect Heading tag'), 'class' => 'checkbox'), 
    array('data' => $title_head, 'class' => 'checkbox'),
  );

  $rows = array();
  foreach($form['taxonomy_title_page_titles']['#options'] as $vid => $name) {
    $row = array();
    $row[] = check_plain($name);
    unset($form['taxonomy_title_headings'][$vid]['#title']);
    $row[] = array('data' => drupal_render($form['taxonomy_title_headings'][$vid]), 'class' => 'checkbox');
    unset($form['taxonomy_title_page_titles'][$vid]['#title']);
    $row[] = array('data' => drupal_render($form['taxonomy_title_page_titles'][$vid]), 'class' => 'checkbox');
    $rows[] = $row;
  }

  // Add a row with screenshots.
  $heading_path = drupal_get_path('module', 'taxonomy_title') . '/includes/' . 'heading.png';
  $heading_example = theme('image', array('path' => $heading_path));

  $title_path = drupal_get_path('module', 'taxonomy_title') . '/includes/' . 'title.png';
  $title_example = theme('image', array('path' => $title_path));

  $rows[] = array(t('Example'), array('data' => $heading_example, 'class' => 'checkbox'), array('data' => $title_example, 'class' => 'checkbox'));

  // Create the table inside the form.
  $form['settings'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows)),
    '#weight' => -1,
  );

  $form['#sorted'] = FALSE;

  return drupal_render_children($form);
}
