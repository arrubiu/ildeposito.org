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
  /* Relazione: Contenuto: Autore */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
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
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'title';
  $handler->display->display_options['row_options']['link_field'] = 'path';
  $handler->display->display_options['row_options']['description_field'] = 'field_informazioni';
  $handler->display->display_options['row_options']['creator_field'] = 'name';
  $handler->display->display_options['row_options']['date_field'] = 'created';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'path',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Data evento */
  $handler->display->display_options['fields']['field_data_evento_1']['id'] = 'field_data_evento_1';
  $handler->display->display_options['fields']['field_data_evento_1']['table'] = 'field_data_field_data_evento';
  $handler->display->display_options['fields']['field_data_evento_1']['field'] = 'field_data_evento';
  $handler->display->display_options['fields']['field_data_evento_1']['label'] = '';
  $handler->display->display_options['fields']['field_data_evento_1']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_data_evento_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_data_evento_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_data_evento_1']['settings'] = array(
    'format_type' => 'data_estesa',
    'fromto' => 'value',
    'multiple_number' => '1',
    'multiple_from' => '0',
    'multiple_to' => '',
    'show_repeat_rule' => 'hide',
  );
  $handler->display->display_options['fields']['field_data_evento_1']['delta_offset'] = '0';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[field_data_evento_1] - [title]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Canti collegati */
  $handler->display->display_options['fields']['field_canti_evento']['id'] = 'field_canti_evento';
  $handler->display->display_options['fields']['field_canti_evento']['table'] = 'field_data_field_canti_evento';
  $handler->display->display_options['fields']['field_canti_evento']['field'] = 'field_canti_evento';
  $handler->display->display_options['fields']['field_canti_evento']['label'] = '';
  $handler->display->display_options['fields']['field_canti_evento']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_canti_evento']['alter']['text'] = '[field_canti_evento]';
  $handler->display->display_options['fields']['field_canti_evento']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_canti_evento']['delta_offset'] = '0';
  /* Campo: Contenuto: Data evento */
  $handler->display->display_options['fields']['field_data_evento']['id'] = 'field_data_evento';
  $handler->display->display_options['fields']['field_data_evento']['table'] = 'field_data_field_data_evento';
  $handler->display->display_options['fields']['field_data_evento']['field'] = 'field_data_evento';
  $handler->display->display_options['fields']['field_data_evento']['label'] = '';
  $handler->display->display_options['fields']['field_data_evento']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_data_evento']['alter']['text'] = 'Data evento: [field_data_evento]';
  $handler->display->display_options['fields']['field_data_evento']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_data_evento']['settings'] = array(
    'format_type' => 'data_estesa',
    'fromto' => 'value',
    'multiple_number' => '1',
    'multiple_from' => '0',
    'multiple_to' => '',
    'show_repeat_rule' => 'hide',
  );
  $handler->display->display_options['fields']['field_data_evento']['delta_offset'] = '0';
  /* Campo: Contenuto: Localizzazioni */
  $handler->display->display_options['fields']['field_localizzazione']['id'] = 'field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['table'] = 'field_data_field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['field'] = 'field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['label'] = '';
  $handler->display->display_options['fields']['field_localizzazione']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_localizzazione']['alter']['text'] = '<br />Localizzazione: [field_localizzazione]';
  $handler->display->display_options['fields']['field_localizzazione']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_localizzazione']['delta_offset'] = '0';
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'image_style' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
    'image_link' => 'file',
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Campo: Contenuto: Percorsi */
  $handler->display->display_options['fields']['field_percorso']['id'] = 'field_percorso';
  $handler->display->display_options['fields']['field_percorso']['table'] = 'field_data_field_percorso';
  $handler->display->display_options['fields']['field_percorso']['field'] = 'field_percorso';
  $handler->display->display_options['fields']['field_percorso']['label'] = '';
  $handler->display->display_options['fields']['field_percorso']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_percorso']['alter']['text'] = '<br />Percorso: [field_percorso]';
  $handler->display->display_options['fields']['field_percorso']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_percorso']['delta_offset'] = '0';
  /* Campo: Contenuto: Percorso */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Campo: Contenuto: Sezione */
  $handler->display->display_options['fields']['field_sezione']['id'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['table'] = 'field_data_field_sezione';
  $handler->display->display_options['fields']['field_sezione']['field'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['label'] = '';
  $handler->display->display_options['fields']['field_sezione']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sezione']['alter']['text'] = 'Sezione: [field_sezione]';
  $handler->display->display_options['fields']['field_sezione']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sezione']['delta_offset'] = '0';
  /* Campo: Contenuto: Tag */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['label'] = '';
  $handler->display->display_options['fields']['field_tags']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_tags']['alter']['text'] = '<br />Tags: [field_tags]';
  $handler->display->display_options['fields']['field_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tags']['type'] = 'ds_taxonomy_separator';
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  /* Campo: Contenuto: Informazioni */
  $handler->display->display_options['fields']['field_informazioni']['id'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['table'] = 'field_data_field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['field'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['label'] = '';
  $handler->display->display_options['fields']['field_informazioni']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_informazioni']['alter']['text'] = '[field_data_evento]<br />
[field_sezione]
[field_percorso]
[field_localizzazione]

<br />[field_images]
[field_informazioni]

<a href="[path]">Visualizza l\'evento completo</a>

<p>Canti collegati: [field_canti_evento]
[field_tags]</p>';
  $handler->display->display_options['fields']['field_informazioni']['element_label_colon'] = FALSE;
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y-m-d';
  /* Campo: Utente: Nome */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Criterio di ordinamento: Contenuto: Data evento -  data di inizio (field_data_evento) */
  $handler->display->display_options['sorts']['field_data_evento_value']['id'] = 'field_data_evento_value';
  $handler->display->display_options['sorts']['field_data_evento_value']['table'] = 'field_data_field_data_evento';
  $handler->display->display_options['sorts']['field_data_evento_value']['field'] = 'field_data_evento_value';
  $handler->display->display_options['sorts']['field_data_evento_value']['order'] = 'DESC';
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
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'evento' => 'evento',
  );
  /* Criterio del filtro: Workbench Moderation: Corrente */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['value'] = '1';
  /* Criterio del filtro: Workbench Moderation: Pubblicato */
  $handler->display->display_options['filters']['published']['id'] = 'published';
  $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['published']['field'] = 'published';
  $handler->display->display_options['filters']['published']['value'] = '1';
  $handler->display->display_options['path'] = 'app/eventi_giorno.rss';

  /* Display: Articoli */
  $handler = $view->new_display('feed', 'Articoli', 'articoli');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['description'] = 'Gli articoli de ilDeposito.org';
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'title';
  $handler->display->display_options['row_options']['link_field'] = 'path';
  $handler->display->display_options['row_options']['description_field'] = 'body';
  $handler->display->display_options['row_options']['creator_field'] = 'name';
  $handler->display->display_options['row_options']['date_field'] = 'created';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'path',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Tag */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_tags']['alter']['text'] = '<p>Tags: [field_tags]</p>';
  $handler->display->display_options['fields']['field_tags']['type'] = 'ds_taxonomy_separator';
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  /* Campo: Contenuto: Percorso */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_images']['alter']['text'] = '[field_images]<br />';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'image_style' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
    'image_link' => 'file',
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Campo: Contenuto: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['text'] = '[field_images]
[body]
<p><a href="[path]">Leggi l\'articolo completo</a></p>

[field_tags]';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'smart_trim_format';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '400',
    'trim_type' => 'chars',
    'trim_suffix' => ' [...]',
    'more_link' => '0',
    'more_text' => ' Continua a leggere',
    'summary_handler' => 'full',
    'trim_options' => array(
      'text' => 'text',
    ),
  );
  /* Campo: Utente: Nome */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y-m-d';
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

  /* Display: Canti */
  $handler = $view->new_display('feed', 'Canti', 'canti');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['description'] = 'I canti de ilDeposito.org';
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'title';
  $handler->display->display_options['row_options']['link_field'] = 'path';
  $handler->display->display_options['row_options']['description_field'] = 'field_testo';
  $handler->display->display_options['row_options']['creator_field'] = 'name';
  $handler->display->display_options['row_options']['date_field'] = 'created';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'path',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relazione: Contenuto: Autore */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relazione: Contenuto: Autori testo (field_autore_testo) */
  $handler->display->display_options['relationships']['field_autore_testo_nid']['id'] = 'field_autore_testo_nid';
  $handler->display->display_options['relationships']['field_autore_testo_nid']['table'] = 'field_data_field_autore_testo';
  $handler->display->display_options['relationships']['field_autore_testo_nid']['field'] = 'field_autore_testo_nid';
  $handler->display->display_options['relationships']['field_autore_testo_nid']['delta'] = '-1';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Tag */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_tags']['alter']['text'] = '<p>Tags: [field_tags]</p>';
  $handler->display->display_options['fields']['field_tags']['type'] = 'ds_taxonomy_separator';
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  /* Campo: Utente: Nome */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y-m-d';
  /* Campo: Contenuto: Percorso */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['relationship'] = 'field_autore_testo_nid';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_images']['alter']['text'] = '<br />[field_images]';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'image_style' => 'foto_autore',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Campo: Contenuto: Anno */
  $handler->display->display_options['fields']['field_anno']['id'] = 'field_anno';
  $handler->display->display_options['fields']['field_anno']['table'] = 'field_data_field_anno';
  $handler->display->display_options['fields']['field_anno']['field'] = 'field_anno';
  $handler->display->display_options['fields']['field_anno']['label'] = '';
  $handler->display->display_options['fields']['field_anno']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_anno']['alter']['text'] = '<br />Anno: [field_anno]';
  $handler->display->display_options['fields']['field_anno']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_anno']['settings'] = array(
    'format_type' => 'solo_anno',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  /* Campo: Contenuto: Sezione */
  $handler->display->display_options['fields']['field_sezione']['id'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['table'] = 'field_data_field_sezione';
  $handler->display->display_options['fields']['field_sezione']['field'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['label'] = '';
  $handler->display->display_options['fields']['field_sezione']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sezione']['alter']['text'] = 'Sezione: [field_sezione]';
  $handler->display->display_options['fields']['field_sezione']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sezione']['delta_offset'] = '0';
  /* Campo: Contenuto: Autori testo */
  $handler->display->display_options['fields']['field_autore_testo']['id'] = 'field_autore_testo';
  $handler->display->display_options['fields']['field_autore_testo']['table'] = 'field_data_field_autore_testo';
  $handler->display->display_options['fields']['field_autore_testo']['field'] = 'field_autore_testo';
  $handler->display->display_options['fields']['field_autore_testo']['label'] = '';
  $handler->display->display_options['fields']['field_autore_testo']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_autore_testo']['alter']['text'] = '<br />Autore: [field_autore_testo]';
  $handler->display->display_options['fields']['field_autore_testo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_autore_testo']['delta_offset'] = '0';
  /* Campo: Contenuto: Informazioni */
  $handler->display->display_options['fields']['field_informazioni']['id'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['table'] = 'field_data_field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['field'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['label'] = '';
  $handler->display->display_options['fields']['field_informazioni']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_informazioni']['alter']['text'] = 'Informazioni: [field_informazioni]';
  $handler->display->display_options['fields']['field_informazioni']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_informazioni']['settings'] = array(
    'trim_length' => '300',
    'trim_type' => 'chars',
    'trim_suffix' => '[...]',
    'more_link' => '0',
    'more_text' => 'Read more',
    'summary_handler' => 'full',
    'trim_options' => array(
      'text' => 0,
    ),
  );
  /* Campo: Contenuto: Testo */
  $handler->display->display_options['fields']['field_testo']['id'] = 'field_testo';
  $handler->display->display_options['fields']['field_testo']['table'] = 'field_data_field_testo';
  $handler->display->display_options['fields']['field_testo']['field'] = 'field_testo';
  $handler->display->display_options['fields']['field_testo']['label'] = '';
  $handler->display->display_options['fields']['field_testo']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_testo']['alter']['text'] = '[field_sezione]
[field_anno]
[field_autore_testo]
[field_images]


<p><pre>"<em>[field_testo]</em>"</pre>
<a href="[path]">Visualizza tutto il canto</a>
</p>

[field_tags]
[field_informazioni]';
  $handler->display->display_options['fields']['field_testo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_testo']['type'] = 'smart_trim_format';
  $handler->display->display_options['fields']['field_testo']['settings'] = array(
    'trim_length' => '200',
    'trim_type' => 'chars',
    'trim_suffix' => '[...]',
    'more_link' => '0',
    'more_text' => '',
    'trim_options' => array(
      'text' => 0,
    ),
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Criterio di ordinamento: Contenuto: Data di inserimento */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'canto' => 'canto',
  );
  /* Criterio del filtro: Workbench Moderation: Corrente */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['value'] = '1';
  /* Criterio del filtro: Workbench Moderation: Pubblicato */
  $handler->display->display_options['filters']['published']['id'] = 'published';
  $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['published']['field'] = 'published';
  $handler->display->display_options['filters']['published']['value'] = '1';
  $handler->display->display_options['path'] = 'app/canti.rss';

  /* Display: Traduzioni */
  $handler = $view->new_display('feed', 'Traduzioni', 'traduzioni');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['description'] = 'Le traduzioni de ilDeposito.org';
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'title';
  $handler->display->display_options['row_options']['link_field'] = 'path';
  $handler->display->display_options['row_options']['description_field'] = 'field_testo';
  $handler->display->display_options['row_options']['creator_field'] = 'name';
  $handler->display->display_options['row_options']['date_field'] = 'created';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'path',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relazione: Contenuto: Autore */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Tag */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_tags']['alter']['text'] = '<p>Tags: [field_tags]</p>';
  $handler->display->display_options['fields']['field_tags']['type'] = 'ds_taxonomy_separator';
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  /* Campo: Utente: Nome */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y-m-d';
  /* Campo: Contenuto: Lingua traduzione */
  $handler->display->display_options['fields']['field_lingua']['id'] = 'field_lingua';
  $handler->display->display_options['fields']['field_lingua']['table'] = 'field_data_field_lingua';
  $handler->display->display_options['fields']['field_lingua']['field'] = 'field_lingua';
  $handler->display->display_options['fields']['field_lingua']['label'] = '';
  $handler->display->display_options['fields']['field_lingua']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_lingua']['delta_offset'] = '0';
  /* Campo: Contenuto: Percorso */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Campo: Contenuto: Canto di riferimento */
  $handler->display->display_options['fields']['field_canto_riferimento']['id'] = 'field_canto_riferimento';
  $handler->display->display_options['fields']['field_canto_riferimento']['table'] = 'field_data_field_canto_riferimento';
  $handler->display->display_options['fields']['field_canto_riferimento']['field'] = 'field_canto_riferimento';
  $handler->display->display_options['fields']['field_canto_riferimento']['label'] = '';
  $handler->display->display_options['fields']['field_canto_riferimento']['element_label_colon'] = FALSE;
  /* Campo: Contenuto: Lingua originale */
  $handler->display->display_options['fields']['field_lingua_originale']['id'] = 'field_lingua_originale';
  $handler->display->display_options['fields']['field_lingua_originale']['table'] = 'field_data_field_lingua_originale';
  $handler->display->display_options['fields']['field_lingua_originale']['field'] = 'field_lingua_originale';
  $handler->display->display_options['fields']['field_lingua_originale']['label'] = '';
  $handler->display->display_options['fields']['field_lingua_originale']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_lingua_originale']['delta_offset'] = '0';
  /* Campo: Contenuto: Sezione */
  $handler->display->display_options['fields']['field_sezione']['id'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['table'] = 'field_data_field_sezione';
  $handler->display->display_options['fields']['field_sezione']['field'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['label'] = '';
  $handler->display->display_options['fields']['field_sezione']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sezione']['alter']['text'] = 'Sezione: [field_sezione]';
  $handler->display->display_options['fields']['field_sezione']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sezione']['delta_offset'] = '0';
  /* Campo: Contenuto: Informazioni */
  $handler->display->display_options['fields']['field_informazioni']['id'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['table'] = 'field_data_field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['field'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['label'] = '';
  $handler->display->display_options['fields']['field_informazioni']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_informazioni']['alter']['text'] = 'Informazioni: [field_informazioni]';
  $handler->display->display_options['fields']['field_informazioni']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_informazioni']['settings'] = array(
    'trim_length' => '300',
    'trim_type' => 'chars',
    'trim_suffix' => '[...]',
    'more_link' => '0',
    'more_text' => 'Read more',
    'summary_handler' => 'full',
    'trim_options' => array(
      'text' => 0,
    ),
  );
  /* Campo: Contenuto: Testo */
  $handler->display->display_options['fields']['field_testo']['id'] = 'field_testo';
  $handler->display->display_options['fields']['field_testo']['table'] = 'field_data_field_testo';
  $handler->display->display_options['fields']['field_testo']['field'] = 'field_testo';
  $handler->display->display_options['fields']['field_testo']['label'] = '';
  $handler->display->display_options['fields']['field_testo']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_testo']['alter']['text'] = 'Sezione: [field_sezione]<br />
Canto originale: [field_canto_riferimento] ([field_lingua_originale])<br />
Lingua traduzione: [field_lingua]

<p><pre>"<em>[field_testo]</em>"</pre>
<a href="[path]">Leggi tutta la traduzione</a>
</p>

[field_tags]
[field_informazioni]';
  $handler->display->display_options['fields']['field_testo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_testo']['type'] = 'smart_trim_format';
  $handler->display->display_options['fields']['field_testo']['settings'] = array(
    'trim_length' => '200',
    'trim_type' => 'chars',
    'trim_suffix' => '[...]',
    'more_link' => '0',
    'more_text' => '',
    'trim_options' => array(
      'text' => 0,
    ),
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Criterio di ordinamento: Contenuto: Data di inserimento */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'traduzione' => 'traduzione',
  );
  /* Criterio del filtro: Workbench Moderation: Corrente */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['value'] = '1';
  /* Criterio del filtro: Workbench Moderation: Pubblicato */
  $handler->display->display_options['filters']['published']['id'] = 'published';
  $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['published']['field'] = 'published';
  $handler->display->display_options['filters']['published']['value'] = '1';
  $handler->display->display_options['path'] = 'app/traduzioni.rss';

  /* Display: Eventi */
  $handler = $view->new_display('feed', 'Eventi', 'eventi');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['description'] = 'Gli eventi della Storia Cantata';
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'title';
  $handler->display->display_options['row_options']['link_field'] = 'path';
  $handler->display->display_options['row_options']['description_field'] = 'field_informazioni';
  $handler->display->display_options['row_options']['creator_field'] = 'name';
  $handler->display->display_options['row_options']['date_field'] = 'created';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'path',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Data evento */
  $handler->display->display_options['fields']['field_data_evento_1']['id'] = 'field_data_evento_1';
  $handler->display->display_options['fields']['field_data_evento_1']['table'] = 'field_data_field_data_evento';
  $handler->display->display_options['fields']['field_data_evento_1']['field'] = 'field_data_evento';
  $handler->display->display_options['fields']['field_data_evento_1']['label'] = '';
  $handler->display->display_options['fields']['field_data_evento_1']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_data_evento_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_data_evento_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_data_evento_1']['settings'] = array(
    'format_type' => 'data_estesa',
    'fromto' => 'value',
    'multiple_number' => '1',
    'multiple_from' => '0',
    'multiple_to' => '',
    'show_repeat_rule' => 'hide',
  );
  $handler->display->display_options['fields']['field_data_evento_1']['delta_offset'] = '0';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[field_data_evento_1] - [title]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Canti collegati */
  $handler->display->display_options['fields']['field_canti_evento']['id'] = 'field_canti_evento';
  $handler->display->display_options['fields']['field_canti_evento']['table'] = 'field_data_field_canti_evento';
  $handler->display->display_options['fields']['field_canti_evento']['field'] = 'field_canti_evento';
  $handler->display->display_options['fields']['field_canti_evento']['label'] = '';
  $handler->display->display_options['fields']['field_canti_evento']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_canti_evento']['alter']['text'] = '[field_canti_evento]';
  $handler->display->display_options['fields']['field_canti_evento']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_canti_evento']['delta_offset'] = '0';
  /* Campo: Contenuto: Data evento */
  $handler->display->display_options['fields']['field_data_evento']['id'] = 'field_data_evento';
  $handler->display->display_options['fields']['field_data_evento']['table'] = 'field_data_field_data_evento';
  $handler->display->display_options['fields']['field_data_evento']['field'] = 'field_data_evento';
  $handler->display->display_options['fields']['field_data_evento']['label'] = '';
  $handler->display->display_options['fields']['field_data_evento']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_data_evento']['alter']['text'] = 'Data evento: [field_data_evento]';
  $handler->display->display_options['fields']['field_data_evento']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_data_evento']['settings'] = array(
    'format_type' => 'data_estesa',
    'fromto' => 'value',
    'multiple_number' => '1',
    'multiple_from' => '0',
    'multiple_to' => '',
    'show_repeat_rule' => 'hide',
  );
  $handler->display->display_options['fields']['field_data_evento']['delta_offset'] = '0';
  /* Campo: Contenuto: Localizzazioni */
  $handler->display->display_options['fields']['field_localizzazione']['id'] = 'field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['table'] = 'field_data_field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['field'] = 'field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['label'] = '';
  $handler->display->display_options['fields']['field_localizzazione']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_localizzazione']['alter']['text'] = '<br />Localizzazione: [field_localizzazione]';
  $handler->display->display_options['fields']['field_localizzazione']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_localizzazione']['delta_offset'] = '0';
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'image_style' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
    'image_link' => 'file',
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Campo: Contenuto: Percorsi */
  $handler->display->display_options['fields']['field_percorso']['id'] = 'field_percorso';
  $handler->display->display_options['fields']['field_percorso']['table'] = 'field_data_field_percorso';
  $handler->display->display_options['fields']['field_percorso']['field'] = 'field_percorso';
  $handler->display->display_options['fields']['field_percorso']['label'] = '';
  $handler->display->display_options['fields']['field_percorso']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_percorso']['alter']['text'] = '<br />Percorso: [field_percorso]';
  $handler->display->display_options['fields']['field_percorso']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_percorso']['delta_offset'] = '0';
  /* Campo: Contenuto: Percorso */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Campo: Contenuto: Sezione */
  $handler->display->display_options['fields']['field_sezione']['id'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['table'] = 'field_data_field_sezione';
  $handler->display->display_options['fields']['field_sezione']['field'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['label'] = '';
  $handler->display->display_options['fields']['field_sezione']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sezione']['alter']['text'] = 'Sezione: [field_sezione]';
  $handler->display->display_options['fields']['field_sezione']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sezione']['delta_offset'] = '0';
  /* Campo: Contenuto: Tag */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['label'] = '';
  $handler->display->display_options['fields']['field_tags']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_tags']['alter']['text'] = '<br />Tags: [field_tags]';
  $handler->display->display_options['fields']['field_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tags']['type'] = 'ds_taxonomy_separator';
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  /* Campo: Contenuto: Informazioni */
  $handler->display->display_options['fields']['field_informazioni']['id'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['table'] = 'field_data_field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['field'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['label'] = '';
  $handler->display->display_options['fields']['field_informazioni']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_informazioni']['alter']['text'] = '[field_data_evento]<br />
[field_sezione]
[field_percorso]
[field_localizzazione]

<br />[field_images]
[field_informazioni]

<a href="[path]">Visualizza l\'evento completo</a>

<p>Canti collegati: [field_canti_evento]
[field_tags]</p>';
  $handler->display->display_options['fields']['field_informazioni']['element_label_colon'] = FALSE;
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'Y-m-d';
  /* Campo: Utente: Nome */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Criterio di ordinamento: Contenuto: Data di inserimento */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'evento' => 'evento',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Criterio del filtro: Contenuto: Pubblicato */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['path'] = 'app/eventi.rss';
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
    t('autore'),
    t('Eventi del giorno'),
    t('[field_data_evento_1] - [title]'),
    t('[field_canti_evento]'),
    t('Data evento: [field_data_evento]'),
    t('<br />Localizzazione: [field_localizzazione]'),
    t('<br />Percorso: [field_percorso]'),
    t('Sezione: [field_sezione]'),
    t('<br />Tags: [field_tags]'),
    t('[field_data_evento]<br />
[field_sezione]
[field_percorso]
[field_localizzazione]

<br />[field_images]
[field_informazioni]

<a href="[path]">Visualizza l\'evento completo</a>

<p>Canti collegati: [field_canti_evento]
[field_tags]</p>'),
    t('Tutti'),
    t('Articoli'),
    t('Tag'),
    t('<p>Tags: [field_tags]</p>'),
    t('[field_images]<br />'),
    t('[field_images]
[body]
<p><a href="[path]">Leggi l\'articolo completo</a></p>

[field_tags]'),
    t('Archivio'),
    t('Canti'),
    t('field_autore_testo'),
    t('<br />[field_images]'),
    t('<br />Anno: [field_anno]'),
    t('<br />Autore: [field_autore_testo]'),
    t('Informazioni: [field_informazioni]'),
    t('[field_sezione]
[field_anno]
[field_autore_testo]
[field_images]


<p><pre>"<em>[field_testo]</em>"</pre>
<a href="[path]">Visualizza tutto il canto</a>
</p>

[field_tags]
[field_informazioni]'),
    t('Traduzioni'),
    t('Sezione: [field_sezione]<br />
Canto originale: [field_canto_riferimento] ([field_lingua_originale])<br />
Lingua traduzione: [field_lingua]

<p><pre>"<em>[field_testo]</em>"</pre>
<a href="[path]">Leggi tutta la traduzione</a>
</p>

[field_tags]
[field_informazioni]'),
    t('Eventi'),
  );
  $export['rss_app'] = $view;

  return $export;
}
