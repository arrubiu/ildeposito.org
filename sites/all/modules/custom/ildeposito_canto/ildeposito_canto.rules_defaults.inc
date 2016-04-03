<?php
/**
 * @file
 * ildeposito_canto.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ildeposito_canto_default_rules_configuration() {
  $items = array();
  $items['rules_canto_riempi_presenza_accordi'] = entity_import('rules_config', '{ "rules_canto_riempi_presenza_accordi" : {
      "LABEL" : "Canto - Riempi presenza accordi",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_presave" : [] },
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "canto" : "canto" } } } },
        { "NOT data_is_empty" : { "data" : [ "node:field-accordi" ] } }
      ],
      "DO" : [
        { "data_set" : { "data" : [ "node:field-presenza-accordi" ], "value" : "si" } }
      ]
    }
  }');
  return $items;
}
