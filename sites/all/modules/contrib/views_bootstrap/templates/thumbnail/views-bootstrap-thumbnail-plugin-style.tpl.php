<?php
/**
 * @file views-bootstrap-thumbnail-plugin-style.tpl.php
 * Default simple view template to display Bootstrap Thumbnails.
 *
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 * - $column_type contains a number (default Bootstrap grid system column type).
 *
 * @ingroup views_templates
 */
?>

<div id="views-bootstrap-thumbnail-<?php print $id ?>" class="row <?php print $classes ?>">
  <?php foreach ($rows as $key => $row): ?>
    <div class="col col-lg-<?php print $column_type ?>">
      <div class="thumbnail">
        <?php print $row ?>
      </div>
    </div>
  <?php endforeach ?>
</div>
