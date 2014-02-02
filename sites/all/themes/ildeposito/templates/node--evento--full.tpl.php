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
  <div class="evento-head">
  <?php 
    if (isset($field_percorso)) {
      print render($content['field_percorso']);
    }
    
  ?>
  
  </div>
      
  <div class="grid-12 col-first">
    <div class="grid-6 col-second mappa">
    <div class="invisibile"><?php print render($content['field_images']); ?></div>
    <?php print render($content['field_geofield']); ?>  
    </div>
    <?php print render($content['field_informazioni']); ?>  

    <div class="grid-6 col-first">
      <?php if ($field_canti_evento): ?>
        <h2 class="block-title">Canti collegati</h2>
        <?php print render($content['field_canti_evento']); ?>
      <?php endif; ?>
    </div>

    <div class="grid-6 col-second">
      <?php if ($field_links): ?>
        <h2 class="block-title"">Link di approfondimento</h2>
        <?php print render($content['field_links']); ?>
      <?php endif; ?>
    </div>
  </div>

  <div class="grid-6 col-second">
    <h2 class="block-title">Condividi</h2>

    <?php
    $block = module_invoke('service_links', 'block_view', 'service_links');
    print render($block['content']);
    ?>
    
    <h2 class="block-title" style="margin-top: 20px;">Strumenti</h2>
      <div class="strumenti">
      <?php
      $block = module_invoke('alterator', 'block_view', 'strumenti');
      print render($block['content']);
      ?>
      </div>

    <h2 class="block-title top">Scheda dell'evento</h2>
    <?php
    print render($content['field_data_evento']);
    print render($content['field_percorso']);
    print render($content['field_sezione']);
    print render($content['field_tags']);
    print render($content['field_localizzazione']);

    ?>

    <?php
    if (isset($field_evento[0])) {
      print '<h2 class="block-title top">La storia cantata</h2>';
      print render($content['field_evento']);
    }
    ?>


  </div>



  <div class="clearfix" style="clear: left; padding-top: 30px;">
    <?php if (!empty($content['links'])): ?>
      <div class="links node-links clearfix"><?php print render($content['links']); ?></div>
    <?php endif; ?>

    <?php print render($content['comments']); ?>
  </div>
</div>
