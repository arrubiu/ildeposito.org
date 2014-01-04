<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 * 
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */
function ildeposito_preprocess_page(&$vars) {
	$autore = entity_load('node', array('9138')); 
	$autore = reset($autore);
	aggiorna_autori($autore);
	drupal_add_library('system', 'ui.tabs');
	drupal_add_js(drupal_get_path('theme', 'ildeposito') . '/js/tabs.js', 'file');
	$vars['scripts'] = drupal_get_js();

	if (isset($vars['node']) && $vars['node']->type == 'evento') {
		$data = new DateTime($vars['node']->field_data_evento['und'][0]['value']);
		$data_ut = $data->format('U');
		$title = format_date($data_ut, 'custom', 'j F Y') . ' - ' . $vars['node']->title;
	}

	// pagina utenti
	if ($_GET['q'] == 'user' && $GLOBALS['user']->uid == '0') {
		$title = 'Accedi su ilDeposito.org';
	}

	if ($GLOBALS['user']->uid == '0' && $_GET['q'] == 'user/password') {
		$title = 'Recupera la password';
	}

	if ($GLOBALS['user']->uid == '0' && $_GET['q'] == 'user/register') {
		$title = 'Crea il tuo account su ilDeposito.org';
	}

	$item = menu_get_item();
	//dsm($item);
	// Imposto titolo per le sezioni
	if ($item['page_arguments'][0]->vid == '6') {
		$title = $item['page_arguments'][0]->name;
	}

	if ($title != '') {
		drupal_set_title($title);
	}
}

function ildeposito_preprocess_node(&$vars) {
	$vars['human_type'] = node_type_get_name($vars['node']);

	if ($vars['view_mode'] == 'rss_app' && $vars[$node]->type == 'evento') {
		$data = new DateTime($vars['node']->field_data_evento['und'][0]['value']);
		$data_ut = $data->format('U');
		$vars['title'] = format_date($data_ut, 'custom', 'j F Y') . ' - ' . $vars['node']->title;
	}

	if ($vars['view_mode'] == 'search_result') {
		/* gestione icona tipo contenuto */

		$vars['icon_type'] = '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildeposito') . '/images/type_' . $vars['node']->type . '.png" alt="' . $vars['human_type'] . '" title="' . $vars['human_type'] . '" />';

		/* fine gestione icona */
		$vars['theme_hook_suggestions'][] = 'node__' . $vars['view_mode'];
		if ($vars['node']->type == 'articolo') {
			$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__' . $vars['view_mode'];
		}

		if ($vars['node']->type == 'canto') {
			if (isset($vars['field_accordi']['und']) || isset($vars['field_link_audio']['und']) || isset($vars['field_evento']['und']) || isset($vars['field_traduzione']['und'])) {
				$vars['icons'] = _get_canto_icons($vars);
			}
		}

		if ($vars['node']->type == 'evento') {
			$data = new DateTime($vars['node']->field_data_evento['und'][0]['value']);
			$data_ut = $data->format('U');
			$data_ok = format_date($data_ut, 'custom', 'j F Y');
			$a = 1;
			$vars['title'] = $vars['title'] . ' (' . $data_ok . ')';
//drupal_set_title(format_date($data_ut, 'custom', 'j F Y') . ' - ' . $vars['node']->title);
		}
	}

	if ($vars['node']->type == 'evento' && $vars['view_mode'] == 'riferimento_evento') {
		$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__riferimento_evento';
	}

	if ($vars['node']->type == 'autore' && $vars['view_mode'] == 'full') {

		$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__full';
		drupal_set_title('I canti di ' . $vars['title']);
	}

	if ($vars['node']->type == 'articolo' && $vars['view_mode'] == 'full') {
		$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__full';
	}

	if ($vars['node']->type == 'articolo' && $vars['view_mode'] == 'articolo') {
		$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__articolo';
	}

	if ($vars['node']->type == 'canto' && $vars['view_mode'] == 'print_canzoniere') {

		$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__print_canzoniere';
	}

	// Controlli e operazioni sulla visualizzazione del singolo canto
	if ($vars['node']->type == 'canto' && $vars['view_mode'] == 'full') {

		$vars['foto_autori']  = views_embed_view('contenuti_canti_db', 'foto_autore');

		$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__full';

		$view = views_get_view('check_relazioni');
		$view->set_display('traduzioni');
		$view->set_arguments(array($vars['node']->nid));
		$view->pre_execute();
		$view->execute();
		if (count($view->result) > 0) {
			$vars['traduzioni'] = $view->preview();
		}

		if (isset($vars['field_accordi'][0]) || isset($vars['traduzioni']) || isset($vars['field_link_audio'][0])) {
			$vars['tabs'] = _get_canto_tab($vars);
		} else {
			$vars['tabs'] = '<div id="contenuti-tab"><div id="tabs-testo"><p>' . $vars['node']->field_testo['und'][0]['value'] . '</p></div></div>';
		}

		if ((isset($vars['field_autore_testo'][0]))) {
			$vars['content']['field_autore_testo']['#title'] = 'Autore';
		}
	}

	if ($vars['node']->type == 'evento' && $vars['view_mode'] == 'full') {
		$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__full';
	}

	if ($vars['node']->type == 'traduzione' && $vars['view_mode'] == 'full') {
		$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__full';
	}

	if ($vars['view_mode'] == 'print' && $vars['node']->type == 'canto') {
		$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__print';
		$vars['type'] == 'canto';
	}
}

/**
 * Funzione che crea il tab da visualizzare nel canto
 * @param type $vars
 * @return string
 */
function _get_canto_tab($vars) {

	$list = '<li><a href="#tabs-testo">Testo</a></li>';
	$element = '<div id="tabs-testo"><p>' . $vars['node']->field_testo['und'][0]['value'] . '</p></div>';

	if (isset($vars['field_accordi'][0])) {
		$list .= '<li><a href="#tabs-accordi">Accordi</a></li>';
		$element .= '<div id="tabs-accordi"><p>' . $vars['node']->field_accordi['und'][0]['value'] . '</p></div>';
	}

	if (isset($vars['field_link_audio'][0])) {
		$list .= '<li><a href="#tabs-audio">Audio</a></li>';
		$vars['content']['field_link_audio']['#prefix'] = '<p>ilDeposito.org non fornisce file o audio o registrazioni dei canti presenti ma ci limitiamo a segnalare altri siti dove è possibile ascoltare e/o scaricare i canti.</p><p>Link per ascoltare e/o scaricare il canto:</p>';
		unset($vars['content']['field_link_audio']['#title']);
		$element .= '<div id="tabs-audio">' . render($vars['content']['field_link_audio']) . '</div>';
	}

	if (isset($vars['traduzioni'])) {
		$list .= '<li><a href="#tabs-traduzione">Traduzioni</a></li>';
		$element .= '<div id="tabs-traduzione"><p>Per il presente canto sono disponibili le seguenti traduzioni:</p>' . $vars['traduzioni'] . '</div>';
	}

	$tabs = '<div id="contenuti-tab"><ul>' . $list . '</ul>' . $element . '</div>';

	return $tabs;
}

/**
 * Funzione che crea la icone da visualizzare accanto al titolo
 */
function _get_canto_icons($vars) {
	$icons = '';
	if (isset($vars['field_accordi']['und'])) {
		$icons .= '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildeposito') . '/images/icon_accordi.png" alt="accordi" title="Sono presenti gli accordi" class="icon" />';
	}

	if (isset($vars['field_link_audio']['und'])) {
		$icons .= '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildeposito') . '/images/icon_audio.png" alt="audio" title="Sono presenti risorse audio" class="icon" />';
	}

	if (isset($vars['field_evento']['und'])) {
		$icons .= '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildeposito') . '/images/icon_evento.png" alt="evento" title="Il contenuto è legato a un evento" class="icon" />';
	}

	if (isset($vars['field_traduzione']['und'])) {
		$icons .= '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildeposito') . '/images/icon_trad.png" alt="traduzione" title="Sono presenti traduzioni" class="icon" />';
	}

	return $icons;
}

function ildeposito_breadcrumb($variables) {
	$sep = '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildeposito') . '/images/bread.png" alt="audio" title="Sono presenti risorse audio" class="icon" />';
	if (count($variables['breadcrumb']) > 0) {
		return implode($sep, $variables['breadcrumb']);
	} else {
		return t("Home");
	}
}

// implode(drupal_get_path('theme', 'ildeposito') 
//drupal_get_path('theme', 'ildeposito') . '/images/bread.png'

function ildeposito_facetapi_deactivate_widget($variables) {
	$sep = '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildeposito') . '/images/facet_uncheck.png" alt="-" title="Elimina filtro" class="icon" />';
	return $sep;
}

function ildeposito_preprocess_views_view(&$vars) {
	if ($vars['name'] == 'calendario_eventi' && $vars['display_id'] == 'calendario_mese') {
		setlocale(LC_ALL, 'it_IT.utf8', 'it_IT');
		$mese = strftime('%B', mktime(0, 0, 0, $vars['view']->date_info->month, 10));
		$vars['view']->build_info['title'] = 'Gli eventi per il mese di ' . $mese;
	}

	if ($vars['name'] == 'calendario_eventi' && $vars['display_id'] == 'calendario_giorno') {
		setlocale(LC_TIME, 'it_IT.utf8');
		$mese = strftime('%B', mktime(0, 0, 0, $vars['view']->date_info->month, 10));
		$vars['view']->build_info['title'] = 'Gli eventi per il ' . $vars['view']->date_info->day . ' ' . $mese;
	}

	if ($vars['name'] == 'calendario_eventi' && $vars['display_id'] == 'calendario_settimana') {
		setlocale(LC_ALL, 'it_IT.utf8');
		$mese = strftime('%B', mktime(0, 0, 0, $vars['view']->date_info->month, 10));
		$vars['view']->build_info['title'] = 'Gli eventi per la settimana del ' . $vars['view']->date_info->day . ' ' . $mese;
	}
}

function ildeposito_preprocess_field(&$vars) {
	/* if ($vars['element']['#field_name'] == 'field_sezione') {
	  $vars['theme_hook_suggestions'][] = '"field__field_sezione"';
	  } */

	//$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__full';
	$a = 1;
}

/**
 * Theme a single sort item.
 *
 * @param array $variables
 *   An associative array containing:
 *   - name: The name to display for the item.
 *   - path: The destination path when the sort link is clicked.
 *   - options: An array of options to pass to l().
 *   - active: A boolean telling whether this sort filter is active or not.
 *   - order_options: If active, a set of options to reverse the order
 */
function ildeposito_search_api_sorts_sort(array $variables) {
	$name = $variables['name'];
	$path = $variables['path'];
	$options = $variables['options'] + array('attributes' => array());
	$options['attributes'] += array('class' => array());

	$order_options = $variables['order_options'] + array('query' => array(), 'attributes' => array());
	$order_options['attributes'] += array('class' => array());

	// For the default sort there is no need to add the sort to the query.
	if (isset($options['query']['sort']) && $variables['default_sort'] == $options['query']['sort']) {
		unset($options['query']['sort']);
	}
	if (isset($order_options['query']['sort']) && $variables['default_sort'] == $order_options['query']['sort']) {
		unset($order_options['query']['sort']);
	}

	if ($variables['active']) {
		$return_html = '<span class="search-api-sort-active">';
		//$return_html .= l(t($name), $path, $order_options) . ' ';
		$return_html .= l(theme('tablesort_indicator', array('style' => $order_options['query']['order'])) . $name, $path, $order_options + array('html' => TRUE));
		$return_html .= '</span>';
	} else {
		$return_html = l($name, $path, $options);
	}

	return $return_html;
}

/**
 * Override of theme_tablesort_indicator().
 *
 * Use our own image versions, so they show up as black and not gray on gray.
 */
function ildeposito_tablesort_indicator($variables) {
	$style = $variables['style'];
	$theme_path = drupal_get_path('theme', 'ildeposito');
	if ($style == 'asc') {
		return theme('image', array('path' => $theme_path . '/images/facet_su.png', 'alt' => t('sort ascending'), 'title' => t('sort ascending')));
	} else {
		return theme('image', array('path' => $theme_path . '/images/facet_giu.png', 'alt' => t('sort descending'), 'title' => t('sort descending')));
	}
}

function ildeposito_preprocess_menu_link(&$variables) {
	/* if ($variables['element']['#original_link']['href'] == 'user') {
	  if (realname_load($GLOBALS['user'])) {
	  $variables['element']['#title'] = realname_load($GLOBALS['user']);
	  }
	  else {
	  $variables['element']['#title'] = $GLOBALS['user']->name;
	  }
	  } */
}

function ildeposito_preprocess_region(&$vars) {
	$theme = alpha_get_theme();

	if ($vars['elements']['#region'] == 'content') {
		$vars['messages'] = $theme->page['messages'];
		$vars['breadcrumb'] = $theme->page['breadcrumb'];
	}
}

function ildeposito_preprocess_block(&$vars) {
	if ($vars['block_html_id'] == 'block-system-user-menu') {
		$vars['utente'] = 'Benvenuto ' . $vars['user']->name;
	}
	$a = 1;
}

/**
 * Returns the rendered logo.
 *
 * @ingroup themeable
 */
function ildeposito_delta_blocks_logo($variables) {
	if ($variables['logo']) {
		$image = array(
				'#theme' => 'image',
				'#path' => $variables['logo'],
				'#alt' => $variables['site_name'],
		);

		$image = render($image);

		if ($variables['logo_linked']) {
			$options['html'] = TRUE;
			$options['attributes']['id'] = 'logo';
			$options['attributes']['title'] = t('Return to the @name home page', array('@name' => $variables['site_name']));

			$image = l($image, '<front>', $options);
		}

		return '<div class="logo-img">' . $image . '</div>';
	}
}

function ildeposito_preprocess_html(&$vars) {
	drupal_add_feed('http://feeds2.feedburner.com/ildeposito', $title = 'ilDeposito.org - Feed RSS');
}

function ildeposito_theme($existing, $type, $theme, $path) {
	return array(
			'user_register' => array(
					'render element' => 'form',
					'template' => 'templates/user-register',
			),
	);
}

function ildeposito_preprocess_user_register(&$variables) {
	$block = module_invoke('hybridauth', 'block_view', 'hybridauth');
	$variables['hybridauth'] = render($block['content']);
	$variables['rendered'] = drupal_render_children($variables['form']);
}

function ildeposito_preprocess_user_profile(&$vars) {
	if (isset($vars['elements']['#account']->picture->uri)) {
		$path = $vars['elements']['#account']->picture->uri;
	} else {
		$path = 'public://immagine_profilo_default.png';
	}
	$image = array(
			'style_name' => 'utente_profile',
			'path' => $path,
			'alt' => 'Immagine profilo',
	);
	$vars['image_profile'] = theme('image_style', $image);

	if (realname_load($vars['elements']['#account'])) {
		$vars['nome_utente'] = realname_load($vars['elements']['#account']) . ' (' . $vars['elements']['#account']->name . ')';
	} else {
		$vars['nome_utente'] = $vars['elements']['#account']->name;
	}

	unset($vars['elements']['#account']->roles[2]);
	$vars['ruoli'] = 'Ruoli: ' . implode(', ', $vars['elements']['#account']->roles);
	if (in_array('staff', $vars['elements']['#account']->roles)) {
		$vars['staff'] = 'Amministratore e moderatore de ilDeposito.org';
	}


	$vars['membro_dal'] = render($vars['user_profile']['summary']['member_for']['#markup']);
}
