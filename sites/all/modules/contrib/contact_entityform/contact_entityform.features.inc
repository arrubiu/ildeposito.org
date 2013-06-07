<?php
/**
 * @file
 * contact_entityform.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function contact_entityform_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_entityform_type().
 */
function contact_entityform_default_entityform_type() {
  $items = array();
  $items['personal_contact_form'] = entity_import('entityform_type', '{
    "type" : "personal_contact_form",
    "label" : "Personal Contact Form",
    "data" : {
      "draftable" : 0,
      "draft_button_text" : "werewer",
      "draft_save_text" : { "value" : "", "format" : "filtered_html" },
      "submit_button_text" : "",
      "submission_page_title" : "Contact Request Sent",
      "submission_text" : { "value" : "", "format" : "filtered_html" },
      "submission_show_submitted" : 0,
      "submissions_view" : "entityforms",
      "form_status" : "ENTITYFORM_OPEN",
      "roles" : { "1" : "1", "2" : "2", "5" : 0, "3" : 0, "4" : 0 },
      "resubmit_action" : "new",
      "access_rules" : [],
      "redirect_path" : "",
      "instruction_pre" : { "value" : "", "format" : "filtered_html" },
      "submission_rules" : { "rules_personal_contact_form" : "rules_personal_contact_form" },
      "notification_text" : "",
      "notify_emails" : ""
    },
    "weight" : "0",
    "rdf_mapping" : []
  }');
  $items['site_contact_form'] = entity_import('entityform_type', '{
    "type" : "site_contact_form",
    "label" : "Contact",
    "data" : {
      "draftable" : 0,
      "draft_button_text" : "",
      "draft_save_text" : { "value" : "", "format" : "filtered_html" },
      "submit_button_text" : "Send Message",
      "submission_page_title" : "",
      "submission_text" : {
        "value" : "Thanks you.  Your message has been received.",
        "format" : "filtered_html"
      },
      "submission_show_submitted" : 0,
      "submissions_view" : "entityforms",
      "form_status" : "ENTITYFORM_OPEN",
      "roles" : { "1" : "1", "2" : "2", "3" : 0 },
      "resubmit_action" : "new",
      "access_rules" : [],
      "redirect_path" : "",
      "instruction_pre" : { "value" : "", "format" : "filtered_html" },
      "submission_rules" : { "rules_entitiyform_email_site_admin_" : "rules_entitiyform_email_site_admin_" },
      "notification_text" : "",
      "notify_emails" : ""
    },
    "weight" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}
