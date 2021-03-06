<?php
/**
 * @file
 * ildeposito_backoffice.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ildeposito_backoffice_default_rules_configuration() {
  $items = array();
  $items['rules_assegnazione_ruolo_default_drupal'] = entity_import('rules_config', '{ "rules_assegnazione_ruolo_default_drupal" : {
      "LABEL" : "Assegnazione ruolo default - Drupal",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "utenti" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_insert" : [] },
      "IF" : [
        { "user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "1" : "1" } }
          }
        }
      ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "5" : "5" } } } }
      ]
    }
  }');
  $items['rules_assegnazione_ruolo_default_social'] = entity_import('rules_config', '{ "rules_assegnazione_ruolo_default_social" : {
      "LABEL" : "Assegnazione ruolo default - Social",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "utenti" ],
      "REQUIRES" : [ "rules", "hybridauth" ],
      "ON" : { "hybridauth_user_insert" : [] },
      "DO" : [
        { "user_add_role" : {
            "account" : [ "hybridauth-user" ],
            "roles" : { "value" : { "5" : "5" } }
          }
        }
      ]
    }
  }');
  $items['rules_benenuto_generico'] = entity_import('rules_config', '{ "rules_benenuto_generico" : {
      "LABEL" : "benenuto generico",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "hybridauth" ],
      "ON" : { "user_login" : [], "hybridauth_user_login" : [] },
      "DO" : [
        { "drupal_message" : { "message" : "Ciao [site:current-user], grazie per essere tornato su ilDeposito.org" } }
      ]
    }
  }');
  $items['rules_contenuto_creato'] = entity_import('rules_config', '{ "rules_contenuto_creato" : {
      "LABEL" : "Contenuto creato - No Staff",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert" : [] },
      "IF" : [
        { "NOT user_has_role" : { "account" : [ "node:author" ], "roles" : { "value" : { "4" : "4" } } } }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Grazie per avere inserito un nuovo contenuto.\\r\\nAppena possibile verificheremo il tuo contributo.",
            "repeat" : 0
          }
        },
        { "mail" : {
            "to" : "donnalombarda25@gmail.com, sergio.durzu@gmail.com",
            "subject" : "[ilDeposito.org] Nuovo contenuto inserito",
            "message" : "Ciao,\\r\\nl\\u0027utente [node:author] ha inserito un nuovo contenuto: \\u0022[node:title]\\u0022.\\r\\n\\r\\nPer visualizzarlo visita il seguente link: [node:url]\\r\\n\\r\\nOppure accedi direttamente alla gestione dell\\u0027archivio:\\r\\nhttp:\\/\\/www.ildeposito.org\\/gestione-archivio\\r\\n\\r\\nLo staff de ilDeposito.org",
            "language" : [ "" ]
          }
        },
        { "mail" : {
            "to" : [ "node:author:mail" ],
            "subject" : "[ilDeposito] Grazie per avere collaborato!",
            "message" : "Ciao [node:author],\\r\\ngrazie per avere inserito il contenuto \\u0022[node:title]\\u0022, appena possibile prenderemo in carico il tuo inserimento.\\r\\nQuando il contenuto verr\\u00e0 pubblicato ti contatteremo con un messaggio privato :)\\r\\n\\r\\nGrazie per la collaborazione,\\r\\nlo Staff de ilDeposito.org",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_registrazione_utente'] = entity_import('rules_config', '{ "rules_registrazione_utente" : {
      "LABEL" : "Registrazione utente",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_insert" : [] },
      "DO" : [
        { "mail" : {
            "to" : "info@ildeposito.org",
            "subject" : "[ilDeposito.org] nuovo  utente: [account:name]",
            "message" : "Ciao,\\r\\nsi appena registrato un nuovo utente: [account:name]",
            "language" : [ "account:language" ]
          }
        }
      ]
    }
  }');
  $items['rules_revisione_creata_no_staff'] = entity_import('rules_config', '{ "rules_revisione_creata_no_staff" : {
      "LABEL" : "Revisione creata - No Staff",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_update" : [] },
      "IF" : [
        { "NOT user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "4" : "4" } }
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : "donnalombarda25@gmail.com, sergio.durzu@gmail.com",
            "subject" : "[ilDeposito.org] Modifica di un contenuto",
            "message" : "Ciao,\\r\\nl\\u0027utente [site:current-user] ha modificato un nuovo contenuto.\\r\\nPer visualizzarlo clicca qui:\\r\\n[node:url]\\r\\n\\r\\nLo Staff de ilDeposito.org",
            "language" : [ "" ]
          }
        },
        { "drupal_message" : {
            "message" : "Grazie per avere modificato un contenuto.\\r\\nAppena possibile verificheremo il tuo contributo.",
            "repeat" : 0
          }
        }
      ]
    }
  }');
  $items['rules_utente_senza_email'] = entity_import('rules_config', '{ "rules_utente_senza_email" : {
      "LABEL" : "Utente senza email",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_login" : [] },
      "IF" : [ { "data_is_empty" : { "data" : [ "account:mail" ] } } ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Al tuo account non \\u00e8 associato nessun indirizzo email. \\u00c8 fondamentale per la ricezione delle notifiche, ti invitiamo a inserirlo dalla pagina \\u003Ca href=\\u0022user\\/[account:uid]\\/edit\\u0022\\u003Edel tuo profilo\\u003C\\/a\\u003E.",
            "type" : "warning",
            "repeat" : 0
          }
        }
      ]
    }
  }');
  return $items;
}
