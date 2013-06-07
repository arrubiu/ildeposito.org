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

    <div class="grid-6 col-first">
      <?php
      // We hide the comments and links now so that we can render them later.


      print render($content['field_sezione']);
      print render($content['field_autore_testo']);
      print render($content['field_anno']);

      print $tabs;  
      
      ?>  
      
      <?php  if ($field_informazioni): ?>
        <h2 class="block-title"">Informazioni</h2>
        <?php print render($content['field_informazioni']); ?>
      <?php endif; ?>
      
      <?php  if ($field_fonte): ?>
        <h2 class="block-title"">Indicazioni bibliografiche</h2>
        <?php print render($content['field_fonte']); ?>
      <?php endif; ?>
    </div>

    <div class="grid-3 col-second">
      <h2 class="block-title">Condividi</h2>

      <?php
      $block = module_invoke('service_links', 'block_view', 'service_links');
      print render($block['content']);
      ?>

      <h2 class="block-title top">Scheda del canto</h2>
<?php
print render($content['field_sezione']);
print render($content['field_autore_testo']);
print render($content['field_autore_musica']);
print render($content['field_anno']);
print render($content['field_tematica']);
print render($content['field_lingua']);
print render($content['field_localizzazione']);
print render($content['field_tags']);
?>

      <?php
      if (isset($field_evento[0])) {
        print '<h2 class="block-title top">La storia cantata</h2>';
        print render($content['field_evento']);
      }
      ?>


    </div>
   
    
    
  <div class="clearfix">
<?php if (!empty($content['links'])): ?>
      <div class="links node-links clearfix"><?php print render($content['links']); ?></div>
    <?php endif; ?>

    <?php print render($content['comments']); ?>
  </div>
</div>