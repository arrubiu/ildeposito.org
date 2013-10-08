<?php
/**
 * @file
 * Generates scorecard reports
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_scorecard_report_page($context = '-', $filter_type = '', $filter_element = '') {
  $filters = array();
  if ($filter_type) {
    if ($filter_type == 'node') {
      $filter_type = 'page';
      $filter_element = 'landingPagePath:' . url('node/' . $filter_element->nid);
    }
    elseif ($filter_type == 'visitorid') {
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
    drupal_set_title(t('Scorecard', array('@type' => $type_name)), PASS_THROUGH); 
    $filters += $_GET;
    $filter_form = drupal_get_form('intel_report_filters_form', $filters, $context);
    $output .= drupal_render($filter_form);  
  }
  
  if (empty($_GET['return_type'])) {
    $output .= intel_get_report_ajax_container();
  }
  elseif ($_GET['return_type'] == 'nonajax') {
    $output .= intel_scorecard_report($filters, $context);
  }
  elseif ($_GET['return_type'] == 'json') {
    $data = array(
      'report' => intel_scorecard_report($filters, $context),
    );
    drupal_json_output($data);
    return;    
  }  
   
  return $output;
}

function intel_scorecard_report($filters = array(), $context = '-', $mode = '') {
  intel_include_library_file('ga/class.ga_model.php');
  require_once drupal_get_path('module', 'intel') . "/includes/intel.page_data.inc";
  
  if ($context == '-') {
    $context = 'site';
  }
  $cache_options = array();
  
  $output = '';    
  
  $timeops = 'l30d';
  //$timeops = 'yesterday';
  list($start_date, $end_date, $number_of_days) = _intel_get_report_dates_from_ops($timeops, $cache_options);

  $ga_data = new LevelTen\Intel\GAModel();
  $ga_data->buildFilters($filters, $context);
  $ga_data->setDateRange($start_date, $end_date);
  $ga_data->setRequestCallback('intel_ga_feed_request_callback', array('cache_options' => $cache_options));
//dsm($ga_data->gaFilters);

  
  $ga_data->setRequestSetting('indexBy', 'date');
  $ga_data->setRequestSetting('details', 0);
  $ga_data->setRequestDefaultParam('max_results', 30); 
  
  $ga_data->loadFeedData('pageviews');

  $ga_data->loadFeedData('entrances'); 
  
  $ga_data->setRequestSetting('details', 1);
  $ga_data->setRequestDefaultParam('max_results', 10 * 30); 
  if ($context == 'page') { 
    $ga_data->loadFeedData('pageviews_valuedevents');  
  }
 
  $ga_data->loadFeedData('entrances_valuedevents'); 
  
  $ga_data->setRequestSetting('details', 1);
  $ga_data->setRequestDefaultParam('max_results', 5 * 30);
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
 
  if ($context != 'page') {
    $ga_data->setRequestDefaultParam('max_results', 200); 
    $request = $ga_data->loadFeedData('pageviews', 'content'); 
    
    $ga_data->setRequestDefaultParam('max_results', 50); 
    $request = $ga_data->loadFeedData('entrances', 'content'); 
    
    $ga_data->setRequestDefaultParam('max_results', 200);
    $request = $ga_data->loadFeedData('pageviews_valuedevents', 'content'); 
  }
  $ga_data->setRequestDefaultParam('max_results', 100);
  $request = $ga_data->loadFeedData('entrances', 'trafficsources'); 
  
  $d = $ga_data->data;
 
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
      if ($context == 'page') {
        $d['content'][$index]['score'] = intel_score_page_aggregation($de, 1, $score_components);      
      } 
      else {
        $d['content'][$index]['score'] = intel_score_visit_aggregation($de, 1, $score_components);
      } 
      $d['content'][$index]['score_components'] = $score_components;  
    }    
  }
  if (isset($d['trafficsources'])) {
    $sub_indexes = $ga_data->getTrafficsourcesSubIndexes();
    foreach ($sub_indexes AS $sub_index) {
      foreach ($d['trafficsources'][$sub_index] AS $index => $de) {
        $score_components = array();
        $d['trafficsources'][$sub_index][$index]['score'] = intel_score_visit_aggregation($de, 1, $score_components);
        $d['trafficsources'][$sub_index][$index]['score_components'] = $score_components;  
      } 
    }   
  }
  // order date data cronologically
  ksort($d['date']);
  
//dsm($d); 
  
  $vars = array(
    'data' => $d,
    'number_of_days' => $number_of_days,
    'start_date' => $start_date,
    'end_date' => $end_date,
    'goals' => $goals,
    'analysis_days' => $analysis_days,
    'context' => $context,
  );
  $output .= theme_intel_content_scorecard($vars);

  $output .= t("Timeframe: %start_date - %end_date %refresh", array(
    '%start_date' => date("Y-m-d H:i", $start_date),
    '%end_date' => date("Y-m-d H:i", $end_date),
    '%refresh' => (!empty($cache_options['refresh'])) ? '(refresh)' : '',
  ));  
  
  return $output;  
}

function intel_scorecard_apply_filters_to_request($request, $filterstr, $segmentstr) {
  if ($filterstr) {
    $request['filters'] .= (($request['filters']) ? ';' : '') . $filterstr;
  }
  if ($segmentstr) {
    $request['segment'] .= (($request['segment']) ? ';' : '') . $segmentstr;
  }
  return $request;
}

function theme_intel_content_scorecard($vars) {
  intel_include_library_file("reports/class.scorecard_report_view.php");
  
  $output = '';

  $report_view = new LevelTen\Intel\ScorecardReportView();
  $report_view->setData($vars['data']);
  $report_view->setTableRowCount($vars['row_count']);
  $report_view->setModes($vars['report_modes']);
  $report_view->setParam('context', $vars['context']);
  $report_view->setParam('analysis_days', $vars['analysis_days']);
  $report_view->setPageMetaCallback('intel_get_page_meta_callback');
  $report_view->setTargets(intel_get_targets());
  $report_view->setGoals($vars['goals']);
  $report_view->setDateRange($vars['start_date'], $vars['end_date']);
  \LevelTen\Intel\ReportPageHeader::setAddScriptCallback('intel_report_add_js_callback');
  $output .= $report_view->renderReport();
  
  return $output; 
}
  
function theme_intel_content_scorecard_main_chart($vars) {
  $data = $vars['data'];
  $chart_colors = $vars['chart_colors'];
  $chart_colors_comp = $vars['chart_colors_comp'];
  $rows = array();
  $rows[] = array(
    'Date',
    'Entrances',
    'Additional pageviews',
    //'Valued events (entrance)',
    //'Valued events (pageview)',
    //'Goals (entrance)',
    'Goal value',
    'Event value',
    'Traffic value',
  );
  foreach ($data['date'] AS $day => $d) {
    if (substr($day, 0 , 1) == '_') {
      continue;
    }
    $ts = strtotime(substr($day, 0, 4) . '-' . substr($day, 4, 2) . '-' . substr($day, 6, 2));
    $row = array(
      date("M j", $ts),
      $d['entrance']['entrances'],
      $d['pageview']['pageviews'] - $d['entrance']['entrances'],
    );
    if ($vars['context'] == 'page') {
      $row[] = $d['score_components']['_all']['goals'];
      $row[] = $d['score_components']['_all']['events'];
      $row[] = $d['score_components']['_all']['traffic'];
    }
    else {
      $row[] = $d['score_components']['goals'];
      $row[] = $d['score_components']['events'];
      $row[] = $d['score_components']['traffic'];      
    }
    $rows[] = $row;
  } 
//dsm($rows);

  $c = array(
    'data' => $rows,
    'options' => array(
      'isStacked' => 1,
      'series' => array(
        0 => array(
          'type' => "area",
          'color' => $chart_colors[0],
          'pointSize' => 6,
          'lineWidth' => 3,
          'areaOpacity' => 0.1,
        ),
        1 => array(
          'type' => "line",
          'color' => $chart_colors_comp[0][0],
          'pointSize' => 6,
          'lineWidth' => 3,
        ),
        2 => array(
          'type' => "bars",
          'color' => $chart_colors[1],
        ),
        3 => array(
          'type' => "bars",
          'color' => $chart_colors_comp[1][0],
        ),
        4 => array(
          'type' => "bars",
          'color' => $chart_colors_comp[1][1],
        ),
      ),
    ),
    'settings' => array(
      'default_options' => 'main_chart',
    ),
  );
  $output = '<div id="report-main-chart">';
  $output .= theme_intel_combo_chart($c);
  $output .= '</div>';

  return $output;
}

function theme_intel_content_scorecard_gauges($vars) {
  $data = $vars['data'];
  $datasum = $data['date']['_all'];
  $chart_colors = $vars['chart_colors'];
  $targets = $vars['targets'];
//dsm($targets);
//dsm($data);

  $value_per_day = $datasum['score'] / 30;
  $cart = array();
  $chart['data'] = array(
    array('Label', 'Value'),
    array(
      t('$/day'),
      (float)number_format($value_per_day, 2),
    ),
  );
  $max = (float)2 * $targets['value_per_page_per_day'];
  $max = (float)number_format($max, 2);
  $chart['options'] = array(
    'width' => 180,
    'height' => 180,
    'redFrom' => 0,
    'redTo' => (float)$targets['value_per_page_per_day_warning'],
    'yellowFrom' => (float)$targets['value_per_page_per_day_warning'],
    'yellowTo' => (float)$targets['value_per_page_per_day'],
    'greenFrom' => (float)$targets['value_per_page_per_day'],
    'greenTo' => (float)number_format($max, 2),
    'redColor' => $chart_colors[2],
    'yellowColor' => $chart_colors[3],
    //'yellowColor' => '#FFF',
    'greenColor' => $chart_colors[1],
    'max' => $max,
  );
  $gauge1 = theme_intel_gauge_chart($chart);
  
  $value_per_visit = $datasum['score'] / $datasum['visit']['entrances'];
  $chart['data'][1] = array(
    '$/visit',
    (float)number_format($value_per_visit, 2),
  );
  $max = (float)2 * $targets['value_per_page_per_entry'];
  $max = (float)number_format($max, 2);
  $chart['options'] = array(
    'width' => 90,
    'height' => 90,
    'redFrom' => 0,
    'redTo' => (float)$targets['value_per_page_per_entry_warning'],
    'yellowFrom' => (float)$targets['value_per_page_per_entry_warning'],
    'yellowTo' => (float)$targets['value_per_page_per_entry'],
    'greenFrom' => (float)$targets['value_per_page_per_entry'],
    'greenTo' => (float)number_format($max, 2),
    'redColor' => $chart_colors[2],
    'yellowColor' => $chart_colors[3],
    //'yellowColor' => '#FFF',
    'greenColor' => $chart_colors[1],
    'max' => $max,
  );
  $gauge2 = theme_intel_gauge_chart($chart);
  
  $output = '<div id="report-gauges">';
  $output .= $gauge1;
  $output .= $gauge2;
  $output .= '</div>';
  return $output;  
}

function theme_intel_content_scorecard_summary_section($vars) {
  $data = $vars['data'];
  $datasum = $data['date']['_all'];
  $chart_colors = $vars['chart_colors'];
  $targets = $vars['targets'];
  $analysis_days = $vars['analysis_days'];
  $summary_elements = array();
  $init_e = array(
    'data' => $data['date'],
    'chart_colors' => $chart_colors, 
  );
//dsm($targets);

  $status_colors = array();
  $index = 0.4;
  $val1 = intel_get_value_of_color($chart_colors[1]);
  $val2 = intel_get_value_of_color('#FFFFFF');
  foreach ($val1 AS $i => $v) {
    $newval[$i] = $val1[$i] * $index + $val2[$i] * (1 - $index);
  }
  $status_colors['complete'] = intel_get_color_from_value($newval);
    
  $val1 = intel_get_value_of_color($chart_colors[3]);
  foreach ($val1 AS $i => $v) {
    $newval[$i] = $val1[$i] * $index + $val2[$i] * (1 - $index);
  }
  $status_colors['warning'] = intel_get_color_from_value($newval);
 
  $val1 = intel_get_value_of_color($chart_colors[2]);
  foreach ($val1 AS $i => $v) {
    $newval[$i] = $val1[$i] * $index + $val2[$i] * (1 - $index);
  }
  $status_colors['error'] = intel_get_color_from_value($newval);

  $value = $datasum['score'] / $analysis_days;
  $status = 'complete';
  $cindex = 1;
  if ($value < $targets['value_per_page_per_day']) {
    $cindex = 3;
    $status = 'warning';
  }
  if ($value < $targets['value_per_page_per_day_warning']) {
    $cindex = 2;
    $status = 'error';
  }
  $e = $init_e;
  $e['chart_colors'] = array($chart_colors[$cindex]);
  $e['status_color'] = $status_colors[$status];
  $e['keys'] = 'score';
  $e['title'] = t('Value/Day');
  $e['total'] = number_format($value, 2);
  $summary_elements['value_per_day'] = theme_intel_report_summary_element($e);

  $value = $datasum['entrance']['entrances'] / $analysis_days;
  $status = 'complete';
  $cindex = 1;
  if ($value < $targets['entrances_per_page_per_day']) {
    $cindex = 3;
    $status = 'warning';
  }
  if ($value < $targets['entrances_per_page_per_day_warning']) {
    $cindex = 2;
    $status = 'error';
  }
  $e = $init_e;
  $e['chart_colors'] = array($chart_colors[$cindex]);
  $e['status_color'] = $status_colors[$status];
  $e['keys'] = 'entrance.entrances';
  $e['title'] = t('Entrances/Day');
  $e['total'] = number_format($value, 1);
  $summary_elements['entrances_per_day'] = theme_intel_report_summary_element($e); 

  $value = $datasum['score'] / $datasum['entrance']['entrances'];
  $status = 'complete';
  $cindex = 1;
  if ($value < $targets['value_per_page_per_entrance']) {
    $cindex = 3;
    $status = 'warning';
  }
  if ($value < $targets['value_per_page_per_entrance_warning']) {
    $cindex = 2;
    $status = 'error';
  }
  $e = $init_e;
  $e['chart_colors'] = array($chart_colors[$cindex]);
  $e['status_color'] = $status_colors[$status];
  $e['keys'] = 'score';
  $e['keys2'] = 'entrance.entrances';
  $e['keys_operator'] = '/';
  $e['format'] = array(
    'type' => 'money',
    'decimals' => 2,
  );
  $e['title'] = t('Value/Visit');
  $e['total'] = '$' . number_format($datasum['score'] / $datasum['entrance']['entrances'], 2);
  $summary_elements['valuePerVisit'] = theme_intel_report_summary_element($e);


  $e = $init_e;
  $e['keys'] = 'entrance.entrances';
  $e['title'] = t('Entrances');
  $e['total'] = number_format($datasum['entrance']['entrances']);
  $summary_elements['entrances'] = theme_intel_report_summary_element($e);
  
  $e['keys'] = 'pageview.pageviews';
  $e['title'] = t('Pageviews');
  $e['total'] = number_format($datasum['pageview']['pageviews']);
  $summary_elements['pageviews'] = theme_intel_report_summary_element($e);
  
  $e['keys'] = 'entrance.sticks';
  $e['keys2'] = 'entrance.entrances';
  $e['keys_operator'] = '/';
  $e['format'] = array(
    'type' => 'percentage',
    'decimals' => 1,
  );
  $e['title'] = t('Stick rate');
  $e['total'] = number_format(100 * $datasum['entrance']['sticks'] / $datasum['entrance']['entrances'], 1) . "%";
  $summary_elements['stickrate'] = theme_intel_report_summary_element($e);
  
  $e = $init_e;

  $e['keys'] = 'entrance.newVisits';
  $e['title'] = t('New Visits');
  $e['total'] = number_format(100 * $datasum['entrance']['newVisits'] / $datasum['entrance']['entrances'], 1) . "%";
  $summary_elements['percentNewVisits'] = theme_intel_report_summary_element($e);

  $e = $init_e;
  $e['keys'] = 'entrance.timeOnSite';
  $e['keys2'] = 'entrance.entrances';
  $e['keys_operator'] = '/';
  $e['title'] = t('Avg. Time on Site');
  $e['total'] = _intel_format_delta_time($datasum['entrance']['timeOnSite'] / $datasum['entrance']['entrances']);
  $summary_elements['avgTimeOnSite'] = theme_intel_report_summary_element($e);
  
  $e['keys'] = 'entrance.pageviews';
  $e['keys2'] = 'entrance.entrances';
  $e['keys_operator'] = '/';
  $e['title'] = t('Pages/Visit');
  $e['total'] = number_format($datasum['entrance']['pageviews'] / $datasum['entrance']['entrances'], 2);
  $summary_elements['pageviewsPerVisit'] = theme_intel_report_summary_element($e);
  
  $e = $init_e;
  $e['keys'] = 'score';
  $e['format'] = array(
    'type' => 'money',
    'decimals' => 2,
  );
  $e['title'] = t('Value');
  if ($data['date']['_all']['score'] > 1000) {
    $e['total'] = number_format($data['date']['_all']['score'], 0);
  }
  else {
    $e['total'] = number_format($data['date']['_all']['score'], 2);
  }
  $summary_elements['value'] = theme_intel_report_summary_element($e);
  
  $e['keys'] = 'score';
  $e['format'] = array(
    'type' => 'money',
    'decimals' => 2,
  );
  $e['title'] = t('Value/Day');
  $e['total'] = number_format($data['date']['_all']['score'] / $analysis_days, 2);
  //$summary_elements['valuePerDay'] .= theme_intel_report_summary_element($e);
  
  $e = $init_e;
  $e['keys'] = 'entrance.goalCompletionsAll';
  $e['title'] = t('Goals completed');
  $e['total'] = number_format($datasum['entrance']['goalCompletionsAll']);
  $summary_elements['goals'] = theme_intel_report_summary_element($e);
  
  $e['keys2'] = 'entrance.entrances';
  $e['keys_operator'] = '/';
  $e['format'] = array(
    'type' => 'percentage',
    'decimals' => 1,
  );
  $e['title'] = t('Conversion/Visit');
  $e['total'] = number_format(100 * $datasum['entrance']['goalCompletionsAll'] / $datasum['entrance']['entrances'], 2) . '%';
  $summary_elements['goalsPerVisit'] = theme_intel_report_summary_element($e);
  
  $e = $init_e;
  $e['keys'] = 'entrance.events._all.totalValuedEvents';
  $e['title'] = t('Val. events (entr)');
  $e['total'] = number_format($datasum['entrance']['events']['_all']['totalValuedEvents']);
  $summary_elements['valuedEventsVisit'] = theme_intel_report_summary_element($e);
  
  $e['keys2'] = 'entrance.entrances';
  $e['keys_operator'] = '/';
  $e['format'] = array(
    'type' => 'percentage',
    'decimals' => 1,
  );
  $e['title'] = t('Val. events/dVisits');
  $e['total'] = number_format(100 * $datasum['entrance']['events']['_all']['totalValuedEvents'] / $datasum['entrance']['entrances'], 2);
  $summary_elements['valuedEventsPerVisit'] = theme_intel_report_summary_element($e);
  
  $output = '<div id="key-metrics-section" class="report-section">';
  $decimal = ($analysis_days < 10) ? 1 : 0;
  $output .= '<h3>' . t('Key metrics (%days)', array('%days' => number_format($analysis_days, $decimal) . " days")) . '</h3>';
  
  //$output = '<div class="kpis">';
  
  $output .= $summary_elements['value_per_day'];
  $output .= $summary_elements['entrances_per_day'];
  $output .= $summary_elements['valuePerVisit'];
  
  //$output .= '</div>';
  
  $output .= $summary_elements['entrances'];
  $output .= $summary_elements['stickrate']; 

  $output .= $summary_elements['pageviews'];
  $output .= $summary_elements['pageviewsPerVisit'];

  $output .= $summary_elements['percentNewVisits'];
  $output .= $summary_elements['avgTimeOnSite']; 
  
  $output .= $summary_elements['value'];
   
  
  $output .= $summary_elements['goals'];
  $output .= $summary_elements['goalsPerVisit']; 
  
  $output .= $summary_elements['valuedEventsVisit'];
  $output .= $summary_elements['valuedEventsPerVisit']; 
  
  $output .= '</div>'; 
  
  return $output;
}

function theme_intel_content_scorecard_goals_section($vars) {
  $data = $vars['data'];
  $datasum = $data['date']['_all'];
  $chart_colors = $vars['chart_colors'];  
  $context = $vars['context'];
  
  $v = array(
    'header' => array(
      t('Top goals'),
      array(
        'data' => t('Completed'),
        'class' => array('numeric-header'),
      ),
      array(
        'data' => t('Value'),
        'class' => array('numeric-header'),
      ),      
    ),
    'rows' => array(),
  );  
  
  // Goals (entrance)
  $rowlimit = 5;
  $chartdata_goals = array();
  $chartdata_events = array();
  
  usort($datasum['entrance']['goals'], '_intel_sort_by_value_then_completions');
  $i = 1;
  foreach ($datasum['entrance']['goals'] AS $n => $d) {
    if (empty($d['i'])) { 
      continue; 
    }
    $v['rows'][] = _intel_format_scorecard_goals_table_row($vars['goals'][$d['i']], $d['completions'], $d['value'], $chartdata_goals);
    if ($i++ >= $rowlimit) {
      break;
    }
  } 
  
  $out_goals_entrance = '<h3>' . t('Goals (entrance)') . '</h3>';
  $v['empty'] = t('No goals were generated from entrance.');
  $out_goals_entrance .= theme('table', $v);  
  
  $v['rows'] = array();
  usort($datasum['pageview']['goals'], '_intel_sort_by_value_then_completions');
  $i = 1;
  foreach ($datasum['pageview']['goals'] AS $n => $d) {
    if (empty($d['i'])) { 
      continue; 
    }
    $v['rows'][] = _intel_format_scorecard_goals_table_row($vars['goals'][$d['i']], $d['completions'], $d['value']);
    if ($i++ >= $rowlimit) {
      break;
    }
  } 
  $out_goals_assist = '<h3>' . t('Goals (assist)') . '</h3>';
  $v['empty'] = t('No goal assists were generated by this page.');
  $out_goals_assist .= theme('table', $v);    
  
  $v['header'][0] = t('Top valued events');   
  
  usort($datasum['entrance']['events'], '_intel_sort_by_value_then_total_valued_events');
  $i = 1;
  $v['rows'] = array();
  foreach ($datasum['entrance']['events'] AS $n => $d) {
    if (empty($d['i'])) { 
      continue; 
    }
    $v['rows'][] = _intel_format_scorecard_goals_table_row($d['i'], $d['totalValuedEvents'], $d['value'], $chartdata_events);
    if ($i++ >= $rowlimit) {
      break;
    }
  } 
  $out_events_entrance = '<h3>' . t('Valued events (entrance)') . '</h3>';
  $v['empty'] = t('No valued events were generated from entrance.');
  $out_events_entrance .= theme('table', $v);  

  usort($datasum['pageview']['events'], '_intel_sort_by_value_then_total_valued_events');
  $i = 1;
  $v['rows'] = array();
  foreach ($datasum['pageview']['events'] AS $cat => $d) {
    if (empty($d['i'])) { 
      continue; 
    }
    $v['rows'][] = _intel_format_scorecard_goals_table_row($d['i'], $d['totalValuedEvents'], $d['value']);
    if ($i++ >= $rowlimit) {
      break;
    }
  }
  $out_events_page = '<h3>' . t('Valued events (on page)') . '</h3>';
  $v['empty'] = t('No valued events occured on this page.');
  $out_events_page .= theme('table', $v);
  
  if ($context == 'page') {
    $chartdata = array_merge($chartdata_goals, $chartdata_events);    
  }
  else {
    $chartdata = $chartdata_goals;
  }
  
  usort($chartdata_goals, '_intel_usort_sort_pie_chart_data');
  $a = array(
    'data' => $chartdata,
    'options' => array(
    ),
    'settings' => array(
      'colors' => $chart_colors,
    ),
  );  
  $out_chart = theme_intel_pie_chart($a);

  $output = '<div id="goals-section" class="report-section">';
  $output .= '<h3>Goals &amp; valued events</h3>';
  $output .= '<div class="pane-left">' . $out_chart . '</div>';
  $output .= '<div class="pane-spacer">&nbsp;</div>';
  if ($context != 'page') {
    usort($chartdata_events, '_intel_usort_sort_pie_chart_data');
    $a['data'] = $chartdata_events;
    $out_events_page = theme_intel_pie_chart($a);   
  }
  $output .= '<div class="pane-right">' . $out_events_page . '</div>';  
  $output .= '<div class="pane-left" style="clear: left;">' . $out_goals_entrance . '</div>';
  $output .= '<div class="pane-spacer">&nbsp;</div>';
  $output .= '<div class="pane-right">' . $out_events_entrance . '</div>';  
  $output .= '</div>';
  
  return $output;
}

function _intel_format_scorecard_goals_table_row($item, $count, $value, &$chartdata = array()) {
  $a = array(
    $item,
    array(
      'data' => number_format($count),
      'class' => array('numeric-cell'),
    ),
    array(
      'data' => number_format($value, 2),
      'class' => array('numeric-cell'),
    ),
  ); 
  if ($value) {
    $chartdata[] = array($item, $value);
  }
  return $a;
}

function theme_intel_content_scorecard_content_section($vars) {
  $data = $vars['data'];
  $datasum = $data['date']['_all'];
  $chart_colors = $vars['chart_colors'];
  
  $v = array(
    'header' => array(
      t('Top pages'),
      array(
        'data' => t('Entrances'),
        'class' => array('numeric-header'),
      ),
      array(
        'data' => t('Pageviews'),
        'class' => array('numeric-header'),
      ),
      array(
        'data' => t('Value'),
        'class' => array('numeric-header'),
      ),    
      array(
        'data' => t('Value/entr'),
        'class' => array('numeric-header'),
      ),    
    ),
    'rows' => array(),
  );    
  
  $rowlimit = 10;
  $pages = array(
    'all' => array(),
    't' => array(),
    'l' => array(),
  );
  
  usort($data['content'], '_intel_sort_by_score_then_entrances');
  $i = 1;
  $limit = 50;
  foreach ($data['content'] AS $n => $d) {
    if (empty($d['i']) || (substr($d['i'], 0 , 1) == '_')) { 
      continue; 
    }
    list($host, $path) = explode('/', $d['i'], 2);
    $node_meta = intel_get_node_meta_from_path($path);      
    if ($node_meta) {
      $intent = intel_get_page_intent($node_meta);
    }
    else {
      $intent = '';
    }

    if (count($pages['all']) < $rowlimit) {
      if (($context != 'site') || (($intent != 'u') && ($intent != 'a'))) {
        $l = l(intel_format_text_data("/$path", 60), 'http://' . $d['i'], array('attributes' => array('target' => '_blank')));
        $pages['all'][] = _intel_format_scorecard_content_table_row($l, $d['entrance']['entrances'], $d['pageview']['pageviews'], $d['score'], $chartdata);  
      }    
    }
    if (isset($pages[$intent]) && (count($pages[$intent]) < $rowlimit)) {
      $l = l(intel_format_text_data("/$path", 60), 'http://' . $d['i'], array('attributes' => array('target' => '_blank')));
      $pages[$intent][] = _intel_format_scorecard_content_table_row($l, $d['entrance']['entrances'], $d['pageview']['pageviews'], $d['score'], $chartdata);      
    }
    $done = 1;
    foreach ($pages AS $intent) {
      if (count($pages[$intent]) < $rowlimit) {
        $done = 0;
        break;
      }
    } 
    if ($done || ($i >= $limit)) {
      break;
    }
    $i++;
  } 
  $v['rows'] = $pages['all'];
  $out_all_pages = '<h3>' . t('All pages') . '</h3>';
  $v['empty'] = t('No pages were found.');
  $out_all_pages .= theme('table', $v);

  $v['rows'] = $pages['t'];
  $out_attr_pages = '<h3>' . t('Attraction pages') . '</h3>';
  $v['empty'] = t('No pages were found.');
  $out_attr_pages .= theme('table', $v);

  $v['rows'] = $pages['l'];
  $out_lp_pages = '<h3>' . t('Landing pages') . '</h3>';
  $v['empty'] = t('No pages were found.');
  $out_lp_pages .= theme('table', $v); 
  

  
  $a = array(
    'data' => $chartdata,
    'options' => array(
    ),
    'settings' => array(
      'colors' => $chart_colors,
    ),
  );   
//dsm($a); 
  //$out_categories_chart = theme_intel_pie_chart($a);  
  
  $output = '<div id="content-section" class="report-section">';
  $output .= "<h3>Content</h3>";
  $output .= '<div>' . $out_all_pages . '</div>';
  
  $output .= '<div>' . $out_attr_pages . '</div>';
  
  //$output .= '<div>' . $out_lp_pages . '</div>';
    
  $output .= '</div>';    
  
  return $output;
}

function _intel_format_scorecard_content_table_row($item, $entrances, $pageviews, $value, &$chartdata = array()) {
  $a = array(
    $item,
    array(
      'data' => number_format($entrances),
      'class' => array('numeric-cell'),
    ),
    array(
      'data' => number_format($pageviews),
      'class' => array('numeric-cell'),
    ),
    array(
      'data' => number_format($value, 2),
      'class' => array('numeric-cell'),
    ),
    array(
      'data' => number_format((($entrances) ? ($value / $entrances) : 0), 2),
      'class' => array('numeric-cell'),
    ),
  ); 
  $chartdata[] = array($item, $value);
  return $a;
}

function theme_intel_content_scorecard_trafficsource_section($vars) {
  $data = $vars['data'];
  $datasum = $data['date']['_all'];
  $chart_colors = $vars['chart_colors'];
  
  //$refdims = _intel_get_trafficsource_sub_indexes();

  $v = array(
    'header' => array(
      t('Top traffic sources'),
      array(
        'data' => t('Visits'),
        'class' => array('numeric-header'),
      ),
      array(
        'data' => t('Value'),
        'class' => array('numeric-header'),
      ),  
      array(
        'data' => t('Value/entr'),
        'class' => array('numeric-header'),
      ),    
    ),
    'rows' => array(),
  );  
  
  // Goals (entrance)
  $chartdata = array();
  $rowlimit = 5;
  
  usort($data['trafficsources']['category'], '_intel_sort_by_score_then_entrances');
  $i = 1;
  foreach ($data['trafficsources']['category'] AS $n => $d) {
    if (empty($d['i']) || (substr($d['i'], 0 , 1) == '_')) { 
      continue; 
    }
    $v['rows'][] = _intel_format_scorecard_trafficsource_table_row($d['i'], $d['entrance']['entrances'], $d['score'], $chartdata);
    if ($i++ >= $rowlimit) {
      break;
    }
  } 
  $out_categories = '<h3>' . t('Categories') . '</h3>';
  $v['empty'] = t('No goals were generated from any category.');
  $out_categories .= theme('table', $v); 
  
  $a = array(
    'data' => $chartdata,
    'options' => array(
    ),
    'settings' => array(
      'colors' => $chart_colors,
    ),
  );   
//dsm($a); 
  $out_categories_chart = theme_intel_pie_chart($a);
  
  
  usort($data['trafficsources']['medium'], '_intel_sort_by_score_then_entrances');
  $i = 1;
  $v['rows'] = array();
  foreach ($data['trafficsources']['medium'] AS $n => $d) {
    if (empty($d['i']) || (substr($d['i'], 0 , 1) == '_')) { 
      continue; 
    }
    $v['rows'][] = _intel_format_scorecard_trafficsource_table_row($d['i'], $d['entrance']['entrances'], $d['score'], $chart_data);
    if ($i++ >= $rowlimit) {
      break;
    }
  } 
  $out_mediums = '<h3>' . t('Mediums') . '</h3>';
  $v['empty'] = t('No goals were generated from any medium.');
  $out_mediums .= theme('table', $v);  
  
  usort($data['trafficsources']['source'], '_intel_sort_by_score_then_entrances');
  $i = 1;
  $v['rows'] = array();
  foreach ($data['trafficsources']['source'] AS $n => $d) {
    if (empty($d['i']) || (substr($d['i'], 0 , 1) == '_')) { 
      continue; 
    }
    $v['rows'][] = _intel_format_scorecard_trafficsource_table_row($d['i'], $d['entrance']['entrances'], $d['score']);
    if ($i++ >= $rowlimit) {
      break;
    }
  } 
  $out_sources = '<h3>' . t('Sources') . '</h3>';
  $v['empty'] = t('No goals were generated from any medium.');
  $out_sources .= theme('table', $v); 
  
  usort($data['trafficsources']['referralHostpath'], '_intel_sort_by_score_then_entrances');
  $i = 1;
  $v['rows'] = array();
  foreach ($data['trafficsources']['referralHostpath'] AS $n => $d) {
    if (empty($d['i']) || (substr($d['i'], 0 , 1) == '_')) { 
      continue; 
    }
    $v['rows'][] = _intel_format_scorecard_trafficsource_table_row($d['i'], $d['entrance']['entrances'], $d['score']);
    if ($i++ >= $rowlimit) {
      break;
    }
  } 
  $out_referralurls = '<h3>' . t('Referral links') . '</h3>';
  $v['empty'] = t('No goals were generated from any referral links.');
  $out_referralurls .= theme('table', $v);

  $v['rows'] = array();
  if (isset($data['trafficsources']['socialNetwork'])) {
    usort($data['trafficsources']['socialNetwork'], '_intel_sort_by_score_then_entrances');
    $i = 1;
    $v['rows'] = array();
    foreach ($data['trafficsources']['socialNetwork'] AS $n => $d) {
      if (empty($d['i']) || (substr($d['i'], 0 , 1) == '_')) { 
        continue; 
      }
      $v['rows'][] = _intel_format_scorecard_trafficsource_table_row($d['i'], $d['entrance']['entrances'], $d['score']);
      if ($i++ >= $rowlimit) {
        break;
      }
    } 
  }
  $out_socialnetworks = '<h3>' . t('Social networks') . '</h3>';
  $v['empty'] = t('No goals were generated from any social network.');
  $out_socialnetworks .= theme('table', $v); 
  
  usort($data['trafficsources']['searchKeyword'], '_intel_sort_by_score_then_entrances');
  $i = 1;
  $v['rows'] = array();
  foreach ($data['trafficsources']['searchKeyword'] AS $n => $d) {
    if (empty($d['i']) || (substr($d['i'], 0 , 1) == '_')) { 
      continue; 
    }
    $v['rows'][] = _intel_format_scorecard_trafficsource_table_row($d['i'], $d['entrance']['entrances'], $d['score']);
    if ($i++ >= $rowlimit) {
      break;
    }
  } 
  $out_keywords = '<h3>' . t('Search keywords') . '</h3>';
  $v['empty'] = t('No goals were generated from any keywords.');
  $out_keywords .= theme('table', $v); 
  
  usort($data['trafficsources']['campaign'], '_intel_sort_by_score_then_entrances');
  $i = 1;
  $v['rows'] = array();
  foreach ($data['trafficsources']['campaign'] AS $n => $d) {
    if (empty($d['i']) || (substr($d['i'], 0 , 1) == '_')) { 
      continue; 
    }
    $v['rows'][] = _intel_format_scorecard_trafficsource_table_row($d['i'], $d['entrance']['entrances'], $d['score']);
    if ($i++ >= $rowlimit) {
      break;
    }
  } 
  $out_campaigns = '<h3>' . t('Campaigns') . '</h3>';
  $v['empty'] = t('No goals were generated from any campaigns.');
  $out_campaigns .= theme('table', $v); 
  
  $output = '<div id="trafficsources-section" class="report-section">';
  $output .= "<h3>Traffic sources</h3>";
  $output .= '<div class="pane-left">' . $out_categories_chart . '</div>';
  $output .= '<div class="pane-spacer">&nbsp;</div>';
  $output .= '<div class="pane-right">' . $out_mediums . '</div>'; 
  
  $output .= '<div class="pane-left" style="clear: left;">' . $out_categories . '</div>';
  $output .= '<div class="pane-spacer">&nbsp;</div>';
  $output .= '<div class="pane-right">' . $out_sources . '</div>';  
  
  $output .= '<div class="pane-left" style="clear: left;">' . $out_referralurls . '</div>';
  $output .= '<div class="pane-spacer">&nbsp;</div>';
  $output .= '<div class="pane-right">' . $out_socialnetworks . '</div>';
  
  $output .= '<div class="pane-left" style="clear: left;">' . $out_keywords . '</div>';
  $output .= '<div class="pane-spacer">&nbsp;</div>';
  $output .= '<div class="pane-right">' . $out_campaigns . '</div>';
    
  $output .= '</div>';  
  
  return $output;
}

function _intel_format_scorecard_trafficsource_table_row($item, $count, $value, &$chartdata = array()) {
  $a = array(
    $item,
    array(
      'data' => number_format($count),
      'class' => array('numeric-cell'),
    ),
    array(
      'data' => number_format($value, 2),
      'class' => array('numeric-cell'),
    ),
    array(
      'data' => number_format((($count) ? ($value / $count) : 0), 2),
      'class' => array('numeric-cell'),
    ),
  ); 
  $chartdata[] = array($item, $value);
  return $a;
}





function intel_content_scorecard_node($node, $mode = 'entrance') {
  $path = url('node/' . $node->nid);
  if ($mode == 'pageview') {
    $filters = array(
      'page' => "pagePath:$path",
    );
  }
  else {
    $filters = array(
      'page' => "landingPagePath:$path",
    );    
  }
  $output = '';
  //$output .= l(t('Entrance'), 'node/' . $node->nid . '/insight/visitors/entrance');
  //$output .= ' | ' . l(t('Page view'), 'node/' . $node->nid . '/insight/visitors/pageview');
  $output .= intel_content_scorecard($filters);
  return $output;
}

/*
 * 
  $ga_data->loadFeedData('pageviews', 'date', 0, 30);
  
  $ga_data->loadFeedData('entrances', 'date', 0, 30); 
  
  if ($context == 'page') { 
    $ga_data->loadFeedData('page_valuedevents', 'date', 1, 10 * 30);  
  }
  
  $ga_data->loadFeedData('session_valuedevents', 'date', 1, 10 * 30); 
  
  $ga_data->setDebug(1);
  $submission_goals = variable_get('intel_submission_goals', intel_get_submission_goals_default());
  for ($b = 0; isset($submission_goals[$b]) && ($b < 20); $b += 5) {
    $details = array();
    for($i = $b; isset($submission_goals[$i]); $i++) {
      $id = $submission_goals[$i]['ga_id'];
      $details[] = $id;      
      $goals["n$id"] = $submission_goals[$i]['name'];
    }
    $ga_data->loadFeedData('session_goals', 'date', $details, 30);  
  }
  $ga_data->setDebug(0);
  
  if ($context != 'page') {
    
    $request = $ga_data->loadFeedData('pageviews', 'content', 0, 200); 
    
    $request = $ga_data->loadFeedData('entrances', 'content', 0, 50); 
    
    $request = $ga_data->loadFeedData('session_valuedevents', 'content', 0, 100); 
  }
  //$ga_data->setDebug(1);
  $request = $ga_data->loadFeedData('entrances', 'trafficsources', 0, 100); 
 */