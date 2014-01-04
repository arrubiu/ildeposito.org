<?php
/**
 * @file
 * ildeposito_ct_canto.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ildeposito_ct_canto_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'contenuti_canti';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_default_node_index';
  $view->human_name = ' Contenuti - Canti';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'I canti dell\'archivio';
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
  /* Intestazione: Entità: Rendered entity */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['entity_id'] = '5991';
  /* Campo: Indexed Contenuto: ID del nodo */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  /* Campo: Indexed Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_entity'] = 1;
  /* Criterio di ordinamento: Indexed Contenuto: Titolo - Ordinamento */
  $handler->display->display_options['sorts']['search_api_aggregation_1']['id'] = 'search_api_aggregation_1';
  $handler->display->display_options['sorts']['search_api_aggregation_1']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['sorts']['search_api_aggregation_1']['field'] = 'search_api_aggregation_1';
  /* Criterio del filtro: Indexed Contenuto: Tipo di contenuto */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'canto' => 'canto',
  );

  /* Display: Canti */
  $handler = $view->new_display('page', 'Canti', 'eventi_elenco');
  $handler->display->display_options['metatags'] = array(
    'title' => array(
      'value' => '[view:title] - tutti i canti dell\'archivio - Pagina [current-page:page-number] | [site:name]',
    ),
    'description' => array(
      'value' => 'L\'elenco completo di tutti i canti e le canzoni di lotta, di protesta, rivoluzionarie di tutto il mondo, testi accordi musica e spartiti. Canti comunisti, anarchici, socialisti, femministi, contro la guerra, etc.',
    ),
    'abstract' => array(
      'value' => 'L\'elenco completo di tutti i canti e le canzoni di lotta, di protesta, rivoluzionarie di tutto il mondo, testi accordi musica e spartiti. Canti comunisti, anarchici, socialisti, femministi, contro la guerra, etc.',
    ),
  );
  $handler->display->display_options['path'] = 'archivio/canti';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Canti';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-ildeposito-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Capoversi */
  $handler = $view->new_display('page', 'Capoversi', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'I capoversi dei canti';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'risultato';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'canti_capoversi';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Intestazione: Entità: Rendered entity */
  $handler->display->display_options['header']['entity']['id'] = 'entity';
  $handler->display->display_options['header']['entity']['table'] = 'entity__global';
  $handler->display->display_options['header']['entity']['field'] = 'entity';
  $handler->display->display_options['header']['entity']['entity_id'] = '11498';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Indexed Contenuto: ID del nodo */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['separator'] = '';
  $handler->display->display_options['fields']['nid']['link_to_entity'] = 0;
  /* Campo: Indexed Contenuto: Capoverso */
  $handler->display->display_options['fields']['field_capoverso']['id'] = 'field_capoverso';
  $handler->display->display_options['fields']['field_capoverso']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['field_capoverso']['field'] = 'field_capoverso';
  $handler->display->display_options['fields']['field_capoverso']['label'] = '';
  $handler->display->display_options['fields']['field_capoverso']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_capoverso']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['fields']['field_capoverso']['element_label_colon'] = FALSE;
  /* Campo: Indexed Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['link_to_entity'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Criterio di ordinamento: Indexed Contenuto:  Capoverso - Ordinamento */
  $handler->display->display_options['sorts']['search_api_aggregation_2']['id'] = 'search_api_aggregation_2';
  $handler->display->display_options['sorts']['search_api_aggregation_2']['table'] = 'search_api_index_default_node_index';
  $handler->display->display_options['sorts']['search_api_aggregation_2']['field'] = 'search_api_aggregation_2';
  $handler->display->display_options['path'] = 'archivio/canti/capoversi';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Canti';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-ildeposito-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['contenuti_canti'] = array(
    t('Master'),
    t('I canti dell\'archivio'),
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
    t('Canti'),
    t('Capoversi'),
    t('I capoversi dei canti'),
    t('Titolo'),
  );
  $export['contenuti_canti'] = $view;

  $view = new view();
  $view->name = 'contenuti_canti_db';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Contenuti canti - DB';
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
  $handler->display->display_options['style_plugin'] = 'flexslider';
  $handler->display->display_options['style_options']['optionset'] = 'foto_autore';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relazione: Contenuto: Autori testo (field_autore_testo) */
  $handler->display->display_options['relationships']['field_autore_testo_nid']['id'] = 'field_autore_testo_nid';
  $handler->display->display_options['relationships']['field_autore_testo_nid']['table'] = 'field_data_field_autore_testo';
  $handler->display->display_options['relationships']['field_autore_testo_nid']['field'] = 'field_autore_testo_nid';
  $handler->display->display_options['relationships']['field_autore_testo_nid']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_autore_testo_nid']['delta'] = '-1';
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['relationship'] = 'field_autore_testo_nid';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'image_style' => 'foto_autore',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Filtro contestuale: Contenuto: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['exception']['title'] = 'Tutti';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Criterio del filtro: Campo: Immagini (field_images:fid) */
  $handler->display->display_options['filters']['field_images_fid']['id'] = 'field_images_fid';
  $handler->display->display_options['filters']['field_images_fid']['table'] = 'field_data_field_images';
  $handler->display->display_options['filters']['field_images_fid']['field'] = 'field_images_fid';
  $handler->display->display_options['filters']['field_images_fid']['relationship'] = 'field_autore_testo_nid';
  $handler->display->display_options['filters']['field_images_fid']['operator'] = 'not empty';

  /* Display: Foto autori */
  $handler = $view->new_display('block', 'Foto autori', 'foto_autore');
  $translatables['contenuti_canti_db'] = array(
    t('Master'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('field_autore_testo'),
    t('Tutti'),
    t('Foto autori'),
  );
  $export['contenuti_canti_db'] = $view;

  return $export;
}
