<?php
/**
 * @file
 * migrando_d8.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function migrando_d8_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'd8_files';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'file_managed';
  $view->human_name = 'D8 files';
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
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_json';
  $handler->display->display_options['style_options']['root_object'] = 'items';
  $handler->display->display_options['style_options']['top_child_object'] = 'item';
  $handler->display->display_options['style_options']['field_output'] = 'raw';
  $handler->display->display_options['style_options']['plaintext_output'] = 1;
  $handler->display->display_options['style_options']['remove_newlines'] = 0;
  $handler->display->display_options['style_options']['jsonp_prefix'] = '';
  $handler->display->display_options['style_options']['using_views_api_mode'] = 0;
  $handler->display->display_options['style_options']['object_arrays'] = 1;
  $handler->display->display_options['style_options']['numeric_strings'] = 0;
  $handler->display->display_options['style_options']['bigint_string'] = 0;
  $handler->display->display_options['style_options']['pretty_print'] = 0;
  $handler->display->display_options['style_options']['unescaped_slashes'] = 0;
  $handler->display->display_options['style_options']['unescaped_unicode'] = 0;
  $handler->display->display_options['style_options']['char_encoding'] = array();
  /* Campo: File: ID file */
  $handler->display->display_options['fields']['fid']['id'] = 'fid';
  $handler->display->display_options['fields']['fid']['table'] = 'file_managed';
  $handler->display->display_options['fields']['fid']['field'] = 'fid';
  $handler->display->display_options['fields']['fid']['label'] = 'id';
  /* Campo: File: File UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'file_managed';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: File: Nome */
  $handler->display->display_options['fields']['filename']['id'] = 'filename';
  $handler->display->display_options['fields']['filename']['table'] = 'file_managed';
  $handler->display->display_options['fields']['filename']['field'] = 'filename';
  $handler->display->display_options['fields']['filename']['label'] = 'filename';
  $handler->display->display_options['fields']['filename']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['filename']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['filename']['link_to_file'] = FALSE;
  /* Campo: File: Percorso */
  $handler->display->display_options['fields']['uri']['id'] = 'uri';
  $handler->display->display_options['fields']['uri']['table'] = 'file_managed';
  $handler->display->display_options['fields']['uri']['field'] = 'uri';
  $handler->display->display_options['fields']['uri']['label'] = 'filepath';
  /* Campo: File: Percorso */
  $handler->display->display_options['fields']['uri_1']['id'] = 'uri_1';
  $handler->display->display_options['fields']['uri_1']['table'] = 'file_managed';
  $handler->display->display_options['fields']['uri_1']['field'] = 'uri';
  $handler->display->display_options['fields']['uri_1']['label'] = 'url';
  $handler->display->display_options['fields']['uri_1']['file_download_path'] = TRUE;
  /* Campo: Campo: Links */
  $handler->display->display_options['fields']['field_links']['id'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['field_links']['field'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['label'] = 'links';
  $handler->display->display_options['fields']['field_links']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_links']['type'] = 'services';
  $handler->display->display_options['fields']['field_links']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_links']['delta_offset'] = '0';
  /* Campo: File: Alt Text */
  $handler->display->display_options['fields']['field_file_image_alt_text']['id'] = 'field_file_image_alt_text';
  $handler->display->display_options['fields']['field_file_image_alt_text']['table'] = 'field_data_field_file_image_alt_text';
  $handler->display->display_options['fields']['field_file_image_alt_text']['field'] = 'field_file_image_alt_text';
  $handler->display->display_options['fields']['field_file_image_alt_text']['label'] = 'alt_text';
  /* Campo: File: Data di caricamento */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'file_managed';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'created';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: File: Stato */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'file_managed';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'stato';
  /* Campo: File: Data di caricamento */
  $handler->display->display_options['fields']['timestamp_1']['id'] = 'timestamp_1';
  $handler->display->display_options['fields']['timestamp_1']['table'] = 'file_managed';
  $handler->display->display_options['fields']['timestamp_1']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp_1']['label'] = 'created_year';
  $handler->display->display_options['fields']['timestamp_1']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp_1']['custom_date_format'] = 'Y';
  $handler->display->display_options['fields']['timestamp_1']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Globale: Testo personalizzato */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'directory';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'public://immagini/[timestamp_1]/[filename]';
  /* Criterio di ordinamento: File: Data di caricamento */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'file_managed';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Criterio del filtro: File: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'file_managed';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'image' => 'image',
  );

  /* Display: Immagini */
  $handler = $view->new_display('services', 'Immagini', 'immagini');
  $handler->display->display_options['path'] = 'immagini';
  $translatables['d8_files'] = array(
    t('Master'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('id'),
    t('uuid'),
    t('filename'),
    t('filepath'),
    t('url'),
    t('links'),
    t('alt_text'),
    t('created'),
    t('stato'),
    t('created_year'),
    t('directory'),
    t('public://immagini/[timestamp_1]/[filename]'),
    t('Immagini'),
  );
  $export['d8_files'] = $view;

  $view = new view();
  $view->name = 'd8_nodi';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'D8 nodi';
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
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_json';
  $handler->display->display_options['style_options']['plaintext_output'] = 1;
  $handler->display->display_options['style_options']['remove_newlines'] = 0;
  $handler->display->display_options['style_options']['jsonp_prefix'] = '';
  $handler->display->display_options['style_options']['using_views_api_mode'] = 0;
  $handler->display->display_options['style_options']['object_arrays'] = 0;
  $handler->display->display_options['style_options']['numeric_strings'] = 0;
  $handler->display->display_options['style_options']['bigint_string'] = 0;
  $handler->display->display_options['style_options']['pretty_print'] = 0;
  $handler->display->display_options['style_options']['unescaped_slashes'] = 0;
  $handler->display->display_options['style_options']['unescaped_unicode'] = 0;
  $handler->display->display_options['style_options']['char_encoding'] = array();
  /* Campo: Contenuto: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'nid';
  /* Campo: Contenuto: Contenuto UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'node';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'titolo';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Identificativo uid dell'autore */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'uid';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'testo';
  $handler->display->display_options['fields']['body']['type'] = 'services';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Tag */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['label'] = 'tags';
  $handler->display->display_options['fields']['field_tags']['type'] = 'services';
  $handler->display->display_options['fields']['field_tags']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'term_name' => 0,
  );
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = 'immagini';
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'services';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Data modifica */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Pubblicato */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'stato';
  $handler->display->display_options['fields']['status']['type'] = 'boolean';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Criterio di ordinamento: Contenuto: Data di inserimento */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'articolo' => 'articolo',
  );

  /* Display: Articoli */
  $handler = $view->new_display('services', 'Articoli', 'services_1');
  $handler->display->display_options['path'] = 'migrando_articoli';

  /* Display: Pagine */
  $handler = $view->new_display('services', 'Pagine', 'services_2');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'nid';
  /* Campo: Contenuto: Contenuto UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'node';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'titolo';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Identificativo uid dell'autore */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'uid';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'testo';
  $handler->display->display_options['fields']['body']['type'] = 'services';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Data modifica */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Pubblicato */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'stato';
  $handler->display->display_options['fields']['status']['type'] = 'boolean';
  $handler->display->display_options['fields']['status']['not'] = 0;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pagina' => 'pagina',
  );
  $handler->display->display_options['path'] = 'migrando_pagine';

  /* Display: Pagine libro */
  $handler = $view->new_display('services', 'Pagine libro', 'services_3');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'nid';
  /* Campo: Contenuto: Contenuto UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'node';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'titolo';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Identificativo uid dell'autore */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'uid';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'testo';
  $handler->display->display_options['fields']['body']['type'] = 'services';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Data modifica */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Pubblicato */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'stato';
  $handler->display->display_options['fields']['status']['type'] = 'boolean';
  $handler->display->display_options['fields']['status']['not'] = 0;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'book' => 'book',
  );
  $handler->display->display_options['path'] = 'migrando_pagine_libro';

  /* Display: Autori */
  $handler = $view->new_display('services', 'Autori', 'services_4');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'nid';
  /* Campo: Contenuto: Contenuto UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'node';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'titolo';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Identificativo uid dell'autore */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'uid';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Data modifica */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Pubblicato */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'stato';
  $handler->display->display_options['fields']['status']['type'] = 'boolean';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = 'immagini';
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'services';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Campo: Campo: Links */
  $handler->display->display_options['fields']['field_links']['id'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['field_links']['field'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['label'] = 'links';
  $handler->display->display_options['fields']['field_links']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_links']['type'] = 'services';
  $handler->display->display_options['fields']['field_links']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_links']['delta_offset'] = '0';
  /* Campo: Contenuto: Altri nomi */
  $handler->display->display_options['fields']['field_altri_nomi']['id'] = 'field_altri_nomi';
  $handler->display->display_options['fields']['field_altri_nomi']['table'] = 'field_data_field_altri_nomi';
  $handler->display->display_options['fields']['field_altri_nomi']['field'] = 'field_altri_nomi';
  $handler->display->display_options['fields']['field_altri_nomi']['label'] = 'altri_nomi';
  $handler->display->display_options['fields']['field_altri_nomi']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  $handler->display->display_options['fields']['field_altri_nomi']['delta_offset'] = '0';
  /* Campo: Contenuto: Cognome (o nome del gruppo) */
  $handler->display->display_options['fields']['field_cognome']['id'] = 'field_cognome';
  $handler->display->display_options['fields']['field_cognome']['table'] = 'field_data_field_cognome';
  $handler->display->display_options['fields']['field_cognome']['field'] = 'field_cognome';
  $handler->display->display_options['fields']['field_cognome']['label'] = 'cognome';
  $handler->display->display_options['fields']['field_cognome']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Localizzazioni */
  $handler->display->display_options['fields']['field_localizzazione']['id'] = 'field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['table'] = 'field_data_field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['field'] = 'field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['label'] = 'localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['type'] = 'services';
  $handler->display->display_options['fields']['field_localizzazione']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_localizzazione']['delta_offset'] = '0';
  /* Campo: Contenuto: Nome */
  $handler->display->display_options['fields']['field_nome']['id'] = 'field_nome';
  $handler->display->display_options['fields']['field_nome']['table'] = 'field_data_field_nome';
  $handler->display->display_options['fields']['field_nome']['field'] = 'field_nome';
  $handler->display->display_options['fields']['field_nome']['label'] = 'nome';
  $handler->display->display_options['fields']['field_nome']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Sezione */
  $handler->display->display_options['fields']['field_sezione']['id'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['table'] = 'field_data_field_sezione';
  $handler->display->display_options['fields']['field_sezione']['field'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['label'] = 'sezione';
  $handler->display->display_options['fields']['field_sezione']['type'] = 'services';
  $handler->display->display_options['fields']['field_sezione']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_sezione']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'autore' => 'autore',
  );
  $handler->display->display_options['path'] = 'migrando_autori';

  /* Display: Canti */
  $handler = $view->new_display('services', 'Canti', 'services_5');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'nid';
  /* Campo: Contenuto: Contenuto UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'node';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'titolo';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Identificativo uid dell'autore */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'uid';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Data modifica */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Pubblicato */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'stato';
  $handler->display->display_options['fields']['status']['type'] = 'boolean';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Campo: Campo: Links */
  $handler->display->display_options['fields']['field_links']['id'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['field_links']['field'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['label'] = 'links';
  $handler->display->display_options['fields']['field_links']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_links']['type'] = 'services';
  $handler->display->display_options['fields']['field_links']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_links']['delta_offset'] = '0';
  /* Campo: Contenuto: Accordi */
  $handler->display->display_options['fields']['field_accordi']['id'] = 'field_accordi';
  $handler->display->display_options['fields']['field_accordi']['table'] = 'field_data_field_accordi';
  $handler->display->display_options['fields']['field_accordi']['field'] = 'field_accordi';
  $handler->display->display_options['fields']['field_accordi']['label'] = 'accordi';
  $handler->display->display_options['fields']['field_accordi']['type'] = 'services';
  $handler->display->display_options['fields']['field_accordi']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Anno */
  $handler->display->display_options['fields']['field_anno']['id'] = 'field_anno';
  $handler->display->display_options['fields']['field_anno']['table'] = 'field_data_field_anno';
  $handler->display->display_options['fields']['field_anno']['field'] = 'field_anno';
  $handler->display->display_options['fields']['field_anno']['label'] = 'anno';
  $handler->display->display_options['fields']['field_anno']['type'] = 'services';
  $handler->display->display_options['fields']['field_anno']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Campo: Contenuto: Autori musica */
  $handler->display->display_options['fields']['field_autore_musica']['id'] = 'field_autore_musica';
  $handler->display->display_options['fields']['field_autore_musica']['table'] = 'field_data_field_autore_musica';
  $handler->display->display_options['fields']['field_autore_musica']['field'] = 'field_autore_musica';
  $handler->display->display_options['fields']['field_autore_musica']['label'] = 'autori_musica';
  $handler->display->display_options['fields']['field_autore_musica']['type'] = 'services';
  $handler->display->display_options['fields']['field_autore_musica']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_autore_musica']['delta_offset'] = '0';
  /* Campo: Contenuto: Autori testo */
  $handler->display->display_options['fields']['field_autore_testo']['id'] = 'field_autore_testo';
  $handler->display->display_options['fields']['field_autore_testo']['table'] = 'field_data_field_autore_testo';
  $handler->display->display_options['fields']['field_autore_testo']['field'] = 'field_autore_testo';
  $handler->display->display_options['fields']['field_autore_testo']['label'] = 'autori_testo';
  $handler->display->display_options['fields']['field_autore_testo']['type'] = 'services';
  $handler->display->display_options['fields']['field_autore_testo']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_autore_testo']['delta_offset'] = '0';
  /* Campo: Contenuto: Capoverso */
  $handler->display->display_options['fields']['field_capoverso']['id'] = 'field_capoverso';
  $handler->display->display_options['fields']['field_capoverso']['table'] = 'field_data_field_capoverso';
  $handler->display->display_options['fields']['field_capoverso']['field'] = 'field_capoverso';
  $handler->display->display_options['fields']['field_capoverso']['label'] = 'capoverso';
  $handler->display->display_options['fields']['field_capoverso']['type'] = 'services';
  $handler->display->display_options['fields']['field_capoverso']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Fonte */
  $handler->display->display_options['fields']['field_fonte']['id'] = 'field_fonte';
  $handler->display->display_options['fields']['field_fonte']['table'] = 'field_data_field_fonte';
  $handler->display->display_options['fields']['field_fonte']['field'] = 'field_fonte';
  $handler->display->display_options['fields']['field_fonte']['label'] = 'fonte';
  $handler->display->display_options['fields']['field_fonte']['type'] = 'services';
  $handler->display->display_options['fields']['field_fonte']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Informazioni */
  $handler->display->display_options['fields']['field_informazioni']['id'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['table'] = 'field_data_field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['field'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['label'] = 'informazioni';
  $handler->display->display_options['fields']['field_informazioni']['type'] = 'services';
  $handler->display->display_options['fields']['field_informazioni']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Lingua traduzione */
  $handler->display->display_options['fields']['field_lingua']['id'] = 'field_lingua';
  $handler->display->display_options['fields']['field_lingua']['table'] = 'field_data_field_lingua';
  $handler->display->display_options['fields']['field_lingua']['field'] = 'field_lingua';
  $handler->display->display_options['fields']['field_lingua']['label'] = 'lingua';
  $handler->display->display_options['fields']['field_lingua']['type'] = 'services';
  $handler->display->display_options['fields']['field_lingua']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_lingua']['delta_offset'] = '0';
  /* Campo: Contenuto: Risorse audio o video */
  $handler->display->display_options['fields']['field_link_audio']['id'] = 'field_link_audio';
  $handler->display->display_options['fields']['field_link_audio']['table'] = 'field_data_field_link_audio';
  $handler->display->display_options['fields']['field_link_audio']['field'] = 'field_link_audio';
  $handler->display->display_options['fields']['field_link_audio']['label'] = 'audio';
  $handler->display->display_options['fields']['field_link_audio']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_link_audio']['type'] = 'services';
  $handler->display->display_options['fields']['field_link_audio']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_link_audio']['delta_offset'] = '0';
  /* Campo: Contenuto: Sezione */
  $handler->display->display_options['fields']['field_sezione']['id'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['table'] = 'field_data_field_sezione';
  $handler->display->display_options['fields']['field_sezione']['field'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['label'] = 'sezione';
  $handler->display->display_options['fields']['field_sezione']['type'] = 'services';
  $handler->display->display_options['fields']['field_sezione']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_sezione']['delta_offset'] = '0';
  /* Campo: Contenuto: Tag */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['label'] = 'tags';
  $handler->display->display_options['fields']['field_tags']['type'] = 'services';
  $handler->display->display_options['fields']['field_tags']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  /* Campo: Contenuto: Testo */
  $handler->display->display_options['fields']['field_testo']['id'] = 'field_testo';
  $handler->display->display_options['fields']['field_testo']['table'] = 'field_data_field_testo';
  $handler->display->display_options['fields']['field_testo']['field'] = 'field_testo';
  $handler->display->display_options['fields']['field_testo']['label'] = 'testo';
  $handler->display->display_options['fields']['field_testo']['type'] = 'services';
  $handler->display->display_options['fields']['field_testo']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Titolo alternativo */
  $handler->display->display_options['fields']['field_titolo_alt']['id'] = 'field_titolo_alt';
  $handler->display->display_options['fields']['field_titolo_alt']['table'] = 'field_data_field_titolo_alt';
  $handler->display->display_options['fields']['field_titolo_alt']['field'] = 'field_titolo_alt';
  $handler->display->display_options['fields']['field_titolo_alt']['label'] = 'titolo_alternativo';
  $handler->display->display_options['fields']['field_titolo_alt']['type'] = 'services';
  $handler->display->display_options['fields']['field_titolo_alt']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  $handler->display->display_options['fields']['field_titolo_alt']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'canto' => 'canto',
  );
  $handler->display->display_options['path'] = 'migrando_canti';

  /* Display: Eventi */
  $handler = $view->new_display('services', 'Eventi', 'services_6');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'nid';
  /* Campo: Contenuto: Contenuto UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'node';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'titolo';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Identificativo uid dell'autore */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'uid';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Data modifica */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Pubblicato */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'stato';
  $handler->display->display_options['fields']['status']['type'] = 'boolean';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = 'immagini';
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'services';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Campo: Campo: Links */
  $handler->display->display_options['fields']['field_links']['id'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['field_links']['field'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['label'] = 'links';
  $handler->display->display_options['fields']['field_links']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_links']['type'] = 'services';
  $handler->display->display_options['fields']['field_links']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_links']['delta_offset'] = '0';
  /* Campo: Contenuto: Canti collegati */
  $handler->display->display_options['fields']['field_canti_evento']['id'] = 'field_canti_evento';
  $handler->display->display_options['fields']['field_canti_evento']['table'] = 'field_data_field_canti_evento';
  $handler->display->display_options['fields']['field_canti_evento']['field'] = 'field_canti_evento';
  $handler->display->display_options['fields']['field_canti_evento']['label'] = 'canti_collegati';
  $handler->display->display_options['fields']['field_canti_evento']['type'] = 'services';
  $handler->display->display_options['fields']['field_canti_evento']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_canti_evento']['delta_offset'] = '0';
  /* Campo: Contenuto: Data evento */
  $handler->display->display_options['fields']['field_data_evento']['id'] = 'field_data_evento';
  $handler->display->display_options['fields']['field_data_evento']['table'] = 'field_data_field_data_evento';
  $handler->display->display_options['fields']['field_data_evento']['field'] = 'field_data_evento';
  $handler->display->display_options['fields']['field_data_evento']['label'] = 'data_evento';
  $handler->display->display_options['fields']['field_data_evento']['type'] = 'services';
  $handler->display->display_options['fields']['field_data_evento']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_data_evento']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_data_evento']['delta_offset'] = '0';
  /* Campo: Contenuto: Geolocation */
  $handler->display->display_options['fields']['field_geolocation']['id'] = 'field_geolocation';
  $handler->display->display_options['fields']['field_geolocation']['table'] = 'field_data_field_geolocation';
  $handler->display->display_options['fields']['field_geolocation']['field'] = 'field_geolocation';
  $handler->display->display_options['fields']['field_geolocation']['label'] = 'geolocation';
  $handler->display->display_options['fields']['field_geolocation']['click_sort_column'] = 'lat';
  $handler->display->display_options['fields']['field_geolocation']['type'] = 'services';
  $handler->display->display_options['fields']['field_geolocation']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Campo: Contenuto: Informazioni */
  $handler->display->display_options['fields']['field_informazioni']['id'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['table'] = 'field_data_field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['field'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['label'] = 'informazioni';
  /* Campo: Contenuto: Descrizione Social */
  $handler->display->display_options['fields']['field_descrizione_social']['id'] = 'field_descrizione_social';
  $handler->display->display_options['fields']['field_descrizione_social']['table'] = 'field_data_field_descrizione_social';
  $handler->display->display_options['fields']['field_descrizione_social']['field'] = 'field_descrizione_social';
  $handler->display->display_options['fields']['field_descrizione_social']['label'] = 'descrizione_social';
  /* Campo: Contenuto: Localizzazioni */
  $handler->display->display_options['fields']['field_localizzazione']['id'] = 'field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['table'] = 'field_data_field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['field'] = 'field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['label'] = 'localizzazioni';
  $handler->display->display_options['fields']['field_localizzazione']['type'] = 'services';
  $handler->display->display_options['fields']['field_localizzazione']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_localizzazione']['delta_offset'] = '0';
  /* Campo: Contenuto: Percorsi */
  $handler->display->display_options['fields']['field_percorso']['id'] = 'field_percorso';
  $handler->display->display_options['fields']['field_percorso']['table'] = 'field_data_field_percorso';
  $handler->display->display_options['fields']['field_percorso']['field'] = 'field_percorso';
  $handler->display->display_options['fields']['field_percorso']['label'] = 'percorsi';
  $handler->display->display_options['fields']['field_percorso']['type'] = 'services';
  $handler->display->display_options['fields']['field_percorso']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_percorso']['delta_offset'] = '0';
  /* Campo: Contenuto: Sezione */
  $handler->display->display_options['fields']['field_sezione']['id'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['table'] = 'field_data_field_sezione';
  $handler->display->display_options['fields']['field_sezione']['field'] = 'field_sezione';
  $handler->display->display_options['fields']['field_sezione']['label'] = 'sezione';
  $handler->display->display_options['fields']['field_sezione']['type'] = 'services';
  $handler->display->display_options['fields']['field_sezione']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_sezione']['delta_offset'] = '0';
  /* Campo: Contenuto: Tag */
  $handler->display->display_options['fields']['field_tags']['id'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['table'] = 'field_data_field_tags';
  $handler->display->display_options['fields']['field_tags']['field'] = 'field_tags';
  $handler->display->display_options['fields']['field_tags']['label'] = 'tags';
  $handler->display->display_options['fields']['field_tags']['type'] = 'services';
  $handler->display->display_options['fields']['field_tags']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_tags']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'evento' => 'evento',
  );
  $handler->display->display_options['path'] = 'migrando_eventi';

  /* Display: Gruppi */
  $handler = $view->new_display('services', 'Gruppi', 'services_7');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'nid';
  /* Campo: Contenuto: Contenuto UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'node';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'titolo';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Identificativo uid dell'autore */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'uid';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Data modifica */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Pubblicato */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'stato';
  $handler->display->display_options['fields']['status']['type'] = 'boolean';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = 'immagini';
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'services';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Campo: Campo: Links */
  $handler->display->display_options['fields']['field_links']['id'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['field_links']['field'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['label'] = 'links';
  $handler->display->display_options['fields']['field_links']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_links']['type'] = 'services';
  $handler->display->display_options['fields']['field_links']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_links']['delta_offset'] = '0';
  /* Campo: Contenuto: Anno */
  $handler->display->display_options['fields']['field_anno']['id'] = 'field_anno';
  $handler->display->display_options['fields']['field_anno']['table'] = 'field_data_field_anno';
  $handler->display->display_options['fields']['field_anno']['field'] = 'field_anno';
  $handler->display->display_options['fields']['field_anno']['label'] = 'anno';
  $handler->display->display_options['fields']['field_anno']['type'] = 'services';
  $handler->display->display_options['fields']['field_anno']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Campo: Contenuto: Email */
  $handler->display->display_options['fields']['field_email']['id'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['table'] = 'field_data_field_email';
  $handler->display->display_options['fields']['field_email']['field'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['label'] = 'email';
  $handler->display->display_options['fields']['field_email']['type'] = 'services';
  $handler->display->display_options['fields']['field_email']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Campo: Contenuto: Geofield */
  $handler->display->display_options['fields']['field_geofield']['id'] = 'field_geofield';
  $handler->display->display_options['fields']['field_geofield']['table'] = 'field_data_field_geofield';
  $handler->display->display_options['fields']['field_geofield']['field'] = 'field_geofield';
  $handler->display->display_options['fields']['field_geofield']['label'] = 'geofield';
  $handler->display->display_options['fields']['field_geofield']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_geofield']['type'] = 'services';
  $handler->display->display_options['fields']['field_geofield']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Campo: Contenuto: Indirizzo */
  $handler->display->display_options['fields']['field_indirizzo']['id'] = 'field_indirizzo';
  $handler->display->display_options['fields']['field_indirizzo']['table'] = 'field_data_field_indirizzo';
  $handler->display->display_options['fields']['field_indirizzo']['field'] = 'field_indirizzo';
  $handler->display->display_options['fields']['field_indirizzo']['label'] = 'address';
  $handler->display->display_options['fields']['field_indirizzo']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_indirizzo']['type'] = 'services';
  $handler->display->display_options['fields']['field_indirizzo']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Campo: Contenuto: Informazioni */
  $handler->display->display_options['fields']['field_informazioni']['id'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['table'] = 'field_data_field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['field'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['label'] = 'informazioni';
  $handler->display->display_options['fields']['field_informazioni']['type'] = 'services';
  $handler->display->display_options['fields']['field_informazioni']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Localizzazioni */
  $handler->display->display_options['fields']['field_localizzazione']['id'] = 'field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['table'] = 'field_data_field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['field'] = 'field_localizzazione';
  $handler->display->display_options['fields']['field_localizzazione']['label'] = 'localizzazioni';
  $handler->display->display_options['fields']['field_localizzazione']['type'] = 'services';
  $handler->display->display_options['fields']['field_localizzazione']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_localizzazione']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gruppi' => 'gruppi',
  );
  $handler->display->display_options['path'] = 'migrando_gruppi';

  /* Display: Traduzioni */
  $handler = $view->new_display('services', 'Traduzioni', 'services_8');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'nid';
  /* Campo: Contenuto: Contenuto UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'node';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'titolo';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Identificativo uid dell'autore */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'uid';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Campo: Contenuto: Data di inserimento */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Data modifica */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Contenuto: Pubblicato */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'stato';
  $handler->display->display_options['fields']['status']['type'] = 'boolean';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Campo: Contenuto: Canto di riferimento */
  $handler->display->display_options['fields']['field_canto_riferimento']['id'] = 'field_canto_riferimento';
  $handler->display->display_options['fields']['field_canto_riferimento']['table'] = 'field_data_field_canto_riferimento';
  $handler->display->display_options['fields']['field_canto_riferimento']['field'] = 'field_canto_riferimento';
  $handler->display->display_options['fields']['field_canto_riferimento']['label'] = 'canto_riferimento';
  $handler->display->display_options['fields']['field_canto_riferimento']['type'] = 'services';
  $handler->display->display_options['fields']['field_canto_riferimento']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Campo: Contenuto: Informazioni */
  $handler->display->display_options['fields']['field_informazioni']['id'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['table'] = 'field_data_field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['field'] = 'field_informazioni';
  $handler->display->display_options['fields']['field_informazioni']['label'] = 'informazioni';
  $handler->display->display_options['fields']['field_informazioni']['type'] = 'services';
  $handler->display->display_options['fields']['field_informazioni']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
    'skip_text_format' => 1,
  );
  /* Campo: Contenuto: Lingua traduzione */
  $handler->display->display_options['fields']['field_lingua']['id'] = 'field_lingua';
  $handler->display->display_options['fields']['field_lingua']['table'] = 'field_data_field_lingua';
  $handler->display->display_options['fields']['field_lingua']['field'] = 'field_lingua';
  $handler->display->display_options['fields']['field_lingua']['label'] = 'lingua';
  $handler->display->display_options['fields']['field_lingua']['type'] = 'services';
  $handler->display->display_options['fields']['field_lingua']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_lingua']['delta_offset'] = '0';
  /* Campo: Contenuto: Testo */
  $handler->display->display_options['fields']['field_testo']['id'] = 'field_testo';
  $handler->display->display_options['fields']['field_testo']['table'] = 'field_data_field_testo';
  $handler->display->display_options['fields']['field_testo']['field'] = 'field_testo';
  $handler->display->display_options['fields']['field_testo']['label'] = 'testo';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'traduzione' => 'traduzione',
  );
  $handler->display->display_options['path'] = 'migrando_traduzioni';
  $translatables['d8_nodi'] = array(
    t('Master'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('nid'),
    t('uuid'),
    t('titolo'),
    t('uid'),
    t('testo'),
    t('tags'),
    t('immagini'),
    t('created'),
    t('changed'),
    t('stato'),
    t('Articoli'),
    t('Pagine'),
    t('Pagine libro'),
    t('Autori'),
    t('links'),
    t('altri_nomi'),
    t('cognome'),
    t('localizzazione'),
    t('nome'),
    t('sezione'),
    t('Canti'),
    t('accordi'),
    t('anno'),
    t('autori_musica'),
    t('autori_testo'),
    t('capoverso'),
    t('fonte'),
    t('informazioni'),
    t('lingua'),
    t('audio'),
    t('titolo_alternativo'),
    t('Eventi'),
    t('canti_collegati'),
    t('data_evento'),
    t('geolocation'),
    t('localizzazioni'),
    t('percorsi'),
    t('Gruppi'),
    t('email'),
    t('geofield'),
    t('address'),
    t('Traduzioni'),
    t('canto_riferimento'),
  );
  $export['d8_nodi'] = $view;

  $view = new view();
  $view->name = 'd8_termini';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'D8 termini';
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
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_json';
  $handler->display->display_options['style_options']['field_output'] = 'raw';
  $handler->display->display_options['style_options']['plaintext_output'] = 0;
  $handler->display->display_options['style_options']['remove_newlines'] = 0;
  $handler->display->display_options['style_options']['jsonp_prefix'] = '';
  $handler->display->display_options['style_options']['using_views_api_mode'] = 0;
  $handler->display->display_options['style_options']['object_arrays'] = 0;
  $handler->display->display_options['style_options']['numeric_strings'] = 0;
  $handler->display->display_options['style_options']['bigint_string'] = 0;
  $handler->display->display_options['style_options']['pretty_print'] = 0;
  $handler->display->display_options['style_options']['unescaped_slashes'] = 0;
  $handler->display->display_options['style_options']['unescaped_unicode'] = 0;
  $handler->display->display_options['style_options']['char_encoding'] = array();
  /* Campo: Vocabolario della tassonomia: Nome ad uso interno */
  $handler->display->display_options['fields']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['fields']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['fields']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['fields']['machine_name']['label'] = 'voc_name';
  /* Campo: Vocabolario della tassonomia: ID vocabolario */
  $handler->display->display_options['fields']['vid']['id'] = 'vid';
  $handler->display->display_options['fields']['vid']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['fields']['vid']['field'] = 'vid';
  $handler->display->display_options['fields']['vid']['label'] = 'id_voc';
  $handler->display->display_options['fields']['vid']['separator'] = '';
  /* Campo: Termine della tassonomia: ID Termine */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = 'id';
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Campo: Termine della tassonomia: Termine della tassonomia UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: Termine della tassonomia: Nome */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Campo: Campo: Immagini */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = 'immagini';
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'services';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'data_element_key' => '',
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Campo: Termine della tassonomia: Descrizione del termine */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = 'descrizione';
  $handler->display->display_options['fields']['description']['empty'] = 'NULL';
  $handler->display->display_options['fields']['description']['hide_alter_empty'] = FALSE;
  /* Campo: Termine della tassonomia: Periodo */
  $handler->display->display_options['fields']['field_periodo']['id'] = 'field_periodo';
  $handler->display->display_options['fields']['field_periodo']['table'] = 'field_data_field_periodo';
  $handler->display->display_options['fields']['field_periodo']['field'] = 'field_periodo';
  $handler->display->display_options['fields']['field_periodo']['label'] = 'periodo';
  /* Campo: Termine della tassonomia: Peso */
  $handler->display->display_options['fields']['weight']['id'] = 'weight';
  $handler->display->display_options['fields']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['weight']['field'] = 'weight';
  $handler->display->display_options['fields']['weight']['label'] = 'peso';
  $handler->display->display_options['fields']['weight']['separator'] = '';
  /* Criterio di ordinamento: Termine della tassonomia: ID Termine */
  $handler->display->display_options['sorts']['tid']['id'] = 'tid';
  $handler->display->display_options['sorts']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['tid']['field'] = 'tid';
  /* Criterio del filtro: Termine della tassonomia: Vocabolario */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['value'] = array(
    6 => '6',
    4 => '4',
  );

  /* Display: Termini */
  $handler = $view->new_display('services', 'Termini', 'termini');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Criterio del filtro: Termine della tassonomia: Vocabolario */
  $handler->display->display_options['filters']['vid']['id'] = 'vid';
  $handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['filters']['vid']['field'] = 'vid';
  $handler->display->display_options['filters']['vid']['operator'] = 'not in';
  $handler->display->display_options['filters']['vid']['value'] = array(
    7 => '7',
    6 => '6',
    5 => '5',
    4 => '4',
    8 => '8',
  );
  $handler->display->display_options['path'] = 'termini';

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['path'] = 'sezioni_percorsi';
  $translatables['d8_termini'] = array(
    t('Master'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('voc_name'),
    t('id_voc'),
    t('.'),
    t('id'),
    t('uuid'),
    t('immagini'),
    t('descrizione'),
    t('NULL'),
    t('periodo'),
    t('peso'),
    t('Termini'),
    t('Services'),
  );
  $export['d8_termini'] = $view;

  $view = new view();
  $view->name = 'd8_utenti';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'D8 utenti';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'altro';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access comments';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Applica';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Ripristina';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Ordina per';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Disc';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_json';
  $handler->display->display_options['style_options']['root_object'] = 'items';
  $handler->display->display_options['style_options']['top_child_object'] = 'item';
  $handler->display->display_options['style_options']['field_output'] = 'raw';
  $handler->display->display_options['style_options']['plaintext_output'] = 1;
  $handler->display->display_options['style_options']['remove_newlines'] = 0;
  $handler->display->display_options['style_options']['jsonp_prefix'] = '';
  $handler->display->display_options['style_options']['using_views_api_mode'] = 0;
  $handler->display->display_options['style_options']['object_arrays'] = 1;
  $handler->display->display_options['style_options']['numeric_strings'] = 0;
  $handler->display->display_options['style_options']['bigint_string'] = 0;
  $handler->display->display_options['style_options']['pretty_print'] = 0;
  $handler->display->display_options['style_options']['unescaped_slashes'] = 0;
  $handler->display->display_options['style_options']['unescaped_unicode'] = 0;
  $handler->display->display_options['style_options']['char_encoding'] = array();
  /* Campo: Utente: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'uid';
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Campo: Utente: Utente UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'users';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = 'uuid';
  /* Campo: Utente: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['label'] = 'e-mail';
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* Campo: Utente: Nome */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'users';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['label'] = 'name';
  $handler->display->display_options['fields']['name_1']['link_to_user'] = FALSE;
  $handler->display->display_options['fields']['name_1']['format_username'] = FALSE;
  /* Campo: Utente: Attivo */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'stato';
  $handler->display->display_options['fields']['status']['type'] = 'boolean';
  $handler->display->display_options['fields']['status']['type_custom_true'] = 'attivo';
  $handler->display->display_options['fields']['status']['type_custom_false'] = 'bloccato';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Campo: Utente: Data creazione */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Utente: Ultimo accesso */
  $handler->display->display_options['fields']['access']['id'] = 'access';
  $handler->display->display_options['fields']['access']['table'] = 'users';
  $handler->display->display_options['fields']['access']['field'] = 'access';
  $handler->display->display_options['fields']['access']['label'] = 'access';
  $handler->display->display_options['fields']['access']['date_format'] = 'custom';
  $handler->display->display_options['fields']['access']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['access']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Utente: Ultimo login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['label'] = 'login';
  $handler->display->display_options['fields']['login']['date_format'] = 'custom';
  $handler->display->display_options['fields']['login']['custom_date_format'] = 'U';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'privatemsg_current_day';
  /* Campo: Utente: Lingua */
  $handler->display->display_options['fields']['language']['id'] = 'language';
  $handler->display->display_options['fields']['language']['table'] = 'users';
  $handler->display->display_options['fields']['language']['field'] = 'language';
  $handler->display->display_options['fields']['language']['label'] = 'lingua';
  $handler->display->display_options['fields']['language']['link_to_user'] = FALSE;
  /* Criterio di ordinamento: Utente: Data creazione */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Criterio del filtro: Utente: L'ID dell'utente */
  $handler->display->display_options['filters']['uid_raw']['id'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw']['table'] = 'users';
  $handler->display->display_options['filters']['uid_raw']['field'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw']['operator'] = '>';
  $handler->display->display_options['filters']['uid_raw']['value']['value'] = '1';
  /* Criterio del filtro: Utente: L'ID dell'utente */
  $handler->display->display_options['filters']['uid_raw_1']['id'] = 'uid_raw_1';
  $handler->display->display_options['filters']['uid_raw_1']['table'] = 'users';
  $handler->display->display_options['filters']['uid_raw_1']['field'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid_raw_1']['expose']['operator_id'] = 'uid_raw_1_op';
  $handler->display->display_options['filters']['uid_raw_1']['expose']['label'] = 'L\'ID dell\'utente';
  $handler->display->display_options['filters']['uid_raw_1']['expose']['operator'] = 'uid_raw_1_op';
  $handler->display->display_options['filters']['uid_raw_1']['expose']['identifier'] = 'uid_raw_1';
  $handler->display->display_options['filters']['uid_raw_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
  );

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'utenti');
  $handler->display->display_options['path'] = 'utenti';
  $translatables['d8_utenti'] = array(
    t('Master'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('uid'),
    t('uuid'),
    t('e-mail'),
    t('name'),
    t('stato'),
    t('attivo'),
    t('bloccato'),
    t('created'),
    t('access'),
    t('login'),
    t('lingua'),
    t('L\'ID dell\'utente'),
    t('Services'),
  );
  $export['d8_utenti'] = $view;

  return $export;
}
