<?php
/**
 * @file
 * ildeposito_ct_fonte.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_ct_fonte_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function ildeposito_ct_fonte_node_info() {
  $items = array(
    'fonte_bibliografica' => array(
      'name' => t('Fonte bibliografica'),
      'base' => 'node_content',
      'description' => t('Il contenuto per indicare la fonte bibliografica di canti e traduzioni'),
      'has_title' => '1',
      'title_label' => t('Titolo'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_rdf_default_mappings().
 */
function ildeposito_ct_fonte_rdf_default_mappings() {
  $schemaorg = array();

  // Exported RDF mapping: comment_node_fonte_bibliografica
  $schemaorg['comment']['comment_node_fonte_bibliografica'] = array(
    'rdftype' => array(
      0 => 'sioc:Post',
      1 => 'sioct:Comment',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'dc:title',
      ),
    ),
    'created' => array(
      'predicates' => array(
        0 => 'dc:date',
        1 => 'dc:created',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'changed' => array(
      'predicates' => array(
        0 => 'dc:modified',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'comment_body' => array(
      'predicates' => array(
        0 => 'content:encoded',
      ),
    ),
    'pid' => array(
      'predicates' => array(
        0 => 'sioc:reply_of',
      ),
      'type' => 'rel',
    ),
    'uid' => array(
      'predicates' => array(
        0 => 'sioc:has_creator',
      ),
      'type' => 'rel',
    ),
    'name' => array(
      'predicates' => array(
        0 => 'foaf:name',
      ),
    ),
  );

  // Exported RDF mapping: fonte_bibliografica
  $schemaorg['node']['fonte_bibliografica'] = array(
    'rdftype' => array(
      0 => 'sioc:Item',
      1 => 'foaf:Document',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'dc:title',
      ),
    ),
    'created' => array(
      'predicates' => array(
        0 => 'dc:date',
        1 => 'dc:created',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'changed' => array(
      'predicates' => array(
        0 => 'dc:modified',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'body' => array(
      'predicates' => array(
        0 => 'content:encoded',
      ),
    ),
    'uid' => array(
      'predicates' => array(
        0 => 'sioc:has_creator',
      ),
      'type' => 'rel',
    ),
    'name' => array(
      'predicates' => array(
        0 => 'foaf:name',
      ),
    ),
    'comment_count' => array(
      'predicates' => array(
        0 => 'sioc:num_replies',
      ),
      'datatype' => 'xsd:integer',
    ),
    'last_activity' => array(
      'predicates' => array(
        0 => 'sioc:last_activity_date',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
  );

  return $schemaorg;
}
