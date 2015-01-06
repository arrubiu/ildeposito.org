<?php
/**
 * @file
 * ildeposito_gruppi.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ildeposito_gruppi_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'elenco_cori';
  $page->task = 'page';
  $page->admin_title = 'Elenco cori';
  $page->admin_description = '';
  $page->path = 'archivio/gruppi/cori';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_elenco_cori_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'elenco_cori';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Pannello',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'pagina-cori',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'I Cori';
  $display->uuid = 'd13d3946-002e-4104-9aa1-efe3356b24d7';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-3bb28bdc-4b72-411b-a40a-ab07286e792f';
    $pane->panel = 'middle';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => '<p>Da ormai qualche anno abbiamo visto nascere e stiamo vedendo crescere una rete spontanea di cori e gruppi, che si incontrano sempre più spesso all\'interno di svariati eventi e che portano avanti il repertorio di canto politico e sociale. Le caratteristiche delle varie realtà sono tra loro per molti aspetti comuni, ma di sicuro ognuna ha una sua identità ben precisa legata all\'approccio interpretativo, alle scelte di gestione del gruppo, alle tradizioni o ai fenomeni sociali emergenti presenti sul territorio. Abbiamo la fortuna di conoscere personalmente molte di queste realtà e le persone che le animano, e abbiamo spesso verificato la volontà e il desiderio di scambiare e condividere le esperienze, di creare contatti e possibilità di incontro.</p>

<p>È nata quindi l\'idea di creare un archivio consultabile di cori e gruppi da pubblicare nel sito, con delle brevi schede contenti le informazioni necessarie per sapere dove sono, cosa fanno, e come contattarli. Questo per favorire la creazione di contatti tra cori, ma anche per facilitare chi cercasse dalle proprie parti qualche gruppo a cui aggregarsi per cantare.</p>
',
      'format' => 'filtered_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-first grid-9',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '3bb28bdc-4b72-411b-a40a-ab07286e792f';
    $display->content['new-3bb28bdc-4b72-411b-a40a-ab07286e792f'] = $pane;
    $display->panels['middle'][0] = 'new-3bb28bdc-4b72-411b-a40a-ab07286e792f';
    $pane = new stdClass();
    $pane->pid = 'new-3b3f3482-f4af-44b6-9d4d-df4e1c507f23';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'views-elenco_gruppi-block_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Mappa dei cori',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-second grid-9',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '3b3f3482-f4af-44b6-9d4d-df4e1c507f23';
    $display->content['new-3b3f3482-f4af-44b6-9d4d-df4e1c507f23'] = $pane;
    $display->panels['middle'][1] = 'new-3b3f3482-f4af-44b6-9d4d-df4e1c507f23';
    $pane = new stdClass();
    $pane->pid = 'new-58f7f3c9-e170-4279-a11a-29167adfd3af';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'views-elenco_gruppi-elenco_cori';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Elenco alfabetico',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-first grid-18',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '58f7f3c9-e170-4279-a11a-29167adfd3af';
    $display->content['new-58f7f3c9-e170-4279-a11a-29167adfd3af'] = $pane;
    $display->panels['middle'][2] = 'new-58f7f3c9-e170-4279-a11a-29167adfd3af';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-3b3f3482-f4af-44b6-9d4d-df4e1c507f23';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['elenco_cori'] = $page;

  return $pages;

}
