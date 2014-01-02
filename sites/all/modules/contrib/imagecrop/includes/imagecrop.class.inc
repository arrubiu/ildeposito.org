<?php
/**
 * @file
 * Imagecrop class to handle the javascript imagecrop.
 *
 */

class ImageCrop {

  protected $allowedExtensions = array('image/jpeg', 'image/gif', 'image/png', 'image/pjpeg');
  protected $inCroppingMode = FALSE;
  public $skipPreview = FALSE;
  public $extraControls = FALSE;

  protected $file;
  protected $imageStyle;
  protected $entityType = 'none';
  protected $bundle = 'none';
  protected $fieldName = 'none';
  protected $styleDestination;
  protected $cropDestination;
  protected $imageWidth;
  protected $originalImageWidth;
  protected $originalImageHeight;

  protected $isResizable = FALSE;
  protected $downscalingAllowed = TRUE;
  protected $resizeAspectRatio = FALSE;
  protected $width = 0;
  protected $startWidth = 0;
  protected $height = 0;
  protected $startHeight = 0;
  protected $xoffset = 0;
  protected $yoffset = 0;
  protected $scale = 'original';
  protected $rotation = 0;
  protected $disableIfNoData = FALSE;
  protected $hasSettings = FALSE;

  /**
   * Construct imagecrop.
   */
  public function __construct() {
    $this->skipPreview = variable_get('imagecrop_skip_preview', FALSE);
    $this->extraControls = variable_get('imagecrop_ui_controls', FALSE);
  }

  /**
   * Load the imagecrop settings for the given fid or filesource.
   * @param $lookup fid of filesource
   * @param $use_fid the first param is a fid
   */
  public function loadFile($filesource, $use_fid = TRUE) {

    if ($use_fid) {
      $this->file = file_load($filesource);
    }
    else {
      $query = db_select('file_managed', 'f');
      $query->fields('f', array('fid', 'uid', 'uri', 'filemime'));
      $query->condition('uri', $filesource);
      $this->file = $query->execute()->fetchObject();
    }

    if (!$this->file) {
      throw new Exception('The image to crop was not found.');
    }

    if (!in_array($this->file->filemime, $this->allowedExtensions)) {
      throw new Exception('The file to crop was not an image.');
    }

    $this->file->filepath = file_create_url($this->file->uri);

  }

  /**
   * Get the current file.
   */
  public function getFile() {
    return $this->file;
  }

  /**
   * Set the current file
   */
  public function setFile($file) {
    $this->file = $file;
  }

  /**
   * Set the entity type from the current imagecrop.
   */
  public function setEntityType($entity_type) {
    $this->entityType = $entity_type;
  }

 /**
   * Get the entity type from the current imagecrop.
   */
  public function getEntityType() {
    return $this->entityType;
  }

  /**
   * Set the bundle from the current imagecrop.
   */
  public function setBundle($bundle) {
    $this->bundle = $bundle;
  }

  /**
   * Get the bundle from the current imagecrop.
   */
  public function getBundle() {
    return $this->bundle;
  }

  /**
   * Set the field name from the current imagecrop.
   */
  public function setFieldName($field_name) {
    $this->fieldName = $field_name;
  }

  /**
   * Get the field name from the current imagecrop.
   */
  public function getFieldName() {
    return $this->fieldName;
  }

  /**
   * Is the crop resizable or not.
   */
  public function isResizable() {
    return $this->isResizable;
  }

  /**
   * Get the X offset from the current imagecrop object.
   */
  public function getXOffset() {
    return $this->xoffset;
  }

  /**
   * Get the X offset from the current imagecrop object.
   */
  public function getYOffset() {
    return $this->yoffset;
  }

  /**
   * Get the width from the current crop area.
   */
  public function getWidth() {
    return $this->width;
  }

  /**
   * Get the height from the current crop area.
   */
  public function getHeight() {
    return $this->height;
  }

  /**
   * Get the width from the image to crop.
   */
  public function getImageWidth() {
    return $this->imageWidth;
  }

  /**
   * Get the original width from the image to crop.
   */
  public function getOriginalImageWidth() {
    return $this->originalImageWidth;
  }

  /**
   * Set the scaling width from the image to crop.
   */
  public function setScale($scale) {
    $this->scale = $scale;
  }

  /**
   * Get the scaling from the image to crop.
   */
  public function getScale() {
    return $this->scale;
  }

  /**
   * Set the rotation from the image to crop.
   */
  public function setRotation($rotation) {
    $this->rotation = $rotation;
  }

  /**
   * Get the rotation from the image to crop.
   */
  public function getRotation() {
    return $this->rotation;
  }

  /**
   * Get the height from the image to crop.
   */
  public function getImageHeight() {
    return $this->imageHeight;
  }

  /**
   * Get the original height from the image to crop.
   */
  public function getOriginalImageHeight() {
    return $this->originalImageHeight;
  }

  /**
   * Set the status of cropping mode (TRUE = busy cropping).
   */
  public function setInCroppingMode($inCroppingMode) {
    $this->inCroppingMode = $inCroppingMode;
  }

  /**
   * Get the current value for cropping mode.
   */
  public function getInCroppingMode() {
    return $this->inCroppingMode;
  }

  /**
   * Set the current cropped image style.
   */
  public function setImageStyle($style_name) {

    $this->imageStyle = image_style_load($style_name);

    if (!$this->imageStyle) {
      throw new Exception('The image style to crop was not found.');
    }

    // add default settings
    foreach ($this->imageStyle['effects'] as $effect) {
      if ($effect['name'] == 'imagecrop_javascript') {
        $this->width = $effect['data']['width'];
        $this->startWidth = $effect['data']['width'];
        $this->height = $effect['data']['height'];
        $this->startHeight = $effect['data']['height'];

        if ($effect['data']['xoffset']) {
          $this->xoffset = $effect['data']['xoffset'];
        }

        if ($effect['data']['yoffset']) {
          $this->yoffset = $effect['data']['yoffset'];
        }

        $this->isResizable = $effect['data']['resizable'];
        $this->disableIfNoData = $effect['data']['disable_if_no_data'];
        $this->resizeAspectRatio = !empty($effect['data']['aspect_ratio']) ? $effect['data']['aspect_ratio'] : FALSE;
        $this->downscalingAllowed = !$effect['data']['downscaling'];
        break;
      }
    }

  }

  /**
   * Get the current cropped image style.
   */
  public function getImageStyle() {
    return $this->imageStyle;
  }

  /**
   * Set the crop destinations.
   */
  public function setCropDestinations() {

    $this->styleDestination = image_style_path($this->imageStyle['name'], $this->file->uri);
    if (file_uri_scheme($this->file->uri) != 'public') {
      $this->cropDestination = $this->styleDestination;
    }
    else {
      $this->cropDestination = image_style_path('_imagecrop_temp', $this->file->uri);
    }

  }

  /**
   * Get the destination from the image for current style.
   */
  public function getStyleDestination() {
    return $this->styleDestination;
  }

  /**
   * Get the destination from the image for cropping the current style.
   * @param $filepath Boolean, TRUE to return the filepath, FALSE to return the uri.
   */
  public function getCropDestination($filepath = TRUE, $add_timestamp = TRUE) {
    $image_url = ($filepath) ?  file_create_url($this->cropDestination) : $this->cropDestination;
    if ($add_timestamp) {
      $image_url .= (strpos($image_url, '?') !== FALSE) ? '&' : '?';
      $image_url .= 'time=' . $_SERVER['REQUEST_TIME'];
    }
    return $image_url;
  }

  /**
   * Check if a user has permissions to crop the current file.
   *
   * @param object $account
   *   The user whose access you want to check
   */
  public function hasUserAccess($account) {

    // User has access to all images
    if (user_access('crop any image', $account) || user_access('administer nodes', $account)) {
      return TRUE;
    }

    // User has access to this specific image
    if ($this->file && user_access('crop own images', $account) && $account->uid == $this->file->uid) {
      return TRUE;
    }

    return FALSE;

  }

  /**
   * Load the crop settings that are available.
   */
  public function loadCropSettings() {

    $size = getimagesize($this->file->uri);
    $this->imageWidth = $this->originalImageWidth = $size[0];
    $this->imageHeight = $this->originalImageHeight = $size[1];

    $settings = db_select('image_crop_settings')
      ->fields('image_crop_settings')
      ->condition('fid', $this->file->fid)
      ->condition('style_name', $this->imageStyle['name'])
      ->execute()->fetchObject();

    // Load settings
    if ($settings) {

      $this->xoffset = $settings->xoffset;
      $this->yoffset = $settings->yoffset;
      $this->width = $settings->width;
      $this->height = $settings->height;
      $this->scale = $settings->scale;
      $this->rotation = $settings->rotation;
      $this->hasSettings = TRUE;

    }
    else {

      // Check for default scale
      if (variable_get('imagecrop_scale_default', FALSE)) {

        $step = variable_get('imagecrop_scale_step', 50);
        $popup_width = variable_get('imagecrop_popup_width', 700);
        $popup_height = variable_get('imagecrop_popup_height', 600) - 50;

        // If controls are in sidebar, count this also.
        if ($this->extraControls) {
          $popup_width -= 215;
        }

        $scale_width = $this->originalImageWidth;
        $aspect = $this->originalImageWidth / $this->originalImageHeight;
        if ($step > 0) {
          $scale_width -= $step;
          while ($scale_width > $this->width && ($scale_width / $aspect) > $this->height) {
            $scaled_height = intval($scale_width / $aspect);
            if ($scaled_height < $popup_height && $scale_width < $popup_width) {
              $this->scale = $scale_width;
              break;
            }
            $scale_width -= $step;
          }
        }

      }

    }

    // Scale to requested width
    if ($this->scale != 'original') {
      $aspect = $this->originalImageWidth / $this->originalImageHeight;
      $this->imageWidth = $this->scale;
      $this->imageHeight = intval($this->imageWidth / $aspect);
    }

    // Extra actions after the scaling action.
    if (!$this->hasSettings) {
      // Check if the default width is a %
      if (strpos($this->width, '%')) {
        $procent_width = str_replace('%', '', $this->width);
        $this->width = ($this->imageWidth * ($procent_width / 100));
      }

      // Check if the default width is a %
      if (strpos($this->height, '%')) {
        $procent_height = str_replace('%', '', $this->height);
        $this->height = ($this->imageHeight * ($procent_height / 100));
      }
    }

    // Keep the aspect ratio from original image
    if ($this->resizeAspectRatio == 'KEEP') {
      $this->resizeAspectRatio = $this->imageWidth / $this->imageHeight;
    }
    // Keep the aspect ratio from the crop settings
    elseif ($this->resizeAspectRatio == 'CROP') {
      $this->resizeAspectRatio = $this->startWidth / $this->startHeight;
    }

    // Set correct xoffset when a keyword is entered.
    if (!is_numeric($this->xoffset)) {

      switch ($this->xoffset) {

        case 'right':
          $this->xoffset = $this->imageWidth - $this->width;
        break;

        case 'center':
          $this->xoffset = round(($this->imageWidth / 2) - ($this->width / 2));
        break;

        case 'left':
        default:
          $this->xoffset = 0;
        break;

      }

    }

    // Set correct yoffset when a keyword is entered.
    if (!is_numeric($this->yoffset)) {

      switch ($this->yoffset) {

        case 'bottom':
          $this->yoffset = $this->imageHeight - $this->height;
        break;

        case 'center':
          $this->yoffset = round(($this->imageHeight / 2) - ($this->height / 2));
        break;

        case 'top':
        default:
          $this->yoffset = 0;
        break;

      }

    }

  }

  /**
   * Apply all the crop settings to the given image source.
   * @param $image image object from image module
   */
  public function applyCrop(&$image) {

    if (!$this->hasSettings && $this->disableIfNoData) {
      return;
    }

    // Scale first if requested
    if ($this->scale != 'original') {
      $data = array(
        'width' => $this->scale,
        'height' => PHP_INT_MAX,
      );
      image_scale_effect($image, $data);
    }

    // Rotate if requested
    if ($this->rotation > 0) {

      $data = array(
        'degrees' => $this->rotation,
      );
      image_rotate_effect($image, $data);

    }

    $data = array(
      'anchor' => $this->xoffset . '-' . $this->yoffset,
      'width' => $this->width,
      'height' => $this->height,
    );
    image_crop_effect($image, $data);

  }

  /**
   * Write the file to crop, and apply all effects, untill the imagecrop effectso cropping can be done.
   */
  public function writeCropreadyImage() {

    $unset = FALSE;
    $smartcrop = FALSE;
    $style = $this->imageStyle;

    foreach ($this->imageStyle['effects'] as $key => $effect) {

      if ($effect['name'] == 'smartcrop_crop') {
        $smartcrop = $effect;
      //  $unset = TRUE;
      }

      if ($effect['name'] == 'imagecrop_javascript') {
        $unset = TRUE;
      }

      if ($unset) {
        unset($style['effects'][$key]);
      }

    }

    /*if ($smartcrop) {
      $image = image_load($this->file->uri);
      $coordinates = _smartcrop_get_coordinates($image, $this->width, $this->height);
      if (!$this->hasSettings) {
        $this->xoffset = $coordinates['dst_x'];
        $this->yoffset = $coordinates['dst_y'];
      }
    }*/

    // Save a first time, after the effects are done, for knowing the resulted width / height
    image_style_create_derivative($style, $this->file->uri, $this->cropDestination);

    // Set imageWidth and height after effects are done.
    $size = getimagesize($this->cropDestination);
    $this->imageWidth = $this->originalImageWidth = $size[0];
    $this->imageHeight = $this->originalImageHeight = $size[1];

    $changed = FALSE;
    if ($this->scale !== 'original') {

      $style['effects'][] = array(
        'effect callback' => 'image_scale_effect',
        'data' => array(
          'width' => $this->scale,
        ),
      );

      $changed = TRUE;

    }

    if ($this->rotation > 0) {

      $style['effects'][] = array(
        'effect callback' => 'image_rotate_effect',
        'data' => array(
          'degrees' => $this->rotation,
        ),
      );

      $changed = TRUE;

    }

    // Extra changes need to be done, save second time.
    if ($changed) {
      image_style_create_derivative($style, $this->file->uri, $this->cropDestination);
    }

  }

  /**
   * Add all the files for the cropping UI.
   */
  public function addImagecropUi($in_cropping_mode) {

    $path = drupal_get_path('module', 'imagecrop');
    drupal_add_js($path . '/js/imagecrop.js');
    drupal_add_css($path . '/css/imagecrop.css');

    $popup_js = $path . '/js/popups/' . variable_get('imagecrop_popup', 'basic') . '.js';
    if (file_exists($popup_js)) {
      drupal_add_js($popup_js);
    }

    // Add crop ui if in cropping mode.
    if ($in_cropping_mode) {

      drupal_add_js($path . '/js/jcrop/jquery.Jcrop.js');
      drupal_add_css($path.'/css/jquery.Jcrop.css');
      drupal_add_js($path . '/js/imagecrop.ui.crop.js');

      $settings = array(
        'manipulationUrl' => url('imagecrop/generate_image'),
        'cropped' => isset($_GET['cropping']),
        'resizable' => $this->isResizable,
        'aspectRatio' => FALSE,
        'minWidth' => 0,
        'minHeight' => 0,
        'rotation' => variable_get('imagecrop_rotation', FALSE),
      );

      if ($this->isResizable) {
        $settings['aspectRatio'] = $this->resizeAspectRatio;
        $settings['minWidth'] = ($this->downscalingAllowed ? 0 : $this->startWidth);
        $settings['minHeight'] = ($this->downscalingAllowed ? 0 : $this->startHeight);
        $settings['startHeight'] = $this->startHeight;
        $settings['startWidth'] = $this->startWidth;
      }

      drupal_add_js(array('imagecrop' => $settings), 'setting');

    }

  }

}
