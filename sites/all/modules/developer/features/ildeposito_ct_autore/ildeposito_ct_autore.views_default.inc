<?php
/**
 * @file
 * ildeposito_ct_autore.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ildeposito_ct_autore_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'contenuti_autore';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_default_node_index';
  $view->human_name = 'Contenuti autore';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Contenuti autore';
  $handler->display->display_options['css_class'] = 'search-results';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'altro';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
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
  /* Campo: Indexed Contenuto: ID del nodo */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  /* Campo: Indexed Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Criterio di ordinamento: Indexed Contenuto: Titolo - Ordinamento */
  $handler->display->display_options['sorts']['search_api_aggregation_1']['id'] = 'search_api_aggregation_1';
  $handler->display->display_options['sorts']['search_api_aggregation_1']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['sorts']['search_api_aggregation_1']['field'] = 'search_api_aggregation_1';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'OR',
  );
  /* Criterio del filtro: Indexed Contenuto: Autori musica */
  $handler->display->display_options['filters']['field_autore_musica']['id'] = 'field_autore_musica';
  $handler->display->display_options['filters']['field_autore_musica']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['field_autore_musica']['field'] = 'field_autore_musica';
  $handler->display->display_options['filters']['field_autore_musica']['value'] = '1';
  $handler->display->display_options['filters']['field_autore_musica']['group'] = 1;
  /* Criterio del filtro: Indexed Contenuto: Autori testo */
  $handler->display->display_options['filters']['field_autore_testo']['id'] = 'field_autore_testo';
  $handler->display->display_options['filters']['field_autore_testo']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['field_autore_testo']['field'] = 'field_autore_testo';
  $handler->display->display_options['filters']['field_autore_testo']['value'] = '2';
  $handler->display->display_options['filters']['field_autore_testo']['group'] = 1;

  /* Display: Autore */
  $handler = $view->new_display('page', 'Autore', 'autore_singolo');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'OR',
    2 => 'AND',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Indexed Contenuto: Autori musica */
  $handler->display->display_options['filters']['field_autore_musica']['id'] = 'field_autore_musica';
  $handler->display->display_options['filters']['field_autore_musica']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['field_autore_musica']['field'] = 'field_autore_musica';
  $handler->display->display_options['filters']['field_autore_musica']['value'] = '1';
  $handler->display->display_options['filters']['field_autore_musica']['group'] = 1;
  /* Criterio del filtro: Indexed Contenuto: Autori testo */
  $handler->display->display_options['filters']['field_autore_testo']['id'] = 'field_autore_testo';
  $handler->display->display_options['filters']['field_autore_testo']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['field_autore_testo']['field'] = 'field_autore_testo';
  $handler->display->display_options['filters']['field_autore_testo']['value'] = '2';
  $handler->display->display_options['filters']['field_autore_testo']['group'] = 1;
  /* Criterio del filtro: Indexed Contenuto: Tipo di contenuto */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'canto' => 'canto',
  );
  $handler->display->display_options['filters']['type']['group'] = 2;
  $handler->display->display_options['path'] = 'contenuti-autore';

  /* Display: Autori */
  $handler = $view->new_display('page', 'Autori', 'elenco_autori');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Gli autori dell\'archivio';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'risultato';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'search_result';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Intestazione: Entità: Rendered entity */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['entity_id'] = '5985';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Indexed Contenuto: Tipo di contenuto */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'autore' => 'autore',
  );
  $handler->display->display_options['path'] = 'archivio/autori';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Autori';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-ildeposito-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['contenuti_autore'] = array(
    t('Master'),
    t('Contenuti autore'),
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
    t('ID del nodo'),
    t('.'),
    t(','),
    t('Titolo'),
    t('Autore'),
    t('Autori'),
    t('Gli autori dell\'archivio'),
  );
  $export['contenuti_autore'] = $view;

  return $export;
}
