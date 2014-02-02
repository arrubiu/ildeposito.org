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
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
