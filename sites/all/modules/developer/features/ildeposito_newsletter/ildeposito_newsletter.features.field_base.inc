<?php
/**
 * @file
 * ildeposito_newsletter.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function ildeposito_newsletter_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_ultimi_contenuti'
  $field_bases['field_ultimi_contenuti'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_ultimi_contenuti',
    'foreign keys' => array(),
    'indexes' => array(
      'view_id' => array(
        0 => 'view_id',
      ),
    ),
    'locked' => 0,
    'module' => 'viewreference',
    'settings' => array(
      'append_id' => 0,
      'arguments' => array(
        'delimiter' => '/',
        'dsv_arguments' => 0,
        'label' => '!field_label arguments',
        'php_arguments' => 0,
        'rows' => 1,
      ),
      'referenceable_tags' => array(
        'allow' => '',
        'deny' => '',
      ),
      'referenceable_views' => array(),
      'skip_default' => 1,
      'skip_empty' => 0,
    ),
    'translatable' => 0,
    'type' => 'viewreference',
  );

  return $field_bases;
}
