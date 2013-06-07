<?php
/**
 * @file
 * ildeposito_ct_fonte.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ildeposito_ct_fonte_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_fonte_bibliografica';
  $strongarm->value = 'edit-workflow';
  $export['additional_settings__active_tab_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_fonte_bibliografica';
  $strongarm->value = '0';
  $export['ant_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_pattern_fonte_bibliografica';
  $strongarm->value = '';
  $export['ant_pattern_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_php_fonte_bibliografica';
  $strongarm->value = 0;
  $export['ant_php_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_fonte_bibliografica';
  $strongarm->value = 0;
  $export['comment_anonymous_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_fonte_bibliografica';
  $strongarm->value = 1;
  $export['comment_default_mode_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_fonte_bibliografica';
  $strongarm->value = '50';
  $export['comment_default_per_page_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_fonte_bibliografica';
  $strongarm->value = '1';
  $export['comment_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_fonte_bibliografica';
  $strongarm->value = 1;
  $export['comment_form_location_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_fonte_bibliografica';
  $strongarm->value = '1';
  $export['comment_preview_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_fonte_bibliografica';
  $strongarm->value = 1;
  $export['comment_subject_field_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_fonte_bibliografica';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_fonte_bibliografica';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_fonte_bibliografica';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__fonte_bibliografica';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'ical' => array(
        'custom_settings' => TRUE,
      ),
      'elenco_archivio' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => TRUE,
      ),
      'print' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'elenco_termini_contenuti' => array(
        'custom_settings' => TRUE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '8',
        ),
      ),
      'display' => array(
        'ildeposito_extrafields_icontype' => array(
          'default' => array(
            'weight' => '10',
            'visible' => TRUE,
          ),
          'elenco_archivio' => array(
            'weight' => '10',
            'visible' => TRUE,
          ),
          'search_result' => array(
            'weight' => '10',
            'visible' => TRUE,
          ),
          'elenco_termini_contenuti' => array(
            'weight' => '10',
            'visible' => TRUE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_fonte_bibliografica';
  $strongarm->value = '0';
  $export['language_content_type_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_fonte_bibliografica';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_fonte_bibliografica';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_fonte_bibliografica';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_fonte_bibliografica';
  $strongarm->value = '1';
  $export['node_preview_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_fonte_bibliografica';
  $strongarm->value = 0;
  $export['node_submitted_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_title_type_fonte_bibliografica';
  $strongarm->value = '';
  $export['page_title_type_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'page_title_type_fonte_bibliografica_showfield';
  $strongarm->value = 0;
  $export['page_title_type_fonte_bibliografica_showfield'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_fonte_bibliografica_pattern';
  $strongarm->value = '';
  $export['pathauto_node_fonte_bibliografica_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_html_display_comment_fonte_bibliografica';
  $strongarm->value = 0;
  $export['print_html_display_comment_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_html_display_fonte_bibliografica';
  $strongarm->value = 1;
  $export['print_html_display_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_html_display_urllist_fonte_bibliografica';
  $strongarm->value = 1;
  $export['print_html_display_urllist_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_display_comment_fonte_bibliografica';
  $strongarm->value = 0;
  $export['print_pdf_display_comment_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_display_fonte_bibliografica';
  $strongarm->value = 1;
  $export['print_pdf_display_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_display_urllist_fonte_bibliografica';
  $strongarm->value = 1;
  $export['print_pdf_display_urllist_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_orientation_fonte_bibliografica';
  $strongarm->value = '';
  $export['print_pdf_orientation_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'print_pdf_size_fonte_bibliografica';
  $strongarm->value = '';
  $export['print_pdf_size_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'redirect_setting_name_fonte_bibliografica';
  $strongarm->value = 'rh_node_redirect';
  $export['redirect_setting_name_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rh_module_fonte_bibliografica';
  $strongarm->value = 'rh_node';
  $export['rh_module_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rh_node_action_fonte_bibliografica';
  $strongarm->value = '0';
  $export['rh_node_action_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rh_node_redirect_fonte_bibliografica';
  $strongarm->value = '';
  $export['rh_node_redirect_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rh_node_redirect_response_fonte_bibliografica';
  $strongarm->value = '301';
  $export['rh_node_redirect_response_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'workbench_moderation_default_state_fonte_bibliografica';
  $strongarm->value = 'draft';
  $export['workbench_moderation_default_state_fonte_bibliografica'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_fonte_bibliografica';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_node_fonte_bibliografica'] = $strongarm;

  return $export;
}
