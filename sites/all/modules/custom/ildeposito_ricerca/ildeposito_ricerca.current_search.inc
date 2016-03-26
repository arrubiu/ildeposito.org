<?php
/**
 * @file
 * ildeposito_ricerca.current_search.inc
 */

/**
 * Implements hook_current_search_default_items().
 */
function ildeposito_ricerca_current_search_default_items() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->name = 'current_center';
  $item->label = 'Current center text';
  $item->settings = array(
    'items' => array(
      'results' => array(
        'id' => 'text',
        'label' => 'Results',
        'text' => 'Trovato <strong>1</strong> contenuto',
        'plural' => 1,
        'text_plural' => '[facetapi_results:result-count] risultati trovati, pagina [facetapi_results:page-number] di [facetapi_results:page-total]',
        'plural_condition' => 'facetapi_results:result-count',
        'wrapper' => 0,
        'element' => 'h3',
        'css' => 0,
        'classes' => '',
        'weight' => '-50',
      ),
      'stringa' => array(
        'id' => 'text',
        'label' => 'Stringa',
        'text' => 'Hai cercato <strong>[facetapi_results:keys]</strong>',
        'plural' => 0,
        'text_plural' => '',
        'plural_condition' => 'facetapi_results:result-count',
        'wrapper' => 0,
        'element' => '0',
        'css' => 0,
        'classes' => '',
        'weight' => '-49',
      ),
      'active_items' => array(
        'id' => 'active',
        'label' => 'Active items',
        'pattern' => '[facetapi_active:active-value]',
        'keys' => 0,
        'css' => 0,
        'classes' => '',
        'nofollow' => 1,
        'weight' => '-48',
      ),
    ),
    'advanced' => array(
      'empty_searches' => '0',
    ),
  );
  $export['current_center'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->name = 'current_center_notext';
  $item->label = 'Current center notext';
  $item->settings = array(
    'items' => array(
      'results' => array(
        'id' => 'text',
        'label' => 'Results',
        'text' => 'Trovato <strong>1</strong> contenuto',
        'plural' => 1,
        'text_plural' => 'Risultati trovati: [facetapi_results:result-count], pagina [facetapi_results:page-number] di [facetapi_results:page-total]',
        'plural_condition' => 'facetapi_results:result-count',
        'wrapper' => 0,
        'element' => 'h3',
        'css' => 0,
        'classes' => '',
        'weight' => '-50',
      ),
      'active_items' => array(
        'id' => 'active',
        'label' => 'Active items',
        'pattern' => '[facetapi_active:active-value]',
        'keys' => 0,
        'css' => 0,
        'classes' => '',
        'nofollow' => 1,
        'weight' => '-48',
      ),
    ),
    'advanced' => array(
      'empty_searches' => '1',
    ),
  );
  $export['current_center_notext'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->name = 'current_center_onlyfacet';
  $item->label = 'Current center only facet';
  $item->settings = array(
    'items' => array(
      'active_items' => array(
        'id' => 'active',
        'label' => 'Active items',
        'pattern' => '[facetapi_active:active-value]',
        'keys' => 0,
        'css' => 0,
        'classes' => '',
        'nofollow' => 1,
        'weight' => '-48',
      ),
    ),
    'advanced' => array(
      'empty_searches' => '2',
    ),
  );
  $export['current_center_onlyfacet'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->name = 'current_right';
  $item->label = 'Current Right';
  $item->settings = array(
    'items' => array(
      'results' => array(
        'id' => 'text',
        'label' => 'Results',
        'text' => '1 contenuto trovato',
        'plural' => 1,
        'text_plural' => '[facetapi_results:result-count] risultati trovati, pagina [facetapi_results:page-number] di [facetapi_results:page-total]',
        'plural_condition' => 'facetapi_results:result-count',
        'wrapper' => 0,
        'element' => 'h3',
        'css' => 0,
        'classes' => '',
        'weight' => '-50',
      ),
      'active_items' => array(
        'id' => 'active',
        'label' => 'Active items',
        'pattern' => '[facetapi_active:active-value]',
        'keys' => 0,
        'css' => 0,
        'classes' => '',
        'nofollow' => 1,
        'weight' => '-47',
      ),
    ),
    'advanced' => array(
      'empty_searches' => '0',
    ),
  );
  $export['current_right'] = $item;

  return $export;
}
