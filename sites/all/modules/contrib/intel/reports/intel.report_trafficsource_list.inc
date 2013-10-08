<?php
/**
 * @file
 * Generates traffic source reports
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_trafficsource_list_report_page($sub_index = '-', $filter_type = '', $filter_element = '') {
  $filters = array();
  $reports = intel_reports();
  if ($filter_type) {
    if ($filter_type == 'node') {
      $filter_type = 'page';
      $node = $filter_element;
      //$title_for = t('node') . ' ' . $node->title;
      $filter_element = 'landingPagePath:' . url('node/' . $filter_element->nid);
    }
    elseif ($filter_type == 'visitorid') {
      $filter_type = 'visitor';
      //$title_for = ' ' . t('for visitor %label', array('%label' => $filter_element->getLabel()));
      $filter_element = 'vtk:' . substr($filter_element, 0, 20);
    }
    $filters[$filter_type] = urldecode($filter_element);
    $context = $filter_type;
  }
  
  require_once drupal_get_path('module', 'intel') . "/includes/intel.ga.inc";  
  
  if (empty($_GET['return_type']) || ($_GET['return_type'] == 'nonajax')) {
    intel_add_report_headers();

    $report_modes = explode('.', $report_mode);
    drupal_set_title(t('@title report', array('@title' => $reports['trafficsource'][$sub_index]['title'], '@for' => $title_for)), PASS_THROUGH);
    $filters += $_GET;
    $filter_form = drupal_get_form('intel_report_filters_form', $filters, $context);
    $output .= drupal_render($filter_form);  
  }
  
  if (empty($_GET['return_type'])) {
    $output .= intel_get_report_ajax_container();
  }
  elseif ($_GET['return_type'] == 'nonajax') {
    $output .= intel_trafficsource_list_report($filters, $context, $sub_index);
  }
  elseif ($_GET['return_type'] == 'json') {
    $data = array(
      'report' => intel_trafficsource_list_report($filters, $context, $sub_index),
    );
    drupal_json_output($data);
    return;    
  }  
   
  return $output;  
}

function intel_trafficsource_list_report($filters = array(), $context = 'site', $sub_index = '-') {
  intel_include_library_file('ga/class.ga_model.php');
  
  $reports = intel_reports();
  $report_mode = $reports['trafficsource'][$sub_index]['key'];
  $report_modes = explode('.', $report_mode);
  $indexBy = $report_modes[0];
  $indexByLabel = $reports['trafficsource'][$sub_index]['title'];
//dsm($indexBy);

  $cache_options = array();
  $row_count = 100;
  $feed_rows = 2 * $row_count;
  
  $output = '';    
  
  $timeops = 'l30d';
  //$timeops = 'yesterday';
  list($start_date, $end_date, $number_of_days) = _intel_get_report_dates_from_ops($timeops, $cache_options);

  $ga_data = new LevelTen\Intel\GAModel();
  $ga_data->setReportModes($report_modes);
  $ga_data->buildFilters($filters, $context);
  $ga_data->setDateRange($start_date, $end_date);
  $ga_data->setRequestCallback('intel_ga_feed_request_callback', array('cache_options' => $cache_options));
//$ga_data->setDebug(1);
  $ga_data->setRequestSetting('indexBy', $indexBy);
  $ga_data->setRequestSetting('details', 0);
  
  if ($indexBy == 'trafficcategory') {
    $ga_data->setRequestDefaultParam('max_results', 10 * $feed_rows);
  }
  else {
    $ga_data->setRequestDefaultParam('max_results', 2 * $feed_rows);
  }
  $ga_data->loadFeedData('entrances'); 
  $ga_data->loadFeedData('entrances_valuedevents');  
  
  $d = $ga_data->data;

  foreach ($d[$indexBy] AS $index => $de) {
    $score_components = array();
    $d[$indexBy][$index]['score'] = intel_score_visit_aggregation($de, 1, $score_components);
    $d[$indexBy][$index]['score_components'] = $score_components;  
    $d[$indexBy][$index]['links'] = array();
    $d[$indexBy][$index]['links'][] = l(t('scorecard'), 'admin/reports/intel/scorecard/trafficsource/trafficsource/' . $indexBy . ':' . urlencode($de['i']));
    $d[$indexBy][$index]['links'][] = l(t('content'), 'admin/reports/intel/content/-/trafficsource/' . $indexBy . ':' . urlencode($de['i']));
    $d[$indexBy][$index]['links'][] = l(t('visitors'), 'admin/reports/intel/visitor/-/trafficsource/' . $indexBy . ':' . urlencode($de['i']));
  }    

  // order date data cronologically
  //ksort($d['content']);
  
//dsm($d);
  
  $vars = array(
    'data' => $d,
    'row_count' => $row_count,
    'number_of_days' => $number_of_days,
    'start_date' => $start_date,
    'end_date' => $end_date,
    'goals' => $goals,
    'targets' => intel_get_targets(),
    'analysis_days' => $number_of_days,
    'context' => $context,
    'indexBy' => $indexBy,
    'indexByLabel' => $indexByLabel,
    'report_modes' => $report_modes,
  );
  $output .= theme_intel_trafficsource_list_report($vars);

  $output .= t("Timeframe: %start_date - %end_date %refresh", array(
    '%start_date' => date("Y-m-d H:i", $start_date),
    '%end_date' => date("Y-m-d H:i", $end_date),
    '%refresh' => (!empty($cache_options['refresh'])) ? '(refresh)' : '',
  ));  
  
  return $output;  
}

function theme_intel_trafficsource_list_report($vars) {
  intel_include_library_file("reports/class.trafficsource_report_view.php");
  
  $output = '';

  $report_view = new LevelTen\Intel\TrafficsourceReportView();
  $report_view->setData($vars['data']);
  $report_view->setTableRowCount($vars['row_count']);
  $report_view->setModes($vars['report_modes']);
  $report_view->setParam('indexBy', $vars['indexBy']);
  $report_view->setParam('indexByLabel', $vars['indexByLabel']);
  $report_view->setDateRange($vars['start_date'], $vars['end_date']);
  $report_view->setTargets(intel_get_targets());
  \LevelTen\Intel\ReportPageHeader::setAddScriptCallback('intel_report_add_js_callback');
  $output .= $report_view->renderReport();
  
  return $output; 
}