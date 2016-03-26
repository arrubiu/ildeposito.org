<?php
/**
 * @file
 * ildeposito_home.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function ildeposito_home_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'homepage';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'alterator-logo_deposito' => array(
          'module' => 'alterator',
          'delta' => 'logo_deposito',
          'region' => 'user_first',
          'weight' => '-10',
        ),
        'boxes-social_top' => array(
          'module' => 'boxes',
          'delta' => 'social_top',
          'region' => 'user_second',
          'weight' => '-10',
        ),
        'superfish-1' => array(
          'module' => 'superfish',
          'delta' => '1',
          'region' => 'branding',
          'weight' => '-9',
        ),
        'superfish-3' => array(
          'module' => 'superfish',
          'delta' => '3',
          'region' => 'branding',
          'weight' => '10',
        ),
        'boxes-footer_left' => array(
          'module' => 'boxes',
          'delta' => 'footer_left',
          'region' => 'footer_first',
          'weight' => '-10',
        ),
      ),
    ),
    'cache' => array(
      'type' => 'internal',
      'lifetime' => '900',
    ),
  );
  $context->condition_mode = 1;
  $export['homepage'] = $context;

  return $export;
}
