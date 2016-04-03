<?php
/**
 * @file
 * ildeposito_evento.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function ildeposito_evento_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'evento';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'evento' => 'evento',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'node/5990',
  );
  $context->condition_mode = 0;
  $export['evento'] = $context;

  return $export;
}
