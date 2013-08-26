<?php
// $Id: contentanalysis.inc,v 1.1.2.6 2011/01/05 20:42:59 tomdude48 Exp $


/**
 * @file
 * Contains Content Analysis integration functions
 */

/**
 *  Implentation of hook_contentanalysis_analyzers()
 *  register contentanalysisexample with contentanalysis analyzers registry
 */
function kwresearch_contentanalysis_analyzer_info() {
  $analyzers['kwresearch'] = array(
    'title' => t('Keyword research'),
    'module' => 'kwresearch',
    'callback' => 'kwresearch_analyzer',
    'form elements callback' => 'kwresearch_analyzer_form_elements',
  );
  return $analyzers;
}

/**
 * Implements hook_analyzer_form_elements() via custom define callback().
 *
 * hook to add any analyzier specific form elements to the content analyzer form.
 * callback is defined in hook_contentanalysis_analyzers ['form elements callback']
 *
 * @param $form_state
 *   Array defined by form_api
 * @param $analysis
 *   Array analysis formated array defined in conentanalysis
 * @param $node
 *   Node object
 */
function kwresearch_analyzer_form_elements($form_state, $analysis = '', $node = NULL) {
  //dsm($form_state);

  //dsm($node);


  drupal_add_css(drupal_get_path('module', 'kwresearch') . '/kwresearch.css');
  drupal_add_js(drupal_get_path('module', 'kwresearch') . '/kwresearch.js');

  $site_kw = array();
  $sql = '
    SELECT * FROM {kwresearch_keyword}
    WHERE priority > 0
  ';
  $res = db_query($sql);

  while ($r = $res->fetchObject()) {
    $site_kw[$r->keyword] = array(
      'priority' => (int) $r->priority,
      'value' => (int) $r->value,
    );
  }

  $page_kw = array();
  if (isset($node->nid) && $node->nid) {
    $sql = '
      SELECT p.*, k.keyword 
      FROM {kwresearch_page_keyword} p
      JOIN {kwresearch_keyword} k ON k.kid = p.kid
      WHERE nid = :nid
    ';
    $args = array(
      ':nid' => $node->nid
    );
    $res = db_query($sql, $args);
    while ($r = $res->fetchObject()) {
      $page_kw[$r->keyword] = array(
        'priority' => (int) $r->priority,
      );
    }
  }
  $site_priority_options = kwresearch_get_priority_options();
  $page_priority_options = kwresearch_get_priority_options();
  drupal_add_js(
    array('kwresearch' => array(
      'form' => 'node_edit',
      'analyze_callback' => base_path() . 'kwresearch/analyze_js',
      'toggle_site_keyword_callback' => base_path() . 'kwresearch/toggle_site_keyword_js',
      'toggle_page_keyword_callback' => base_path() . 'kwresearch/toggle_page_keyword_js',
      'module_path' => base_path() . drupal_get_path('module', 'kwresearch'),
      'keyword_tag_vocabulary' => variable_get('kwresearch_keyword_tag_vocabulary', ''),
      'keyword_sync_vocabulary' => variable_get('kwresearch_keyword_sync_vocabulary', ''),
      'enable_site_keyword_tool' => user_access('kwresearch admin site keywords'),
      'enable_page_keyword_tool' => user_access('kwresearch admin page keywords'),
      'site_keywords_data' => $site_kw,
      'page_keywords_data' => $page_kw,
      'site_priority_options' => $site_priority_options,
      'page_priority_options' => $page_priority_options,
    )), array('type' => 'setting', 'scope' => JS_DEFAULT));
  //return $form;

}

/**
 * Implements hook_analyzer() via custom define callback().
 */
function kwresearch_analyzer($context, $analysis, $params) {
  require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'kwresearch') . "/includes/stats_report.inc";
  $form = drupal_get_form('kwresearch_stats_report_form', $analysis, TRUE);
  $form = render($form);
  //$form .= drupal_get_form('kwresearch_keyword_stats_report_page');

  $form .= '<div id="kwresearch-report"></div>';

  $analysis['content'][] = contentanalysis_format_content($form, -1);

  return $analysis;
}
