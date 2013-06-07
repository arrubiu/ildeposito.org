<?php
/**
 * @file
 * ildeposito_backoffice.linkit_profiles.inc
 */

/**
 * Implements hook_default_linkit_profiles().
 */
function ildeposito_backoffice_default_linkit_profiles() {
  $export = array();

  $linkit_profile = new stdClass();
  $linkit_profile->disabled = FALSE; /* Edit this to true to make a default linkit_profile disabled initially */
  $linkit_profile->api_version = 1;
  $linkit_profile->name = 'redazione';
  $linkit_profile->admin_title = 'Redazione';
  $linkit_profile->data = array(
    'plugins' => array(
      'entity:user' => array(
        'weight' => '0',
        'enabled' => 1,
      ),
      'entity:file' => array(
        'weight' => '0',
        'enabled' => 1,
      ),
      'entity:node' => array(
        'weight' => '0',
        'enabled' => 1,
      ),
      'entity:taxonomy_term' => array(
        'weight' => '0',
        'enabled' => 1,
      ),
      'linkit_views' => array(
        'weight' => '0',
        'enabled' => 1,
      ),
    ),
    'entity:node' => array(
      'result_description' => '',
      'bundles' => array(
        'forum' => 'forum',
        'articolo' => 'articolo',
        'autore' => 'autore',
        'canto' => 'canto',
        'evento' => 'evento',
        'fonte_bibliografica' => 'fonte_bibliografica',
        'pagina' => 'pagina',
        'book' => 'book',
        'traduzione' => 'traduzione',
        'custom_content' => 0,
      ),
      'group_by_bundle' => 1,
      'reverse_menu_trail' => 0,
      'include_unpublished' => 0,
    ),
    'entity:file' => array(
      'result_description' => '',
      'bundles' => array(
        'image' => 0,
        'video' => 0,
        'audio' => 0,
        'document' => 0,
      ),
      'group_by_bundle' => 0,
      'reverse_menu_trail' => 0,
      'show_scheme' => 0,
      'group_by_scheme' => 0,
      'image_extra_info' => array(
        'thumbnail' => 'thumbnail',
        'dimensions' => 'dimensions',
      ),
    ),
    'entity:taxonomy_term' => array(
      'result_description' => '',
      'bundles' => array(
        'forums' => 0,
        'tags' => 0,
        'lingue' => 0,
        'localizzazione' => 0,
        'percorsi' => 0,
        'tematiche' => 0,
        'sezioni' => 0,
      ),
      'group_by_bundle' => 1,
      'reverse_menu_trail' => 0,
    ),
    'entity:user' => array(
      'result_description' => '',
      'reverse_menu_trail' => 0,
    ),
    'autocomplete' => array(
      'charLimit' => 3,
      'wait' => 350,
      'remoteTimeout' => 10000,
    ),
    'attributes' => array(
      'rel' => array(
        'weight' => '0',
        'enabled' => 0,
      ),
      'class' => array(
        'weight' => '0',
        'enabled' => 1,
      ),
      'accesskey' => array(
        'weight' => '0',
        'enabled' => 0,
      ),
      'id' => array(
        'weight' => '0',
        'enabled' => 0,
      ),
      'title' => array(
        'weight' => '0',
        'enabled' => 1,
      ),
    ),
  );
  $linkit_profile->role_rids = array(
    2 => 1,
    3 => 1,
  );
  $linkit_profile->weight = 0;
  $export['redazione'] = $linkit_profile;

  return $export;
}
