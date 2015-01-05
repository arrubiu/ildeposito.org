<?php
/**
 * @file
 * ildeposito_gruppi.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function ildeposito_gruppi_taxonomy_default_vocabularies() {
  return array(
    'tipi_gruppi' => array(
      'name' => 'Tipi gruppi',
      'machine_name' => 'tipi_gruppi',
      'description' => '',
      'hierarchy' => 0,
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
