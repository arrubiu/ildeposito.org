<div<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>    
    Questo contenuto è legato all'avento <?php print l($node->title, 'node/' . $node->nid); ?>  (<?php       
      print date("j F Y", strtotime($node->field_data_evento['und'][0]['value'])) . ').';     
      
     
      ?>

  </div>
</div>
