<?php
/**
 * @file
 * ildeposito_tassonomie.openlayers_maps.inc
 */

/**
 * Implements hook_openlayers_maps().
 */
function ildeposito_tassonomie_openlayers_maps() {
  $export = array();

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'mappa_percorsoclone_of_eventi_mappa';
  $openlayers_maps->title = 'Mappa percorso';
  $openlayers_maps->description = 'gli eventi del percorso';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '250px',
    'image_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/img/',
    'css_path' => 'sites/all/modules/contrib/openlayers/themes/default_dark/style.css',
    'proxy_host' => '',
    'hide_empty_map' => 0,
    'center' => array(
      'initial' => array(
        'centerpoint' => '0,0',
        'zoom' => '2',
      ),
      'restrict' => array(
        'restrictextent' => 0,
        'restrictedExtent' => '',
      ),
    ),
    'behaviors' => array(
      'openlayers_behavior_cluster' => array(
        'clusterlayer' => array(
          'mappa_percorso_mappa_overlay_percorso' => 'mappa_percorso_mappa_overlay_percorso',
        ),
        'distance' => '20',
        'threshold' => '',
        'display_cluster_numbers' => 1,
        'middle_lower_bound' => '15',
        'middle_upper_bound' => '50',
        'low_color' => 'rgb(141, 203, 61)',
        'middle_color' => 'rgb(49, 190, 145)',
        'high_color' => 'rgb(35, 59, 177)',
      ),
      'openlayers_behavior_keyboarddefaults' => array(),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_popup' => array(
        'layers' => array(
          'mappa_percorso_mappa_overlay_percorso' => 'mappa_percorso_mappa_overlay_percorso',
        ),
        'panMapIfOutOfView' => 1,
        'keepInMap' => 1,
      ),
      'openlayers_behavior_touch_navigation' => array(
        'documentDrag' => 1,
      ),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'mappa_percorso_mappa_overlay_percorso' => 'mappa_percorso_mappa_overlay_percorso',
          'mapquest_osm' => 0,
        ),
        'point_zoom_level' => '7',
        'zoomtolayer_scale' => '1',
      ),
    ),
    'default_layer' => 'mapquest_osm',
    'layers' => array(
      'mapquest_osm' => 'mapquest_osm',
      'mappa_percorso_mappa_overlay_percorso' => 'mappa_percorso_mappa_overlay_percorso',
    ),
    'layer_weight' => array(
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'home_eventi_eventi_home_overlay' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
    ),
    'layer_styles' => array(
      'contenuti_eventi_eventi_mappa_overlay' => 'default',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'home_eventi_eventi_home_overlay' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'mappa_percorso_mappa_overlay_percorso' => 'ildeposito',
    ),
    'layer_styles_select' => array(
      'contenuti_eventi_eventi_mappa_overlay' => 'default',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'home_eventi_eventi_home_overlay' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'mappa_percorso_mappa_overlay_percorso' => 'ildeposito',
    ),
    'layer_styles_temporary' => array(
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'home_eventi_eventi_home_overlay' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
    ),
    'layer_activated' => array(
      'mappa_percorso_mappa_overlay_percorso' => 'mappa_percorso_mappa_overlay_percorso',
      'contenuti_eventi_eventi_mappa_overlay' => 0,
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'openlayers_kml_example' => 0,
      'contenuti_eventi_overlay_singolo_evento' => 0,
      'home_eventi_eventi_home_overlay' => 0,
      'evento_mappa_mappa_evento_overlay' => 0,
      'evento_mappa_mappa_evento_overlay_prox' => 0,
    ),
    'layer_switcher' => array(
      'mappa_percorso_mappa_overlay_percorso' => 0,
      'contenuti_eventi_eventi_mappa_overlay' => 0,
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'openlayers_kml_example' => 0,
      'contenuti_eventi_overlay_singolo_evento' => 0,
      'home_eventi_eventi_home_overlay' => 0,
      'evento_mappa_mappa_evento_overlay' => 0,
      'evento_mappa_mappa_evento_overlay_prox' => 0,
    ),
    'projection' => 'EPSG:900913',
    'displayProjection' => 'EPSG:4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default_select',
      'temporary' => 'default',
    ),
  );
  $export['mappa_percorsoclone_of_eventi_mappa'] = $openlayers_maps;

  return $export;
}
