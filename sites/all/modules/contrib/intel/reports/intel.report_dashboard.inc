<?php
/**
 * @file
 * Generates dashboard report
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_dashboard_report_page($sub_index = '-', $filter_type = '', $filter_element = '') {
  $filters = array();
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

    $report_modes = explode('.', $report_mode);
    drupal_set_title(t('Dashboard'), PASS_THROUGH);  
  }
  
  if (empty($_GET['return_type'])) {
    $output .= intel_get_report_ajax_container();
  }
  elseif ($_GET['return_type'] == 'nonajax') {
    $output .= intel_dashboard_report($filters, $context, $sub_index);
  }
  elseif ($_GET['return_type'] == 'json') {
    $data = array(
      'report' => intel_dashboard_report($filters, $context, $sub_index),
    );
    drupal_json_output($data);
    return;    
  }  
   
  return $output;
  
  
  
}

function intel_dashboard_report($filters = array(), $context = 'site', $sub_index = '-') {
  intel_include_library_file('ga/class.ga_model.php');
  
  if ($context == '-') {
    $context = 'site';
  }
  if ($sub_index == '-') {
    $sub_index = '.default';
  }
  $report_modes = explode('.', $sub_index);

  $cache_options = array();
  
  $output = '';    
  $filters += $_GET;
  
  if (!empty($filters['page'])) {
    $a = explode(":", $filters['page']);
    $path = $a[1];
  }
  
  $a = explode('-', $report_modes[0]);
  $cur_month = 1;
  if ((count($a) == 2) ) {
    $target_yr = $a[0];
    $target_mo = $a[1];
    $cur_month = 0;
  }
  else {
    $target_yr = (int)date('Y');
    if (!empty($a[0])) {
      $target_mo = $a[0];
    }
    else {
      $target_mo = (int)date('m');
    }
  }

  $last_mo = $target_mo-1;
  $last_yr = $target_yr;
  if ($last_mo == 0) {
    $last_mo = 12;
    $last_yr--;
  }
  $next_mo = $target_mo+1;
  $next_yr = $target_yr;
  if ($next_mo == 13) {
    $next_mo = 1;
    $next_yr++;
  }
  list($lastmonth_start_date, $lastmonth_end_date, $lastmonth_number_of_days) = _intel_get_report_dates("$last_mo/1/$last_yr", "$target_mo/1/$target_yr - 1 second");

  list($start_date, $end_datemo, $number_of_days) = _intel_get_report_dates("$target_mo/1/$target_yr", "$next_mo/1/$next_yr - 1 second");
  // round end date to next hour to cache per hour
  if (!$cur_month) {
    $end_date = $end_datemo;
  }
  else {
    $end_date = (int)(3600 * round((time() + 1800) / 3600));
  }

  if (!empty($_GET['refresh'])) {
    $cache_options = array('refresh' => 1);
  }
  else {
    $cache_options = array('expire' => $end_date);
  }
  
  // get last month's data  
  $last_month_data = new LevelTen\Intel\GAModel();
  $last_month_data->buildFilters($filters, $context);
  $last_month_data->setDateRange($lastmonth_start_date, $lastmonth_end_date);
  $last_month_data->setRequestCallback('intel_ga_feed_request_callback', array('cache_options' => $cache_options));
  
  $last_month_data->setRequestSetting('indexBy', '');
  $last_month_data->setRequestSetting('details', 0);
  $last_month_data->setRequestDefaultParam('max_results', 31); 


  $last_month_data->loadFeedData('entrances'); 

  $last_month_data->setRequestSetting('details', 1);
  $last_month_data->setRequestDefaultParam('max_results', 10); 
  $last_month_data->loadFeedData('entrances_valuedevents'); 

  
  // get this month's data
  $ga_data = new LevelTen\Intel\GAModel();
  $ga_data->buildFilters($filters, $context);
  $ga_data->setDateRange($start_date, $end_date);
  $ga_data->setRequestCallback('intel_ga_feed_request_callback', array('cache_options' => $cache_options));

  $ga_data->setRequestSetting('indexBy', 'date');
  $ga_data->setRequestSetting('details', 0);
  $ga_data->setRequestDefaultParam('max_results', 31); 
//$last_month_data->setDebug(1);
  $ga_data->loadFeedData('entrances'); 
//$last_month_data->setDebug(0);  
  $ga_data->setRequestSetting('details', 1);
  $ga_data->setRequestDefaultParam('max_results', 10 * 31); 
  $ga_data->loadFeedData('entrances_valuedevents');
  
  $ga_data->setRequestDefaultParam('max_results', 5 * 31);
  $submission_goals = variable_get('intel_submission_goals', intel_get_submission_goals_default());
  for ($b = 0; isset($submission_goals[$b]) && ($b < 20); $b += 5) {
    $details = array();
    for ($i = $b; isset($submission_goals[$i]); $i++) {
      $id = $submission_goals[$i]['ga_id'];
      $details[] = $id;      
      $goals["n$id"] = $submission_goals[$i]['name'];
    }
    $ga_data->loadFeedData('entrances_goals', 'date', $details);  
  }
 
  $ga_data->setRequestSetting('details', 0);
  $ga_data->setRequestDefaultParam('max_results', 10*31);  
  $ga_data->setRequestSetting('subIndexBy', 'trafficcategory');
  $ga_data->loadFeedData('entrances');
  $ga_data->setRequestSetting('subIndexBy', '');

  $d = $ga_data->data;
  
  $d['lastmonth'] = $last_month_data->data['site'];
  $d['lastmonth']['daterange'] = array(
    'start' => $lastmonth_start_date,
    'end' => $lastmonth_end_date,
    'days' => $lastmonth_number_of_days,
  );
  
  $request = array(
    'dimensions' => array('ga:date', 'ga:customVarValue5', 'ga:medium', 'ga:socialNetwork'),
    'metrics' => array('ga:entrances'),
    'sort_metric' => '',
    'start_date' => $start_date,
    'end_date' => $end_date,
    'filters' => 'ga:customVarValue3=@&k&',
    'segment' => '',
    'max_results' => 1000,
  );

  $request = array(
    'dimensions' => array('ga:date', 'ga:customVarValue5', 'ga:medium', 'ga:socialNetwork'),
    'metrics' => array('ga:entrances'),
    'sort_metric' => '-ga:date',
    'start_date' => $start_date,
    'end_date' => $end_date,
    'filters' => '', //ga:customVarValue3=@&k&',
    'segment' => 'dynamic::ga:eventCategory=~^Form,ga:customVarValue3=@&k&',
    'max_results' => 1000,
  );  
  
  $data = google_analytics_api_report_data($request, $cache_options);
  $visitors = array();
  if (!empty($data->results)) {
    foreach ($data->results AS $row) {    
      $cat = $ga_data->initFeedIndex($row, 'trafficcategory'); 
      $visitors[$row['customVarValue5']] = $cat;
    }
  }
  
  $query = db_select('intel_visitor', 'v')
    ->fields('v', array('contact_created', 'vtkid'))
    ->condition('contact_created', $start_date, '>=');
  $result = $query->execute();
  $unknowns = array();
  $d['date']['_all']['lead'] = array(
    'leads' => 0,
    'trafficcategory' => array(),
  );
  while ($row = $result->fetchObject()) {
    $index = date("Ymd", $row->contact_created);
    if (!isset($d['date'][$index]['lead'])) {
      $d['date'][$index]['lead'] = array(
        'leads' => 0,
        'trafficcategory' => array(),
      );
      $vtkids[$index] = array();
    }
    $d['date'][$index]['lead']['leads']++; 
    $d['date']['_all']['lead']['leads']++; 
    $cat = $visitors[$row->vtkid];
    if (empty($cat)) {
      $cat = 'unknown';
      $unknowns[$row->vtkid];
    }
    if (!isset($d['date'][$index]['lead']['trafficcategory'][$cat])) {
      $d['date'][$index]['lead']['trafficcategory'][$cat] = 0;
    }
    $d['date'][$index]['lead']['trafficcategory'][$cat]++;
  }
  $query = db_select('intel_visitor', 'v')
    ->fields('v', array('contact_created', 'vtkid'))
    ->condition('contact_created', $lastmonth_start_date, '>=')
    ->condition('contact_created', $lastmonth_end_date, '<=');
  $query->addExpression('COUNT(v.vid)', 'leads_created');

  $row = $query->execute()->fetchObject();
  $d['lastmonth']['_all']['lead'] = array(
    'leads' => $row->leads_created,
  );
  
  // get nodes published this month
  $query = db_select('node', 'n')
    ->fields('n')
    ->condition('status', 1)
    ->condition('created', $start_date, '>=');
  $result = $query->execute();
  $page_filter = '';
  $entrance_filter = '';
  $count = 0;
  while ($row = $result->fetchObject()) {
    $index = date("Ymd", $row->created);
    if (!isset($d['date'][$index]['post'])) {
      $d['date'][$index]['post'] = array();
    }
    $host = 'getlevelten.com';
    $path = url('node/' . $row->nid);
    $d['date'][$index]['post'][$row->nid] = array(
      'id' => $row->nid,
      'type' => str_replace('enterprise_', '', $row->type),
      'created' => $row->created,
      'title' => $row->title,
      'author' => $row->uid,
      'path' => $path,
      'host' => $host,
    );
    $page_filter .= (($page_filter) ? ',' : '') . $ga_data->formatPathFilter($path, 'pagePath', TRUE);
    $entrance_filter .= (($entrance_filter) ? ',' : '') . $ga_data->formatPathFilter($path, 'landingPagePath', TRUE);
    $count ++;
  }
  $d['date']['_all']['post'] = array(
    'published' => $count,
  );
  
  $query = db_select('node', 'n')
    ->fields('n')
    ->condition('status', 1)
    ->condition('created', $lastmonth_start_date, '>=')
    ->condition('created', $lastmonth_end_date, '<=');
  $query->addExpression('COUNT(n.nid)', 'published_nodes');
  $row = $query->execute()->fetchObject();
  $d['lastmonth']['_all']['post'] = array(
    'published' => $row->published_nodes,
  );
  //dsm($row);  
  
  $ga_data = new LevelTen\Intel\GAModel();
  $ga_data->buildFilters($filters, $context);
  $ga_data->setDateRange($start_date, $end_date);
  $ga_data->setRequestCallback('intel_ga_feed_request_callback', array('cache_options' => $cache_options));
  $ga_data->setDataIndexCallback('category', '_intel_determine_category_index');
  
  $entrance_filter = 'ga:landingPagePath=~/blog/';
  $page_filter = 'ga:pagePath=~/blog/';
  
  $regex = $ga_data->formatGtRegexFilter('ga:customVarValue1', $start_date, 'pt');

//$ga_data->setDebug(1); 
  $ga_data->setCustomFilter($regex, 'segment');
  //$ga_data->setCustomFilter('ga:landingPagePath=@/');
  //$ga_data->setCustomFilter($entrance_filter);
  $ga_data->setRequestDefaultParam('max_results', 10 * $count); 
  $request = $ga_data->loadFeedData('entrances', 'content');
 
  $ga_data->setCustomFilter($regex . ';ga:landingPagePath=@/');
  //$ga_data->setCustomFilter($page_filter);
  $ga_data->setRequestDefaultParam('max_results', 40 * $count); 
  $request = $ga_data->loadFeedData('entrances_valuedevents', 'content');    
  
  //$ga_data->setCustomFilter('', 'segment');
  $ga_data->setCustomFilter($regex . ';ga:pagePath=@/');
  //$ga_data->setCustomFilter($page_filter);
  $ga_data->setRequestDefaultParam('max_results', 40 * $count); 
  $request = $ga_data->loadFeedData('pageviews_valuedevents', 'content');  
//dsm($ga_data->data['content']);   
  $d['content'] = $ga_data->data['content'];
  
  // testing
  /*
  $ga_data = new LevelTen\Intel\GAModel();
  $ga_data->buildFilters($filters, $context);
  $ga_data->setDateRange($start_date, $end_date);
  $ga_data->setRequestCallback('intel_ga_feed_request_callback', array('cache_options' => $cache_options));
  $ga_data->setDataIndexCallback('category', '_intel_determine_category_index');
  
  $entrance_filter = 'ga:landingPagePath=~/blog/';
  $page_filter = 'ga:pagePath=~/blog/';
  
  $regex = $ga_data->formatGtRegexFilter('ga:customVarValue1', $start_date, 'pt');

  $ga_data->setCustomFilter($entrance_filter);
  $ga_data->setRequestDefaultParam('max_results', 10 * $count); 
  $request = $ga_data->loadFeedData('entrances', 'content');
 
  $ga_data->setCustomFilter($entrance_filter);
  $ga_data->setRequestDefaultParam('max_results', 40 * $count); 
  $request = $ga_data->loadFeedData('entrances_valuedevents', 'content');    
  
  $ga_data->setCustomFilter($page_filter);
  $ga_data->setRequestDefaultParam('max_results', 40 * $count); 
  $request = $ga_data->loadFeedData('pageviews_valuedevents', 'content');
dsm($ga_data->data['content']);  
  
  //$d['content'] = $ga_data->data['content'];
  */
  
  
  if (!empty($path)) {
    $created = intel_get_node_created($path);
    $start = ($created > $start_date) ? $created : $start_date;
    $analysis_days = ($end_date - $start) / 86400;
  }
  else {
    $start = $created = $start_date;
    $analysis_days = ($end_date - $start) / 86400;
  }

  
  foreach ($d['date'] AS $index => $de) {
    $score_components = array();
    if ($context == 'page') {
      $d['date'][$index]['score'] = intel_score_page_aggregation($de, 1, $score_components);      
    } 
    else {
      $d['date'][$index]['score'] = intel_score_visit_aggregation($de, 1, $score_components);
    } 
    $d['date'][$index]['score_components'] = $score_components;  
  }
  if (isset($d['content'])) {
    foreach ($d['content'] AS $index => $de) {
      $score_components = array();
      $d['content'][$index]['score'] = intel_score_visit_aggregation($de, 1, $score_components);
      $d['content'][$index]['score_components'] = $score_components;  
    }    
  }
  /*
  if (isset($d['trafficsources'])) {
    $sub_indexes = _intel_get_trafficsource_sub_indexes();
    foreach ($sub_indexes AS $sub_index => $t) {
      foreach ($d['trafficsources'][$sub_index] AS $index => $de) {
        $score_components = array();
        $d['trafficsources'][$sub_index][$index]['score'] = intel_score_visit_aggregation($de, 1, $score_components);
        $d['trafficsources'][$sub_index][$index]['score_components'] = $score_components;  
      } 
    }   
  }
  */
  // order date data cronologically
  ksort($d['date']);
  
  $vars = array(
    'data' => $d,
    'number_of_days' => $number_of_days,
    'start_date' => $start_date,
    'end_date' => $end_datemo,
    'goals' => $goals,
    'targets' => intel_get_targets(),
    'analysis_days' => $analysis_days,
    'context' => $context,
  );
  $output .= theme_intel_dashboard_report($vars);

  $output .= t("Timeframe: %start_date - %end_date %refresh", array(
    '%start_date' => date("Y-m-d H:i", $start_date),
    '%end_date' => date("Y-m-d H:i", $end_date),
    '%refresh' => (!empty($cache_options['refresh'])) ? '(refresh)' : '',
  )); 

  $output .= ' (' . l(t('refresh data'), $_GET['q'], array('query' => array('refresh' => 1))) . ')';
  
  return $output;  
}

function theme_intel_dashboard_report($vars) {
  intel_include_library_file("reports/class.dashboard_report_view.php");
  
  $output = '';

  $report_view = new LevelTen\Intel\DashboardReportView();
  $report_view->setData($vars['data']);
  $report_view->setTableRowCount($vars['row_count']);
  $report_view->setModes($vars['report_modes']);
  $report_view->setParam('indexBy', $vars['indexBy']);
  $report_view->setParam('indexByLabel', $vars['indexByLabel']);
  //$report_view->setObjective('entrances_per_month', 3000);
  //$report_view->setObjective('leads_per_month', 30);
  //$report_view->setObjective('posts_per_month', 8);
  $report_view->setTargets($vars['targets']);
  $report_view->setDateRange($vars['start_date'], $vars['end_date']);
  $report_view->setLibraryUri(libraries_get_path('LevelTen') . '/Intel');
  \LevelTen\Intel\ReportPageHeader::setAddScriptCallback('intel_report_add_js_callback');
  $output .= $report_view->renderReport();
  
  return $output; 
}