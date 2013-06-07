<?php
/**
 * @file
 * contact_entityform.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function contact_entityform_default_rules_configuration() {
  $items = array();
  $items['rules_entitiyform_email_site_admin_'] = entity_import('rules_config', '{ "rules_entitiyform_email_site_admin_" : {
      "LABEL" : "Entitiyform Email Site admin ",
      "PLUGIN" : "rule",
      "TAGS" : [ "entityform submission" ],
      "REQUIRES" : [ "rules", "variable_email" ],
      "USES VARIABLES" : {
        "submitted_entityform" : { "label" : "Submitted Entityform", "type" : "entityform" },
        "entityform_type" : { "label" : "Entityform Type", "type" : "entityform_type" }
      },
      "IF" : [
        { "component_rules_submitted_entityform_notify" : { "submitted_entityform" : [ "submitted-entityform" ] } }
      ],
      "DO" : [
        { "variable_email_mail" : {
            "to" : [ "site:mail" ],
            "variable" : "entityform_notify_admin_[mail_part]",
            "language" : "default"
          }
        }
      ]
    }
  }');
  $items['rules_personal_contact_form'] = entity_import('rules_config', '{ "rules_personal_contact_form" : {
      "LABEL" : "Personal Contact Form",
      "PLUGIN" : "rule",
      "TAGS" : [ "contact entityform", "entityform submission" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "submitted_entityform" : { "label" : "Submitted Entityform", "type" : "entityform" },
        "entityform_type" : { "label" : "Entityform Type", "type" : "entityform_type" }
      },
      "IF" : [
        { "entity_has_field" : {
            "entity" : [ "submitted-entityform" ],
            "field" : "field_contacted_user"
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "submitted-entityform:field-contacted-user:mail" ],
            "subject" : "You have received a contact message from [site:current-user].",
            "message" : "You have received a contact message from [site:current-user].\\r\\n\\r\\nMessage:\\r\\n\\r\\n[submitted-entityform:field-message]",
            "from" : [ "site:current-user:mail" ],
            "language" : [ "entityform-type:type" ]
          }
        },
        { "drupal_message" : { "message" : "Your contact message has been sent." } },
        { "entity_delete" : { "data" : [ "submitted-entityform" ] } },
        { "redirect" : { "url" : "user\\/[submitted-entityform:field-contacted-user:uid]" } }
      ]
    }
  }');
  return $items;
}
