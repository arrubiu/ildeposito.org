<?php
/**
 * @file
 * Generates content reports
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_content_list_report_page($report_mode = '-', $filter_type = '', $filter_element = '') {
  $filters = array();
  $context = 'site';
  $reports = intel_reports();
  if ($filter_type) {
    if ($filter_type == 'visitorid') {
      $filter_type = 'visitor';
      $filter_element = 'vtk:' . substr($filter_element, 0, 20);
    }
    $filters[$filter_type] = urldecode($filter_element);
    $context = $filter_type;
  }  
  require_once drupal_get_path('module', 'intel') . "/includes/intel.ga.inc";  
  
  if (empty($_GET['return_type']) || ($_GET['return_type'] == 'nonajax')) {
    intel_add_report_headers();

    $report_modes = explode('.', $report_mode);
    drupal_set_title(t('Content: Top @title report', array('@type' => $type_name, '@title' => $reports['content'][$report_mode]['title'])), PASS_THROUGH);
    $filters += $_GET;
    $filter_form = drupal_get_form('intel_report_filters_form', $filters, $context);
    $output .= drupal_render($filter_form);  
  }
  
  if (empty($_GET['return_type'])) {
    $output .= intel_get_report_ajax_container();
  }
  elseif ($_GET['return_type'] == 'nonajax') {
    $output .= intel_content_list_report($filters, $context, $report_mode);
  }
  elseif ($_GET['return_type'] == 'json') {
    $data = array(
      'report' => intel_content_list_report($filters, $context, $report_mode),
    );
    drupal_json_output($data);
    return;    
  }  
   
  return $output;
  
}

function intel_content_list_report($filters = array(), $context = 'site', $report_mode = '-', $mode = '') {
  intel_include_library_file('ga/class.ga_model.php');
  require_once drupal_get_path('module', 'intel') . "/includes/intel.page_data.inc";
  if ($report_mode == '-') {
    $report_mode = 'default.top.combined';
  }
  $report_modes = explode('.', $report_mode);
  
  $cache_options = array();
  // number of rows in report 
  $row_count = 100;
  // number of rows needed in data feed
  $feed_rows = 2 * $row_count;
  if ($report_modes[0] == 'engagement') {
    $feed_rows *= 4;
  }
  
  $output = '';    
  
  if (!empty($filters['page'])) {
    $a = explode(":", $filters['page']);
    $path = $a[1];
  }
  
  $timeops = 'l30d';
  //$timeops = 'yesterday';
  list($start_date, $end_date, $number_of_days) = _intel_get_report_dates_from_ops($timeops, $cache_options);
  
  $ga_data = new LevelTen\Intel\GAModel();
  $ga_data->setReportModes($report_modes);
  $ga_data->buildFilters($filters, $context);
  $ga_data->setDateRange($start_date, $end_date);
  $ga_data->setRequestCallback('intel_ga_feed_request_callback', array('cache_options' => $cache_options));
//$ga_data->setDebug(1); 
//dsm($context);  
//dsm($ga_data->gaFilters); 
  //$ga_data->setDataIndexCallback('category', '_intel_determine_category_index');  

  $ga_data->setRequestSetting('indexBy', 'content');
  $ga_data->setRequestSetting('details', 0);
    
  // base pageview/entrance data
  if (($report_modes[0] != 'social') && ($report_modes[0] != 'seo')) {
    $ga_data->setRequestDefaultParam('max_results', 2 * $feed_rows);
    $ga_data->loadFeedData('pageviews'); 
  } 

  if (($report_modes[0] != 'social') && ($report_modes[0] != 'seo')) {
    $ga_data->setRequestDefaultParam('max_results', $feed_rows);
    $ga_data->loadFeedData('entrances'); 
  } 
  
  // events data
//$ga_data->setDebug(1);  
  $use_default = 1;
  if (($report_modes[0] == 'engagement') || ($report_modes[0] == 'social')) {
    $ga_data->setRequestSetting('details', 1);
    $ga_data->setRequestDefaultParam('max_results', 5 * $feed_rows);    
    $ga_data->loadFeedData('pageviews_valuedevents');
    $use_default = 0;
  }
  elseif ($report_modes[0] == 'social') {
    $use_default = 0;
  }
  if ($use_default) {
    $ga_data->setRequestSetting('details', 0);
    $ga_data->setRequestDefaultParam('max_results', 2 * $feed_rows);    
    $ga_data->loadFeedData('pageviews_valuedevents');
    
    $ga_data->setRequestDefaultParam('max_results', $feed_rows);
    $ga_data->loadFeedData('entrances_valuedevents');
  }
  
  // referrer data
//$ga_data->setDebug(1); 
  if ($report_modes[0] == 'seo') {
    $ga_data->setRequestSetting('details', 0);
    $ga_data->setRequestDefaultParam('max_results', $feed_rows);  
    $ga_data->setRequestSetting('subIndexBy', 'organicSearch');
    $ga_data->loadFeedData('entrances');
    
    $ga_data->setRequestSetting('details', 1);
    $ga_data->setRequestDefaultParam('max_results', 5 * $feed_rows);  
    $ga_data->setRequestSetting('subIndexBy', 'searchKeyword');
    $ga_data->loadFeedData('entrances');
  }
  elseif ($report_modes[0] == 'social') {
    $ga_data->setRequestSetting('details', 1);
    $ga_data->setRequestDefaultParam('max_results', 10 * $feed_rows);  
    $ga_data->setRequestSetting('subIndexBy', 'socialNetwork');
    $ga_data->loadFeedData('entrances');
  }


  $d = $ga_data->data;
//dsm($data);

  foreach ($d['content'] AS $index => $de) {
    $score_components = array();

    if ($report_modes[0] == 'seo') {
      $d['content'][$index]['score'] = intel_score_visit_aggregation($de, 1, $score_components, 'seo');   
    }
    elseif ($report_modes[0] == 'social') {
      $d['content'][$index]['score'] = intel_score_visit_aggregation($de, 1, $score_components, 'social');   
      $d['content'][$index]['score'] += $d['content'][$index]['pageview']['events']['_all']['value'];  
    }
    elseif ($report_modes[0] == 'engagement') {
      $d['content'][$index]['score'] = $d['content'][$index]['pageview']['events']['_all']['value'];      
    }
    else {
      if ($context == 'page') {
        $d['content'][$index]['score'] = intel_score_page_aggregation($de, 1, $score_components);      
      }
      else { 
        $d['content'][$index]['score'] = intel_score_visit_aggregation($de, 1, $score_components);
      }
    } 
    $d['content'][$index]['score_components'] = $score_components;  
    $u = explode('/', $de['i'], 2);
    $d['content'][$index]['links'] = array();
    $d['content'][$index]['links'][] = l(t('scorecard'), 'admin/reports/intel/scorecard/page/page/landingPagePath:' . urlencode('/' . $u[1])); 
    $d['content'][$index]['links'][] = l(t('sources'), 'admin/reports/intel/trafficsource/-/page/landingPagePath:' . urlencode('/' . $u[1]));
    $d['content'][$index]['links'][] = l(t('visitors'), 'admin/reports/intel/visitor/-/page/landingPagePath:' . urlencode('/' . $u[1]));
  }

  // order date data cronologically
  //ksort($d['content']);
  $vars = array(
    'data' => $d,
    'row_count' => $row_count,
    'number_of_days' => $number_of_days,
    'start_date' => $start_date,
    'end_date' => $end_date,
    'goals' => $goals,
    'targets' => intel_get_targets(),
    'analysis_days' => $analysis_days,
    'context' => $context,
    'report_modes' => $report_modes,
  );
  $output .= theme_intel_content_list_report($vars);

  $output .= t("Timeframe: %start_date - %end_date %refresh", array(
    '%start_date' => date("Y-m-d H:i", $start_date),
    '%end_date' => date("Y-m-d H:i", $end_date),
    '%refresh' => (!empty($cache_options['refresh'])) ? '(refresh)' : '',
  ));  
  
  return $output;  
}

function theme_intel_content_list_report($vars) {
  intel_include_library_file("reports/class.content_report_view.php");
  
  $output = '';

  $report_view = new levelten\intel\ContentReportView();
  $report_view->setData($vars['data']);
  $report_view->setTableRowCount($vars['row_count']);
  $report_view->setModes($vars['report_modes']);
  $report_view->setDateRange($vars['start_date'], $vars['end_date']);
  $report_view->setPageMetaCallback('intel_get_page_meta_callback');
  $report_view->setTargets(intel_get_targets());
  \LevelTen\Intel\ReportPageHeader::setAddScriptCallback('intel_report_add_js_callback');
  $output .= $report_view->renderReport();
  
  return $output; 
}