<div<?php print $attributes; ?>>
  <?php print $user_picture; ?>
  <?php print render($title_prefix); ?>
  <?php if (!$page && $title): ?>
    <div>
      <h2<?php print $title_attributes; ?>><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
    </div>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($display_submitted): ?>
    <div class="submitted"><?php print $date; ?> -- <?php print $name; ?></div>
  <?php endif; ?>  
</div>
<div<?php print $content_attributes; ?>>

  <div class="<?php print $type; ?>">
    <?php
    // We hide the comments and links now so that we can render them later.
    print render($content['field_autore_testo']);
    print render($content['field_autore_musica']);
    print render($content['field_anno']);
    print render($content['field_sezione']);
    print render($content['field_tematica']);
    print render($content['field_lingua']);
    print render($content['field_localizzazione']);
    print render($content['field_tags']);

    if ($node->field_presenza_accordi['und']['0']['value'] == 'no') {
      print render($content['field_testo']);
    }
    else {
      print render($content['field_accordi']);
    }

    print render($content['field_informazioni']);
    print render($content['field_fonte']);
    ?>
  </div>


  <div class="clearfix">
<?php if (!empty($content['links'])): ?>
      <div class="links node-links clearfix"><?php print render($content['links']); ?></div>
    <?php endif; ?>

    <?php print render($content['comments']); ?>
  </div>
</div>