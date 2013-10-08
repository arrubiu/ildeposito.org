<?php
/**
 * @file
 * Generates visitor reports
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_visitor_list_report_page($sub_index = '-', $filter_type = '', $filter_element = '') {
  if (!intel_api_access()) {
    $output = intel_api_access_error($vars = array());
    return $output;
  }
  $filters = array();
  $context = 'site';
  $reports = intel_reports();
  if ($filter_type) {
    if ($filter_type == 'node') {
      $filter_type = 'page';
      $filter_element = 'landingPagePath:' . url('node/' . $filter_element->nid);
    }
    $filters[$filter_type] = urldecode($filter_element);
    $context = $filter_type;
  } 
  require_once drupal_get_path('module', 'intel') . "/includes/intel.ga.inc";  
  
  if (empty($_GET['return_type']) || ($_GET['return_type'] == 'nonajax')) {
    intel_add_report_headers();

    drupal_set_title(t('@title report', array('@type' => $type_name, '@title' => $reports['visitor'][$sub_index]['title'])), PASS_THROUGH); 
    $filters += $_GET;
    $filter_form = drupal_get_form('intel_report_filters_form', $filters, $context);
    $output .= drupal_render($filter_form);  
  }
  
  if (empty($_GET['return_type'])) {
    $output .= intel_get_report_ajax_container();
  }
  elseif ($_GET['return_type'] == 'nonajax') {
    $output .= intel_visitor_list_report($filters, $context, $sub_index);
  }
  elseif ($_GET['return_type'] == 'json') {
    $data = array(
      'report' => intel_visitor_list_report($filters, $context, $sub_index),
    );
    drupal_json_output($data);
    return;    
  }  
   
  return $output;
}

function intel_visitor_list_report($filters = array(), $context = 'site', $sub_index = '-') {
  intel_include_library_file('ga/class.ga_model.php'); 
  
  $reports = intel_reports();
  $report_mode = $reports['visitor'][$sub_index]['key'];
  $report_modes = explode('.', $report_mode);
  $indexBy = $report_modes[0];
  $indexByLabel = $reports['visitor'][$sub_index]['title'];     
  
  $cache_options = array();
  $row_count = 100;
  $feed_rows = 2 * $row_count;
  
  $output = '';    
  
  if (!empty($filters['page'])) {
    $a = explode(":", $filters['page']);
    $path = $a[1];
  }
  
  $timeops = 'l30d';
  if ($report_modes[1] == 'recent') {
    $timeops = 'l30dfn';
    $cache_options = array('refresh' => 1);
  }
  //$timeops = 'yesterday';
  list($start_date, $end_date, $number_of_days) = _intel_get_report_dates_from_ops($timeops, $cache_options);

  $ga_data = new LevelTen\Intel\GAModel();
  $ga_data->setReportModes($report_modes);
  $ga_data->buildFilters($filters, $context);

  $ga_data->setDateRange($start_date, $end_date);
  $ga_data->setRequestCallback('intel_ga_feed_request_callback', array('cache_options' => $cache_options));
  $ga_data->setRequestSetting('indexBy', $indexBy);
  $ga_data->setRequestSetting('details', 0);

//$ga_data->setDebug(1); 
  $ga_data->setRequestDefaultParam('max_results', 1 * $feed_rows);
  $ga_data->loadFeedData('entrances'); 
  if ($report_modes[1] == 'recent') {
    $ga_data->setRequestDefaultParam('max_results', 5 * $feed_rows);
    $ga_data->loadFeedData('pageviews'); 
  }
  $ga_data->loadFeedData('entrances_valuedevents'); 
  
  $ga_data->setRequestDefaultParam('max_results', 2 * $feed_rows);
  $ga_data->loadFeedData('visit_info');
  
//$ga_data->setDebug(1); 
/* 
  $submission_goals = variable_get('intel_submission_goals', intel_get_submission_goals_default());
  for ($b = 0; isset($submission_goals[$b]) && ($b < 20); $b += 5) {
    $details = array();
    for($i = $b; isset($submission_goals[$i]); $i++) {
      $id = $submission_goals[$i]['ga_id'];
      $details[] = $id;      
      $goals["n$id"] = $submission_goals[$i]['name'];
    }
    $ga_data->loadFeedData('session_goals', 'content', $details, 200);  
  }
  */ 

  $d = $ga_data->data;
  $vtkids = array();
  foreach ($d[$indexBy] AS $index => $de) {
    $score_components = array();
    if ($report_modes[1] == 'recent') {
      $d[$indexBy][$index]['entrance']['pageviews'] = $d[$indexBy][$index]['pageview']['pageviews'];
    }
    $d[$indexBy][$index]['score'] = intel_score_visit_aggregation($d[$indexBy][$index], 1, $score_components);
    $d[$indexBy][$index]['score_components'] = $score_components;  
    if (!empty($de['i'])) {
      if ($report_modes[0] == 'visit') {
        $a = explode('-', $de['i']);
        $vtkid = $a[0];
      }
      else {
        $vtkid = $de['i'];
      }
      $vtkids[] = $vtkid;
    }
    $d[$indexBy][$index]['vtkid'] = $vtkid;
    $d[$indexBy][$index]['links'] = array();
    $d[$indexBy][$index]['links'][] = l(t('scorecard'), 'admin/reports/intel/scorecard/visitor/visitor/vtk:' . urlencode($vtkid));
    $d[$indexBy][$index]['links'][] = l(t('content'), 'admin/reports/intel/content/-/visitor/vtk:' . urlencode($vtkid));
    $d[$indexBy][$index]['links'][] = l(t('sources'), 'admin/reports/intel/trafficsource/-/visitor/vtk:' . urlencode($vtkid));  
  } 

  $visitors = intel_visitors_load_by_vtkids($vtkids);
  foreach ($d[$indexBy] AS $index => $de) {
    if (!empty($visitors[$de['vtkid']]) && !empty($visitors[$de['vtkid']]->name)) {
      $d[$indexBy][$index]['visitor'] = $visitors[$de['vtkid']];    
    }
  }
  
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
    'indexBy' => $indexBy,
    'indexByLabel' => $indexByLabel,
    'report_modes' => $report_modes,    
  );
  $output .= theme_intel_visitor_list_report($vars);

  $output .= t("Timeframe: %start_date - %end_date %refresh", array(
    '%start_date' => date("Y-m-d H:i", $start_date),
    '%end_date' => date("Y-m-d H:i", $end_date),
    '%refresh' => (!empty($cache_options['refresh'])) ? '(refresh)' : '',
  ));  
  
  return $output;  
}

/*
function intel_scorecard_apply_filters_to_request($request, $filterstr, $segmentstr) {
  if ($filterstr) {
    $request['filters'] .= (($request['filters']) ? ';' : '') . $filterstr;
  }
  if ($segmentstr) {
    $request['segment'] .= (($request['segment']) ? ';' : '') . $segmentstr;
  }
  return $request;
}
*/

function theme_intel_visitor_list_report($vars) {
  intel_include_library_file("reports/class.visitor_report_view.php");
  
  $output = '';

  $report_view = new LevelTen\Intel\VisitorReportView();
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