<?php

/**
 * Funzioni di appoggio al tema
 */

/**
 * Creazione tab per il canto
 */
function ildepositoboot_canto_tabs($vars) {
	$canto = entity_metadata_wrapper('node', $vars['node']);

	$ul = '<ul class="nav nav-pills">';
	$ul .= '<li class="active"><a href="#testo" data-toggle="tab">Testo</a></li>';
	$contents = '<div class="tab-content">';
	$contents .= '<div class="tab-pane active testo-accordi" id="testo">' . $canto->field_testo->value() . '</div>';

	// Verifica accordi
	if ($canto->field_accordi->value()) {
		$ul .= '<li><a href="#accordi" data-toggle="tab">Accordi</a></li>';
		$contents .= '<div class="tab-pane active testo-accordi" id="accordi">' . $canto->field_accordi->value() . '</div>';
	}

	// Verifica file audio
	if ($canto->field_link_audio->value()) {
		$ul .= '<li><a href="#audio" data-toggle="tab">Audio</a></li>';
		$contents .= '<div class="tab-pane active" id="audio">' . render($vars['content']['field_link_audio']) . '</div>';
	}
	
	// Verifica traduzioni
	$traduzioni = ildepositoboot_check_traduzione($vars['node']->nid);
	if ($traduzioni) {
		$ul .= '<li><a href="#traduzioni" data-toggle="tab">Traduzioni</a></li>';
		$contents .= '<div class="tab-pane" id="traduzioni"><ul>';
		foreach ($traduzioni as $traduzione) {
			$titolo = ildepositoboot_get_title($traduzione->nid);
			$contents .= '<li>' . l($titolo, 'node/' . $traduzione->nid);
		}		
		$contents .= '</ul></div>';
	}
	$ul .= '</ul>';
	$contents .= '</div>';

	return $ul . $contents;
}

/**
 * Verifica la presenza di una traduzione in base al nid del canto
 */
function ildepositoboot_check_traduzione($nid) {
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
					->entityCondition('bundle', 'traduzione')
					->fieldCondition('field_canto_riferimento', 'nid', $nid, '=');
	$result = $query->execute();
	if (isset($result['node'])) {
		return $result['node'];
	} 
}

/**
 * Restituisce il titolo di un nodo in  base al nid
 */
function ildepositoboot_get_title($nid) {
  $result = db_query("SELECT title FROM {node} WHERE nid = :nid", array(':nid' => $nid));
  if ($result) {
    foreach ($result as $value) {
      return $value->title;
    }
  }
}

/**
 * Funzione che crea la icone da visualizzare accanto al titolo
 */
function ildepositoboot_get_icons($vars) {
	$icons = '';
	if (isset($vars['field_accordi']['und'])) {
		$icons .= '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildepositoboot') . '/images/icon_accordi.png" alt="accordi" title="Sono presenti gli accordi" class="icon" />';
	}

	if (isset($vars['field_link_audio']['und'])) {
		$icons .= '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildepositoboot') . '/images/icon_audio.png" alt="audio" title="Sono presenti risorse audio" class="icon" />';
	}

	if (isset($vars['field_evento']['und'])) {
		$icons .= '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildepositoboot') . '/images/icon_evento.png" alt="evento" title="Il contenuto è legato a un evento" class="icon" />';
	}

	if (isset($vars['field_traduzione']['und'])) {
		$icons .= '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildepositoboot') . '/images/icon_trad.png" alt="traduzione" title="Sono presenti traduzioni" class="icon" />';
	}

	return $icons;
}