<?php
/**
 * @file
 * ildeposito_gruppi.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ildeposito_gruppi_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'elenco_gruppi';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Elenco gruppi';
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
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'cori';
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
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Campo: Contenuto: Indirizzo - Locality (i.e. City) */
  $handler->display->display_options['fields']['field_indirizzo_locality']['id'] = 'field_indirizzo_locality';
  $handler->display->display_options['fields']['field_indirizzo_locality']['table'] = 'field_data_field_indirizzo';
  $handler->display->display_options['fields']['field_indirizzo_locality']['field'] = 'field_indirizzo_locality';
  $handler->display->display_options['fields']['field_indirizzo_locality']['label'] = '';
  $handler->display->display_options['fields']['field_indirizzo_locality']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_indirizzo_locality']['alter']['text'] = '[title] ([field_indirizzo_locality])';
  $handler->display->display_options['fields']['field_indirizzo_locality']['element_label_colon'] = FALSE;
  /* Criterio di ordinamento: Contenuto: Titolo */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Criterio del filtro: Contenuto: Tipo */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gruppi' => 'gruppi',
  );
  /* Criterio del filtro: Workbench Moderation: Pubblicato */
  $handler->display->display_options['filters']['published']['id'] = 'published';
  $handler->display->display_options['filters']['published']['table'] = 'workbench_moderation_node_history';
  $handler->display->display_options['filters']['published']['field'] = 'published';
  $handler->display->display_options['filters']['published']['value'] = '1';

  /* Display: Overlay mappa cori */
  $handler = $view->new_display('openlayers', 'Overlay mappa cori', 'overlay_mappa_cori');
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
    'name_field' => '',
    'description_field' => 'field_indirizzo_locality',
    'style_field' => '',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
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
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Campo: Contenuto: Indirizzo - Locality (i.e. City) */
  $handler->display->display_options['fields']['field_indirizzo_locality']['id'] = 'field_indirizzo_locality';
  $handler->display->display_options['fields']['field_indirizzo_locality']['table'] = 'field_data_field_indirizzo';
  $handler->display->display_options['fields']['field_indirizzo_locality']['field'] = 'field_indirizzo_locality';
  $handler->display->display_options['fields']['field_indirizzo_locality']['label'] = '';
  $handler->display->display_options['fields']['field_indirizzo_locality']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_indirizzo_locality']['alter']['text'] = '[title] ([field_indirizzo_locality])';
  $handler->display->display_options['fields']['field_indirizzo_locality']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_indirizzo_locality']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['fields']['field_indirizzo_locality']['element_label_colon'] = FALSE;

  /* Display: Mappa */
  $handler = $view->new_display('block', 'Mappa', 'block_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'cori';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  /* Display: Elenco cori */
  $handler = $view->new_display('block', 'Elenco cori', 'elenco_cori');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'elenco-riga';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Campo: Contenuto: Titolo */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Campo: Contenuto: Indirizzo - Locality (i.e. City) */
  $handler->display->display_options['fields']['field_indirizzo_locality']['id'] = 'field_indirizzo_locality';
  $handler->display->display_options['fields']['field_indirizzo_locality']['table'] = 'field_data_field_indirizzo';
  $handler->display->display_options['fields']['field_indirizzo_locality']['field'] = 'field_indirizzo_locality';
  $handler->display->display_options['fields']['field_indirizzo_locality']['label'] = '';
  $handler->display->display_options['fields']['field_indirizzo_locality']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_indirizzo_locality']['alter']['text'] = '[title] ([field_indirizzo_locality])';
  $handler->display->display_options['fields']['field_indirizzo_locality']['element_label_colon'] = FALSE;
  $translatables['elenco_gruppi'] = array(
    t('Master'),
    t('altro'),
    t('Applica'),
    t('Ripristina'),
    t('Ordina per'),
    t('Asc'),
    t('Disc'),
    t('[title] ([field_indirizzo_locality])'),
    t('Overlay mappa cori'),
    t('Mappa'),
    t('Elenco cori'),
  );
  $export['elenco_gruppi'] = $view;

  return $export;
}
