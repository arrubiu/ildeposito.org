<?php
/**
 * @file
 * ildeposito_ct_evento.openlayers_maps.inc
 */

/**
 * Implements hook_openlayers_maps().
 */
function ildeposito_ct_evento_openlayers_maps() {
  $export = array();

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'eventi_mappa';
  $openlayers_maps->title = 'Eventi - Mappa';
  $openlayers_maps->description = 'La mappa di tutti gli eventi';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '500px',
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
          'contenuti_eventi_eventi_mappa_overlay' => 'contenuti_eventi_eventi_mappa_overlay',
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
      'openlayers_behavior_panzoombar' => array(
        'zoomWorldIcon' => 1,
        'panIcons' => 1,
      ),
      'openlayers_behavior_popup' => array(
        'layers' => array(
          'contenuti_eventi_eventi_mappa_overlay' => 'contenuti_eventi_eventi_mappa_overlay',
        ),
        'panMapIfOutOfView' => 1,
        'keepInMap' => 1,
      ),
      'openlayers_behavior_touch_navigation' => array(
        'documentDrag' => 1,
      ),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'contenuti_eventi_eventi_mappa_overlay' => 'contenuti_eventi_eventi_mappa_overlay',
          'mapquest_osm' => 0,
        ),
        'point_zoom_level' => '4',
        'zoomtolayer_scale' => '1',
      ),
    ),
    'default_layer' => 'mapquest_osm',
    'layers' => array(
      'mapquest_osm' => 'mapquest_osm',
      'contenuti_eventi_eventi_mappa_overlay' => 'contenuti_eventi_eventi_mappa_overlay',
    ),
    'layer_weight' => array(
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'home_eventi_eventi_home_overlay' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'geofield_formatter' => '0',
    ),
    'layer_styles' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'home_eventi_eventi_home_overlay' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => 'ildeposito',
    ),
    'layer_styles_select' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'home_eventi_eventi_home_overlay' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => 'ildeposito',
    ),
    'layer_styles_temporary' => array(
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'home_eventi_eventi_home_overlay' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
    ),
    'layer_activated' => array(
      'contenuti_eventi_eventi_mappa_overlay' => 'contenuti_eventi_eventi_mappa_overlay',
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'openlayers_kml_example' => 0,
      'contenuti_eventi_overlay_singolo_evento' => 0,
      'home_eventi_eventi_home_overlay' => 0,
      'evento_mappa_mappa_evento_overlay' => 0,
      'evento_mappa_mappa_evento_overlay_prox' => 0,
      'mappa_percorso_mappa_overlay_percorso' => 0,
    ),
    'layer_switcher' => array(
      'contenuti_eventi_eventi_mappa_overlay' => 'contenuti_eventi_eventi_mappa_overlay',
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'openlayers_kml_example' => 0,
      'contenuti_eventi_overlay_singolo_evento' => 0,
      'home_eventi_eventi_home_overlay' => 0,
      'evento_mappa_mappa_evento_overlay' => 0,
      'evento_mappa_mappa_evento_overlay_prox' => 0,
      'mappa_percorso_mappa_overlay_percorso' => 0,
    ),
    'projection' => 'EPSG:900913',
    'displayProjection' => 'EPSG:4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default_select',
      'temporary' => 'default',
    ),
  );
  $export['eventi_mappa'] = $openlayers_maps;

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'evento_singolo';
  $openlayers_maps->title = 'Eventi Singolo';
  $openlayers_maps->description = 'La mappa dell\'evento singolo';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '200px',
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
      'openlayers_behavior_layerswitcher' => array(
        'ascending' => 1,
        'sortBaseLayer' => 'ASC',
        'roundedCorner' => 1,
        'roundedCornerColor' => '#222222',
        'maximizeDefault' => 0,
        'div' => '',
      ),
      'openlayers_behavior_navigation' => array(
        'zoomWheelEnabled' => 1,
        'zoomBoxEnabled' => 1,
        'documentDrag' => 0,
      ),
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'evento_mappa_mappa_evento_overlay' => 'evento_mappa_mappa_evento_overlay',
          'mapquest_osm' => 0,
          'google_normal' => 0,
          'mapbox_world_black' => 0,
          'mapbox_world_bright' => 0,
          'mapbox_world_dark' => 0,
          'mapbox_world_light' => 0,
        ),
        'point_zoom_level' => '5',
        'zoomtolayer_scale' => '1',
      ),
    ),
    'default_layer' => 'mapquest_osm',
    'layers' => array(
      'mapquest_osm' => 'mapquest_osm',
      'google_normal' => 'google_normal',
      'mapbox_world_black' => 'mapbox_world_black',
      'mapbox_world_bright' => 'mapbox_world_bright',
      'mapbox_world_dark' => 'mapbox_world_dark',
      'mapbox_world_light' => 'mapbox_world_light',
      'evento_mappa_mappa_evento_overlay' => 'evento_mappa_mappa_evento_overlay',
    ),
    'layer_weight' => array(
      'home_eventi_eventi_home_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'evento_mappa_mappa_evento_overlay' => '10',
    ),
    'layer_styles' => array(
      'contenuti_eventi_eventi_mappa_overlay' => 'default',
      'geofield_formatter' => 'default',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_overlay_singolo_evento' => 'default',
      'home_eventi_eventi_home_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => 'default_marker_black_small',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'evento_mappa_mappa_evento_overlay' => 'ildeposito',
    ),
    'layer_styles_select' => array(
      'contenuti_eventi_eventi_mappa_overlay' => 'default',
      'geofield_formatter' => 'default',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_overlay_singolo_evento' => 'default',
      'home_eventi_eventi_home_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => 'default_marker_black_small',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'evento_mappa_mappa_evento_overlay' => 'ildeposito',
    ),
    'layer_styles_temporary' => array(
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'geofield_formatter' => '0',
      'openlayers_geojson_picture_this' => '0',
      'openlayers_kml_example' => '0',
      'contenuti_eventi_overlay_singolo_evento' => '0',
      'home_eventi_eventi_home_overlay' => '0',
      'evento_mappa_mappa_evento_overlay_prox' => '0',
      'mappa_percorso_mappa_overlay_percorso' => '0',
      'evento_mappa_mappa_evento_overlay' => '0',
    ),
    'layer_activated' => array(
      'evento_mappa_mappa_evento_overlay' => 'evento_mappa_mappa_evento_overlay',
      'contenuti_eventi_eventi_mappa_overlay' => 0,
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'openlayers_kml_example' => 0,
      'contenuti_eventi_overlay_singolo_evento' => 0,
      'home_eventi_eventi_home_overlay' => 0,
      'evento_mappa_mappa_evento_overlay_prox' => 0,
      'mappa_percorso_mappa_overlay_percorso' => 0,
    ),
    'layer_switcher' => array(
      'evento_mappa_mappa_evento_overlay' => 'evento_mappa_mappa_evento_overlay',
      'contenuti_eventi_eventi_mappa_overlay' => 0,
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'openlayers_kml_example' => 0,
      'contenuti_eventi_overlay_singolo_evento' => 0,
      'home_eventi_eventi_home_overlay' => 0,
      'evento_mappa_mappa_evento_overlay_prox' => 0,
      'mappa_percorso_mappa_overlay_percorso' => 0,
    ),
    'projection' => 'EPSG:3857',
    'displayProjection' => 'EPSG:4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default_select',
      'temporary' => 'default',
    ),
  );
  $export['evento_singolo'] = $openlayers_maps;

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'evento_singolo_riferito';
  $openlayers_maps->title = 'Evento singolo riferito';
  $openlayers_maps->description = 'La mappa per l\'evento singolo riferito';
  $openlayers_maps->data = array(
    'width' => '120px',
    'height' => '80px',
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
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'geofield_formatter' => 'geofield_formatter',
          'mapquest_osm' => 0,
        ),
        'point_zoom_level' => '3',
        'zoomtolayer_scale' => '1',
      ),
    ),
    'default_layer' => 'mapquest_osm',
    'layers' => array(
      'mapquest_osm' => 'mapquest_osm',
      'geofield_formatter' => 'geofield_formatter',
    ),
    'layer_weight' => array(
      'geofield_formatter' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'openlayers_geojson_picture_this' => '0',
    ),
    'layer_styles' => array(
      'openlayers_geojson_picture_this' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'geofield_formatter' => 'default_marker_black_small',
    ),
    'layer_styles_select' => array(
      'openlayers_geojson_picture_this' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'geofield_formatter' => 'default_marker_black_small',
    ),
    'layer_activated' => array(
      'geofield_formatter' => 'geofield_formatter',
      'openlayers_geojson_picture_this' => 0,
      'contenuti_eventi_eventi_mappa_overlay' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'contenuti_eventi_eventi_mappa_overlay' => 0,
    ),
    'projection' => 'EPSG:900913',
    'displayProjection' => 'EPSG:4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default_select',
      'temporary' => 'default',
    ),
  );
  $export['evento_singolo_riferito'] = $openlayers_maps;

  $openlayers_maps = new stdClass();
  $openlayers_maps->disabled = FALSE; /* Edit this to true to make a default openlayers_maps disabled initially */
  $openlayers_maps->api_version = 1;
  $openlayers_maps->name = 'evento_slide';
  $openlayers_maps->title = 'Evento - Slide';
  $openlayers_maps->description = '';
  $openlayers_maps->data = array(
    'width' => 'auto',
    'height' => '200px',
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
      'openlayers_behavior_zoomtolayer' => array(
        'zoomtolayer' => array(
          'geofield_formatter' => 'geofield_formatter',
          'mapquest_osm' => 0,
        ),
        'point_zoom_level' => '5',
        'zoomtolayer_scale' => '1',
      ),
    ),
    'default_layer' => 'mapquest_osm',
    'layers' => array(
      'mapquest_osm' => 'mapquest_osm',
      'geofield_formatter' => 'geofield_formatter',
    ),
    'layer_weight' => array(
      'geofield_formatter' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'openlayers_geojson_picture_this' => '0',
    ),
    'layer_styles' => array(
      'openlayers_geojson_picture_this' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'geofield_formatter' => 'default_marker_black_small',
    ),
    'layer_styles_select' => array(
      'openlayers_geojson_picture_this' => '0',
      'contenuti_eventi_eventi_mappa_overlay' => '0',
      'geofield_formatter' => 'default_marker_black_small',
    ),
    'layer_activated' => array(
      'geofield_formatter' => 'geofield_formatter',
      'openlayers_geojson_picture_this' => 0,
      'contenuti_eventi_eventi_mappa_overlay' => 0,
    ),
    'layer_switcher' => array(
      'geofield_formatter' => 0,
      'openlayers_geojson_picture_this' => 0,
      'contenuti_eventi_eventi_mappa_overlay' => 0,
    ),
    'projection' => 'EPSG:900913',
    'displayProjection' => 'EPSG:4326',
    'styles' => array(
      'default' => 'default',
      'select' => 'default_select',
      'temporary' => 'default',
    ),
  );
  $export['evento_slide'] = $openlayers_maps;

  return $export;
}
