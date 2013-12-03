<?php
/**
 * @file
 * ildeposito_tassonomie.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ildeposito_tassonomie_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'ds_views|tassonomie_contenuti-contenuti_lingua|default';
  $ds_fieldsetting->entity_type = 'ds_views';
  $ds_fieldsetting->bundle = 'tassonomie_contenuti-contenuti_lingua';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'header' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'rows' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'pager' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'current_center_notext' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_sezioni' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tags' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tipo_contenuto' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['ds_views|tassonomie_contenuti-contenuti_lingua|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'ds_views|tassonomie_contenuti-contenuti_localizzazioni|default';
  $ds_fieldsetting->entity_type = 'ds_views';
  $ds_fieldsetting->bundle = 'tassonomie_contenuti-contenuti_localizzazioni';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'header' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'rows' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'pager' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'current_center_notext' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_sezioni' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tags' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tipo_contenuto' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['ds_views|tassonomie_contenuti-contenuti_localizzazioni|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'ds_views|tassonomie_contenuti-contenuti_sezione|default';
  $ds_fieldsetting->entity_type = 'ds_views';
  $ds_fieldsetting->bundle = 'tassonomie_contenuti-contenuti_sezione';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'header' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'rows' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'pager' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'current_center_notext' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_localizzazioni' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tags' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tipo_contenuto' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['ds_views|tassonomie_contenuti-contenuti_sezione|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'ds_views|tassonomie_contenuti-contenuti_tags|default';
  $ds_fieldsetting->entity_type = 'ds_views';
  $ds_fieldsetting->bundle = 'tassonomie_contenuti-contenuti_tags';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'header' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'rows' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'pager' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'current_center_notext' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_sezioni' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tags' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tipo_contenuto' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['ds_views|tassonomie_contenuti-contenuti_tags|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'ds_views|tassonomie_contenuti-contenuti_tematica|default';
  $ds_fieldsetting->entity_type = 'ds_views';
  $ds_fieldsetting->bundle = 'tassonomie_contenuti-contenuti_tematica';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'header' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'rows' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'pager' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'current_center_notext' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_lingue' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_sezioni' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'facet_tipo_contenuto' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['ds_views|tassonomie_contenuti-contenuti_tematica|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'taxonomy_term|percorsi|default';
  $ds_fieldsetting->entity_type = 'taxonomy_term';
  $ds_fieldsetting->bundle = 'percorsi';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'mappa_percorso' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['taxonomy_term|percorsi|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'taxonomy_term|percorsi|full';
  $ds_fieldsetting->entity_type = 'taxonomy_term';
  $ds_fieldsetting->bundle = 'percorsi';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'mappa_percorso' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'service_links_not_node' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['taxonomy_term|percorsi|full'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function ildeposito_tassonomie_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'facet_lingua_originale';
  $ds_field->label = 'Facet lingua originale';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'facetapi|J1R7RGUcggmjGH0W9xEobNvwRAkLAP5g',
    'block_render' => '1',
  );
  $export['facet_lingua_originale'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'facet_lingue';
  $ds_field->label = 'Facet lingue';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'facetapi|lYd1NZ3lTQ2akjypu1RVrwb7zmQuLmbz',
    'block_render' => '1',
  );
  $export['facet_lingue'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'facet_localizzazioni';
  $ds_field->label = 'Facet localizzazioni';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'facetapi|Or4QCwpfC02AvyeSF3upC7fydap1S4wc',
    'block_render' => '1',
  );
  $export['facet_localizzazioni'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'facet_percorsi';
  $ds_field->label = 'Facet percorsi';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'facetapi|9CUTtnKeWYQznRkDkMZX0nY0CXEFjtGc',
    'block_render' => '1',
  );
  $export['facet_percorsi'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'facet_sezioni';
  $ds_field->label = 'Facet sezioni';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'facetapi|i9XEXsGWoqI8fi3JsZLVRyqcSa4Puyjp',
    'block_render' => '1',
  );
  $export['facet_sezioni'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'facet_tags';
  $ds_field->label = 'Facet tags';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'facetapi|IPaCM7H1dF7Clj1WBtiZQw516MCvTYka',
    'block_render' => '1',
  );
  $export['facet_tags'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'facet_tematiche';
  $ds_field->label = 'Facet tematiche';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'facetapi|2vtQFk9G13WS6ztmEpgMvGxnbzWaFrMW',
    'block_render' => '1',
  );
  $export['facet_tematiche'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'mappa_percorso';
  $ds_field->label = 'Mappa percorso';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'taxonomy_term' => 'taxonomy_term',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'views|mappa_percorso-block',
    'block_render' => '1',
  );
  $export['mappa_percorso'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ildeposito_tassonomie_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'ds_views|tassonomie_contenuti-contenuti_lingua|default';
  $ds_layout->entity_type = 'ds_views';
  $ds_layout->bundle = 'tassonomie_contenuti-contenuti_lingua';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'header',
        1 => 'current_center_notext',
      ),
      'left' => array(
        2 => 'rows',
        3 => 'pager',
      ),
      'right' => array(
        4 => 'service_links_not_node',
        5 => 'facet_sezioni',
        6 => 'facet_tags',
        7 => 'facet_tipo_contenuto',
      ),
    ),
    'fields' => array(
      'header' => 'header',
      'current_center_notext' => 'header',
      'rows' => 'left',
      'pager' => 'left',
      'service_links_not_node' => 'right',
      'facet_sezioni' => 'right',
      'facet_tags' => 'right',
      'facet_tipo_contenuto' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 0,
  );
  $export['ds_views|tassonomie_contenuti-contenuti_lingua|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'ds_views|tassonomie_contenuti-contenuti_localizzazioni|default';
  $ds_layout->entity_type = 'ds_views';
  $ds_layout->bundle = 'tassonomie_contenuti-contenuti_localizzazioni';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'header',
        1 => 'current_center_notext',
      ),
      'left' => array(
        2 => 'rows',
        3 => 'pager',
      ),
      'right' => array(
        4 => 'service_links_not_node',
        5 => 'facet_tipo_contenuto',
        6 => 'facet_sezioni',
        7 => 'facet_tags',
      ),
    ),
    'fields' => array(
      'header' => 'header',
      'current_center_notext' => 'header',
      'rows' => 'left',
      'pager' => 'left',
      'service_links_not_node' => 'right',
      'facet_tipo_contenuto' => 'right',
      'facet_sezioni' => 'right',
      'facet_tags' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 0,
  );
  $export['ds_views|tassonomie_contenuti-contenuti_localizzazioni|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'ds_views|tassonomie_contenuti-contenuti_sezione|default';
  $ds_layout->entity_type = 'ds_views';
  $ds_layout->bundle = 'tassonomie_contenuti-contenuti_sezione';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'header',
        1 => 'current_center_notext',
      ),
      'left' => array(
        2 => 'rows',
        3 => 'pager',
      ),
      'right' => array(
        4 => 'service_links_not_node',
        5 => 'facet_tipo_contenuto',
        6 => 'facet_localizzazioni',
        7 => 'facet_tags',
      ),
    ),
    'fields' => array(
      'header' => 'header',
      'current_center_notext' => 'header',
      'rows' => 'left',
      'pager' => 'left',
      'service_links_not_node' => 'right',
      'facet_tipo_contenuto' => 'right',
      'facet_localizzazioni' => 'right',
      'facet_tags' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 0,
  );
  $export['ds_views|tassonomie_contenuti-contenuti_sezione|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'ds_views|tassonomie_contenuti-contenuti_tags|default';
  $ds_layout->entity_type = 'ds_views';
  $ds_layout->bundle = 'tassonomie_contenuti-contenuti_tags';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'header',
      ),
      'left' => array(
        1 => 'current_center_notext',
        2 => 'rows',
        3 => 'pager',
      ),
      'right' => array(
        4 => 'service_links_not_node',
        5 => 'facet_tipo_contenuto',
        6 => 'facet_sezioni',
        7 => 'facet_tags',
      ),
    ),
    'fields' => array(
      'header' => 'header',
      'current_center_notext' => 'left',
      'rows' => 'left',
      'pager' => 'left',
      'service_links_not_node' => 'right',
      'facet_tipo_contenuto' => 'right',
      'facet_sezioni' => 'right',
      'facet_tags' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 0,
  );
  $export['ds_views|tassonomie_contenuti-contenuti_tags|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'ds_views|tassonomie_contenuti-contenuti_tematica|default';
  $ds_layout->entity_type = 'ds_views';
  $ds_layout->bundle = 'tassonomie_contenuti-contenuti_tematica';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'right' => array(
        0 => 'service_links_not_node',
        5 => 'facet_lingue',
        6 => 'facet_sezioni',
        7 => 'facet_tipo_contenuto',
      ),
      'header' => array(
        1 => 'header',
        2 => 'current_center_notext',
      ),
      'left' => array(
        3 => 'rows',
        4 => 'pager',
      ),
    ),
    'fields' => array(
      'service_links_not_node' => 'right',
      'header' => 'header',
      'current_center_notext' => 'header',
      'rows' => 'left',
      'pager' => 'left',
      'facet_lingue' => 'right',
      'facet_sezioni' => 'right',
      'facet_tipo_contenuto' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 0,
  );
  $export['ds_views|tassonomie_contenuti-contenuti_tematica|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|percorsi|default';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'percorsi';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_immagine',
        1 => 'description',
      ),
      'right' => array(
        2 => 'mappa_percorso',
        3 => 'service_links_not_node',
      ),
    ),
    'fields' => array(
      'field_immagine' => 'left',
      'description' => 'left',
      'mappa_percorso' => 'right',
      'service_links_not_node' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['taxonomy_term|percorsi|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|percorsi|full';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'percorsi';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_immagine',
        1 => 'description',
      ),
      'right' => array(
        2 => 'mappa_percorso',
        3 => 'service_links_not_node',
      ),
    ),
    'fields' => array(
      'field_immagine' => 'left',
      'description' => 'left',
      'mappa_percorso' => 'right',
      'service_links_not_node' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
  );
  $export['taxonomy_term|percorsi|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|sezioni|default';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'sezioni';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'description',
        1 => 'field_immagine',
      ),
    ),
    'fields' => array(
      'description' => 'left',
      'field_immagine' => 'left',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 0,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['taxonomy_term|sezioni|default'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function ildeposito_tassonomie_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'percorso';
  $ds_view_mode->label = 'Percorso';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['percorso'] = $ds_view_mode;

  return $export;
}
