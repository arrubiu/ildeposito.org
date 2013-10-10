<?php
/**
 * @file
 * Template file for ZURB clearing.
 */
?>

<div class="clearing-container">
  <ul class="clearing-thumbs<?php if ($options['featured']) : ?> clearing-feature<?php endif; ?>" data-clearing>
    <?php foreach ($images as $key => $image) : ?>
      <li<?php if ($key == 0 && $options['featured']) : ?> class="clearing-featured-img"<?php endif; ?>><?php print $image['thumbnail']; ?></li>
    <?php endforeach; ?>
  </ul>
</div>