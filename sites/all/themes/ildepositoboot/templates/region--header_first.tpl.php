<div<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
    <?php //print $content; ?>

    <div id="breadcrumb">
      <?php
      $bcarr = drupal_get_breadcrumb();
      $bcarr [] = drupal_get_title();
      print theme('breadcrumb', array('breadcrumb' => $bcarr));
      ?>
    </div>
  </div>
</div>

