<?php
/**
 * @file
 * admin > content enhancements
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_admin_content_alter_js($content_type = '') {
  require_once drupal_get_path('module', 'intel') . "/includes/intel.ga.inc";
  require_once drupal_get_path('module', 'intel') . "/includes/intel.page_data.inc";
  intel_include_library_file('ga/class.ga_model.php');
  intel_include_library_file("reports/class.report_view.php");
  $filters = array();
  $context = 'page';
  
  $report_mode = 'default.top.combined';
  $report_modes = explode('.', $report_mode);
  
  $timeops = 'l30d';
  $cache_options = array();
  list($start_date, $end_date, $number_of_days) = _intel_get_report_dates_from_ops($timeops, $cache_options);

  $ga_data = new LevelTen\Intel\GAModel();
  $ga_data->setReportModes($report_modes);
  $ga_data->buildFilters($filters, $context);
  $ga_data->setDateRange($start_date, $end_date);
  $ga_data->setRequestCallback('intel_ga_feed_request_callback', array('cache_options' => $cache_options));
//dsm($filters);  
//dsm($context);  
//dsm($ga_data->gaFilters); 
  //$ga_data->setDataIndexCallback('category', '_l10insight_determine_category_index');  

  $ga_data->setRequestSetting('indexBy', 'content');
  $ga_data->setRequestSetting('details', 0);
  
  //$ga_data->setDebug(1);
  $ga_data->setRequestDefaultParam('max_results', 1000);
  $ga_data->loadFeedData('entrances'); 
  
  $ga_data->setRequestDefaultParam('max_results', 1000);
  $ga_data->loadFeedData('pageviews'); 
  
  $ga_data->setRequestDefaultParam('max_results', 1000);
  $ga_data->loadFeedData('entrances_valuedevents');
  
  $data = $ga_data->data;
  
  $report_view = new LevelTen\Intel\ReportView();
  $report_view->setTargets(intel_get_targets());
  
  $rows = array();
  foreach ($data['content'] AS $i => $d) {
    if (empty($d['i']) || (substr($d['i'], 0, 1) == '_')) {
      continue;
    }
    list($host, $path) = explode('/', $d['i'], 2);
    $path = '/' . $path;
    if (!in_array($path, $_REQUEST['hrefs'])) {
      continue;
    }
    $node_meta = intel_get_node_meta_from_path($path);
    $created = $node_meta->created;
    $start = ($created > $start_date) ? $created : $start_date;
    $days_included = ($end_date - $start) / 86400;
     
    $d['score'] = intel_score_page_aggregation($d, $days_included);

    $title = $report_view->formatValueScoreTitle($d['score'] * $days_included, $start, $end_date);
    $value_str = '';
    $score = $report_view->renderValueScore(array('value' => $d['score'], 'type' => 'value_per_page_per_day', 'title' => $title), $value_str);
    $score_link = l($score, 'node/' . $node_meta->nid . '/analytics', array('html' => 1));
    $pageviews = (!empty($d['pageview']['pageviews'])) ? number_format($d['pageview']['pageviews']) : '-';
    $entrances = (!empty($d['entrance']['entrances'])) ? number_format($d['entrance']['entrances']) : '-';
    $rows[$path] = '<td class="intel-value">' . $score_link . '</td><td class="intel-entrances">' . $entrances . '</td><td class="intel-pageviews">' . $pageviews . '</td>';
  }  

  //dsm($data); dsm($rows);
  //return '';

  $output['rows'] = $rows;
  $output['rowcount'] = count($rows);

  drupal_json_output($output);
}