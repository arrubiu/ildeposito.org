<?php

/**
 * Funzioni preprocess per la pagina
 */

/**
 * Implements hook_preprocess_page().
 *
 * @see page.tpl.php
 */
function ildepositoboot_preprocess_page(&$vars) {
	$vars['ildeposito_logo'] = ildepositoboot_logo_deposito();
	$vars['ildeposito_social'] = ildepositoboot_page_blocks('boxes', 'social_top');
	$vars['ildeposito_menu'] = ildepositoboot_page_blocks('superfish', '1');
	
  $vars['content_column_class'] = ' class="col-sm-12 col-md-9"';

}

/** 
 * @param type $module
 * @param type $delta
 * @return typeRestituisce blocchi per la gestione della pagina
 */
function ildepositoboot_page_blocks($module, $delta) {	
	$block = module_invoke($module, 'block_view', $delta);
  return render($block['content']);
}

function ildepositoboot_logo_deposito() {

	$logo = theme('image', array(
			'path' => drupal_get_path('theme', 'ildepositoboot') . '/images/logo_nota.png',
			'alt' => 'logo',
			'title' => 'ilDeposito.org',
			'attributes' => array('class' => array('logo', 'hidden-xs', 'pull-left')),
	));

	$titolo = theme('image', array(
			'path' => drupal_get_path('theme', 'ildepositoboot') . '/images/logo_titolo.png',
			'alt' => 'titolo',
			'title' => 'ilDeposito.org',
			'attributes' => array('class' => array('titolo')),
	));

	$sottotitolo = theme('image', array(
			'path' => drupal_get_path('theme', 'ildepositoboot') . '/images/logo_sottotitolo.png',
			'alt' => 'sottotitolo',
			'title' => 'ilDeposito.org',
			'attributes' => array('class' => array('sottotitolo', 'hidden-xs')),
	));


	return l($logo . $titolo . $sottotitolo, '', array('html' => TRUE));
}