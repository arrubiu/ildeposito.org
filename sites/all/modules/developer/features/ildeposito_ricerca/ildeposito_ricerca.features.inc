<?php
/**
 * @file
 * ildeposito_ricerca.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_ricerca_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "current_search" && $api == "current_search") {
    return array("version" => "1");
  }
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "ds_extras" && $api == "ds_extras") {
    return array("version" => "1");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function ildeposito_ricerca_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function ildeposito_ricerca_default_search_api_index() {
  $items = array();
  $items['default_node_index'] = entity_import('search_api_index', '{
    "name" : "Default node index",
    "machine_name" : "default_node_index",
    "description" : "An automatically created search index for indexing node data. Might be configured to specific needs.",
    "server" : "localhost",
    "item_type" : "node",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "100",
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : {
            "default" : "1",
            "bundles" : { "custom_content" : "custom_content", "simplenews" : "simplenews" }
          }
        },
        "search_api_alter_node_access" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_viewed_entity" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "mode" : "search_result" }
        },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "search_api_aggregation_1" : {
                "name" : "Titolo - Ordinamento",
                "type" : "fulltext",
                "fields" : [ "title" ],
                "description" : "A Fulltext aggregation of the following fields: Titolo."
              },
              "search_api_aggregation_2" : {
                "name" : " Capoverso - Ordinamento",
                "type" : "fulltext",
                "fields" : [ "field_capoverso" ],
                "description" : "A Fulltext aggregation of the following fields: Capoverso."
              }
            }
          }
        }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "title" : true,
              "field_altri_nomi" : true,
              "field_cognome" : true,
              "field_nome" : true,
              "field_testo" : true,
              "field_accordi" : true,
              "field_capoverso" : true,
              "field_titolo_alt" : true,
              "field_autore_biblio" : true,
              "field_editore" : true,
              "body:value" : true,
              "body:summary" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_altri_nomi" : true,
              "field_cognome" : true,
              "field_nome" : true,
              "field_testo" : true,
              "field_accordi" : true,
              "field_capoverso" : true,
              "field_titolo_alt" : true,
              "field_autore_biblio" : true,
              "field_editore" : true,
              "body:value" : true,
              "body:summary" : true
            },
            "title" : 1,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_transliteration" : {
          "status" : 1,
          "weight" : "15",
          "settings" : { "fields" : {
              "title" : true,
              "field_altri_nomi" : true,
              "field_cognome" : true,
              "field_nome" : true,
              "field_testo" : true,
              "field_accordi" : true,
              "field_capoverso" : true,
              "field_titolo_alt" : true,
              "field_autore_biblio" : true,
              "field_editore" : true,
              "search_api_viewed" : true,
              "body:value" : true,
              "body:summary" : true,
              "field_tags:name" : true,
              "field_sezione:name" : true,
              "field_sezione:description" : true,
              "field_localizzazione:name" : true,
              "field_localizzazione:description" : true,
              "field_informazioni:value" : true,
              "field_lingua:name" : true,
              "field_lingua:description" : true,
              "field_autore_musica:title" : true,
              "field_autore_testo:title" : true,
              "field_tematica:name" : true,
              "field_tematica:description" : true,
              "field_percorso:name" : true,
              "field_percorso:description" : true,
              "field_geofield:geom" : true
            }
          }
        },
        "search_api_tokenizer" : {
          "status" : 1,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_altri_nomi" : true,
              "field_cognome" : true,
              "field_nome" : true,
              "field_testo" : true,
              "field_accordi" : true,
              "field_capoverso" : true,
              "field_titolo_alt" : true,
              "field_autore_biblio" : true,
              "field_editore" : true,
              "body:value" : true,
              "body:summary" : true
            },
            "spaces" : "[^\\\\p{L}\\\\p{N}]",
            "ignorable" : "[-]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "title" : true,
              "field_altri_nomi" : true,
              "field_cognome" : true,
              "field_nome" : true,
              "field_testo" : true,
              "field_accordi" : true,
              "field_capoverso" : true,
              "field_titolo_alt" : true,
              "field_autore_biblio" : true,
              "field_editore" : true,
              "body:value" : true,
              "body:summary" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 1,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "highlight" : "always"
          }
        }
      },
      "fields" : {
        "nid" : { "type" : "integer" },
        "type" : { "type" : "string" },
        "title" : { "type" : "text", "boost" : "5.0" },
        "url" : { "type" : "uri" },
        "edit_url" : { "type" : "uri" },
        "promote" : { "type" : "boolean" },
        "sticky" : { "type" : "boolean" },
        "created" : { "type" : "date" },
        "changed" : { "type" : "date" },
        "author" : { "type" : "integer", "entity_type" : "user" },
        "book" : { "type" : "integer", "entity_type" : "node" },
        "comment_count" : { "type" : "integer" },
        "field_old_id" : { "type" : "integer" },
        "field_sezione" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_canto_riferimento" : { "type" : "integer", "entity_type" : "node" },
        "field_lingua" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_lingua_originale" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_testo" : { "type" : "text" },
        "field_tags" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_altri_nomi" : { "type" : "list\\u003Ctext\\u003E" },
        "field_cognome" : { "type" : "text" },
        "field_nome" : { "type" : "text" },
        "field_numero_canti" : { "type" : "integer" },
        "field_localizzazione" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_anno" : { "type" : "date" },
        "field_accordi" : { "type" : "text" },
        "field_autore_musica" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_autore_testo" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_capoverso" : { "type" : "text" },
        "field_fonte_biblio" : { "type" : "integer", "entity_type" : "node" },
        "field_presenza_accordi" : { "type" : "string" },
        "field_tematica" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_titolo_alt" : { "type" : "list\\u003Ctext\\u003E" },
        "field_canti_evento" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_percorso" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_evento_ordinamento" : { "type" : "string" },
        "field_collegamenti" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "node" },
        "field_autore_biblio" : { "type" : "list\\u003Ctext\\u003E" },
        "field_cura" : { "type" : "boolean" },
        "field_editore" : { "type" : "text" },
        "field_tipo_fonte" : { "type" : "string" },
        "search_api_language" : { "type" : "string" },
        "search_api_aggregation_1" : { "type" : "string" },
        "search_api_aggregation_2" : { "type" : "string" },
        "search_api_viewed" : { "type" : "text" },
        "search_api_access_node" : { "type" : "list\\u003Cstring\\u003E" },
        "body:value" : { "type" : "text" },
        "body:summary" : { "type" : "text" },
        "field_sezione:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_sezione:description" : { "type" : "list\\u003Ctext\\u003E" },
        "field_informazioni:value" : { "type" : "text" },
        "field_lingua:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_lingua:description" : { "type" : "list\\u003Ctext\\u003E" },
        "field_tags:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_localizzazione:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_localizzazione:description" : { "type" : "list\\u003Ctext\\u003E" },
        "field_autore_musica:title" : { "type" : "list\\u003Ctext\\u003E" },
        "field_autore_testo:title" : { "type" : "list\\u003Ctext\\u003E" },
        "field_tematica:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_tematica:description" : { "type" : "list\\u003Ctext\\u003E" },
        "field_data_evento:value" : { "type" : "list\\u003Cdate\\u003E" },
        "field_percorso:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_percorso:description" : { "type" : "list\\u003Ctext\\u003E" },
        "field_geofield:geom" : { "type" : "text" }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}
