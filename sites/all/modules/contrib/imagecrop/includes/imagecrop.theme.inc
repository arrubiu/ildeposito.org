<?php
/**
 * @file
 * Theming functions for showing the imagecrop pages.
 *
 * @date
 * Oct 7, 2010
 */

/**
 * Override the page theming for the imagecrop pages.
 */
function imagecrop_page($variables) {

  $output = '';
  if (isset($variables['messages'])) {
    $output .= $variables['messages'];
  }

  if (!module_exists('block')) {
    $region = 'content';
  }
  else {
    global $theme;
    $query = db_select('block');
    $query->addField('block', 'region');
    $query->condition('theme', $theme);
    $query->condition('module', 'system');
    $query->condition('delta', 'main');
    $region = $query->execute()->fetchField();
  }

  // Render only the main content.
  if (isset($variables['page'][$region])) {
    $output .= imagecrop_render_main_content($variables['page'][$region]);
  }
  // Old version from Omega theme uses zones
  elseif (isset($variables['page']['content_zone']['#regions']['content'])) {
    $variables['page']['content_zone']['#regions']['content']['#omega']['page_data']['title'] = FALSE;
    $output .= drupal_render($variables['page']['content_zone']['#regions']['content']);
  }
  else {
    $output = t('The main content block was not found.');
  }

  return $output;

}

/**
 * Theme the summary from given imagecrop effect.
 */
function theme_imagecrop_effect_summary($variables) {

  $data = $variables['data'];

  $description = t('width') .': '. $data['width'] .', '. t('height') .': '. $data['height'];
  if (!empty($data['xoffset'])) {
    $description .= ', '. t('xoffset') .': '. $data['xoffset'];
  }

  if (!empty($data['yoffset'])) {
    $description .= ', '. t('yoffset') .': '. $data['yoffset'];
  }

  if ($data['resizable']) {
    $description .= ', '. t('resizable');
  }

  if ($data['aspect_ratio']) {
    $description .= ', aspect ratio: '. $data['aspect_ratio'];
  }

  if ($data['disable_if_no_data']) {
    $description .= ', '. t("don't crop if region is not set");
  }

  if ($data['downscaling']) {
    $description .= ', '. t('no downscaling allowed');
  }

  return $description;

}

/**
 * Theme the summary from an imagecrop re-use effect.
 */
function theme_imagecrop_reuse($element) {

  $data = $element['#value'];
  $description = t('Crop settings from @preset', array('@preset' => $data['imagecrop_presetname']));

  return $description;

}