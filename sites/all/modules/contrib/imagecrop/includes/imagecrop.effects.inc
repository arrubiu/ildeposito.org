<?php
/**
 * @file
 * Registry for the image style effects from imagecrop.
 *
 */

/**
 * Implements hook_image_effect_info().
 */
function imagecrop_image_effect_info() {

  $effects = array();

  $effects['imagecrop_javascript'] = array(
    'label' => t('Javascript crop'),
    'help' => t('Create a crop with a javascript toolbox.'),
    'effect callback' => 'imagecrop_effect',
    'form callback' => 'imagecrop_effect_form',
    'summary theme' => 'imagecrop_effect_summary',
    //'dimensions callback' => 'imagecrop_javascript_dimensions',
  );

  $effects['imagecrop_reuse'] = array(
    'label' => t('Reuse a javascript crop selection'),
    'help' => 'Reuse crop selection from another javascript crop preset.',
    'effect callback' => 'imagecrop_reuse_effect',
    'form callback' => 'imagecrop_reuse_form',
    'summary theme' => 'theme_imagecrop_reuse',
    //'dimensions callback' => 'imagecrop_reuse_dimensions',
  );

  return $effects;

}

/**
 * Image effect callback: Crop the image based on the javascript selected crop.
 *
 * @param $image An image object returned by image_load().
 * @param $data An array of settings from the user for cropping the image.
 * @return TRUE on success. FALSE on failure to crop the image.
 *
 */
function imagecrop_effect(&$image, $data) {

  try {

    $imagecrop = ImageCrop::getInstance($image);
    $imagecrop->applyCrop($image);

  }
  catch (Exception $e) {
    watchdog($e->getMessage(), 'error');
    return FALSE;
  }

  return TRUE;

}

/**
 * Image dimensions callback; imagecrop.
 *
 * @param $dimensions
 *   Dimensions to be modified - an array with components width and height, in
 *   pixels.
 * @param $data
 *   An array of attributes to use when performing the imagecrop effect.
 */
function imagecrop_javascript_dimensions(array &$dimensions, array $data) {

  try {

    $imagecrop = ImageCrop::getInstance();
    $dimensions['width'] = $imagecrop->getWidth();
    $dimensions['height'] = $imagecrop->getHeight();

  }
  catch (Exception $e) {
    watchdog($e->getMessage(), 'error');
    return FALSE;
  }

  return TRUE;

}

/**
 * Settings form for configuring a javascript imagecrop effect.
 */
function imagecrop_effect_form($data) {

  $form = array();
  $form['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => isset($data['width']) ? $data['width'] : '',
    '#required' => TRUE,
    '#size' => 10,
    '#element_validate' => array('image_crop_validate_size'),
    '#description' => t('Enter the width in pixels or %'),
  );

  $form['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#default_value' => isset($data['height']) ? $data['height'] : '',
    '#required' => TRUE,
    '#size' => 10,
    '#element_validate' => array('image_crop_validate_size'),
    '#description' => t('Enter the height in pixels or %'),
  );

  $form['xoffset'] = array(
    '#type' => 'textfield',
    '#title' => t('X offset'),
    '#default_value' => isset($data['xoffset']) ? $data['xoffset'] : '',
    '#description' => t('Enter an offset in pixels (without px) or use a keyword: <em>left</em>, <em>center</em>, or <em>right</em>.'),
    '#element_validate' => array('imagecrop_validate_offset'),
  );

  $form['yoffset'] = array(
    '#type' => 'textfield',
    '#title' => t('Y offset'),
    '#default_value' => isset($data['yoffset']) ? $data['yoffset'] : '',
    '#description' => t('Enter an offset in pixels (without px) or use a keyword: <em>top</em>, <em>center</em> or <em>bottom</em>.'),
    '#element_validate' => array('imagecrop_validate_offset'),
  );

  $form['resizable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Resizable toolbox'),
    '#default_value' => isset($data['resizable']) ? $data['resizable'] : '',
    '#description' => t('If the toolbox is resized, the crop values won\'t be respected, so you should add a Scale action after the ImageCrop.'),
  );

  $form['downscaling'] = array(
    '#type' => 'checkbox',
    '#title' => t('Do not allow down scaling'),
    '#default_value' => isset($data['downscaling']) ? $data['downscaling'] : FALSE,
    '#description' => t('If checked, you can\'t resize the toolbox smaller than width and height.'),
  );

  $description = t('Enter an aspect ratio to preserve during resizing. This can take one of the following formats:');
  $description .= '<ul><li>' . t('A float (like 0.5 or 2).') . '</li>';
  $description .= '<li>' . t('The string \'KEEP\'. This will constrain the aspect ratio to that of the original image.') . '</li>';
  $description .= '<li>' . t('The string \'CROP\'. This will constrain the aspect ratio to the dimensions set above.') . '</li></ul>';
  $description .= t('Leave blank for no aspect ratio constraints.');

  $form['aspect_ratio'] = array(
    '#type' => 'textfield',
    '#title' => t('Aspect ratio'),
    '#default_value' => isset($data['aspect_ratio']) ? $data['aspect_ratio'] : '',
    '#description' => $description,
    '#element_validate' => array('imagecrop_validate_aspect'),
  );

  $form['disable_if_no_data'] = array(
    '#type' => 'checkbox',
    '#title' => t('Don\'t crop if cropping region wasn\'t set.'),
    '#default_value' => isset($data['disable_if_no_data']) ? $data['disable_if_no_data'] : FALSE,
  );

  return $form;

}

/**
 * Reset the cropped images when the reset checkbox is enabled.
 */
function imagecrop_javascript_effect_submit($form, &$form_state) {

  if ($form_state['values']['reset-crops'] === 1) {
    db_update('image_crop_settings')
      ->fields(array('width' => $form_state['values']['data']['width'], 'height' => $form_state['values']['data']['height']))
      ->condition('width', $form_state['values']['old-width'])
      ->condition('height', $form_state['values']['old-height'])
      ->condition('style_name', $form_state['image_style']['name'])
      ->execute();
  }

}

/**
 * Validate the entered height / width. (can be procent or numeric)
 */
function image_crop_validate_size($element, &$form_state) {

  $value = str_replace('%', '', $element['#value']);
  if ($value != '' && (!is_numeric($value) || intval($value) <= 0)) {
    form_error($element, t('!name must be a correct size.', array('!name' => $element['#title'])));
  }

}

/**
 * Validation function to validate an entered offset value. (numbers or left / center / right)
 */
function imagecrop_validate_offset($element, &$form_state) {

  if ($element['#value'] == '') {
    return;
  }

  // numbers are allowed.
  if (is_numeric($element['#value'])) {
    return;
  }

  if ($element['#name'] == 'data[yoffset]') {
    $allowed_values = array('center', 'top', 'bottom');
  }
  else {
    $allowed_values = array('center', 'left', 'right');
  }

  // if the value is a string, check on allowed strings
  if (!in_array($element['#value'], $allowed_values)) {
    form_error($element, t('@name must be a correct offset value', array('@name' => $element['#title'])));
  }

}

/**
 * Validation function to validate an entered aspect value.
 */
function imagecrop_validate_aspect($element, &$form_state) {

  if ($element['#value'] == '') {
    return;
  }

  // numbers are allowed.
  if (is_numeric($element['#value'])) {
    return;
  }

  // if the value is a string, check on allowed strings
  if ($element['#value'] != 'KEEP' && $element['#value'] != 'CROP') {
    form_error($element, t('@name must be a correct aspect value', array('@name' => $element['#title'])));
  }

}

/**
 * Settings form for reüsing a crop selection.
 */
function imagecrop_reuse_form($data) {

  $presets = get_imagecrop_styles();
  // Make sure people don't select current preset.
  if ($key = array_search(arg(5), $presets)) {
    unset($presets[$key]);
  }

  if (count($presets) > 0) {
    $form['imagecrop_style'] = array(
      '#title' => t('Use the crop settings from'),
      '#type' => 'select',
      '#options' => $presets,
      '#default_value' => isset($data['imagecrop_style']) ? $data['imagecrop_style'] : '',
    );
  }
  else {
    $form['imagecrop_warning'] = array(
      '#value' => t('No image style is found with the javascript_crop action so far. If you want to take advantage of this module, you will need to create at least one image style with that action.'),
    );
  }

  return $form;

}

/**
 * Image effect callback: Crop the image based on the image style.
 *
 * @param $image An image object returned by image_load().
 * @param $data An array with the preset to use..
 * @return TRUE on success. FALSE on failure to crop the image.
 *
 */
function imagecrop_reuse_effect(&$image, $data) {

  if (empty($data['imagecrop_style'])) {
    return FALSE;
  }

  // Load selected image style and apply the imagecrop_javascript action.
  $style = image_style_load($data['imagecrop_style']);
  foreach ($style['effects'] as $effect) {
    if ($effect['name'] == 'imagecrop_javascript') {
      $GLOBALS['imagecrop_style'] = $style['name'];
      image_effect_apply($image, $effect);
      return TRUE;
    }
  }

  return FALSE;

}
