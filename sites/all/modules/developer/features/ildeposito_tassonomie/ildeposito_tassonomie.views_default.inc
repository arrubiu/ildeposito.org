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
  $view->tag = 'default';
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
  $handler->display->display_options['cache']['type'] = 'none';
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
  $view->tag = 'default';
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
  $handler->display->display_options['cache']['type'] = 'none';
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
  $view->tag = 'default';
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
  $handler->display->display_options['cache']['type'] = 'none';
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
  $view->tag = 'default';
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
  $handler->display->display_options['arguments']['field_sezione']['break_phrase'] = 0;

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
  $handler->display->display_options['arguments']['field_tematica']['break_phrase'] = 0;

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
  $handler->display->display_options['arguments']['field_lingua']['break_phrase'] = 0;

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
  $handler->display->display_options['arguments']['field_localizzazione']['break_phrase'] = 0;

  /* Display: Percorsi */
  $handler = $view->new_display('block', 'Percorsi', 'contenuti_percorsi');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'search-results percorso';
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
  $handler->display->display_options['arguments']['field_percorso']['break_phrase'] = 0;

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
  $handler->display->display_options['arguments']['field_tags']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_tags']['not'] = 0;
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
  );
  $export['tassonomie_contenuti'] = $view;

  $view = new view();
  $view->name = 'tassonomie_elenco_termini';
  $view->description = 'Le viste con gli elenchi di termini';
  $view->tag = 'default';
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
  $handler->display->display_options['cache']['type'] = 'none';
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
  /* Campo: Campo: Immagine */
  $handler->display->display_options['fields']['field_immagine']['id'] = 'field_immagine';
  $handler->display->display_options['fields']['field_immagine']['table'] = 'field_data_field_immagine';
  $handler->display->display_options['fields']['field_immagine']['field'] = 'field_immagine';
  $handler->display->display_options['fields']['field_immagine']['label'] = '';
  $handler->display->display_options['fields']['field_immagine']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_immagine']['alter']['text'] = '<div class="periodo"><span>[field_periodo]</span></div>
[field_immagine] ';
  $handler->display->display_options['fields']['field_immagine']['alter']['path'] = 'taxonomy/term/[tid]';
  $handler->display->display_options['fields']['field_immagine']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_immagine']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_immagine']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_immagine']['settings'] = array(
    'file_view_mode' => 'elenco_termini_contenuti',
  );
  /* Campo: Termine della tassonomia: Descrizione del termine */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
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
  /* Campo: Campo: Immagine */
  $handler->display->display_options['fields']['field_immagine']['id'] = 'field_immagine';
  $handler->display->display_options['fields']['field_immagine']['table'] = 'field_data_field_immagine';
  $handler->display->display_options['fields']['field_immagine']['field'] = 'field_immagine';
  $handler->display->display_options['fields']['field_immagine']['label'] = '';
  $handler->display->display_options['fields']['field_immagine']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_immagine']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_immagine']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_immagine']['settings'] = array(
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
    t('<div class="periodo"><span>[field_periodo]</span></div>
[field_immagine] '),
    t('Tematiche'),
    t('I tag dell\'archivio'),
    t('Lingue'),
    t('Le lingue dell\'archivio'),
    t('Localizzazioni'),
    t('Le localizzazioni dell\'archivio'),
    t('Percorsi'),
    t('I percorsi dell\'archivio'),
    t('Tags'),
  );
  $export['tassonomie_elenco_termini'] = $view;

  return $export;
}
