<div<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
    <a id="main-content"></a>

    <?php if ($messages): ?>
      <div id="messages"><?php print $messages; ?></div>
    <?php endif; ?>

    <?php print render($title_prefix); ?>
    <?php if ($title): ?>
      <?php if ($title_hidden): ?><div class="element-invisible"><?php endif; ?>
        <h1 class="title" id="page-title">
          <?php
          $args = explode('/', $_SERVER['REQUEST_URI']);

          // Autori
          if (isset($args['3']) && $args['2'] == 'autori') {
            $title = 'I canti di ' . $title;
          }

          // Tematiche
          if (isset($args['3']) && $args['2'] == 'tematiche') {
            $title = 'Contenuti per la tematica \'' . $title . '\'';
          }

          // Lingue
          if (isset($args['3']) && $args['2'] == 'lingue') {
            $title = 'Contenuti in \'' . $title . '\'';
          }

          // Localizzazioni
          if (isset($args['3']) && $args['2'] == 'localizzazione') {
            $title = 'Contenuti localizzati in ' . $title;
          }

          // Percorsi
          if (isset($args['3']) && $args['2'] == 'percorsi') {
            $title = 'Percorso: \'' . $title . '\'';
          }

          // Percorsi
          if (isset($args['3']) && $args['2'] == 'tags') {
            $title = 'Contenuti per il tag \'' . $title . '\'';
          }



          print $title;
          ?>
        </h1>
        <?php if ($title_hidden): ?></div><?php endif; ?>
      <?php endif; ?>
    <?php print render($title_suffix); ?>

    <?php if ($tabs && !empty($tabs['#primary'])): ?><div class="tabs clearfix"><?php print render($tabs); ?></div><?php endif; ?>
    <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
    <?php print $content; ?>
    <?php if ($feed_icons): ?><div class="feed-icon clearfix"><?php print $feed_icons; ?></div><?php endif; ?>
  </div>
</div>
