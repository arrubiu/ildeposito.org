<?php
/**
 * @file
 * ildeposito_ct_autore.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function ildeposito_ct_autore_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'autore';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'autore' => 'autore',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'archivio/autori',
  );
  $context->condition_mode = 0;
  $export['autore'] = $context;

  return $export;
}
