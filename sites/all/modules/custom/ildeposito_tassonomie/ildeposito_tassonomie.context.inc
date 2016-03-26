<?php
/**
 * @file
 * ildeposito_tassonomie.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function ildeposito_tassonomie_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'lingue';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'taxonomy_term' => array(
      'values' => array(
        'lingue' => 'lingue',
      ),
      'options' => array(
        'term_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'archivio/lingue',
  );
  $context->condition_mode = 0;
  $export['lingue'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'localizzazione';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'taxonomy_term' => array(
      'values' => array(
        'localizzazione' => 'localizzazione',
      ),
      'options' => array(
        'term_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'archivio/localizzazioni',
  );
  $context->condition_mode = 0;
  $export['localizzazione'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'percorso';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'taxonomy_term' => array(
      'values' => array(
        'percorsi' => 'percorsi',
      ),
      'options' => array(
        'term_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'archivio/percorsi',
  );
  $context->condition_mode = 0;
  $export['percorso'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sezione';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'taxonomy_term' => array(
      'values' => array(
        'sezioni' => 'sezioni',
      ),
      'options' => array(
        'term_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'archivio/sezioni',
  );
  $context->condition_mode = 0;
  $export['sezione'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'tematica';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'taxonomy_term' => array(
      'values' => array(
        'tematiche' => 'tematiche',
      ),
      'options' => array(
        'term_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'archivio/tematiche',
  );
  $context->condition_mode = 0;
  $export['tematica'] = $context;

  return $export;
}
