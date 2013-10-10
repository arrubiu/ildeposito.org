<?php
/**
 * @file
 * Template file for field_slideshow
 */
?>
<div class="slideshow-wrapper">
  <div class="preloader"></div>
  <ul class="<?php print $classes; ?>" data-orbit data-options="<?php print $data_options; ?>">
    <?php foreach ($items as $key => $item) : ?>
      <li data-orbit-slide="slide-<?php print $key; ?>"><?php print $item['media']; ?>
        <?php if (isset($item['caption']) && $item['caption'] != '') : ?>
          <div class="orbit-caption"><?php print $item['caption']; ?></div>
        <?php endif; ?>
      </li>
    <?php endforeach; ?>
  </ul>

  <?php if ($options['orbit_bullets']) : ?>
    <div class="orbit-bullet-container">
      <ul class="orbit-bullet-thumbs">
        <?php foreach ($items as $key => $item) : ?>
          <li>
            <a href="#" data-orbit-link="slide-<?php print $key; ?>"><?php print $item['thumb']; ?></a>
          </li>
        <?php endforeach; ?>
      </ul>
    </div>
  <?php endif; ?>
</div>