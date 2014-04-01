<?php
/**
 * @file
 * ildeposito_layout.ds.inc
 */

/**
 * Implements hook_ds_custom_fields_info().
 */
function ildeposito_layout_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'current_center_notext';
  $ds_field->label = 'Current center notext';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'current_search|current_center_notext',
    'block_render' => '1',
  );
  $export['current_center_notext'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'current_center_text';
  $ds_field->label = 'Current center text';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'current_search|current_center',
    'block_render' => '3',
  );
  $export['current_center_text'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'current_search';
  $ds_field->label = 'Current search';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'current_search|current_right',
    'block_render' => '1',
  );
  $export['current_search'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'current_search_facet';
  $ds_field->label = 'Current search facet';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'current_search|current_center_onlyfacet',
    'block_render' => '1',
  );
  $export['current_search_facet'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'easy_share';
  $ds_field->label = 'Easy share';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
    'taxonomy_term' => 'taxonomy_term',
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'easy_social|easy_social_block_1',
    'block_render' => '1',
  );
  $export['easy_share'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'facet_presenza_accordi';
  $ds_field->label = 'Facet presenza accordi';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'facetapi|0Pau1GV8D8QAAmzOG638DhV06AjWM6yp',
    'block_render' => '1',
  );
  $export['facet_presenza_accordi'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'facet_pubblicazione';
  $ds_field->label = 'Facet pubblicazione';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'facetapi|006i2ydH3VyJuB1m9c18xr81tXcAwDVN',
    'block_render' => '1',
  );
  $export['facet_pubblicazione'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'facet_tipo_contenuto';
  $ds_field->label = 'Facet tipo contenuto';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'facetapi|zIH8EsYFkvWKeMtTZTGLEm1GrYlAarmk',
    'block_render' => '1',
  );
  $export['facet_tipo_contenuto'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ordinamento';
  $ds_field->label = 'Ordinamento';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
    'taxonomy_term' => 'taxonomy_term',
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'search_api_sorts|search-sorts',
    'block_render' => '2',
  );
  $export['ordinamento'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'searchapi_sort';
  $ds_field->label = 'SearchAPI Sort';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'search_api_sorts|search-sorts',
    'block_render' => '1',
  );
  $export['searchapi_sort'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'service_links_node';
  $ds_field->label = 'Service Links node';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'service_links|service_links',
    'block_render' => '1',
  );
  $export['service_links_node'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'service_links_not_node';
  $ds_field->label = 'Service Links not node';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'taxonomy_term' => 'taxonomy_term',
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'service_links|service_links_not_node',
    'block_render' => '1',
  );
  $export['service_links_not_node'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'tipo_di_conteuto';
  $ds_field->label = 'Tipo di conteuto';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '[node:content-type:name]',
      'format' => 'ds_code',
    ),
    'use_token' => 1,
  );
  $export['tipo_di_conteuto'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'widget_social';
  $ds_field->label = 'Widget social';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
    'taxonomy_term' => 'taxonomy_term',
    'ds_views' => 'ds_views',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'widgets|s_socialmedia_share-default',
    'block_render' => '1',
  );
  $export['widget_social'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function ildeposito_layout_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'elenco_termini_contenuti';
  $ds_view_mode->label = 'Elenco termini contenuti';
  $ds_view_mode->entities = array(
    'node' => 'node',
    'file' => 'file',
    'taxonomy_term' => 'taxonomy_term',
  );
  $export['elenco_termini_contenuti'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'print_canzoniere';
  $ds_view_mode->label = 'Print Canzoniere';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['print_canzoniere'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'rss_app';
  $ds_view_mode->label = 'RSS App';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['rss_app'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'termine_singolo';
  $ds_view_mode->label = 'Termine singolo';
  $ds_view_mode->entities = array(
    'file' => 'file',
    'taxonomy_term' => 'taxonomy_term',
  );
  $export['termine_singolo'] = $ds_view_mode;

  return $export;
}
