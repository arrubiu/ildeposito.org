<?php
/**
 * @file
 * ildeposito_home.openlayers_maps.inc
 */

/**
 * Implements hook_openlayers_maps().
 */
function ildeposito_home_openlayers_maps() {
  $export = array();

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'eventi_home';
  $openlayers_maps->title = 'Eventi Home';
  $openlayers_maps->description = '';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '160px',
    'image_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/img/',
    'css_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0,0',
        'zoom' => '0',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_cluster' => array(
        'clusterlayer' => array(
          'home_eventi_eventi_home_overlay' => 'home_eventi_eventi_home_overlay',
        ),
        'distance' => '20',
        'threshold' => '',
        'display_cluster_numbers' => 1,
        'middle_lower_bound' => '15',
        'middle_upper_bound' => '50',
        'low_color' => 'rgb(141, 203, 61)',
        'low_stroke_color' => 'rgb(141, 203, 61)',
        'low_opacity' => '0.8',
        'low_point_radius' => '10',
        'low_label_outline' => '1',
        'middle_color' => 'rgb(49, 190, 145)',
        'middle_stroke_color' => 'rgb(49, 190, 145)',
        'middle_opacity' => '0.8',
        'middle_point_radius' => '16',
        'middle_label_outline' => '1',
        'high_color' => 'rgb(35, 59, 177)',
        'high_stroke_color' => 'rgb(35, 59, 177)',
        'high_opacity' => '0.8',
        'high_point_radius' => '22',
        'high_label_outline' => '1',
        'label_low_color' => '#000000',
        'label_low_opacity' => '0.8',
        'label_middle_color' => '#000000',
        'label_middle_opacity' => '0.8',
        'label_high_color' => '#000000',
        'label_high_opacity' => '0.8',
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_popup' => array(
        'layers' => array(
          'home_eventi_eventi_home_overlay' => 'home_eventi_eventi_home_overlay',
        ),
        'popupAtPosition' => 'mouse',
        'panMapIfOutOfView' => 1,
        'keepInMap' => 1,
      ),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'home_eventi_eventi_home_overlay' => 'home_eventi_eventi_home_overlay',
          'google_normal' => 0,
        ),
        'point_zoom_level' => '5',
        'zoomtolayer_scale' => '1',
      ),
    ),
    'default_layer' => 'mapquest_osm',
    'layers' => array(
      'mapquest_osm' => 'mapquest_osm',
      'home_eventi_eventi_home_overlay' => 'home_eventi_eventi_home_overlay',
    ),
    'layer_weight' => array(
      'elenco_gruppi_overlay_mappa_cori' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'home_eventi_eventi_home_overlay' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
    ),
    'layer_styles' => array(
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'elenco_gruppi_overlay_mappa_cori' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'home_eventi_eventi_home_overlay' => 'ildeposito',
    ),
    'layer_styles_select' => array(
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'elenco_gruppi_overlay_mappa_cori' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'home_eventi_eventi_home_overlay' => 'ildeposito',
    ),
    'layer_styles_temporary' => array(
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'elenco_gruppi_overlay_mappa_cori' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'home_eventi_eventi_home_overlay' => '0',
    ),
    'layer_activated' => array(
      'home_eventi_eventi_home_overlay' => 'home_eventi_eventi_home_overlay',
      'contenuti_eventi_eventi_mappa_overlay' => 0,
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'openlayers_kml_example' => 0,
      'mappa_percorso_mappa_overlay_percorso' => 0,
      'contenuti_eventi_overlay_singolo_evento' => 0,
      'elenco_gruppi_overlay_mappa_cori' => 0,
      'evento_mappa_mappa_evento_overlay' => 0,
      'evento_mappa_mappa_evento_overlay_prox' => 0,
    ),
    'layer_switcher' => array(
      'home_eventi_eventi_home_overlay' => 'home_eventi_eventi_home_overlay',
      'contenuti_eventi_eventi_mappa_overlay' => 0,
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'openlayers_kml_example' => 0,
      'mappa_percorso_mappa_overlay_percorso' => 0,
      'contenuti_eventi_overlay_singolo_evento' => 0,
      'elenco_gruppi_overlay_mappa_cori' => 0,
      'evento_mappa_mappa_evento_overlay' => 0,
      'evento_mappa_mappa_evento_overlay_prox' => 0,
    ),
    'projection' => 'EPSG:3857',
    'displayProjection' => 'EPSG:4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default_select',
      'temporary' => 'default',
    ),
  );
  $export['eventi_home'] = $openlayers_maps;

  return $export;
}
