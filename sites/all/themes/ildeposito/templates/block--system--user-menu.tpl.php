<div<?php print $attributes; ?>>
  <div class="block-inner clearfix">
    <?php print render($title_prefix); ?>
    <?php if ($block->subject): ?>
      <h2<?php print $title_attributes; ?>><?php print $block->subject; ?></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    
    <div<?php print $content_attributes; ?>>
      <div class="benvenuto"><?php print $utente; ?> (<?php print l('Logout', 'user/logout'); ?>)</div>
      <?php print $content ?>
    </div>
  </div>
</div>
