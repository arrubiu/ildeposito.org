<?php
/**
 * @file
 * ildeposito_tassonomie.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ildeposito_tassonomie_taxonomy_default_vocabularies() {
  return array(
    'lingue' => array(
      'name' => 'Lingue',
      'machine_name' => 'lingue',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -8,
    ),
    'localizzazione' => array(
      'name' => 'Localizzazione',
      'machine_name' => 'localizzazione',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -7,
    ),
    'percorsi' => array(
      'name' => 'Percorsi',
      'machine_name' => 'percorsi',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -6,
    ),
    'sezioni' => array(
      'name' => 'Sezioni',
      'machine_name' => 'sezioni',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -10,
    ),
    'tags' => array(
      'name' => 'Tags',
      'machine_name' => 'tags',
      'description' => 'Use tags to group articles on similar topics into categories.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -4,
    ),
    'tematiche' => array(
      'name' => 'Tematiche',
      'machine_name' => 'tematiche',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -9,
    ),
  );
}
