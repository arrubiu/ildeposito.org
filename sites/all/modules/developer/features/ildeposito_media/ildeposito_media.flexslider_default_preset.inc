<?php
/**
 * @file
 * ildeposito_media.flexslider_default_preset.inc
 */

/**
 * Implements hook_flexslider_default_presets().
 */
function ildeposito_media_flexslider_default_presets() {
  $export = array();

  $preset = new stdClass();
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 1;
  $preset->name = 'foto_autore';
  $preset->title = 'Foto autore';
  $preset->theme = 'classic';
  $preset->imagestyle_normal = 'foto_autore';
  $preset->imagestyle_thumbnail = 'foto_autore';
  $preset->options = array(
    'namespace' => 'flex-',
    'selector' => '.slides > li',
    'easing' => 'swing',
    'direction' => 'horizontal',
    'reverse' => 0,
    'smoothHeight' => 0,
    'startAt' => '0',
    'animationSpeed' => '600',
    'initDelay' => '0',
    'useCSS' => 1,
    'touch' => 0,
    'video' => 0,
    'keyboard' => 0,
    'multipleKeyboard' => 0,
    'mousewheel' => 0,
    'controlsContainer' => '.flex-control-nav-container',
    'sync' => '',
    'asNavFor' => '',
    'itemWidth' => '0',
    'itemMargin' => '0',
    'minItems' => '0',
    'maxItems' => '0',
    'move' => '0',
    'animation' => 'fade',
    'slideshow' => 1,
    'slideshowSpeed' => '7000',
    'directionNav' => 0,
    'controlNav' => '0',
    'prevText' => 'Precedente',
    'nextText' => 'Seguente',
    'pausePlay' => 0,
    'pauseText' => 'Pausa',
    'playText' => 'Play',
    'randomize' => 0,
    'thumbCaptions' => 0,
    'thumbCaptionsBoth' => 0,
    'animationLoop' => 1,
    'pauseOnAction' => 1,
    'pauseOnHover' => 0,
    'manualControls' => '',
  );
  $export['foto_autore'] = $preset;

  return $export;
}
