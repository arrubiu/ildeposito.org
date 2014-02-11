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
	
}