<?php
/**
 * @file
 * ildeposito_app.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ildeposito_app_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'rss_app';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'RSS App';
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

  /* Display: Eventi del giorno */
  $handler = $view->new_display('feed', 'Eventi del giorno', 'eventi_giorno');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['description'] = 'Gli eventi della Storia Cantata';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['row_options']['item_length'] = 'rss_app';
  $handler->display->display_options['row_options']['links'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Filtro contestuale: Contenuto: Data evento -  data di inizio (field_data_evento) */
  $handler->display->display_options['arguments']['field_data_evento_value']['id'] = 'field_data_evento_value';
  $handler->display->display_options['arguments']['field_data_evento_value']['table'] = 'field_data_field_data_evento';
  $handler->display->display_options['arguments']['field_data_evento_value']['field'] = 'field_data_evento_value';
  $handler->display->display_options['arguments']['field_data_evento_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_data_evento_value']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['field_data_evento_value']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['field_data_evento_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_data_evento_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_data_evento_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_data_evento_value']['granularity'] = 'day';
  $handler->display->display_options['path'] = 'app/eventi_giorno.rss';

  /* Display: Articoli */
  $handler = $view->new_display('feed', 'Articoli', 'articoli');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['description'] = 'Gli articoli de ilDeposito.org';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['row_options']['item_length'] = 'rss_app';
  $handler->display->display_options['row_options']['links'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Criterio di ordinamento: Contenuto: Data di inserimento */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'articolo' => 'articolo',
  );
  $handler->display->display_options['path'] = 'app/articoli.rss';

  /* Display: Archivio */
  $handler = $view->new_display('feed', 'Archivio', 'archivio');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['description'] = 'I contenuti dell\'archivio';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['row_options']['item_length'] = 'rss_app';
  $handler->display->display_options['row_options']['links'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Criterio di ordinamento: Contenuto: Data di inserimento */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'autore' => 'autore',
    'canto' => 'canto',
    'traduzione' => 'traduzione',
  );
  $handler->display->display_options['path'] = 'app/archivio.rss';
  $translatables['rss_app'] = array(
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
    t('Eventi del giorno'),
    t('Tutti'),
    t('Articoli'),
    t('Archivio'),
  );
  $export['rss_app'] = $view;

  return $export;
}
