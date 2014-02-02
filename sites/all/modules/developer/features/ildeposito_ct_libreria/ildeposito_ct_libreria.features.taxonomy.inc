<?php
/**
 * @file
 * ildeposito_ct_libreria.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ildeposito_ct_libreria_taxonomy_default_vocabularies() {
  return array(
    'tipo_libreria' => array(
      'name' => 'Tipo libreria',
      'machine_name' => 'tipo_libreria',
      'description' => '',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
