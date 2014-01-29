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

	<div class="grid-12 col-first">
		
		<?php print render($content['field_tipo_voce']); ?>
		<?php print render($content['field_links']); ?>
		
		
		<?php if  ($field_collana) : ?>		
				<?php print render($content['field_autore']); ?>
		
		<div style="margin-top: 20px;">all'interno di:</div>
				<?php print render($content['field_collana']); ?>
				<?php print render($content['field_editore']); ?>
				<?php print render($content['field_citta']); ?>
				<?php print render($content['field_anno']); ?>
		<?php endif; ?>
		
		<?php if  (!$field_collana): ?>		
		
				<?php print render($content['field_autore']); ?>
				<?php print render($content['field_editore']); ?>
				<?php print render($content['field_citta']); ?>
				<?php print render($content['field_anno']); ?>
		<?php endif; ?>

		<?php print render($content['field_tags']); ?>
		
		<?php if ($field_informazioni): ?>
		<h2 class="block-title margin">Informazioni</h2>
      <?php print render($content['field_informazioni']); ?>
	
    <?php endif; ?>

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

	</div>



  <div class="clearfix" style="clear: left;">
		<?php if (!empty($content['links'])): ?>
			<div class="links node-links clearfix"><?php print render($content['links']); ?></div>
		<?php endif; ?>

		<?php print render($content['comments']); ?>
  </div>
</div>
