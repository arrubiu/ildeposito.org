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

  <div class="grid-12 col-first">
		
		<div class="dati-canto">
    <?php
    // We hide the comments and links now so that we can render them later.

		if ($foto_autori) {
			print $foto_autori;
		}
    print render($content['field_sezione']);
    print render($content['field_autore_testo']);
    print render($content['field_anno']);
		
		?>
		</div>
		<?php

    print $tabs;
    ?>  

		<div class="info-canto">
    <?php if ($field_informazioni): ?>
		<h2 class="block-title"">Informazioni</h2>
      <?php print render($content['field_informazioni']); ?>
	
    <?php endif; ?>

    <?php if ($field_fonte): ?>
      <h2 class="block-title"">Indicazioni bibliografiche</h2>
      <?php print render($content['field_fonte']); ?>
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

    <?php
    $view = views_get_view('check_relazioni');
    $view->set_display('eventi');
    $view->set_arguments(array($node->nid));
    $view->pre_execute();
    $view->execute();
    if (count($view->result) > 0) {
      print '<h2 class="block-title top">La storia cantata</h2>';
      print $view->preview();
    }
    ?>

    <h2 class="block-title top">Scheda del canto</h2>
    <?php
    print render($content['field_sezione']);
    print render($content['field_autore_testo']);
    print render($content['field_autore_musica']);
    print render($content['field_anno']);
    print render($content['field_tags']);
    print render($content['field_lingua']);
    print '<div>Inserito da: ' . _print_user($node->uid) . '</div>';
    ?>


    <div id="disclaimer">
      <div class="title">Note di pubblicazione</div>
      I diritti del contenuto sono dei rispettivi autori.<br />
      Lo staff de ilDeposito.org non condivide necessariamente il contenuto,
      che viene inserito nell'archivio unicamente per il suo valore storico, artistico o culturale (<a href="#">maggiori informazioni</a>).

    </div>


  </div>



  <div class="clearfix" style="clear: left;">
    <?php if (!empty($content['links'])): ?>
      <div class="links node-links clearfix"><?php print render($content['links']); ?></div>
    <?php endif; ?>

    <?php print render($content['comments']); ?>
  </div>
</div>
