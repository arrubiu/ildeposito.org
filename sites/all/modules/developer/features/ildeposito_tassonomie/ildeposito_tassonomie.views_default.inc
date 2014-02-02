<?php
/**
 * @file
 * ildeposito_tassonomie.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ildeposito_tassonomie_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'mappa_percorso';
  $view->description = '';
  $view->tag = 'ildeposito, omega';
  $view->base_table = 'node';
  $view->human_name = 'Mappa percorso';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'altro';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '21600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Applica';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Ripristina';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Ordina per';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Disc';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'mappa_percorsoclone_of_eventi_mappa';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Campo: Contenuto: Geofield */
  $handler->display->display_options['fields']['field_geofield']['id'] = 'field_geofield';
  $handler->display->display_options['fields']['field_geofield']['table'] = 'field_data_field_geofield';
  $handler->display->display_options['fields']['field_geofield']['field'] = 'field_geofield';
  $handler->display->display_options['fields']['field_geofield']['label'] = '';
  $handler->display->display_options['fields']['field_geofield']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_geofield']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_geofield']['settings'] = array(
    'data' => 'full',
  );
  /* Criterio di ordinamento: Contenuto: Data di inserimento */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filtro contestuale: Contenuto: Percorsi (field_percorso) */
  $handler->display->display_options['arguments']['field_percorso_tid']['id'] = 'field_percorso_tid';
  $handler->display->display_options['arguments']['field_percorso_tid']['table'] = 'field_data_field_percorso';
  $handler->display->display_options['arguments']['field_percorso_tid']['field'] = 'field_percorso_tid';
  $handler->display->display_options['arguments']['field_percorso_tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_percorso_tid']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_percorso_tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['field_percorso_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_percorso_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_percorso_tid']['summary_options']['items_per_page'] = '25';
  /* Criterio del filtro: Contenuto: Pubblicato */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'evento' => 'evento',
  );

  /* Display: Mappa percorso */
  $handler = $view->new_display('block', 'Mappa percorso', 'block');
  $handler->display->display_options['block_caching'] = '8';

  /* Display: Mappa Overlay Percorso */
  $handler = $view->new_display('openlayers', 'Mappa Overlay Percorso', 'mappa_overlay_percorso');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_data';
  $handler->display->display_options['style_options']['data_source'] = array(
    'value' => 'wkt',
    'other_lat' => 'title',
    'other_lon' => 'title',
    'wkt' => 'field_geofield',
    'other_top' => 'title',
    'other_right' => 'title',
    'other_bottom' => 'title',
    'other_left' => 'title',
    'name_field' => 'title',
    'description_field' => '',
    'view_mode' => 'full',
    'style_field' => '',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['mappa_percorso'] = array(
    t('Master'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('Tutti'),
    t('Mappa percorso'),
    t('Mappa Overlay Percorso'),
  );
  $export['mappa_percorso'] = $view;

  $view = new view();
  $view->name = 'percorsi_eventi';
  $view->description = 'Lista degli eventi di un percorso';
  $view->tag = 'ildeposito, omega';
  $view->base_table = 'node';
  $view->human_name = 'Percorsi - eventi';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'search-results percorso ';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'altro';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '21600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Applica';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Ripristina';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Ordina per';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Disc';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'risultato grid-9 ildeposito-col';
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'percorso';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Criterio di ordinamento: Contenuto: Data evento -  data di inizio (field_data_evento) */
  $handler->display->display_options['sorts']['field_data_evento_value']['id'] = 'field_data_evento_value';
  $handler->display->display_options['sorts']['field_data_evento_value']['table'] = 'field_data_field_data_evento';
  $handler->display->display_options['sorts']['field_data_evento_value']['field'] = 'field_data_evento_value';
  /* Filtro contestuale: Contenuto: Percorsi (field_percorso) */
  $handler->display->display_options['arguments']['field_percorso_tid']['id'] = 'field_percorso_tid';
  $handler->display->display_options['arguments']['field_percorso_tid']['table'] = 'field_data_field_percorso';
  $handler->display->display_options['arguments']['field_percorso_tid']['field'] = 'field_percorso_tid';
  $handler->display->display_options['arguments']['field_percorso_tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_percorso_tid']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_percorso_tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['field_percorso_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_percorso_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_percorso_tid']['summary_options']['items_per_page'] = '25';
  /* Criterio del filtro: Contenuto: Pubblicato */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'evento' => 'evento',
  );
  /* Criterio del filtro: Contenuto: Data evento (field_data_evento:delta) */
  $handler->display->display_options['filters']['delta']['id'] = 'delta';
  $handler->display->display_options['filters']['delta']['table'] = 'field_data_field_data_evento';
  $handler->display->display_options['filters']['delta']['field'] = 'delta';
  $handler->display->display_options['filters']['delta']['value']['value'] = '0';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['block_caching'] = '8';
  $translatables['percorsi_eventi'] = array(
    t('Master'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('Tutti'),
    t('Block'),
  );
  $export['percorsi_eventi'] = $view;

  $view = new view();
  $view->name = 'percorso_contenuti';
  $view->description = 'I contenuti di un percorso';
  $view->tag = 'ildeposito, omega';
  $view->base_table = 'node';
  $view->human_name = 'Percorso - contenuti';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'altro';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '21600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Applica';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Ripristina';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Ordina per';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Disc';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Voci per pagina';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tutto -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Scostamento';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« prima';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ precedente';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'seguente ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'ultima »';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Criterio di ordinamento: Contenuto: Data di inserimento */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Criterio del filtro: Contenuto: Pubblicato */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'evento' => 'evento',
  );
  $translatables['percorso_contenuti'] = array(
    t('Master'),
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
  );
  $export['percorso_contenuti'] = $view;

  $view = new view();
  $view->name = 'tassonomie_contenuti';
  $view->description = 'I contenuti in base alle tassonomie';
  $view->tag = 'ildeposito, omega';
  $view->base_table = 'search_api_index_default_node_index';
  $view->human_name = 'Tassonomie - contenuti';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Tassonomie - contenuti';
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
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Voci per pagina';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tutto -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Scostamento';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« prima';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ prec';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'succ ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'ultima »';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'risultato';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'search_result';
  /* Intestazione: Globale: Area della vista */
  $handler->display->display_options['header']['view']['id'] = 'view';
  $handler->display->display_options['header']['view']['table'] = 'views';
  $handler->display->display_options['header']['view']['field'] = 'view';
  $handler->display->display_options['header']['view']['view_to_insert'] = 'termini_descrizione:block';
  $handler->display->display_options['header']['view']['inherit_arguments'] = TRUE;
  /* Campo: Indexed Contenuto: ID del nodo */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  /* Criterio di ordinamento: Indexed Contenuto: Titolo - Ordinamento */
  $handler->display->display_options['sorts']['search_api_aggregation_1']['id'] = 'search_api_aggregation_1';
  $handler->display->display_options['sorts']['search_api_aggregation_1']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['sorts']['search_api_aggregation_1']['field'] = 'search_api_aggregation_1';
  /* Filtro contestuale: Indexed Contenuto: Sezione */
  $handler->display->display_options['arguments']['field_sezione']['id'] = 'field_sezione';
  $handler->display->display_options['arguments']['field_sezione']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['arguments']['field_sezione']['field'] = 'field_sezione';
  $handler->display->display_options['arguments']['field_sezione']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_sezione']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_sezione']['summary']['format'] = 'default_summary';

  /* Display: Sezioni */
  $handler = $view->new_display('block', 'Sezioni', 'contenuti_sezione');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Filtro contestuale: Indexed Contenuto: Sezione */
  $handler->display->display_options['arguments']['field_sezione']['id'] = 'field_sezione';
  $handler->display->display_options['arguments']['field_sezione']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['arguments']['field_sezione']['field'] = 'field_sezione';
  $handler->display->display_options['arguments']['field_sezione']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_sezione']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_sezione']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['field_sezione']['title'] = '%1';
  $handler->display->display_options['arguments']['field_sezione']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_sezione']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_sezione']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_sezione']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_sezione']['validate_options']['vocabularies'] = array(
    'sezioni' => 'sezioni',
  );
  $handler->display->display_options['arguments']['field_sezione']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_sezione']['not'] = 0;
  $handler->display->display_options['block_caching'] = '-1';

  /* Display: Tematiche */
  $handler = $view->new_display('block', 'Tematiche', 'contenuti_tematica');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Filtro contestuale: Indexed Contenuto: Tematiche */
  $handler->display->display_options['arguments']['field_tematica']['id'] = 'field_tematica';
  $handler->display->display_options['arguments']['field_tematica']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['arguments']['field_tematica']['field'] = 'field_tematica';
  $handler->display->display_options['arguments']['field_tematica']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_tematica']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_tematica']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['field_tematica']['title'] = 'Contentuti per la tematica \'%1\'';
  $handler->display->display_options['arguments']['field_tematica']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_tematica']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_tematica']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_tematica']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_tematica']['validate_options']['vocabularies'] = array(
    'tematiche' => 'tematiche',
  );
  $handler->display->display_options['arguments']['field_tematica']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_tematica']['not'] = 0;

  /* Display: Lingue */
  $handler = $view->new_display('block', 'Lingue', 'contenuti_lingua');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Filtro contestuale: Indexed Contenuto: Lingue */
  $handler->display->display_options['arguments']['field_lingua']['id'] = 'field_lingua';
  $handler->display->display_options['arguments']['field_lingua']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['arguments']['field_lingua']['field'] = 'field_lingua';
  $handler->display->display_options['arguments']['field_lingua']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_lingua']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_lingua']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['field_lingua']['title'] = '%1';
  $handler->display->display_options['arguments']['field_lingua']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_lingua']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_lingua']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_lingua']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_lingua']['validate_options']['vocabularies'] = array(
    'lingue' => 'lingue',
  );
  $handler->display->display_options['arguments']['field_lingua']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_lingua']['not'] = 0;

  /* Display: Localizzazioni */
  $handler = $view->new_display('block', 'Localizzazioni', 'contenuti_localizzazioni');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Filtro contestuale: Indexed Contenuto: Localizzazioni */
  $handler->display->display_options['arguments']['field_localizzazione']['id'] = 'field_localizzazione';
  $handler->display->display_options['arguments']['field_localizzazione']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['arguments']['field_localizzazione']['field'] = 'field_localizzazione';
  $handler->display->display_options['arguments']['field_localizzazione']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_localizzazione']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_localizzazione']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['field_localizzazione']['title'] = '%1';
  $handler->display->display_options['arguments']['field_localizzazione']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_localizzazione']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_localizzazione']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_localizzazione']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_localizzazione']['validate_options']['vocabularies'] = array(
    'localizzazione' => 'localizzazione',
  );
  $handler->display->display_options['arguments']['field_localizzazione']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_localizzazione']['not'] = 0;

  /* Display: Percorsi */
  $handler = $view->new_display('block', 'Percorsi', 'contenuti_percorsi');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'search-results percorso';
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '21600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'risultato grid-9 ildeposito-col';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'percorso';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Criterio di ordinamento: Indexed Contenuto: Evento ordinamento */
  $handler->display->display_options['sorts']['field_evento_ordinamento']['id'] = 'field_evento_ordinamento';
  $handler->display->display_options['sorts']['field_evento_ordinamento']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['sorts']['field_evento_ordinamento']['field'] = 'field_evento_ordinamento';
  $handler->display->display_options['sorts']['field_evento_ordinamento']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Filtro contestuale: Indexed Contenuto: Percorsi */
  $handler->display->display_options['arguments']['field_percorso']['id'] = 'field_percorso';
  $handler->display->display_options['arguments']['field_percorso']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['arguments']['field_percorso']['field'] = 'field_percorso';
  $handler->display->display_options['arguments']['field_percorso']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_percorso']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_percorso']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['field_percorso']['title'] = '%1';
  $handler->display->display_options['arguments']['field_percorso']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_percorso']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_percorso']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_percorso']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_percorso']['validate_options']['vocabularies'] = array(
    'percorsi' => 'percorsi',
  );
  $handler->display->display_options['arguments']['field_percorso']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_percorso']['not'] = 0;
  $handler->display->display_options['block_caching'] = '4';

  /* Display: Tags */
  $handler = $view->new_display('block', 'Tags', 'contenuti_tags');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Filtro contestuale: Indexed Contenuto: Tag */
  $handler->display->display_options['arguments']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['arguments']['field_tags']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['arguments']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['arguments']['field_tags']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_tags']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_tags']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['field_tags']['title'] = '%1';
  $handler->display->display_options['arguments']['field_tags']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['field_tags']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_tags']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_tags']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_tags']['validate_options']['vocabularies'] = array(
    'tags' => 'tags',
  );
  $handler->display->display_options['arguments']['field_tags']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_tags']['not'] = 0;

  /* Display: Libreria */
  $handler = $view->new_display('block', 'Libreria', 'contenuti_libreria');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'risultato';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'search_result';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Filtro contestuale: Indexed Contenuto: Tipo voce */
  $handler->display->display_options['arguments']['field_tipo_voce']['id'] = 'field_tipo_voce';
  $handler->display->display_options['arguments']['field_tipo_voce']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['arguments']['field_tipo_voce']['field'] = 'field_tipo_voce';
  $handler->display->display_options['arguments']['field_tipo_voce']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_tipo_voce']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_tipo_voce']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['field_tipo_voce']['title'] = 'La libreria - %1';
  $handler->display->display_options['arguments']['field_tipo_voce']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['field_tipo_voce']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_tipo_voce']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_tipo_voce']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_tipo_voce']['validate_options']['vocabularies'] = array(
    'tipo_libreria' => 'tipo_libreria',
  );
  $handler->display->display_options['arguments']['field_tipo_voce']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_tipo_voce']['not'] = 0;
  $handler->display->display_options['block_caching'] = '-1';
  $translatables['tassonomie_contenuti'] = array(
    t('Master'),
    t('Tassonomie - contenuti'),
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
    t('‹ prec'),
    t('succ ›'),
    t('ultima »'),
    t('ID del nodo'),
    t('.'),
    t(','),
    t('Tutti'),
    t('Sezioni'),
    t('%1'),
    t('Tematiche'),
    t('Contentuti per la tematica \'%1\''),
    t('Lingue'),
    t('Localizzazioni'),
    t('Percorsi'),
    t('Tags'),
    t('Libreria'),
    t('La libreria - %1'),
  );
  $export['tassonomie_contenuti'] = $view;

  $view = new view();
  $view->name = 'tassonomie_elenco_termini';
  $view->description = 'Le viste con gli elenchi di termini';
  $view->tag = 'ildeposito, omega';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Tassonomie - elenco termini';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Le sezioni dell\'archivio';
  $handler->display->display_options['css_class'] = 'elenco-termini elenco-sezioni';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'altro';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '21600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Applica';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Ripristina';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Ordina per';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Disc';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'risultato grid-8 ildeposito-col';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Intestazione: Entità: Rendered entity */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['entity_id'] = '5981';
  /* Campo: Termine della tassonomia: Nome */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Criterio di ordinamento: Termine della tassonomia: Peso */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  /* Criterio del filtro: Termine della tassonomia: Vocabolario */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    6 => '6',
  );

  /* Display: Sezioni */
  $handler = $view->new_display('page', 'Sezioni', 'sezioni_page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'risultato grid-9 ildeposito-col';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Termine della tassonomia: ID Termine */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Campo: Termine della tassonomia: Nome */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Campo: Termine della tassonomia: Periodo */
  $handler->display->display_options['fields']['field_periodo']['id'] = 'field_periodo';
  $handler->display->display_options['fields']['field_periodo']['table'] = 'field_data_field_periodo';
  $handler->display->display_options['fields']['field_periodo']['field'] = 'field_periodo';
  $handler->display->display_options['fields']['field_periodo']['label'] = '';
  $handler->display->display_options['fields']['field_periodo']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_periodo']['alter']['path'] = 'taxonomy/term/[tid]';
  $handler->display->display_options['fields']['field_periodo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_periodo']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_periodo']['element_wrapper_class'] = 'periodo';
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'image_style' => 'elenco_termine',
    'image_link' => 'content',
  );
  /* Campo: Termine della tassonomia: Descrizione del termine */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['metatags'] = array(
    'title' => array(
      'value' => 'Le sezioni dell\'archivio | i canti, gli eventi, gli autori, le traduzioni [site:name]',
    ),
    'description' => array(
      'value' => 'L\'elenco delle sezioni dell\'archivio, il punto di partenza per navigare nei canti, nelle canzoni, negli eventi. La resistenza, il risorgimento, gli anni \'70, gli anni di piombo, la rivoluzione russa etc.',
    ),
    'abstract' => array(
      'value' => 'L\'elenco delle sezioni dell\'archivio, il punto di partenza per navigare nei canti, nelle canzoni, negli eventi. La resistenza, il risorgimento, gli anni \'70, gli anni di piombo, la rivoluzione russa etc.',
    ),
  );
  $handler->display->display_options['path'] = 'archivio/sezioni';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Sezioni';
  $handler->display->display_options['menu']['name'] = 'menu-ildeposito-menu';

  /* Display: Tematiche */
  $handler = $view->new_display('page', 'Tematiche', 'tematiche_page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'I tag dell\'archivio';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'elenco-termini elenco-tematiche';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Intestazione: Entità: Rendered entity */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['entity_id'] = '5982';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Termine della tassonomia: Vocabolario */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    5 => '5',
  );
  $handler->display->display_options['path'] = 'archivio/tematiche';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Tematiche';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-ildeposito-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Lingue */
  $handler = $view->new_display('page', 'Lingue', 'lingue_page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Le lingue dell\'archivio';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'elenco-termini elenco-lingue';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Intestazione: Entità: Rendered entity */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['entity_id'] = '5983';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Termine della tassonomia: Vocabolario */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    2 => '2',
  );
  $handler->display->display_options['metatags'] = array(
    'title' => array(
      'value' => '[view:title] - i canti, le traduzioni | [site:name]',
    ),
    'description' => array(
      'value' => 'L\'elenco delle lingue dell\'archivio, per cercare canti, canzoni, traduzioni dei canti di lotta, di protesta, rivoluzionari di tutto il mondo.',
    ),
    'abstract' => array(
      'value' => 'L\'elenco delle lingue dell\'archivio, per cercare canti, canzoni, traduzioni dei canti di lotta, di protesta, rivoluzionari di tutto il mondo.',
    ),
  );
  $handler->display->display_options['path'] = 'archivio/lingue';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Lingue';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-ildeposito-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Localizzazioni */
  $handler = $view->new_display('page', 'Localizzazioni', 'localizzazioni_page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Le localizzazioni dell\'archivio';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'elenco-termini elenco-localizzazioni';
  $handler->display->display_options['display_description'] = 'Le localizzazioni dell\'archivio de ilDeposito.org';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Intestazione: Entità: Rendered entity */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['entity_id'] = '5987';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Termine della tassonomia: Vocabolario */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    3 => '3',
  );
  $handler->display->display_options['metatags'] = array(
    'title' => array(
      'value' => '[view:title] - gli autori, gli eventi | [site:name]',
    ),
    'description' => array(
      'value' => 'Le localizzazioni dell\'archivio, per cercare canti, canzoni, autori, eventi in base alla localizzazione geografico. La geografia delle lotte, delle rivolte, delle rivoluzioni nel mondo.',
    ),
    'abstract' => array(
      'value' => 'Le localizzazioni dell\'archivio, per cercare canti, canzoni, autori, eventi in base alla localizzazione geografico. La geografia delle lotte, delle rivolte, delle rivoluzioni nel mondo.',
    ),
  );
  $handler->display->display_options['path'] = 'archivio/localizzazioni';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Localizzazioni';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-ildeposito-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Percorsi */
  $handler = $view->new_display('page', 'Percorsi', 'percorsi_page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'I percorsi dell\'archivio';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'elenco-termini elenco-percorsi';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'risultato grid-9 ildeposito-col';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Intestazione: Entità: Rendered entity */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['entity_id'] = '5986';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Termine della tassonomia: Nome */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'file_view_mode' => 'elenco_termini_contenuti',
  );
  /* Campo: Termine della tassonomia: Descrizione del termine */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['alter']['max_length'] = '300';
  $handler->display->display_options['fields']['description']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['description']['alter']['html'] = TRUE;
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Termine della tassonomia: Vocabolario */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    4 => '4',
  );
  $handler->display->display_options['metatags'] = array(
    'title' => array(
      'value' => '[view:title] - gli eventi e i canti della Storia Cantata | [site:name]',
    ),
    'description' => array(
      'value' => 'I percorsi della Storia cantata, il punto di partenza per navigare nella storia del movimento operaio, rivoluzionario, di tutto il mondo.',
    ),
    'abstract' => array(
      'value' => 'I percorsi della Storia cantata, il punto di partenza per navigare nella storia del movimento operaio, rivoluzionario, di tutto il mondo.',
    ),
  );
  $handler->display->display_options['path'] = 'archivio/storiacantata/percorsi';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Percorsi';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-ildeposito-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Tags */
  $handler = $view->new_display('page', 'Tags', 'tags_page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'I tag dell\'archivio';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'elenco-termini elenco-tags';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Intestazione: Entità: Rendered entity */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['entity_id'] = '5988';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Termine della tassonomia: Vocabolario */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['metatags'] = array(
    'title' => array(
      'value' => '[view:title] - canti, eventi, traduzioni, autori | [site:name]',
    ),
    'description' => array(
      'value' => 'I tag dell\'archivio: tutti i canti, canzoni, autori, eventi, traduzioni sono raggruppati per tag. I più comuni: anarchici, comunisti, socialisti, femministi, contro la guerra, etc. ',
    ),
    'abstract' => array(
      'value' => 'I tag dell\'archivio: tutti i canti, canzoni, autori, eventi, traduzioni sono raggruppati per tag. I più comuni: anarchici, comunisti, socialisti, femministi, contro la guerra, etc. ',
    ),
  );
  $handler->display->display_options['path'] = 'archivio/tags';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Tags';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-ildeposito-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['tassonomie_elenco_termini'] = array(
    t('Master'),
    t('Le sezioni dell\'archivio'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('Sezioni'),
    t('.'),
    t('Tematiche'),
    t('I tag dell\'archivio'),
    t('Lingue'),
    t('Le lingue dell\'archivio'),
    t('Localizzazioni'),
    t('Le localizzazioni dell\'archivio'),
    t('Le localizzazioni dell\'archivio de ilDeposito.org'),
    t('Percorsi'),
    t('I percorsi dell\'archivio'),
    t('Tags'),
  );
  $export['tassonomie_elenco_termini'] = $view;

  $view = new view();
  $view->name = 'termini_descrizione';
  $view->description = '';
  $view->tag = 'ildeposito, omega';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Termini - descrizione';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'altro';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '518400';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '518400';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Applica';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Ripristina';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Ordina per';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Disc';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'entity';
  /* Campo: Termine della tassonomia: Nome */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Filtro contestuale: Termine della tassonomia: ID Termine */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['block_caching'] = '4';
  $translatables['termini_descrizione'] = array(
    t('Master'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('Tutti'),
    t('Block'),
  );
  $export['termini_descrizione'] = $view;

  return $export;
}
