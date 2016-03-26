<?php
/**
 * @file
 * ildeposito_layout.openlayers_styles.inc
 */

/**
 * Implements hook_openlayers_styles().
 */
function ildeposito_layout_openlayers_styles() {
  $export = array();

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'ildeposito';
  $openlayers_styles->title = 'ilDeposito';
  $openlayers_styles->description = 'Basic default style.';
  $openlayers_styles->data = array(
    'pointRadius' => 6,
    'fillColor' => '#aa0000',
    'strokeColor' => '#aa0000',
    'strokeWidth' => 4,
    'fillOpacity' => 0.5,
    'strokeOpacity' => 0.69999999999999996,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicOpacity' => 1,
    'labelAlign' => 'cm',
  );
  $export['ildeposito'] = $openlayers_styles;

  $openlayers_styles = new stdClass();
  $openlayers_styles->disabled = FALSE; /* Edit this to true to make a default openlayers_styles disabled initially */
  $openlayers_styles->api_version = 1;
  $openlayers_styles->name = 'marker_red_ildeposito';
  $openlayers_styles->title = 'Marker Red Ildeposito';
  $openlayers_styles->description = '';
  $openlayers_styles->data = array(
    'externalGraphic' => 'sites/all/themes/ildeposito/images/marker_red.png',
    'pointRadius' => 6,
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => 1,
    'fillOpacity' => 1,
    'strokeOpacity' => 1,
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'graphicWidth' => 24,
    'graphicHeight' => 40,
    'graphicOpacity' => 1,
    'graphicXOffset' => -12,
    'graphicYOffset' => -40,
    'labelAlign' => 'cm',
  );
  $export['marker_red_ildeposito'] = $openlayers_styles;

  return $export;
}
