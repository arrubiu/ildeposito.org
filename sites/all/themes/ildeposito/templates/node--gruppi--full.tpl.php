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
      <div class="submitted">Pubblicato da <?php print $name; ?> il <?php print $date; ?>
          <?php print render($content['field_tags']); ?>
      </div>
    <?php endif; ?>  
</div>
<div<?php print $content_attributes; ?>>

    <div class="grid-10 col-first">
        <?php if (count($field_images) > 0) : ?>
          <div class="gruppo-image">
          <?php
          print render($content['field_images'][0]);
          ?>
          </div>

        <?php endif; ?>


        <?php print render($content['body']); ?>
    </div>
    <div class="grid-8 col-second mappa">

        <?php print render($content['field_geofield']); ?>

        <h2 class="block-title">Condividi</h2>    
        <?php
        $block = module_invoke('service_links', 'block_view', 'service_links');
        print render($block['content']);
        ?>
    </div>

    <div class="clearfix" style="clear: left;">

        <h2 class="block-title">Scheda</h2>  
        <?php print render($content['field_citta']); ?>
        <?php print render($content['field_anno']); ?>
        <?php print render($content['field_indirizzo']); ?>
        <?php print render($content['field_email']); ?>
        <?php print render($content['field_links']); ?>
        <?php print render($content['field_link_audio']); ?>


        <div class="multi">

            <?php
            $a = 1;
            if (count($field_images) > 1) :
              ?>
              <h2 class="block-title">Immagini</h2>
              <?php
              unset ($content['field_images']['#items'][0]);
              print render($content['field_images']);
              ?>

<?php endif; ?>


<?php if (count($field_media) > 0) : ?>

              <h2 class="block-title">Video</h2>
              <?php print render($content['field_media']); ?>

<?php endif; ?>

        </div>
    </div>



    <div class="clearfix" style="clear: left;">
        <?php if (!empty($content['links'])): ?>
          <div class="links node-links clearfix"><?php print render($content['links']); ?></div>
        <?php endif; ?>

<?php print render($content['comments']); ?>
    </div>
</div>
