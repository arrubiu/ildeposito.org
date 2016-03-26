<?php
/**
 * @file
 * ildeposito_ct_libreria.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function ildeposito_ct_libreria_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'libreria';
  $feeds_importer->config = array(
    'name' => 'Libreria',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
        'directory' => 'public://feeds',
        'allowed_schemes' => array(
          0 => 'public',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '227',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'Tipo',
            'target' => 'field_tipo_voce',
            'term_search' => '0',
            'autocreate' => 0,
          ),
          1 => array(
            'source' => 'Titolo',
            'target' => 'title',
            'unique' => 1,
          ),
          2 => array(
            'source' => 'Url',
            'target' => 'field_links:url',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Autore',
            'target' => 'field_autore',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'Collana',
            'target' => 'field_collana',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'Editore',
            'target' => 'field_editore',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'Città',
            'target' => 'field_citta',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'Anno',
            'target' => 'field_anno:start',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'ID_Autori',
            'target' => 'field_autori_correlati:nid',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'Tags',
            'target' => 'field_tags',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'Informazioni',
            'target' => 'field_informazioni',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'filtered_html',
        'skip_hash_check' => 0,
        'bundle' => 'voce_libreria',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['libreria'] = $feeds_importer;

  return $export;
}
