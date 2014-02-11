<div<?php print $attributes; ?>>

  <?php print $unpublished; ?>



  <?php print $picture; ?>

  <div class="comment-submitted">
   <?php
      print t('Submitted by !username', array('!username' => $author));
    ?><br />
    <?php
      print t('!datetime',
      array('!username' => $author, '!datetime' => '<time datetime="' . $datetime . '">' . $created . '</time>')); 
    ?> <?php if ($new) { print '<span class="new">(' . $new . ')</span>'; } ?>


       <?php if (!empty($content['links'])): ?>
    <?php print render($content['links']); ?>
  <?php endif; ?>

  </div>

  <div<?php print $content_attributes; ?>>
    <?php
      hide($content['links']);
      print render($content);
    ?>
  </div>

  <?php if ($signature): ?>
    <div class="user-signature"><?php print $signature ?></div>
  <?php endif; ?>


</div>
