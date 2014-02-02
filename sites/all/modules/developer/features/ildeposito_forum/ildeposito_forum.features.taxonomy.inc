<?php
/**
 * @file
 * ildeposito_forum.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ildeposito_forum_taxonomy_default_vocabularies() {
  return array(
    'forums' => array(
      'name' => 'Forum',
      'machine_name' => 'forums',
      'description' => 'Vocabolario per la navigazione del forum',
      'hierarchy' => 0,
      'module' => 'forum',
      'weight' => -10,
    ),
  );
}
