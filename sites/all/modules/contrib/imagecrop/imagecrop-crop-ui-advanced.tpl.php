<?php

/**
 * @file
 * Advanced Imagecrop crop UI template
 *
 */
$style = $imagecrop->getImageStyle();
?>
<div id="imagecrop-ui-advanced">

  <div id="imagecrop-selection" class="clearfix">
    <?php print drupal_render($style_selection); ?>
    <?php if (!$imagecrop->skipPreview): ?>
    <a href="#" onclick="javascript: Drupal.Imagecrop.changeViewedImage('<?php print $style['name'] ?>'); return false;" class="form-item imagecrop-form-link"><?php print t('Back to preview from this style') ?></a>
    <?php endif; ?>
  </div>

  <div id="imagecrop-left-controls">

    <div id="imagecrop-forms" class="clearfix">
    <?php
      print drupal_render($scale_form);

      if ($rotation_form) {
        print drupal_render($rotation_form);
      }

      print drupal_render($settings_form);
    ?>
    </div>

  </div>

  <div id="imagecrop-right" style="width: <?php print (variable_get('imagecrop_popup_width', 700) - 237) ?>px">

    <div id="imagecrop-help">
      <?php print t("Resize image if needed, then select a crop area. Click 'Save selection' to save the changes."); ?>
    </div>

    <div id="imagecrop-crop-container">
      <?php print theme('image', array('path' => $imagecrop->getCropDestination(), 'attributes' => array('id' => 'imagecrop-image'))); ?>
    </div>

  </div>
</div>