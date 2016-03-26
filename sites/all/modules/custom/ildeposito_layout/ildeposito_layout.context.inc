<?php
/**
 * @file
 * ildeposito_layout.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function ildeposito_layout_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'contatti';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'contatti' => 'contatti',
        'contacts' => 'contacts',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'boxes-box_contatti' => array(
          'module' => 'boxes',
          'delta' => 'box_contatti',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;
  $export['contatti'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'login_page';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'user' => 'user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'hybridauth-hybridauth' => array(
          'module' => 'hybridauth',
          'delta' => 'hybridauth',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;
  $export['login_page'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sitewide';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~<front>' => '~<front>',
      ),
    ),
    'sitewide' => array(
      'values' => array(
        1 => 1,
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
        'user-login' => array(
          'module' => 'user',
          'delta' => 'login',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
        'simplenews-293' => array(
          'module' => 'simplenews',
          'delta' => '293',
          'region' => 'sidebar_second',
          'weight' => '-9',
        ),
        'views-334a0f330c3cb3b95d3ca2bc3a44cf6d' => array(
          'module' => 'views',
          'delta' => '334a0f330c3cb3b95d3ca2bc3a44cf6d',
          'region' => 'sidebar_second',
          'weight' => '-8',
        ),
        'alterator-twitter_timeline_sidebar' => array(
          'module' => 'alterator',
          'delta' => 'twitter_timeline_sidebar',
          'region' => 'sidebar_second',
          'weight' => '-7',
        ),
        'delta_blocks-breadcrumb' => array(
          'module' => 'delta_blocks',
          'delta' => 'breadcrumb',
          'region' => 'header_first',
          'weight' => '-10',
        ),
        'views--exp-ricerca-ricerca_page' => array(
          'module' => 'views',
          'delta' => '-exp-ricerca-ricerca_page',
          'region' => 'header_second',
          'weight' => '-10',
        ),
        'boxes-footer_left' => array(
          'module' => 'boxes',
          'delta' => 'footer_left',
          'region' => 'footer_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;
  $export['sitewide'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'staff';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~<front>' => '~<front>',
      ),
    ),
    'user' => array(
      'values' => array(
        'staff' => 'staff',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-ildeposito-amministrazione' => array(
          'module' => 'menu',
          'delta' => 'menu-ildeposito-amministrazione',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;
  $export['staff'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'storiacantata_main';
  $context->description = 'Pagina principale storia cantata';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'archivio/storiacantata' => 'archivio/storiacantata',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'boxes-storiacantata_icone' => array(
          'module' => 'boxes',
          'delta' => 'storiacantata_icone',
          'region' => 'content',
          'weight' => '52',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Pagina principale storia cantata');
  $export['storiacantata_main'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'utenti_anonimi';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~<front>' => '~<front>',
      ),
    ),
    'user' => array(
      'values' => array(
        'anonymous user' => 'anonymous user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'superfish-3' => array(
          'module' => 'superfish',
          'delta' => '3',
          'region' => 'branding',
          'weight' => '41',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;
  $export['utenti_anonimi'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'utenti_loggati';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~<front>' => '~<front>',
      ),
    ),
    'user' => array(
      'values' => array(
        'authenticated user' => 'authenticated user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'superfish-2' => array(
          'module' => 'superfish',
          'delta' => '2',
          'region' => 'branding',
          'weight' => '10',
        ),
        'system-user-menu' => array(
          'module' => 'system',
          'delta' => 'user-menu',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;
  $export['utenti_loggati'] = $context;

  return $export;
}
