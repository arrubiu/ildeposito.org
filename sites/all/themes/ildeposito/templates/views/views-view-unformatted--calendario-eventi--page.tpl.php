<?php
/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>

<div class=" <?php print $zebra; ?>">

  <?php if (!empty($title)): ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>
  <?php foreach ($rows as $id => $row): ?>
    <div<?php if ($classes_array[$id]) {
    print ' class="' . $classes_array[$id] . ' risultato grid-9 ildeposito-col"';
  } ?>>
    <?php print $row; ?>
    </div>
<?php endforeach; ?>
</div>