<?php

/**
 * @file
 * Functions to generate the keyword stats report
 */

/**
 * Displays keyword stats report
 *
 * @param str $keyword
 */
function kwresearch_keyword_stats_report_page($keyword = NULL) {
  $output = "";
	
	drupal_add_css(drupal_get_path('module', 'kwresearch') . '/kwresearch.css');
  drupal_add_js(drupal_get_path('module', 'kwresearch') . '/kwresearch.js');

  $analysis = '';
  if (isset($_SESSION['kwresearch']['analysis'])) {
    $analysis = $_SESSION['kwresearch']['analysis'];  
    $_SESSION['kwresearch']['analysis'] = '';
  }

  $stats = TRUE;
  if (!$analysis && $keyword) {
    $analysis = array();
    $analysis['inputs']['keyword'] = $keyword;
    $analysis['analysis'] = kwresearch_get_keyword_stats_data($keyword, $msgs);
    if (!empty($msgs)) {
      $analysis['messages'] = $msgs;
    }
  }
  if ($analysis) {
    // turn on keyword operations

    $analysis['inputs']['operations'] = TRUE;
  }

  $output .= render(drupal_get_form('kwresearch_stats_report_form', $analysis));

  //$output = t('Content Analysis.');
  if ($analysis) {
    $output .= '<div id="kwresearch-popularity-analysis" style="clear: both;">';
    $output .= '<h3>' . t('Analysis') . '</h3>';
    $output .= theme_keyword_stats_report($analysis);
    $output .= '</div>';
    // initialize kw data array for javascript
    if (is_array($analysis['analysis'])) {
      foreach ($analysis['analysis'] as $kw => $v) {
      	if(isset($v['term'])) {
	      	$site_kw[$v['term']] = array(
	          'kid' => (int) $v['kid'],
	          'priority' => (int) $v['priority'],
	          'value' => (int) $v['value'],
	          'page_count' => (int) $v['page_count'],
	        );
      	}
      }
    }
  }
  
  

  $site_priority_options = kwresearch_get_priority_options();
  drupal_add_js(
    array('kwresearch' => array(
      'form' => 'admin_keyword_stats',
      'analyze_path' => base_path() . 'admin/structure/kwresearch/keyword_report/',
      'keyword_edit_path' => base_path() . 'admin/structure/kwresearch/keyword_list/edit/',
      'return_destination' => 'admin/structure/kwresearch/keyword_report/' . $keyword,
      'toggle_site_keyword_callback' => base_path() . 'kwresearch/toggle_site_keyword_js',
      'module_path' => base_path() . drupal_get_path('module', 'kwresearch'),
      'enable_site_keyword_tool' => user_access('kwresearch admin site keywords'),
      'site_keywords_data' => isset($site_kw) ? $site_kw : NULL,
      'site_priority_options' => $site_priority_options,
    )), array('type' => 'setting', 'scope' => JS_DEFAULT));

  return $output;
}

/**
 * Generates main keyword research report
 *
 * @param $form_state
 * @param analysis struc $analysis
 * @param bool $ajax
 */
function kwresearch_stats_report_form($form, $form_state, $analysis, $ajax = FALSE) {

  $form['pre_inputs'] = array(
    '#markup' => '<div id="kwresearch-form-inputs">',
  );

  $form['kwresearch_keyword'] = array(
    '#type' => 'textfield',
    '#title' => t('Keyword'),
    '#default_value' => ($analysis && $analysis['inputs']['keyword']) ? $analysis['inputs']['keyword'] : '',
  );
  
  if (!$ajax) {
	  $form['options'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Options'),
	    '#collapsible' => TRUE,
	    '#collapsed' => TRUE,
	  );
	
	  /*
	   $form_e = kwresearch_stats_report_params_form_elements($analysis);
	   $form['options'] = array_merge($form['options'], $form_e);
	   */
	  
	  $sources = module_invoke_all('kwresearch_sources');
	  if (is_array($sources)) {
	    foreach ($sources as $aid => $source) {
	      if (isset($source['form_options'])) {
	        //$form['options'][$aid . '_stats_report_options'] = array(      
	
	//  '#type' => 'item',      
	
	//  '#title' => $source['title'] . ' ' . t('filters'),      
	
	        // );
	
	
	        $form['options'][$aid . '_stats_report_options'] = array(
	          '#type' => 'fieldset',
	          '#title' => $source['title'] . ' ' . ('filters'),
	          '#collapsible' => FALSE,
	          '#collapsed' => FALSE,
	        );
	
	        $form['options'][$aid . '_stats_report_options'] = array_merge($form['options'][$aid . '_stats_report_options'], call_user_func($source['form_options'], $analysis));
	      }
	    }
	  }
  }

  $form['post_inputs'] = array(
    '#markup' => '</div>',
  );

  if ($ajax) {
    $submit_btn = l(t('Submit'), base_path() . 'kwresearch/analyze_js', array('attributes' => array('id' => 'kwresearch-submit-button', 'class' => "contentanalysis-analyze-content contentanalysis-button", "onclick" => "kwresearch.kwresearch_analyze(); return (false);")));
    $back_btn = l(t('Back'), base_path() . '#', array('attributes' => array('class' => "contentanalysis-analyze-content contentanalysis-button", "onclick" => "contentanalysis.contentanalysis_back(); return (false);")));
    $form['submit'] = array(
      '#type' => 'markup',
      '#markup' => '<div id="kwresearch-form-buttons">' . $submit_btn . ' ' . $back_btn . '</div>',
    );
  }
  else {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Submit',
    );
  }

  return $form;
}

/**
 * returns stats report paramter options form fields array
 * @param analysis struc $analysis
 */
function kwresearch_stats_report_params_form_elements($analysis = NULL) {
  /*
   $defvals = $analysis['inputs'];
   $form['kwresearch_include_misspellings'] = array(
   '#type' => 'checkbox',
   '#title' => t('Include misspellings'),
   '#default_value' => (!is_null($defvals['kwresearch_include_misspellings']))?$defvals['kwresearch_include_misspellings']:variable_get('kwresearch_include_misspellings', FALSE),
   );
   $form['kwresearch_include_plurals'] = array(
   '#type' => 'checkbox',
   '#title' => t('Include plurals'),
   '#default_value' => (!is_null($defvals['kwresearch_include_plurals']))?$defvals['kwresearch_include_plurals']:variable_get('kwresearch_include_plurals', TRUE),
   );
   $form['kwresearch_adult_filter'] = array(
   '#type' => 'select',
   '#title' => t('Adult filter'),
   '#options' => array(
   'off' => t('Off'),
   'remove_dubious' => t('Remove Dubious'),
   'remove_offensive' => t('Remove Offensive'),
   'adult_only' => t('Adult Only'),
   ),
   '#default_value' => ($defvals['kwresearch_adult_filter'])?$defvals['kwresearch_adult_filter']:variable_get('kwresearch_adult_filter', 'remove_dubious'),
   );
   */

  $sources = module_invoke_all('kwresearch_sources');
  $form = array();
  foreach ($sources as $aid => $source) {
    if ($source['form_options']) {
      $form[$aid . '_stats_report_options'] = array(
        '#type' => 'fieldset',
        '#title' => $source['title'] . ' ' . ('filters'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      $form[$aid . '_stats_report_options'] = array_merge($form[$aid . '_stats_report_options'], call_user_func($source['form_options'], $analysis));
    }
  }

  return $form;
}

/**
 * Stats report form submit handler.
 * @param unknown_type $form
 * @param unknown_type $form_state
 */
function kwresearch_stats_report_form_submit($form, &$form_state) {
  //echo "setags_extract_tags_submit($form, &$form_state)";

  $params = $form_state['values'];
  $analysis['inputs']['keyword'] = $form_state['values']['kwresearch_keyword'];

  $analysis['analysis'] = kwresearch_get_keyword_stats_data($form_state['values']['kwresearch_keyword'], $msgs, $params);
  if (!empty($msgs)) {
    $analysis['messages'] = $msgs;
  }
  $_SESSION['kwresearch']['analysis'] = $analysis;

  return;
}

/**
 * Themes keyword stats report
 * @param unknown_type $analysis
 */
function theme_keyword_stats_report($analysis) {
  // TODO: Should this theme keyword_stats_report be declared in hook_theme()?
  //dsm(func_get_args());

  $count = 0;
  if (!$analysis['analysis']) {

    if (!is_array($analysis['inputs']['keyword'])) {
      $kws = explode(',', $analysis['inputs']['keyword']);
    }
    else {
      $kws = is_array($analysis['inputs']['keyword']);
    }
    foreach ($kws as $kw) {
      $analysis['analysis'][$kw] = array(
        'wordtracker_count' => 'NA',
      );
    }
  }
  $meta = $analysis['analysis']['_meta'];
  unset($analysis['analysis']['_meta']);
  $def_values = kwresearch_get_report_data_options_defaults();
  $data_options = variable_get('kwresearch_stats_report_data_options', $def_values);
  $column_th = kwresearch_get_report_data_options('stats', TRUE);

  // remove page priority column if no pid is given

  if (!isset($analysis['inputs']['pid']) || !$analysis['inputs']['pid']) {
    unset($column_th['page_priority']);
    unset($data_options['page_priority']);
  }

  $def_values = kwresearch_get_report_links_options_defaults();
  $links_options = variable_get('kwresearch_stats_report_links_options', $def_values);
  $hdrs[] = t('Keyword');
  if (is_array($data_options)) {
    foreach ($data_options as $k => $v) {
      if ($v) {
        $hdrs[] = $column_th[$k];
      }
    }
  }

  $sources = module_invoke_all('kwresearch_sources');

  $hdrs[] = t('More tools');

  $rows = array();
  if (is_array($analysis['analysis']) && !empty($analysis['analysis'])) {
    foreach ($analysis['analysis'] as $keyword => $values) {
      $row = array();
      $row[] = kwresearch_format_report_data_value(array('term' => $keyword));
      foreach ($data_options as $k => $v) {
        if ($v) {
          $values['_meta'] = $meta;
          if (!$r = kwresearch_format_report_data_value($values, $keyword, $k)) {
            if (is_array($sources)) {
              foreach ($sources as $aid => $source) {
                if ($source['stats_report_values_callback'] && ($r = call_user_func($source['stats_report_values_callback'], $values, $keyword, $k))) {
                  break;
                }
              }
            }
          }
          $row[] = $r;
        }
      }
      $links = '<span class="kwresearch-more-tools">';
      foreach ($links_options as $k => $v) {
        if ($v) {
          $links .= (($links) ? '' : '') . kwresearch_format_report_links_value($values, $keyword, $k);
        }
      }
      $links .= '</span>';

      $row[] = $links;
      if ($analysis['inputs']['operations']) {
        $ops = l(t('stats'), 'admin/structure/kwresearch/keyword_report/' . $keyword);
        //$ops .= ' | ' . l(t('edit'),'admin/structure/kwresearch/keyword_list/edit/' . $values['kid'], array('query' => 'destination=admin/structure/kwresearch/keyword_report/' . $keyword));

        $ops .= ' | ' . l(t('edit'), 'admin/structure/kwresearch/keyword_list/edit/' . $values['kid'], array('attributes' => array('target' => '_blank')));
        //$row[] = $ops; 

      }

      $rows[] = array(
        'data' => $row,
        'id' => 'kid-' . $values['kid'],
      );
    }
  }
  $attr = array(
    'id' => 'kwresearch-result-table-' . check_plain(str_replace(' ', '-', $analysis['inputs']['keyword'])),
    'class' => array('kwresearch-result-table'),
  );
  $output = '<div id="kwresearch-result-block-' . check_plain(str_replace(' ', '-', $analysis['inputs']['keyword'])) . '" class="kwresearch-result-block">';
  $empty = t('No keywords were found.');

  $vars = array(
    'header' => $hdrs,
    'rows' => $rows,
    'attributes' => $attr,
    'empty' => $empty,
  );
  $output .= theme('table', $vars);
  if (!empty($analysis['messages'])) {
    foreach ($analysis['messages'] as $msg) {
      $messages = '<div class="' . $msg['status'] . '">' . $msg['value'] . '</div>';
    }
  }
  if (isset($messages) && $messages) {
    $output .= '<div>' . $footer . '</div>';
  }
  $output .= "</div>";
  
  $a = array(
    'attributes' => array('target' => '_blank'),
  );
  $output .= t('For more keywords try the !google_keyword_tool.', 
    array(
      '!google_keyword_tool' => l(t('Google Keyword Tool'), 'https://adwords.google.com/o/KeywordTool', array('attributes' => array('target' => 'google_keyword_tool'))),
    )
  );
  if (module_exists('kwresearch_google')) {
    $output .= ' ' . l(t('Import Google Keyword Tool data'), 'admin/structure/kwresearch/keyword_list/import_google', array('attributes' => array('target' => 'kwresearch_google_import')));
  }

  return $output;
}

/**
 * enables all values by default
 */
function kwresearch_get_report_data_options_defaults() {
  $options = kwresearch_get_report_data_options();
  $def_values = array();
  $def_values = array(
    'site_priority' => 'site_priority',
    'site_value' => 'site_value',
    'total_dailyest' => 'total_dailyest',
    'competition' => 'competition',
  );

  return $def_values;
}

/**
 * returns data options for reports
 */
function kwresearch_get_report_links_options($th = FALSE) {
  $options = array(
    //'google_serp' => ($th)?t('Google SERP'):t('Google search engine results page'),
    //'yahoo_serp' => ($th)?t('Yahoo! SERP'):t('Yahoo! search engine results page'),
    //'bing_serp' => ($th)?t('Bing SERP'):t('Bing search engine results page'),
    //'google_sb_kw_tool' => ($th) ? t('G kw tool') : t('Google Search-based keyword tool'),
    'google_trends' => ($th) ? t('G trends') : t('Google trends'),
    //'google_traffic_estimator' => ($th)?t('G t est'):t('Google traffic estimator'),    
    'google_insights' => ($th) ? t('G Ins') : t('Google Insights for Search'),
    'gorank_related' => ($th) ? t('GR Rel') : t('goRank Related keywords lookup tool'),
    'keyworddiscovery' => ($th) ? t('KWD') : t('KeywordDiscovery tool'),
  );
  return $options;
}

/**
 * enables all values by default
 */
function kwresearch_get_report_links_options_defaults() {
  $options = kwresearch_get_report_links_options();
  $def_values = array();
  $block = array('google_serp', '');
  foreach ($options as $k => $v) {
  	if (!in_array($k, $block)) {
      $def_values[$k] = $k;
  	}
  }
  return $def_values;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function kwresearch_format_report_links_value($value, $keyword, $type = 'term') {
  $labels = kwresearch_get_report_links_options();
  $icons_path = base_path() . drupal_get_path('module', 'kwresearch') . '/icons/';
  switch ($type) {
    case 'google_trends':
      $img = '<img src="' . $icons_path . 'google_trends.png" alt="' . $labels[$type] . '" />';
      $output = l($img, 'http://www.google.com/trends?ctab=0&date=all&geo=US&q=' . $keyword . '%2C+' . kwresearch_pluralize($keyword), array('attributes' => array('target' => $type, 'title' => $labels[$type]), 'html' => TRUE));
      break;
    case 'google_traffic_estimator':
      $img = '<img src="' . $icons_path . 'google_traffic_estimator.png" alt="' . $labels[$type] . '" />';
      $output = l($img, 'https://adwords.google.com/select/TrafficEstimatorSandbox?currency=USD&language=en&save=save&keywords=' . $keyword . '%0A%22' . $keyword . '%22%0A[test] %0A' . kwresearch_pluralize($keyword) . '%0A%22' . kwresearch_pluralize($keyword) . ' %22%0A[' . kwresearch_pluralize($keyword) . ']', array('attributes' => array('target' => $type, title => $labels[$type]), 'html' => TRUE));
      break;
    case 'google_sb_kw_tool':
      $img = '<img src="' . $icons_path . 'google_search_based_kw_tool.png" alt="' . $labels[$type] . '" />';
      $output = l($img, 'http://www.google.com/sktool/#keywords?spm=true&q=' . $keyword, array('attributes' => array('target' => $type, 'title' => $labels[$type]), 'html' => TRUE));
      break;
    case 'google_insights':
      $img = '<img src="' . $icons_path . 'google_insights_for_search.png" alt="' . $labels[$type] . '" />';
      $output = l($img, 'http://www.google.com/insights/search/#cat&q='  . $keyword . '%2C+' . kwresearch_pluralize($keyword), array('attributes' => array('target' => $type, 'title' => $labels[$type]), 'html' => TRUE));
      break;
    case 'gorank_related':
      $img = '<img src="' . $icons_path . 'gorank_related_kws.png" alt="' . $labels[$type] . '" />';
      $output = l($img, 'http://www.gorank.com/seotools/ontology/index.php?keywords=' . $keyword, array('attributes' => array('target' => $type, 'title' => $labels[$type]), 'html' => TRUE));
      break;
    case 'keyworddiscovery':
      $img = '<img src="' . $icons_path . 'trellian_search_term_suggestion.png" alt="' . $labels[$type] . '" />';
      $output = l($img, 'http://www.keyworddiscovery.com/search.html?query=' . $keyword, array('attributes' => array('target' => $type, 'title' => $labels[$type]), 'html' => TRUE));
      break;

  }
  return $output;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function kwresearch_pluralize($keyword) {
  return $keyword . 's';
}
