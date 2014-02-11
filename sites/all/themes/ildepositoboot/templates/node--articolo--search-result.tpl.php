<div class="type-icon">
  <?php print $icon_type; ?>
</div>

<div<?php print $attributes; ?>>
      <?php //print $human_type; ?>
  <h2<?php print $title_attributes; ?>><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2> <?php if (isset($icons)) { print '<span class="icons">' . $icons . '</span>'; } ?>

  <div<?php print $content_attributes; ?> style="clear: left;">
    <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    print '<div>Pubblicato il ' . $date . '</div>';
    print render($content);    
    ?>
  </div>

  <div class="clearfix">
<?php if (!empty($content['links'])): ?>
      <div class="links node-links clearfix"><?php print render($content['links']); ?></div>
    <?php endif; ?>

    <?php print render($content['comments']); ?>
  </div>
</div>