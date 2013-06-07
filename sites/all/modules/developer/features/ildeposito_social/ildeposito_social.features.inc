<?php
/**
 * @file
 * ildeposito_social.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_social_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_flag_default_flags().
 */
function ildeposito_social_flag_default_flags() {
  $flags = array();
  // Exported flag: "Canzoniere".
  $flags['canzoniere'] = array(
    'content_type' => 'node',
    'title' => 'Canzoniere',
    'global' => 0,
    'types' => array(
      0 => 'canto',
    ),
    'flag_short' => 'Aggiungi al canzoniere',
    'flag_long' => 'Aggiunto questo canto al canzoniere',
    'flag_message' => '',
    'unflag_short' => 'Elimina dal canzoniere',
    'unflag_long' => 'Elimina questo canto dal canzoniere',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'ildeposito_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Da rivedere".
  $flags['da_rivedere'] = array(
    'content_type' => 'node',
    'title' => 'Da rivedere',
    'global' => 1,
    'types' => array(
      0 => 'articolo',
      1 => 'autore',
      2 => 'canto',
      3 => 'evento',
      4 => 'pagina',
      5 => 'book',
      6 => 'traduzione',
    ),
    'flag_short' => 'Contenuto da revisionare',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Contenuto revisionato',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 3,
        1 => 4,
      ),
      'unflag' => array(
        0 => 3,
        1 => 4,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'ildeposito_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Flag lists template".
  $flags['fl_template'] = array(
    'content_type' => 'node',
    'title' => 'Flag lists template',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Add to your [flag_lists:title] [flag_lists:term]',
    'flag_long' => 'Add this post to your [flag_lists:title] [flag_lists:term]',
    'flag_message' => 'This post has been added to your [flag_lists:title] [flag_lists:term]',
    'unflag_short' => 'Remove this from your [flag_lists:title] [flag_lists:term]',
    'unflag_long' => 'Remove this post from your [flag_lists:title] [flag_lists:term]',
    'unflag_message' => 'This post has been removed from your [flag_lists:title] [flag_lists:term]',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_contextual_link' => FALSE,
    'i18n' => 0,
    'module' => 'ildeposito_social',
    'api_version' => 2,
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Segnalibri".
  $flags['segnalibri'] = array(
    'content_type' => 'node',
    'title' => 'Segnalibri',
    'global' => 0,
    'types' => array(
      0 => 'articolo',
      1 => 'autore',
      2 => 'canto',
      3 => 'evento',
      4 => 'fonte_bibliografica',
      5 => 'pagina',
      6 => 'book',
      7 => 'traduzione',
    ),
    'flag_short' => 'Aggiungi ai segnalibri',
    'flag_long' => 'Aggiungi questo contenuto ai segnalibri',
    'flag_message' => '',
    'unflag_short' => 'Elimina dai segnalibri',
    'unflag_long' => 'Elimina questo contenuto dai segnalibri',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'ildeposito_social',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
