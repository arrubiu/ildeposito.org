<?php
/**
 * @file
 * ildeposito_home.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ildeposito_home_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'homepage';
  $page->task = 'page';
  $page->admin_title = 'Homepage';
  $page->admin_description = '';
  $page->path = 'homepage';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_homepage_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'homepage';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Pannello',
    'no_blocks' => 1,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'omega_24_threecol_8_8_8';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'middle' => NULL,
      'right' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '64fc8486-469e-43cd-84e6-b114151643a3';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-cc7636ac-5a93-413a-aa58-a757bea92521';
    $pane->panel = 'left';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(),
    );
    $pane->configuration = array(
      'admin_title' => 'Special guerra mondiale',
      'title' => 'Cento anni dalla Grande Guerra',
      'body' => '<p><a href="anniversario-prima-guerra-mondiale" title="Speciale Prima Guerra Mondiale"><img alt="Scalarini - La guerra" class="- La attr__field_file_image_alt_text[und][0][value]__Scalarini attr__field_file_image_title_text[und][0][value]__Scalarini attr__field_links[und][0][_weight]__0 attr__field_links[und][0][title]__ attr__field_links[und][0][url]__http://confederazione.usb.it/index.php?id=20&amp;tx_ttnews%5Btt_news%5D=24392&amp;cHash=548e1a2975&amp;MP=63-552 attr__field_links[und][1][_weight]__1 attr__field_links[und][1][title]__ attr__field_links[und][1][url]__ attr__format__default attr__typeof__foaf:Image guerra img__fid__1388 img__view_mode__default media-image" src="http://www.ildeposito.org/sites/default/files/scalarini_cannone_guerra.jpg" style="float:left; height:95px; margin-right:8px; margin-top:4px; width:100px" title="Scalarini - La guerra" /></a>Il 28 giugno 1914 iniziava la prima guerra mondiale, un evento che ha segnato la storia mondiale.</p>

<p><strong><a href="anniversario-prima-guerra-mondiale">Visualizza&nbsp;lo speciale</a></strong></p>
',
      'format' => 'filtered_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'cc7636ac-5a93-413a-aa58-a757bea92521';
    $display->content['new-cc7636ac-5a93-413a-aa58-a757bea92521'] = $pane;
    $display->panels['left'][0] = 'new-cc7636ac-5a93-413a-aa58-a757bea92521';
    $pane = new stdClass();
    $pane->pid = 'new-c4d74336-3e36-49cf-a4d0-3b638130faa8';
    $pane->panel = 'left';
    $pane->type = 'block';
    $pane->subtype = 'views-home_contenuti-block_2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'In evidenza',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-6 col-first',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'c4d74336-3e36-49cf-a4d0-3b638130faa8';
    $display->content['new-c4d74336-3e36-49cf-a4d0-3b638130faa8'] = $pane;
    $display->panels['left'][1] = 'new-c4d74336-3e36-49cf-a4d0-3b638130faa8';
    $pane = new stdClass();
    $pane->pid = 'new-e846569b-8ef3-4c22-8b73-589f58e544f7';
    $pane->panel = 'left';
    $pane->type = 'block';
    $pane->subtype = 'alterator-social_count';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Social network',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'social-count',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'e846569b-8ef3-4c22-8b73-589f58e544f7';
    $display->content['new-e846569b-8ef3-4c22-8b73-589f58e544f7'] = $pane;
    $display->panels['left'][2] = 'new-e846569b-8ef3-4c22-8b73-589f58e544f7';
    $pane = new stdClass();
    $pane->pid = 'new-0e2f7694-eb5c-4fdd-8532-6fee204d5c3f';
    $pane->panel = 'left';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Social',
      'title' => 'Social',
      'body' => '<a class="twitter-follow-button" href="https://twitter.com/ildeposito" data-show-count="true" data-lang="it">Segui @ildeposito</a></p><div class="fb-like-box" data-href="http://www.facebook.com/ildeposito.org" data-width="200" data-height="100" data-show-faces="false" data-stream="false" data-header="true">&nbsp;</div>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'social',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '0e2f7694-eb5c-4fdd-8532-6fee204d5c3f';
    $display->content['new-0e2f7694-eb5c-4fdd-8532-6fee204d5c3f'] = $pane;
    $display->panels['left'][3] = 'new-0e2f7694-eb5c-4fdd-8532-6fee204d5c3f';
    $pane = new stdClass();
    $pane->pid = 'new-ed29ee03-d21b-4281-8f5d-00ad11f5639b';
    $pane->panel = 'left';
    $pane->type = 'block';
    $pane->subtype = 'views-home_contenuti-block_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Ultimi contenuti',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '3600',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'ed29ee03-d21b-4281-8f5d-00ad11f5639b';
    $display->content['new-ed29ee03-d21b-4281-8f5d-00ad11f5639b'] = $pane;
    $display->panels['left'][4] = 'new-ed29ee03-d21b-4281-8f5d-00ad11f5639b';
    $pane = new stdClass();
    $pane->pid = 'new-7cde485c-1f67-44ff-acb9-49d6a3622d76';
    $pane->panel = 'left';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Disclaimer',
      'title' => 'Disclaimer',
      'body' => 'IlDeposito.org è un progetto autogestito e senza scopo di lucro.
Tutti i contenuti sono pubblicati per la loro valenza storica, artistica, culturale o politica (<a href="informazioni">maggiori informazioni</a>).
',
      'format' => 'filtered_html',
      'substitute' => TRUE,
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '604800',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'disclaimer',
    );
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '7cde485c-1f67-44ff-acb9-49d6a3622d76';
    $display->content['new-7cde485c-1f67-44ff-acb9-49d6a3622d76'] = $pane;
    $display->panels['left'][5] = 'new-7cde485c-1f67-44ff-acb9-49d6a3622d76';
    $pane = new stdClass();
    $pane->pid = 'new-ef57e8be-81fc-4b47-9e89-6de54de3f331';
    $pane->panel = 'middle';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Decennale',
      'title' => 'Festa de ilDeposito - 3/4/5 ottobre a Milano',
      'body' => '<h6>Quest\'anno ilDeposito.org compie 10 anni!<br />
Festeggeremo questo evento con una festa a Milano, al circolo La Scighera, il 3/4/5 ottobre.</h6>

<h5><strong><a href="http://www.ildeposito.org/ildeposito-decennale">Visualizza tutte le informazioni</a>!</strong><br />
<strong><a href="https://www.facebook.com/events/1594321064128937/?ref=5">Partecipa all\'evento su Facebook</a>!</strong></h5>
',
      'format' => 'filtered_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ef57e8be-81fc-4b47-9e89-6de54de3f331';
    $display->content['new-ef57e8be-81fc-4b47-9e89-6de54de3f331'] = $pane;
    $display->panels['middle'][0] = 'new-ef57e8be-81fc-4b47-9e89-6de54de3f331';
    $pane = new stdClass();
    $pane->pid = 'new-24068dc5-8e92-49b7-9347-4d86b5e9ee91';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'views-home_contenuti-block_4';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Gli eventi del giorno',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '28800',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '24068dc5-8e92-49b7-9347-4d86b5e9ee91';
    $display->content['new-24068dc5-8e92-49b7-9347-4d86b5e9ee91'] = $pane;
    $display->panels['middle'][1] = 'new-24068dc5-8e92-49b7-9347-4d86b5e9ee91';
    $pane = new stdClass();
    $pane->pid = 'new-9fb1dab0-4ef7-497d-9518-6cca890b3c40';
    $pane->panel = 'middle';
    $pane->type = 'node';
    $pane->subtype = 'node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'nid' => '11495',
      'links' => 0,
      'leave_node_title' => 0,
      'identifier' => '',
      'build_mode' => 'full',
      'link_node_title' => 0,
      'override_title' => 1,
      'override_title_text' => 'Presentazione',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '604800',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ribelle',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '9fb1dab0-4ef7-497d-9518-6cca890b3c40';
    $display->content['new-9fb1dab0-4ef7-497d-9518-6cca890b3c40'] = $pane;
    $display->panels['middle'][2] = 'new-9fb1dab0-4ef7-497d-9518-6cca890b3c40';
    $pane = new stdClass();
    $pane->pid = 'new-848cb06a-aff0-4cdd-bad0-576888d4a10f';
    $pane->panel = 'middle';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Ribelle',
      'title' => 'Presentazione',
      'body' => '[[{"fid":"16","view_mode":"only_image","type":"media","attributes":{"height":112,"width":95,"class":"media-element file-default file-only-image"}}]]<p class="descrizione">I canti di protesta hanno sempre accompagnato la lotta delle classi oppresse e del movimento operaio. Rappresentano un patrimonio politico e culturale di valore fondamentale, da preservare e fare rivivere.<br />Questo e\' lo spirito che anima il Deposito...</p>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'ribelle',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '848cb06a-aff0-4cdd-bad0-576888d4a10f';
    $display->content['new-848cb06a-aff0-4cdd-bad0-576888d4a10f'] = $pane;
    $display->panels['middle'][3] = 'new-848cb06a-aff0-4cdd-bad0-576888d4a10f';
    $pane = new stdClass();
    $pane->pid = 'new-36520cbb-1bc7-4065-8b9d-f35067288f58';
    $pane->panel = 'middle';
    $pane->type = 'node';
    $pane->subtype = 'node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'nid' => '11496',
      'links' => 0,
      'leave_node_title' => 0,
      'identifier' => '',
      'build_mode' => 'full',
      'link_node_title' => 0,
      'override_title' => 1,
      'override_title_text' => 'I contenuti dell\'archivio',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '604800',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-6 col-first elenco-contenuti',
    );
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '36520cbb-1bc7-4065-8b9d-f35067288f58';
    $display->content['new-36520cbb-1bc7-4065-8b9d-f35067288f58'] = $pane;
    $display->panels['middle'][4] = 'new-36520cbb-1bc7-4065-8b9d-f35067288f58';
    $pane = new stdClass();
    $pane->pid = 'new-3ace6fef-a486-4902-9d0f-5d26402cdc63';
    $pane->panel = 'middle';
    $pane->type = 'node';
    $pane->subtype = 'node';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'nid' => '11497',
      'links' => 0,
      'leave_node_title' => 0,
      'identifier' => '',
      'build_mode' => 'full',
      'link_node_title' => 0,
      'override_title' => 1,
      'override_title_text' => 'Le categorie dell\'archivio',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-6 col-second elenco-contenuti',
    );
    $pane->extras = array();
    $pane->position = 5;
    $pane->locks = array();
    $pane->uuid = '3ace6fef-a486-4902-9d0f-5d26402cdc63';
    $display->content['new-3ace6fef-a486-4902-9d0f-5d26402cdc63'] = $pane;
    $display->panels['middle'][5] = 'new-3ace6fef-a486-4902-9d0f-5d26402cdc63';
    $pane = new stdClass();
    $pane->pid = 'new-3e159394-883a-4432-b463-2abee97e49b9';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'views-home_sezioni-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Le sezioni dell\'archivio',
    );
    $pane->cache = array(
      'method' => '0',
      'settings' => array(),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 6;
    $pane->locks = array();
    $pane->uuid = '3e159394-883a-4432-b463-2abee97e49b9';
    $display->content['new-3e159394-883a-4432-b463-2abee97e49b9'] = $pane;
    $display->panels['middle'][6] = 'new-3e159394-883a-4432-b463-2abee97e49b9';
    $pane = new stdClass();
    $pane->pid = 'new-cb24690f-5e84-4cc0-a395-06e549e4b1ee';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'views-home_eventi-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Prossimi eventi',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '14400',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-6 col-first',
    );
    $pane->extras = array();
    $pane->position = 7;
    $pane->locks = array();
    $pane->uuid = 'cb24690f-5e84-4cc0-a395-06e549e4b1ee';
    $display->content['new-cb24690f-5e84-4cc0-a395-06e549e4b1ee'] = $pane;
    $display->panels['middle'][7] = 'new-cb24690f-5e84-4cc0-a395-06e549e4b1ee';
    $pane = new stdClass();
    $pane->pid = 'new-9c848b2e-eed4-468c-a8ae-2883fdff6fd5';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'views-334a0f330c3cb3b95d3ca2bc3a44cf6d';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Calendario cantato',
    );
    $pane->cache = array(
      'method' => '0',
      'settings' => array(),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-6 col-second',
    );
    $pane->extras = array();
    $pane->position = 8;
    $pane->locks = array();
    $pane->uuid = '9c848b2e-eed4-468c-a8ae-2883fdff6fd5';
    $display->content['new-9c848b2e-eed4-468c-a8ae-2883fdff6fd5'] = $pane;
    $display->panels['middle'][8] = 'new-9c848b2e-eed4-468c-a8ae-2883fdff6fd5';
    $pane = new stdClass();
    $pane->pid = 'new-0b8d5347-5866-4664-a7b0-50bfb0939e48';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'views-calendario_eventi-block_2';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Prossimi eventi',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-6 col-second',
    );
    $pane->extras = array();
    $pane->position = 9;
    $pane->locks = array();
    $pane->uuid = '0b8d5347-5866-4664-a7b0-50bfb0939e48';
    $display->content['new-0b8d5347-5866-4664-a7b0-50bfb0939e48'] = $pane;
    $display->panels['middle'][9] = 'new-0b8d5347-5866-4664-a7b0-50bfb0939e48';
    $pane = new stdClass();
    $pane->pid = 'new-59746621-9d7b-473f-b882-316dc1a0c4c7';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'views-home_contenuti-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Articoli del blog',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '28800',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-6 col-first',
    );
    $pane->extras = array();
    $pane->position = 10;
    $pane->locks = array();
    $pane->uuid = '59746621-9d7b-473f-b882-316dc1a0c4c7';
    $display->content['new-59746621-9d7b-473f-b882-316dc1a0c4c7'] = $pane;
    $display->panels['middle'][10] = 'new-59746621-9d7b-473f-b882-316dc1a0c4c7';
    $pane = new stdClass();
    $pane->pid = 'new-40aa1460-38cc-40e0-80e9-95bc599d63f7';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'views-home_commenti-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Commenti recenti',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '28800',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'grid-6 col-second',
    );
    $pane->extras = array();
    $pane->position = 11;
    $pane->locks = array();
    $pane->uuid = '40aa1460-38cc-40e0-80e9-95bc599d63f7';
    $display->content['new-40aa1460-38cc-40e0-80e9-95bc599d63f7'] = $pane;
    $display->panels['middle'][11] = 'new-40aa1460-38cc-40e0-80e9-95bc599d63f7';
    $pane = new stdClass();
    $pane->pid = 'new-db1ac8e2-ba61-4323-86a5-50e12ce71648';
    $pane->panel = 'right';
    $pane->type = 'block';
    $pane->subtype = 'views--exp-ricerca-ricerca_page';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Ricerca',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '604800',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'db1ac8e2-ba61-4323-86a5-50e12ce71648';
    $display->content['new-db1ac8e2-ba61-4323-86a5-50e12ce71648'] = $pane;
    $display->panels['right'][0] = 'new-db1ac8e2-ba61-4323-86a5-50e12ce71648';
    $pane = new stdClass();
    $pane->pid = 'new-7e29d18c-39fe-4537-995d-3c01839c6442';
    $pane->panel = 'right';
    $pane->type = 'block';
    $pane->subtype = 'system-user-menu';
    $pane->shown = TRUE;
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 1,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => TRUE,
        ),
      ),
    );
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Area Utente',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '28800',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '7e29d18c-39fe-4537-995d-3c01839c6442';
    $display->content['new-7e29d18c-39fe-4537-995d-3c01839c6442'] = $pane;
    $display->panels['right'][1] = 'new-7e29d18c-39fe-4537-995d-3c01839c6442';
    $pane = new stdClass();
    $pane->pid = 'new-6cba09ac-5fd9-427d-8897-5c406be816f2';
    $pane->panel = 'right';
    $pane->type = 'block';
    $pane->subtype = 'user-login';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '28800',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '6cba09ac-5fd9-427d-8897-5c406be816f2';
    $display->content['new-6cba09ac-5fd9-427d-8897-5c406be816f2'] = $pane;
    $display->panels['right'][2] = 'new-6cba09ac-5fd9-427d-8897-5c406be816f2';
    $pane = new stdClass();
    $pane->pid = 'new-51925d2e-61c7-42d4-b8d3-b0b80385850d';
    $pane->panel = 'right';
    $pane->type = 'block';
    $pane->subtype = 'simplenews-293';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Newsletter',
    );
    $pane->cache = array(
      'method' => 'simple',
      'settings' => array(
        'lifetime' => '86400',
        'granularity' => 'none',
      ),
    );
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '51925d2e-61c7-42d4-b8d3-b0b80385850d';
    $display->content['new-51925d2e-61c7-42d4-b8d3-b0b80385850d'] = $pane;
    $display->panels['right'][3] = 'new-51925d2e-61c7-42d4-b8d3-b0b80385850d';
    $pane = new stdClass();
    $pane->pid = 'new-1938fb1e-d4e8-4600-9277-2c4b537ece44';
    $pane->panel = 'right';
    $pane->type = 'block';
    $pane->subtype = 'alterator-twitter_timeline';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '1938fb1e-d4e8-4600-9277-2c4b537ece44';
    $display->content['new-1938fb1e-d4e8-4600-9277-2c4b537ece44'] = $pane;
    $display->panels['right'][4] = 'new-1938fb1e-d4e8-4600-9277-2c4b537ece44';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['homepage'] = $page;

  return $pages;

}
