<?php
/**
 * @file
 * ildeposito_ct_traduzione.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ildeposito_ct_traduzione_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'contenuti_traduzioni';
  $view->description = '';
  $view->tag = 'ildeposito, omega';
  $view->base_table = 'search_api_index_default_node_index';
  $view->human_name = 'Contenuti - Traduzioni';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Le traduzioni dei canti dell\'archivio';
  $handler->display->display_options['css_class'] = 'search-results';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'altro';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Applica';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Ripristina';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Ordina per';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Disc';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Voci per pagina';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tutto -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Scostamento';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« prima';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ precedente';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'seguente ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'ultima »';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'risultato';
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'search_result';
  /* Header: Entity: Rendered entity */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['entity_id'] = '5992';
  /* Field: Indexed Contenuto: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_geofield_wkt']['id'] = 'field_geofield_wkt';
  $handler->display->display_options['fields']['field_geofield_wkt']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_geofield_wkt']['field'] = 'field_geofield_wkt';
  $handler->display->display_options['fields']['field_geofield_wkt']['label'] = '';
  $handler->display->display_options['fields']['field_geofield_wkt']['element_label_colon'] = FALSE;
  /* Field: Indexed Contenuto: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Sort criterion: Indexed Contenuto: Titolo - Ordinamento */
  $handler->display->display_options['sorts']['search_api_aggregation_1']['id'] = 'search_api_aggregation_1';
  $handler->display->display_options['sorts']['search_api_aggregation_1']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['sorts']['search_api_aggregation_1']['field'] = 'search_api_aggregation_1';
  /* Filter criterion: Indexed Contenuto: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'traduzione' => 'traduzione',
  );

  /* Display: Elenco */
  $handler = $view->new_display('page', 'Elenco', 'traduzioni_elenco');
  $handler->display->display_options['metatags'] = array(
    'description' => array(
      'value' => 'Le traduzioni dell\'archivio: traduzioni in molte lingue di canti e canzoni rivoluzionari, di lotta, di rivolta, di tutto il mondo. Comunisti, anarchici, socialisti, antimperialisti, etc.',
    ),
    'abstract' => array(
      'value' => 'Le traduzioni dell\'archivio: traduzioni in molte lingue di canti e canzoni rivoluzionari, di lotta, di rivolta, di tutto il mondo. Comunisti, anarchici, socialisti, antimperialisti, etc.',
    ),
  );
  $handler->display->display_options['path'] = 'archivio/traduzioni';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Traduzioni';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-ildeposito-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['contenuti_traduzioni'] = array(
    t('Master'),
    t('Le traduzioni dei canti dell\'archivio'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('Voci per pagina'),
    t('- Tutto -'),
    t('Scostamento'),
    t('« prima'),
    t('‹ precedente'),
    t('seguente ›'),
    t('ultima »'),
    t('Node ID'),
    t('.'),
    t(','),
    t('Elenco'),
    t('more'),
  );
  $export['contenuti_traduzioni'] = $view;

  return $export;
}
