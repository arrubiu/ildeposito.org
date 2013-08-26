<?php
// $Id$

/**
 * @file
 * Default theme implementation to display the slider-value form element
 *
 * Available variables:
 * - $element: The element array containing #id, #name,...
 */

?>
<?php if (isset($element["#title"])) : ?> 
<div>
  <strong><?php echo $element["#title"];?>:</strong>
</div>
<?php endif; ?> 
<div id="<?php echo $element["#id"]; ?>" class="slider-widget-container">
  <div style="float:left">
    <div id='<?php echo $element["#id"]; ?>_slider' class='ui-slider-1'></div>
  </div>
  <span style="margin-left: 15px;"><?php if (isset($element["#slider_suffix"])) { echo $element["#slider_suffix"]; } ?><span id='<?php echo $element["#id"]; ?>_nr_0'><?php echo $element["#default"] . $element["#value_suffix"]; ?></span></span>
</div>
<div style="clear:both;"></div>
<script type="text/javascript">
<!--
jQuery('#<?php echo $element["#id"];?>_slider').slider({
    slide: Sliders.changeHandle,
    step: <?php echo $element["#step"]; ?>,
    value: <?php echo $element["#default"]; ?>,
    max: <?php echo $element["#max"]; ?>,
    min: <?php echo $element["#min"]; ?>
  });
//-->
</script>
<?php if (isset($element["#description"])) : ?> 
<div class="description" style="margin-bottom:10px;"><?php echo $element["#description"];?></div>
<?php endif; ?> 
<input type="hidden" name='<?php echo $element["#name"]; ?>' id='<?php echo $element["#id"];?>_value_0' value='<?php echo $element["#default"]; ?>' />