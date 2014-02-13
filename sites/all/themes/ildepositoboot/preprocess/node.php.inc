<?php

/**
 * Funzioni preprocess per i nodi
 */

/**
 * Implements hook_preprocess_node().
 */
function ildepositoboot_preprocess_node(&$vars) {
	$node = $vars['node'];
	$vars['theme_hook_suggestions'][] = 'node__' . $node->type . '__' . $vars['view_mode'];

	switch ($node->type) {
		case 'canto':
			if ($vars['view_mode'] == 'full') {
				$vars['canto_tabs'] = ildepositoboot_canto_tabs($vars);
			}
			break;
	}

	if ($vars['view_mode'] == 'search_result') {
		$vars['icon_type'] = '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildepositoboot') . '/images/type_' . $vars['node']->type . '.png" alt="' . $vars['human_type'] . '" title="' . $vars['human_type'] . '" width="20" height="20" />';

		/* fine gestione icona */
		$vars['theme_hook_suggestions'][] = 'node__' . $vars['view_mode'];
		if ($vars['node']->type == 'articolo') {
			$vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__' . $vars['view_mode'];
		}

		if ($vars['node']->type == 'canto') {
			if (isset($vars['field_accordi']['und']) || isset($vars['field_link_audio']['und']) || isset($vars['field_evento']['und']) || isset($vars['field_traduzione']['und'])) {
				$vars['icons'] = ildepositoboot_get_icons($vars);
			}
		}

		if ($vars['node']->type == 'evento') {
			$data = new DateTime($vars['node']->field_data_evento['und'][0]['value']);
			$data_ut = $data->format('U');
			$data_ok = format_date($data_ut, 'custom', 'j F Y');
			$a = 1;
			$vars['title'] = $vars['title'] . ' (' . $data_ok . ')';
		}
	}
}
