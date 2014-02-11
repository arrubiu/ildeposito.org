<div style="page-break-before: always; margin-top: 40px;"></div>
<h2><?php print $title ?></h2>

<div<?php print $content_attributes; ?>>
  




  <?php
  // We hide the comments and links now so that we can render them later.


  print render($content['field_sezione']);
  print render($content['field_autore_testo']);
  print render($content['field_anno']);
  print render($content['field_lingua']);
  print render($content['field_localizzazione']);
  print render($content['field_tags']);
  
  ?>
  <columns column-count="2" vAlign="J" column-gap="7" />
  <div class="testo" style="font-family:monospace;">
  <?php if ($node->field_presenza_accordi['und'][0]['value'] == 'no') {
    print render($content['field_testo']);
  }
  else {
    print render($content['field_accordi']);
  }
  ?>
    <columnbreak />
      <columns column-count="1" vAlign="J" column-gap="7" />
  </div>
  <?php
  print render($content['field_informazioni']);
  print render($content['field_fonte_biblio']);

  ?>  

</div>

