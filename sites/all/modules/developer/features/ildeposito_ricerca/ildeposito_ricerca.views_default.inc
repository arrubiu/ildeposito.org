<?php
/**
 * @file
 * ildeposito_ricerca.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ildeposito_ricerca_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ricerca';
  $view->description = 'I contenuti in base alle tassonomie';
  $view->tag = 'ildeposito, omega';
  $view->base_table = 'search_api_index_default_node_index';
  $view->human_name = 'Ricerca';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Risultati della ricerca';
  $handler->display->display_options['css_class'] = 'search-results ricerca';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'altro';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Applica';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Ripristina';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Ordina per';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Disc';
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Opzioni avanzate',
    ),
    'sort' => array(
      'bef_format' => 'bef_links',
      'advanced' => array(
        'collapsible' => 0,
        'collapsible_label' => 'Sort options',
        'combine' => 0,
        'combine_rewrite' => '',
        'reset' => 0,
        'reset_label' => '',
        'is_secondary' => 0,
      ),
    ),
    'search_api_views_fulltext' => array(
      'more_options' => array(
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
  );
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
  /* Criterio di ordinamento: Cerca: Relevance */
  $handler->display->display_options['sorts']['search_api_relevance']['id'] = 'search_api_relevance';
  $handler->display->display_options['sorts']['search_api_relevance']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['sorts']['search_api_relevance']['field'] = 'search_api_relevance';
  $handler->display->display_options['sorts']['search_api_relevance']['order'] = 'DESC';
  /* Criterio del filtro: Cerca: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'chiave';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['search_api_views_fulltext']['fields'] = array(
    'title' => 'title',
    'field_altri_nomi' => 'field_altri_nomi',
    'field_cognome' => 'field_cognome',
    'field_nome' => 'field_nome',
    'field_testo' => 'field_testo',
    'field_accordi' => 'field_accordi',
    'field_capoverso' => 'field_capoverso',
    'field_titolo_alt' => 'field_titolo_alt',
    'field_editore' => 'field_editore',
    'field_collana' => 'field_collana',
    'field_citta' => 'field_citta',
    'search_api_aggregation_4' => 'search_api_aggregation_4',
    'search_api_viewed' => 'search_api_viewed',
    'body:value' => 'body:value',
    'body:summary' => 'body:summary',
    'field_tags:name' => 'field_tags:name',
    'field_sezione:name' => 'field_sezione:name',
    'field_sezione:description' => 'field_sezione:description',
    'field_localizzazione:name' => 'field_localizzazione:name',
    'field_localizzazione:description' => 'field_localizzazione:description',
    'field_informazioni:value' => 'field_informazioni:value',
    'field_lingua:name' => 'field_lingua:name',
    'field_lingua:description' => 'field_lingua:description',
    'field_autore_musica:title' => 'field_autore_musica:title',
    'field_autore_testo:title' => 'field_autore_testo:title',
    'field_tematica:name' => 'field_tematica:name',
    'field_tematica:description' => 'field_tematica:description',
    'field_percorso:name' => 'field_percorso:name',
    'field_percorso:description' => 'field_percorso:description',
    'field_geofield:geom' => 'field_geofield:geom',
    'field_tipo_voce:name' => 'field_tipo_voce:name',
    'field_tipo_voce:description' => 'field_tipo_voce:description',
  );

  /* Display: Ricerca */
  $handler = $view->new_display('page', 'Ricerca', 'ricerca_page');
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['path'] = 'ricerca';
  $translatables['ricerca'] = array(
    t('Master'),
    t('Risultati della ricerca'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('Seleziona qualsiasi filtro e clicca su Applica per visualizzare i risultati'),
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
    t('Ricerca'),
  );
  $export['ricerca'] = $view;

  return $export;
}
