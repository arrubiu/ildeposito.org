<?php
// $Id: seotools.report.inc,v 1.1.2.2 2011/01/05 22:29:29 tomdude48 Exp $

function seotools_dashboard_page($rid = 'dashboard', $range = 30) {
  //Check that kwresearch and linkintel are install as this will crash if not.
  
  // check enabled modules
  $enabled_modules = array(
    'linkintel' => module_exists('linkintel'),
    'kwresearch' => module_exists('kwresearch'),
    'google_analytics_api' => module_exists('google_analytics_api'),
    'seo_friend' => module_exists('seo_friend'),
  );
  if(module_exists('google_analytics_api')) {    
    if(!google_analytics_api_current_profile_id()) {
      $enabled_modules['google_analytics_api'] = FALSE;
      $msg = t('You enable full dashboard reporting you need to !link.',
        array(
          '!link' => l(t('set your Google Analytics ID'), 'admin/settings/google-analytics-api', array('attributes' => array('target' => 'google_analytics_api'))),
        )
      );
      //drupal_set_message($msg, 'warning');      
    }
  }
  else {
    $enabled_modules['google_analytics_api'] = FALSE;
    $msg = t('You enable full dashboard reporting you need to !link.',
      array(
        '!link' => l(t('enable the Google Analytics API module.'), 'http://drupal.org/project/google_analytics_api', array('attributes' => array('target' => 'drupal.org'))),
      )
    );
    //drupal_set_message($msg, 'warning');
  }
  if (!($enabled_modules['google_analytics_api'])) {
    $msg = t('SEO Tools has not been configured properly.  Please go to ' . l('seotools presets', 'admin/presets/seotools') . ' and ensure that it is configured properly.');
    drupal_set_message($msg, 'error');
    return t('Unable to generate dashboard.');
  }
  drupal_add_css(drupal_get_path('module', 'seotools') . '/seotools.css');
  drupal_add_js(drupal_get_path('module', 'seotools') . '/seotools.js');

  $gid = variable_get('google_analytics_api_profile_id', 0);
  if(!$gid) {
    return t('Google Analytics id not set.');
  }
  global $base_url;
  $siteURL = variable_get('seotools_base_url', $base_url);

  $e = explode('-', $range);
  if(count($e) == 1) {
    $date_range = seotools_get_dates($range);
  }
  else {
    // TODO allow custom ranges
  }

  $labels = array(
    'keywords' => t('keywords'),
  );
  if($rid == 'dashboard') {
    $output .= '<div id="seotools-dashboard">' . "\n";
    $output .= '<div id="dashboard-pane-top">' . "\n";
    $output .= seotools_dashboard_analytics_box($gid, $siteURL, $date_range, $enabled_modules);
    $output .= '</div>' . "\n";
    $output .= '<div id="dashboard-pane-left">' . "\n";
    $output .= seotools_dashboard_keywords_box($gid, $siteURL, $date_range, $enabled_modules);
    $output .= seotools_dashboard_sources_box($gid, $siteURL, $date_range, $enabled_modules, $mediums_data);
    $output .= seotools_dashboard_map_box($gid, $siteURL, $date_range, $enabled_modules, $mediums_data);
    $output .= '</div>' . "\n";
    $output .= '<div class="dashboard-spacer">&nbsp;</div>';
    $output .= '<div id="dashboard-pane-right">' . "\n";
    $output .= seotools_dashboard_entrances_box($gid, $siteURL, $date_range, $enabled_modules);
    $output .= seotools_dashboard_referrers_box($gid, $siteURL, $date_range, $enabled_modules, $mediums_data);
    $output .= seotools_dashboard_pageviews_box($gid, $siteURL, $date_range, $enabled_modules, $mediums_data);
    $output .= '</div>' . "\n";
    $output .= '</div>' . "\n";
  }
  else {
    $output .= seotools_generate_report_top_and_trends($rid, $labels[$rid], 'full', $gid, $siteURL, $date_range, $enabled_modules);
  }
  return $output;
}

function seotools_dashboard_analytics_box($gid, $siteURL, $date_range, $enabled_modules) {
  if(!$enabled_modules['google_analytics_api']) {
    return '';
  }
  if($output = seotools_cache_get('output_analytics_box', $date_range)) {
    $js = seotools_cache_get('js_analytics_box', $date_range);
    drupal_add_js( array('seotools' => $js), 'setting');
    return $output;
  }
  // Grab the data.
  if($rows = seotools_cache_get('data_ga_summary', $date_range, 6)) {
    $rows = unserialize($rows);
  }
  else {
    // for help with query see: http://code.google.com/apis/analytics/docs/gdata/gdataExplorer.html
    $request = array(
      '#dimensions' => array('date'),
      //'#metrics' => array('visits', 'pageviews', 'bounces', 'uniquePageviews'),
      '#metrics' => array('visits', 'pageviews', 'timeOnSite', 'bounces', 'uniquePageviews', 'newVisits', 'goalCompletionsAll'),
      '#sort_metric' => array('date'),
      '#start_date' => $date_range['start_date'],
      '#end_date' => $date_range['end_date']
    );
    $rows = seotools_fetch_ga_data($request);
    seotools_cache_set('data_ga_summary', $rows, $date_range);
  }
  // Check for data.
  if (!$rows) {
    return '<p>No analytics data is currently available.</p>';
  }

  // Format and perform calculations to display charts.

  $totals = array(
    'visits' => 0,
    'goals' => 0,
    'pageviews' => 0,
    'average_pageviews' => 0,
    'bounces' => 0,
    'time_on_site' => 0,
    'vistor_type' => 0,
    'goals_per_visit' => 0,
  );
  $day_counts = array();
  foreach ($rows as $date => $row) {
    $day = array();
    $day_counts['visits'][] = $row['visits'];
    $totals['visits'] += $row['visits'];

    $day_counts['pageviews'][] = $row['pageviews'];
    $totals['pageviews'] += $row['pageviews'];

    $day_counts['average_pageviews'][] = $row['pageviews'] / ($row['visits'] ? $row['visits'] : 1);

    $day_counts['bounce_rate'][] = 100 * $row['bounces'] / ($row['uniquePageviews'] ? $row['uniquePageviews'] : 1);
    $totals['bounces'] += $row['bounces'];

    $day_counts['time_on_site'][] = $row['timeOnSite'] / ($row['visits'] ? $row['visits'] : 1);
    $totals['time_on_site'] += $row['timeOnSite'];

    $day_counts['vistor_type'][] = 100 * $row['newVisits'] / ($row['visits'] ? $row['visits'] : 1);
    $totals['vistor_type'] += $row['newVisits'];

    $day_counts['goals'][] = $row['goalCompletionsAll'];
    $totals['goals'] += $row['goalCompletionsAll'];

    $day_counts['goal_conversion_rate'][] = 100 * $row['goalCompletionsAll'] / ($row['visits'] ? $row['visits'] : 1);

    $chart_dates[] = date('d', strtotime($date));
  }

  $output .= '<h4 id="chart-main-title">' . t('Visits') . '</h4>';
  $output .= '<div class="chart-main-wrapper">';
  //$output .= '<img src="' . $chart . '" />';
  $output .= '</div>';

  $output .= '<h3>' . t('Site Usage') . '</h3>';

  $links[] = l(t('analytics'), 'https://www.google.com/analytics/reporting/dashboard', array('query' => "id=$gid", 'attributes' => array('target' => 'googleanalytics')));
  $links[] = l(t('webmaster tools'), 'https://www.google.com/webmasters/tools/dashboard', array('query' => "siteUrl=$siteURL#", 'attributes' => array('target' => 'googlewebmastertools')));


  $output .= '<div class="dashboard-links">';
  $output .= implode(' | ', $links);
  $output .= '</div>';

  $totals['time_on_site'] = seotools_format_time_on( $totals['time_on_site'] / $totals['visits']);
  $totals['bounce_rate'] = number_format($totals['bounces'] / ($totals['visits'] ? $totals['visits'] : 1) * 100, 2) . "%";
  $totals['vistor_type'] = number_format($totals['vistor_type'] / ($totals['visits'] ? $totals['visits'] : 1) * 100, 2) . "%";
  $totals['visits'] = number_format($totals['visits']);
  $totals['pageviews'] = number_format($totals['pageviews']);
  $totals['average_pageviews'] = number_format($totals['pageviews'] / ($totals['visits'] ? $totals['visits'] : 1), 2);
  $totals['goals'] = number_format($totals['goals']);
  $totals['goal_conversion_rate'] = number_format($totals['goals'] / ($totals['visits'] ? $totals['visits'] : 1) / 10, 2) . "%";


  $cells = array(
    'visits' => t('Visits'),
    'bounce_rate' => t('Bounce Rate'),
    'pageviews' => t('Pageviews'),
    'time_on_site' => t('Avg. Time on Site'),
    'average_pageviews' => t('Pages/Visit'),
    'vistor_type' => t('% New Visits'),
    'goals' => t('Goals'),
    'goal_conversion_rate' => t('Goal Conversion'),
  );
  foreach($cells AS $key => $title) {
    $output .= '<div id="' . $key . '-cell" class="dashboard-ga-cell">' . "\n";
    $output .= '<a href="#" onclick="seotools_show_main_chart(\'' . $key . '_main\')">';
    $output .= chart_render(_seotools_reports_micro_chart($key . '_micro', '', $day_counts[$key], $chart_dates));
    $output .= '</a>';
    $output .= ' ' . $totals[$key];
    $queryadd = '';
    if($key == 'goal_conversion_rate') {
      $queryadd = '&goal=-1';
    }
    $output .= ' ' . l($title, 'https://www.google.com/analytics/reporting/' . $key, array('query' => "id=$gid$queryadd", 'attributes' => array('target' => 'googleanalytics')));
    $output .= '</div>' . "\n";
    $id = $key . '_main';
    $chart = chart_url(_seotools_reports_liquid_chart($id, '', $day_counts[$key], $chart_dates));
    $js['charts'][$id] = array(
      'src' => $chart,
      'location' => 'chart-main',
      'title' => $title,
    );
    if($id != 'visits_main') {
      $js['charts'][$id]['load_only'] = 1;
    }
  }
  drupal_add_js( array('seotools' => $js), 'setting');
  seotools_cache_set('js_analytics_box', $js, $date_range);
  seotools_cache_set('output_analytics_box', $output, $date_range);
  return $output;
}

function seotools_format_time_on($time) {
  $h = floor($time / 3600);
  $m = floor(($time - ($h * 3600)) / 60);
  $s = $time % 60;
  return (($h < 10)?'0':'')."$h:".(($m < 10)?'0':'')."$m:".(($s < 10)?'0':'').$s;
}

function seotools_get_dates($code = 30) {
  $date_range = array();
  $date_range['days'] = $code;
  if($code == 1) {
    $date_range['start_date'] = strtotime('-1 days');
    $date_range['end_date'] = strtotime('-1 days');
  }
  else if($code == 0) {
    $date_range['start_date'] = strtotime();
    $date_range['end_date'] = time();
    $date_range['days'] = .5;
  }
  else if($code == 7) {
    $date_range['start_date'] = strtotime('-7 days');
    $date_range['end_date'] = strtotime('-1 days');
  }
  else if($code == 6) {
    $date_range['start_date'] = strtotime('-7 days');
    $date_range['end_date'] = time();
    $date_range['days'] = 6.5;
  }
  else if($code == 90) {
    $date_range['start_date'] = strtotime('-90 days');
    $date_range['end_date'] = strtotime('-1 days');
  }
  else if($code == 89) {
    $date_range['start_date'] = strtotime('-90 days');
    $date_range['end_date'] = time();
    $date_range['days'] = 90.5;
  }
  else if($code == 365) {
    $date_range['start_date'] = strtotime('-365 days');
    $date_range['end_date'] = strtotime('-1 days');
  }
  else if($code == 364) {
    $date_range['start_date'] = strtotime('-364 days');
    $date_range['end_date'] = time();
    $date_range['days'] = 364.5;
  }
  else if($code == 29) {
    $date_range['start_date'] = strtotime('-29 days');
    $date_range['end_date'] = time();
    $date_range['days'] = 29.5;
  }
  else {
    $date_range['start_date'] = strtotime('-30 days');
    $date_range['end_date'] = strtotime('-1 days');
  }
  $date_range['start_date'] = date("Y-m-d", $date_range['start_date']);
  $date_range['end_date'] = date("Y-m-d", $date_range['end_date']);
  return $date_range;
}

function seotools_cache_get($cid, $date_range = NULL, $records = NULL) {
  // don't cache if end date is today
  if($date_range['end_date'] == date("Y-d-m")) {
    return FALSE;
  }
  $where = "cid = '%s'";
  $args[] = $cid;
  if($date_range['start_date']) {
    $where .= " AND start_date = '%s'";
    $args[] = $date_range['start_date'];
  }
  if($date_range['end_date']) {
    $where .= " AND end_date = '%s'";
    $args[] = $date_range['end_date'];
  }
  if($records) {
    $where .= " AND records >= %d";
    $args[] = $records;
  }
  $sql = "
    SELECT data
    FROM {seotools_cache}
    WHERE $where
  ";
  $data = db_result(db_query($sql, $args));
  if($data) {
    $ret = unserialize($data);
    return $ret;
  }
  else {
    return FALSE;
  }
}

function seotools_cache_set($cid, $data, $date_range = NULL) {
  $where = "cid = '%s'";
  $args[] = $cid;

  if($date_range['start_date']) {
    $fields .= ", start_date";
    $values .= ", '%s'";
    $where .= " AND start_date = '%s'";
    $args[] = $date_range['start_date'];
  }
  if($date_range['end_date']) {
    $fields .= ", end_date";
    $values .= ", '%s'";
    $where .= " AND end_date = '%s'";
    $args[] = $date_range['end_date'];
  }
  $sql = "
    DELETE FROM {seotools_cache}
    WHERE $where
  ";
  db_query($sql, $args);
  if(is_array($data)) {
    $fields .= ", records";
    $values .= ", %d";
    $args[] = count($data);
  }
  $args[] = serialize($data);
  $sql = "
    INSERT INTO {seotools_cache}
    (cid$fields, data)
    VALUES
    ('%s'$values,'%s')
  ";
  db_query($sql, $args);
  return TRUE;
}



function _seotools_reports_liquid_chart($id, $title, $data, $dates) {
  $chart = array(
    '#chart_id' => $id,
    '#title' => '',
    '#type' => CHART_TYPE_LINE,
    '#size' => chart_size(600, 150),
    '#adjust_resolution' => TRUE,
    '#data_colors' => chart_data_colors(array('0077CC')),
    '#line_styles' => array(chart_line_style(3, 10, 0)),
    '#shape_markers' => array(chart_shape_marker(0, -1, 'o', 9, '0077CC')),
    '#grid_lines' => chart_grid_lines(0, 20, 1, 3),
  );
  $chart['#data'] = $data;
  $chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0][] = chart_mixed_axis_range_label(0, max($data));
  foreach ($dates as $date) {
    $chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][1][] = chart_mixed_axis_label($date);
  }
  return $chart;
}

function _seotools_reports_multiline_chart($id, $title, $data, $dates, $colors) {
  $shade_colors = array(
    '058DC7' => 'E8F8FF',
    '50B432' => 'DDF4D7',
    'ED561B' => 'FCE4D9',
    'EDEF00' => 'FFFFD6'
  );
  $line_styles = array();
  $shape_markers = array();
  $i = 0;
  foreach($data AS $series) {
    $line_styles[] = chart_line_style(3);
    //$shape_markers[] = chart_shape_marker($i, -1, 'B', 6, $colors[$i]);
    $shape_markers[] = chart_shape_marker($i, -1, 'B', 6, $shade_colors[$colors[$i]]);
    $i++;
  }
  $chart = array(
    '#chart_id' => $id,
    '#title' => '',
    '#type' => CHART_TYPE_LINE,
    '#size' => chart_size(600, 150),
    '#adjust_resolution' => TRUE,
    '#data_colors' => $colors,
    '#line_styles' => $line_styles,
    '#shape_markers' => $shape_markers,
    '#grid_lines' => chart_grid_lines(0, 20, 1, 3),
  );
  $chart['#data'] = $data;
  $chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0][] = chart_mixed_axis_range_label(0, max($data));
  foreach ($dates as $date) {
    $chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][1][] = chart_mixed_axis_label($date);
  }
  return $chart;
}

function _seotools_reports_micro_chart($id, $title, $data, $dates) {
  $chart = array(
    '#chart_id' => $id,
    '#title' => '',
    '#type' => CHART_TYPE_LINE,
    '#size' => chart_size(80, 20),
    '#adjust_resolution' => TRUE,
    '#data_colors' => array('0077cc'),
    '#line_styles' => array(chart_line_style(2, 10, 0)),
    '#shape_markers' => array(chart_shape_marker(0, -1, 'B', 9, 'E8F8FF')),
    //'#grid_lines' => chart_grid_lines(0, 20, 1, 3),
  );
  $chart['#data'] = $data;
  //$chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0][] = chart_mixed_axis_range_label(0, max($data));
  foreach ($dates as $date) {
    //$chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][1][] = chart_mixed_axis_label($date);
  }
  return $chart;
}

/*
 * Function to collect together data for different aliases.
 */
function seotools_fetch_ga_data($request,  $group_by = 'date') {
  $data = google_analytics_api_report_data($request);

  // Add up all the statistics for different paths.
  $rows = array();
  foreach ($data as $item) {
    $dimensions = $item->getDimensions();
    if (is_array($group_by)) {
      $group_name = '';
      foreach ($group_by as $group_by_item) {
        $group_name .= $dimensions[$group_by_item];
      }
    }
    else {
      $group_name = $dimensions[$group_by];
    }
    if (isset($rows[$group_name])) {
      foreach ($item->getMetrics() as $key => $value) {
        $rows[$group_name][$key] += $value;
      }
    }
    else {
      $rows[$group_name] = $item->getMetrics();
    }
  }
  return $rows;
}
/**
 * valid ids: keywords
 * @param unknown_type $id
 * @param unknown_type $label
 * @param unknown_type $mode
 * @param unknown_type $gid
 * @param unknown_type $siteURL
 * @param unknown_type $date_range
 * @param unknown_type $enabled_modules
 */
function seotools_generate_report_top_and_trends($id, $label, $mode, $gid, $siteURL, $date_range, $enabled_modules) {
  $page_link_icon = '<img src="' . base_path() . drupal_get_path('module', 'seotools') . '/images/url_icon.gif">';
  if($mode == 'full') {
    $top_style = variable_get('seotools_report_top_' . $id . '_style', SEOTOOLS_REPORT_STYLE_DEFAULT);
    $top_row_count = variable_get('seotools_report_top_' . $id . '_rows', SEOTOOLS_REPORT_ROWS_DEFAULT); 
    $top_row_count_ext = $top_row_count + 10;  
    $trend_style = variable_get('seotools_report_top_' . $id . '_style', SEOTOOLS_REPORT_STYLE_DEFAULT);
    $trend_row_count = variable_get('seotools_report_top_' . $id . '_rows', SEOTOOLS_REPORT_ROWS_DEFAULT); 
    $trend_row_count_ext = $trend_row_count + 10;   
  } else {
    $top_style = variable_get('seotools_report_top_' . $id . '_dashboard_style', SEOTOOLS_REPORT_DASHBOARD_STYLE_DEFAULT);
    $top_row_count = variable_get('seotools_report_top_' . $id . '_dashboard_rows', SEOTOOLS_REPORT_DASHBOARD_ROWS_DEFAULT);
    $top_row_count_ext = $top_row_count + 200;
    $trend_style = variable_get('seotools_report_top_' . $id . '_dashboard_style', SEOTOOLS_REPORT_DASHBOARD_STYLE_DEFAULT);
    $trend_row_count = variable_get('seotools_report_top_' . $id . '_dashboard_rows', SEOTOOLS_REPORT_DASHBOARD_ROWS_DEFAULT);
    $trend_row_count_ext = $trend_row_count + 200;
  }
  $style = 'simple';
  if(($top_row_count && $top_style != 'simple') || ($trend_row_count && $trend_style != 'simple')) {
    $style = 'full';
  } 
  $row_count_ext = $top_row_count_ext;
  if ($trend_row_count && ($trend_row_count_ext > $row_count_ext)) {
    $row_count_ext = $trend_row_count_ext;
  }
  if($row_count_ext > 1000) {
    $row_count_ext = 1000;
  }
  
  // configure ga request
  $metrics = array('visits');
  $sort_metric = array('-visits');
  $count = 'visits';
  if ($id == 'keywords') {
    $dimensions = array('keyword');
  }
  else if ($id == 'entrances') {
    $dimensions = array('pagePath');
  }
  else if ($id == 'sources') {
    $dimensions = array('source');
  } 
  else if ($id == 'referrers') {
    $dimensions = array('source', 'referralPath');
  }  
  else if ($id == 'pageviews') {
    $dimensions = array('pagePath');
    $metrics = array('pageviews');
    $sort_metric = array('-pageviews');
    $count = 'pageviews';
  }    

  if(!$data = seotools_cache_get('data_ga_' . $id, $date_range, $row_count_ext)) {
    // for help with query see: http://code.google.com/apis/analytics/docs/gdata/gdataExplorer.html
    $request = array(
      '#dimensions' => $dimensions,
      '#metrics' => $metrics,
      '#sort_metric' => $sort_metric,
      '#max_results' => $row_count_ext,
      '#start_date' => $date_range['start_date'],
      '#end_date' => $date_range['end_date']
    );
    $data = seotools_fetch_ga_data($request, $dimensions);
    seotools_cache_set('data_ga_' . $id, $data, $date_range);
  }

  if($style == 'full') {
    // get yesterday's data
    if(!$yesterdays_data = seotools_cache_get('data_ga_' . $id . '_yesterday', $date_range, $row_count_ext)) {
      // for help with query see: http://code.google.com/apis/analytics/docs/gdata/gdataExplorer.html
      $request = array(
        '#dimensions' => $dimensions,
        '#metrics' => $metrics,
        '#sort_metric' => $sort_metric,
        '#max_results' => $row_count_ext,
        '#start_date' => date("Y-m-d", strtotime('-1 days')),
        '#end_date' => date("Y-m-d", strtotime('-1 days'))
      );
      $yesterdays_data = seotools_fetch_ga_data($request, $dimensions);
      seotools_cache_set('data_ga_' . $id . '_yesterday', $yesterdays_data, $date_range);
    }
  
    // get last weeks data
    if(!$aweekago_data = seotools_cache_get('data_ga_' . $id . '_aweekago', $date_range, $row_count_ext)) {
      // for help with query see: http://code.google.com/apis/analytics/docs/gdata/gdataExplorer.html
      $request = array(
        '#dimensions' => $dimensions,
        '#metrics' => $metrics,
        '#sort_metric' => $sort_metric,
        '#max_results' => $row_count_ext,
        '#start_date' => date("Y-m-d", strtotime('-7 days')),
        '#end_date' => date("Y-m-d", strtotime('-7 days'))
      );
      $aweekago_data = seotools_fetch_ga_data($request, $dimensions);
      seotools_cache_set('data_ga_' . $id . '_aweekago', $aweekago_data, $date_range);
    }
  }
  if($style == 'full' || $trend_row_count) {
    // get today's data
    $request = array(
      '#dimensions' => $dimensions,
      '#metrics' => $metrics,
      '#sort_metric' => $sort_metric,
      '#max_results' => $row_count_ext,
      '#start_date' => date("Y-m-d"),
    );
    $todays_data = seotools_fetch_ga_data($request, $dimensions);  
  }
  
  $site_domain = $_SERVER['HTTP_HOST'];
  $kw_priority_options = kwresearch_get_priority_options();
  $c = 1;
  foreach($data AS $key => $value) {
    $row = array();
    if($id == 'keywords') {
      if($key == '(not set)') {
        continue;
      }
      $row[] =  l(seotools_format_text_data($key), 'https://www.google.com/analytics/reporting/keyword_detail', array('query' => "id=$gid&d1=$keyword", 'attributes' => array('target' => 'googleanalytics')));
      if($enabled_modules['kwresearch']) {
        $kw_obj = kwresearch_load_site_keyword($key);
        $row[] =  array(
          'data' => l((($kw_obj->priority) ? $kw_obj->priority . '%' : 'ns') , 'admin/content/kwresearch/keyword_list/edit', array('query' => "keyword=$key", 'attributes' => array('target' => 'kwreserach', 'title' => $kw_priority_options[$kw_obj->priority]))),
          'class' => 'text-cell',
        );  
      }
    } 
    else if ($id == 'entrances') {
      $path = str_replace($base_path, '', $key);
      if($path == '') {
        $path = '<front>';
      }

      $row[] = l(seotools_format_text_data($key), 'https://www.google.com/analytics/reporting/entrances', array('query' => "id=$gid&d1=$key", 'attributes' => array('target' => 'googleanalytics')));
      if($enabled_modules['linkintel']) {
        $page_settings = linkintel_load_page_settings($path);
        $row[] = array(
          'data' => l((($page_settings->priority) ? $page_settings->priority . '%' : 'ns') , 'admin/content/linkintel/page/edit', array('query' => "pid=$path", 'attributes' => array('target' => 'linkintel'))),
          'class' => 'text-cell',
        );
      }      
    }  
    else if ($id == 'sources') { 
      $fsource = $key;
      if($source == '(none)') {
        $fsource = 'direct';
      }
      $row[] = l(seotools_format_text_data($fsource), 'https://www.google.com/analytics/reporting/referring_source_detail', array('query' => "id=$gid&d1=$key", 'attributes' => array('target' => 'googleanalytics')));
    }
    else if ($id == 'referrers') {
      if(strpos($key, '(not set)') !== FALSE) {
        continue;
      }
      $row[] = l($page_link_icon, 'http://' . $key, array('html' => TRUE, 'attributes' => array('target' => '_blank')))
        . ' ' . l(seotools_format_text_data($key), 'https://www.google.com/analytics/reporting/referring_link_detail', array('query' => "id=$gid&d1=$key", 'attributes' => array('target' => 'googleanalytics')));
      
    }  
    else if ($id == 'pageviews') {
      $row[] =l($page_link_icon, 'http://' . $site_domain . $key, array('html' => TRUE, 'attributes' => array('target' => '_blank')))
        . ' ' . l(seotools_format_text_data($key), 'https://www.google.com/analytics/reporting/content_detail', array('query' => "id=$gid&d1=$key", 'attributes' => array('target' => 'googleanalytics')));
    }
    $row[] = array(
        'data' => number_format($value[$count]),
        'class' => 'numeric-cell',
      );
    if($top_style == 'full') {
      $today = '-';
      if($todays_data[$key]) {
        $today = number_format($todays_data[$key][$count]);
      }
      $yesterday = '-';
      if($yesterdays_data[$key]) {
        $yesterday = number_format($yesterdays_data[$key][$count]);
      }
      $aweekago = '-';
      if($aweekago_data[$key]) {
        $aweekago = number_format($aweekago_data[$key][$count]);
      }
      $row[] = array(
        'data' => number_format($value[$count] / $date_range['days'], 0),
        'class' => 'numeric-cell',
      );
      $row[] = array(
        'data' => $aweekago,
        'class' => 'numeric-cell',
      );
      $row[] = array(
        'data' => $yesterday,
        'class' => 'numeric-cell',
      );
      $row[] = array(
        'data' => $today,
        'class' => 'numeric-cell',
      );
    }
    $rows[] = $row;
    $c++;
    if($c > $top_row_count) {
      break;
    }
  }
  $header = array();
  $header[] = array('data' => t('Top') . ' ' . $label, 'class' => 'label-header');
  if(($id == 'keywords' && $enabled_modules['kwresearch']) || ($id == 'entrances' && $enabled_modules['linkintel'])) {
    $header[] = array('data' => t('Prty'), 'class' => 'text-header');
  }
  $header[] = array('data' => t('Visits'), 'class' => 'numeric-header');
  if($top_style == 'full') {
    $header[] = array('data' => t('/day'), 'class' => 'numeric-header');
    $header[] = array('data' => t('Wkago'), 'class' => 'numeric-header');
    $header[] = array('data' => t('Yda'), 'class' => 'numeric-header');
    $header[] = array('data' => t('Today'), 'class' => 'numeric-header');
  }

  $output .= theme('table', $header, $rows, array('id' => 'seotools-report-top-' . $id . '-' . $mode));

  if(!is_array($todays_data)) {
    return $output;
  }
  // Trending data
  $c = 1;
  $rows = array();
  foreach($todays_data AS $key => $value) {
    $row = array();
    if($id == 'keywords') {
      if($key == '(not set)') {
        continue;
      }
      $row[] = l(seotools_format_text_data($key), 'https://www.google.com/analytics/reporting/keyword_detail', array('query' => "id=$gid&d1=$source", 'attributes' => array('target' => 'googleanalytics')));
      if($enabled_modules['kwresearch']) {
        $kw_obj = kwresearch_load_site_keyword($key);
        $row[] =  array(
          'data' => l((($kw_obj->priority) ? $kw_obj->priority . '%' : 'ns') , 'admin/content/kwresearch/keyword_list/edit', array('query' => "keyword=$key", 'attributes' => array('target' => 'kwreserach', 'title' => $kw_priority_options[$kw_obj->priority]))),
          'class' => 'text-cell',
        );  
      }
    }
    else if ($id == 'entrances') {
      $path = str_replace($base_path, '', $key);
      if($path == '') {
        $path = '<front>';
      }      
      $row[] = l(seotools_format_text_data($key), 'https://www.google.com/analytics/reporting/entrances', array('query' => "id=$gid&d1=$key", 'attributes' => array('target' => 'googleanalytics')));
      if($enabled_modules['linkintel']) {
        $page_settings = linkintel_load_page_settings($path);
        $row[] = array(
          'data' => l((($page_settings->priority) ? $page_settings->priority . '%' : 'ns') , 'admin/content/linkintel/page/edit', array('query' => "pid=$path", 'attributes' => array('target' => 'linkintel'))),
          'class' => 'text-cell',
        ); 
      }     
    }
    else if ($id == 'sources') {
      $fsource = $key;
      if($source == '(none)') {
        $fsource = 'direct';
      }
      $row[] =  l(seotools_format_text_data($fsource), 'https://www.google.com/analytics/reporting/referring_source_detail', array('query' => "id=$gid&d1=$key", 'attributes' => array('target' => 'googleanalytics')));
    } 
      else if ($id == 'referrers') {
      if(strpos($key, '(not set)') !== FALSE) {
        continue;
      }
      $row[] =l($page_link_icon, 'http://' . $key, array('html' => TRUE, 'attributes' => array('target' => '_blank')))
        . ' ' . l(seotools_format_text_data($key), 'https://www.google.com/analytics/reporting/referring_link_detail', array('query' => "id=$gid&d1=$key", 'attributes' => array('target' => 'googleanalytics')));
    }
    else if ($id == 'pageviews') {
      $row[] =l($page_link_icon, 'http://' . $site_domain . $key, array('html' => TRUE, 'attributes' => array('target' => '_blank')))
        . ' ' . l(seotools_format_text_data($key), 'https://www.google.com/analytics/reporting/content_detail', array('query' => "id=$gid&d1=$key", 'attributes' => array('target' => 'googleanalytics')));
    }      
    $row[] = array(
        'data' => number_format($value[$count]),
        'class' => 'numeric-cell',
      );
    if($trend_style == 'full') {
      $yesterday = '-';
      if($yesterdays_data[$key]) {
        $yesterday = number_format($yesterdays_data[$key][$count]);
      }
      $aweekago = '-';
      if($aweekago_data[$key]) {
        $aweekago = number_format($aweekago_data[$key][$count]);
      }
      $histavg = '-';
      if($data[$key]) {
        $histavg = number_format($data[$key][$count] / $date_range['days'], 0);
      }
      $row[] = array(
        'data' => $histavg,
        'class' => 'numeric-cell',
      );
      $row[] = array(
        'data' => $aweekago,
        'class' => 'numeric-cell',
      );
      $row[] = array(
        'data' => $yesterday,
        'class' => 'numeric-cell',
      );
    }
    $rows[] = $row;
    $c++;
    if($c > $trend_row_count) {
      break;
    }
  }
  
  $header = array();
  $header[] = array('data' => t('Trending') . ' ' . $label, 'class' => 'label-header');
  if(($id == 'keywords' && $enabled_modules['kwresearch']) || ($id == 'entrances' && $enabled_modules['linkintel'])) {
    $header[] = array('data' => t('Prty'), 'class' => 'text-header');
  }
  $header[] = array('data' => t('Today'), 'class' => 'numeric-header');
  if($top_style == 'full') {
    $header[] = array('data' => t('/day'), 'class' => 'numeric-header');
    $header[] = array('data' => t('Wkago'), 'class' => 'numeric-header');
    $header[] = array('data' => t('Yda'), 'class' => 'numeric-header');
  }
  $output .= theme('table', $header, $rows, array('id' => 'seotools-report-trend-' . $id . '-' . $mode));
  
  return $output;
}

function seotools_dashboard_keywords_box($gid, $siteURL, $date_range, $enabled_modules) {

  $output = '<h3 class="keywords">' . t('Keywords') . '</h3>';

  $links[] = l(t('report'), 'admin/content/seotools/keywords');
  $links[] = l(t('analytics'), 'https://www.google.com/analytics/reporting/keywords', array('query' => "id=$gid", 'attributes' => array('target' => 'googleanalytics')));
  if($enabled_modules['kwresearch']) {
    $links[] = l(t('research'), 'admin/content/kwresearch/keyword_report', array('attributes' => array('target' => 'kwresearch')));
  }
  $links[] = l(t('search queries'), 'https://www.google.com/webmasters/tools/top-search-queries', array('query' => "siteUrl=$siteURL#", 'attributes' => array('target' => 'googlewebmastertools')));
  $links[] = l(t('found'), 'https://www.google.com/webmasters/tools/keywords', array('query' => "siteUrl=$siteURL#", 'attributes' => array('target' => 'googlewebmastertools')));


  $output .= '<div class="dashboard-links">';
  $output .= implode(' | ', $links);
  $output .= '</div>';
  
  $output .= seotools_generate_report_top_and_trends('keywords', t('keywords'), $mode, $gid, $siteURL, $date_range, $enabled_modules);
  
  // By priority
  $filter = array();
  $options['mode'] = 'site';
  $header[] = array('data' => t('Priority'), 'field' => 'k.priority', 'sort' => 'desc');
  $result = kwresearch_load_filtered_keyword_result($filter, $options, $header = array(), $limit = 100000);
  $kw_counts = array(
    'top' => 0,
    'high' => 0,
    'standard' => 0,
    'total' => 0,
  );
  while($row = db_fetch_object($result)) {
    $kw_counts['total']++;
    if ($row->priority > 80) {
      $kw_counts['top']++;
    }
    else if ($row->priority > 60) {
      $kw_counts['high']++;
    }
    else if ($row->priority > 40) {
      $kw_counts['standard']++;
    }
  }
  $rows = array();
  $header = array(
    array('data' => t('Keywords by priority'), 'class' => 'label-header'),
    array('data' => t('Count'), 'class' => 'numeric-header')
  );

  $rows[] = array(
    l(t('All site keywords'), 'admin/content/kwresearch/keyword_list/site'),
    array(
      'data' => number_format($kw_counts['total']),
      'class' => 'numeric-cell',
    ),
  );
  $rows[] = array(
    '&nbsp;&nbsp;' . l(t('Top'), 'admin/content/kwresearch/keyword_list/site', array('query' => 'filters={"priority":90}', 'attributes' => array('target' => 'kwresearch'))),
    array(
      'data' => number_format($kw_counts['top']),
      'class' => 'numeric-cell',
    ),
  );
  $rows[] = array(
    '&nbsp;&nbsp;' . l(t('High'), 'admin/content/kwresearch/keyword_list/site', array('query' => 'filters={"priority":70}', 'attributes' => array('target' => 'kwresearch')))
    . '|' . l(t('& up'), 'admin/content/kwresearch/keyword_list/site', array('query' => 'filters={"priority":{"1":90,"2":70}}', 'attributes' => array('target' => 'kwresearch'))),
    array(
      'data' => number_format($kw_counts['high']),
      'class' => 'numeric-cell',
    ),
  );
  $rows[] = array(
    '&nbsp;&nbsp;' . l(t('Standard'), 'admin/content/kwresearch/keyword_list/site', array('query' => 'filters={"priority":50}', 'attributes' => array('target' => 'kwresearch')))
    . '|' . l(t('& up'), 'admin/content/kwresearch/keyword_list/site', array('query' => 'filters={"priority":{"1":90,"2":70,"3":50}}', 'attributes' => array('target' => 'kwresearch'))),
    array(
      'data' => number_format($kw_counts['standard']),
      'class' => 'numeric-cell',
    ),
  );
  $output .= theme('table', $header, $rows, array('id' => 'seotools-dashboard-keyword-box'));
  return $output;
}

function seotools_dashboard_entrances_box($gid, $siteURL, $date_range, $enabled_modules) {
  $output = '<h3 class="content">' . t('Entry pages') . '</h3>';

  $links[] = l(t('report'), 'admin/content/seotools/entrances');
  $links[] = l(t('analytics'), 'https://www.google.com/analytics/reporting/entrances', array('query' => "id=$gid", 'attributes' => array('target' => 'googleanalytics')));
  $links[] = l(t('optimize'), 'admin/reports/seo/contentanalysis', array('query' => "sort=desc&order=Quick+SEO", 'attributes' => array('target' => 'seo_friend')));
  $links[] = l(t('html suggestions'), 'https://www.google.com/webmasters/tools/html-suggestions', array('query' => "siteUrl=$siteURL#", 'attributes' => array('target' => 'googlewebmastertools')));
  $links[] = l(t('crawl errors'), 'https://www.google.com/webmasters/tools/crawl-errors', array('query' => "siteUrl=$siteURL#", 'attributes' => array('target' => 'googlewebmastertools')));

  $output .= '<div class="dashboard-links">';
  $output .= implode(' | ', $links);
  $output .= '</div>';

  $output .= seotools_generate_report_top_and_trends('entrances', t('landing pages'), $mode, $gid, $siteURL, $date_range, $enabled_modules);
  // By priority report
  if($enabled_modules['linkintel']) {
    $header[] = array('data' => t('Priority'), 'field' => 'effective_priority', 'sort' => 'desc');
    $result = linkintel_load_filtered_pages_result($filter, $options, $header = array(), $limit = 100000);
    $counts = array(
      'top' => 0,
      'high' => 0,
      'standard' => 0,
      'total' => 0,
    );
    while($row = db_fetch_object($result)) {
      $counts['total']++;
      if ($row->effective_priority > 80) {
        $counts['top']++;
      }
      else if ($row->effective_priority > 60) {
        $counts['high']++;
      }
      else if ($row->effective_priority > 40) {
        $counts['standard']++;
      }
    }
    $rows = array();
    $header = array(
      array('data' => t('By priority'), 'class' => 'label-header'),
      array('data' => t('Count'), 'class' => 'numeric-header'),
    );
  
    $rows[] = array(
      l(t('All prioritized pages'), 'admin/content/linkintel/pages'),
      array(
        'data' => number_format($counts['total']),
        'class' => 'numeric-cell',
      ),
    );
    $rows[] = array(
      '&nbsp;&nbsp;' . l(t('Top'), 'admin/content/linkintel/pages', array('query' => 'filters={"priority":90}', 'attributes' => array('target' => 'linkintel'))),
      array(
        'data' => number_format($counts['top']),
        'class' => 'numeric-cell',
      ),
    );
    $rows[] = array(
      '&nbsp;&nbsp;' . l(t('High'), 'admin/content/linkintel/pages', array('query' => 'filters={"priority":70}', 'attributes' => array('target' => 'linkintel')))
      . '|' . l(t('& up'), 'admin/content/linkintel/pages', array('query' => 'filters={"priority":{"1":90,"2":70}}', 'attributes' => array('target' => 'linkintel'))),
      array(
        'data' => number_format($counts['high']),
        'class' => 'numeric-cell',
      ),
    );
    $rows[] = array(
      '&nbsp;&nbsp;' . l(t('Standard'), 'admin/content/linkintel/pages', array('query' => 'filters={"priority":50}', 'attributes' => array('target' => 'linkintel')))
      . '|' . l(t('& up'), 'admin/content/linkintel/pages', array('query' => 'filters={"priority":{"1":90,"2":70,"3":50}}', 'attributes' => array('target' => 'linkintel'))),
      array(
        'data' => number_format($counts['standard']),
        'class' => 'numeric-cell',
      ),
    );
    $output .= theme('table', $header, $rows, array('id' => 'seotools-dashboard-link-box'));
  }

  return $output;
}

function seotools_dashboard_sources_box($gid, $siteURL, $date_range, $enabled_modules, &$mediums_data) {
  // Query for browser usage information.

  $output = '<h3 class="referrers">' . t('Sources') . '</h3>';

  $links[] = l(t('report'), 'admin/content/seotools/sources');
  $links[] = l(t('analytics'), 'https://www.google.com/analytics/reporting/sources', array('query' => "id=$gid", 'attributes' => array('target' => 'googleanalytics')));
  $links[] = l(t('subscriber stats'), 'https://www.google.com/webmasters/tools/subscribers', array('query' => "siteUrl=$siteURL#", 'attributes' => array('target' => 'googlewebmastertools')));

  $output .= '<div class="dashboard-links">';
  $output .= implode(' | ', $links);
  $output .= '</div>';

  if(!$data = seotools_cache_get('data_ga_mediums', $date_range)) {
    $request = array(
      '#dimensions' => array('medium'),
      '#metrics' => array('visits'),
      '#sort_metric' => array('-visits'),
      '#max_results' => 20,
      '#start_date' => $date_range['start_date'],
      '#end_date' => $date_range['end_date']
    );
    $data = seotools_fetch_ga_data($request, 'medium');
    seotools_cache_set('data_ga_mediums', $data, $date_range);
  }

  $mediums = array();
  $total_visits = 0;
  foreach ($data as $key => $value) {
    if($key == '(none)') {
      $key = 'direct';
    }
    $total_visits += $value['visits'];
    $mediums[$key] = $value['visits'];
  }

  // Any browsers with a marketshare below 0.1% don't get shown.
  $filtered_mediums = array();
  $filtered_mediums_legend = array();
  $total_filtered = 0;
  $threshold = $total_visits * 0.01;

  arsort($mediums);
  $segments = 0;
  foreach ($mediums as $key => $value) {
    if($segments >= 3) {
      break;
    }
    if ($value > $threshold) {
      $percent = $value / $total_visits;
      $filtered_mediums[$key] = $percent;
      $filtered_mediums_legend[$key] = $key . " (" . number_format($value) . ")";
      $total_filtered  += $value;
      $segments++;
    }
  }
  $filtered_mediums['other'] = ($total_visits - $total_filtered) / $total_visits;
  $filtered_mediums_legend['other'] =  "other (" . number_format($total_visits - $total_filtered) . ")";

  // Create browser chart.
  $colors = seotools_get_data_colors();
  arsort($filtered_mediums);
  $mediums_data = array();
  $i=0;
  foreach($filtered_mediums AS $medium => $value) {
    $mediums_data[$medium] = $colors[$i];
    $i++;
  }
  $chart = array(
    '#chart_id' => 'medium_box',
    '#title' => '',
    '#type' => CHART_TYPE_PIE,
    '#size' => chart_size(300, 150),
    '#data_colors' => chart_data_colors($mediums_data),
    '#data' => $filtered_mediums,
    '#legends' => $filtered_mediums_legend,
  );

  $r_chart = chart_url($chart);
  $js['charts']['sources_pie'] = array(
    'src' => $r_chart,
    'location' => 'chart-sources',
  );
  drupal_add_js( array('seotools' => $js), 'setting');

  $output .= '<div class="chart-sources-wrapper">';
  //$output .= $r_chart;
  $output .= '</div>';

  $output .= seotools_generate_report_top_and_trends('sources', t('sources'), $mode, $gid, $siteURL, $date_range, $enabled_modules);

  return $output;
}

function seotools_dashboard_referrers_box($gid, $siteURL, $date_range, $enabled_modules, &$mediums_data) {
  $output = '<h3 class="referrers">' . t('Referrers') . '</h3>';

  $links[] = l(t('report'), 'admin/content/seotools/referrers');
  $links[] = l(t('analytics'), 'https://www.google.com/analytics/reporting/referring_sources', array('query' => "id=$gid", 'attributes' => array('target' => 'googleanalytics')));
  $links[] = l(t('backlinks'), 'https://www.google.com/webmasters/tools/external-links', array('query' => "siteUrl=$siteURL#", 'attributes' => array('target' => 'googlewebmastertools')));
  $links[] = l(t('internal links'), 'https://www.google.com/webmasters/tools/internal-links', array('query' => "siteUrl=$siteURL#", 'attributes' => array('target' => 'googlewebmastertools')));

  $output .= '<div class="dashboard-links">';
  $output .= implode(' | ', $links);
  $output .= '</div>';

  if(!$data = seotools_cache_get('data_ga_mediums_by_date', $date_range)) {
    // for help with query see: http://code.google.com/apis/analytics/docs/gdata/gdataExplorer.html
    $request = array(
      '#dimensions' => array('date', 'medium'),
      '#metrics' => array('visits'),
      '#sort_metric' => array('date'),
      '#start_date' => $date_range['start_date'],
      '#end_date' => $date_range['end_date']
    );
    $rows = seotools_fetch_ga_data($request, array('date','medium'));
    seotools_cache_set('data_ga_mediums_by_date', $data, $date_range);
  }

  $totals = array();
  $day_counts = array();
  $top_mediums = array_keys($mediums_data);
  foreach ($rows as $key => $row) {
    $date = substr($key, 0, 8);
    $medium = substr($key, 8);
    if($medium == '(none)') {
      $medium = 'direct';
    }
    if(in_array($medium, $top_mediums)) {
      $day_counts[$medium][$date] = $row['visits'];
    }
    else {
      $day_counts['other'][$date] += $row['visits'];
    }
    $chart_dates[$date] = date('d', strtotime($date));
  }
  // sort by most visits
  $dc = $day_counts;
  $day_counts = array();
  foreach($top_mediums AS $medium) {
    $day_counts[$medium] = $dc[$medium];
  }
  $colors = seotools_get_data_colors();
  $i = 0;
  $series_colors = array();
  foreach($day_counts AS $medium => $series) {
    $series_colors[] = $mediums_data[$medium];
  }
  $chart = chart_url(_seotools_reports_multiline_chart('mediums_by_day', '', $day_counts, $chart_dates, $series_colors));
  $js['charts']['mediums_by_day'] = array(
    'src' => $chart,
    'location' => 'chart-refferrers',
    'title' => '',
  );
  drupal_add_js( array('seotools' => $js), 'setting');
  $output .= '<div class="chart-refferrers-wrapper">';
  $output .= '</div>';

  $output .= seotools_generate_report_top_and_trends('referrers', t('referrers'), $mode, $gid, $siteURL, $date_range, $enabled_modules);

  return $output;
}

function seotools_dashboard_map_box($gid, $siteURL, $date_range, $enabled_modules, &$mediums_data) {
  // geographic data
  if(!$data = seotools_cache_get('data_ga_country', $date_range)) {
    $request = array(
      '#dimensions' => array('pagePath', 'country'),
      '#metrics' => array('pageviews'),
      '#sort_metric' => array('country', 'pagePath'),
      '#start_date' => $date_range['start_date'],
      '#end_date' => $date_range['end_date']
    );
    $data = seotools_fetch_ga_data($request, 'country');
    seotools_cache_set('data_ga_country', $data, $date_range);
  }
  $name_to_iso = countries_api_get_array('name', 'iso2');
  $countries = array();
  $max_pageviews = 0;
  foreach ($data as $key => $value) {
    $match = $name_to_iso[strtoupper($key)];
    if ($match) {
      $max_pageviews = max($max_pageviews, $value['pageviews']);
      $countries[$match] = $value['pageviews'];
    }
  }

  // Find out proportion share from 1-100 for each country.
  $countries_share = array();
  foreach ($countries as $key => $value) {
    $countries_share[$key] = round(($value / $max_pageviews) * 100);
  }

  // Create the geographical chart.
  $chart = array(
    '#chart_id' => 'countries',
    '#type' => CHART_TYPE_MAP,
    '#size' => chart_size(440, 220),
    '#georange' => 'world',
    '#countries' => array_keys($countries_share),
    '#data' => array_values($countries_share),
    '#data_colors' => array('ffffff', 'edf0d4', '13390a'),
  );

  $output .= '<h3>' . t('Map Overlay') . '</h3>';

  //$r_chart = chart_url($chart);
  $r_chart = chart_render($chart);
  $js['charts']['sources_map'] = array(
    'src' => $r_chart,
    'location' => 'chart-map',
  );
  // TODO figure out why js crashing
  //drupal_add_js( array('seotools' => $js), 'setting');

  $output .= '<div class="chart-map-wrapper">';
  $output .= $r_chart;
  $output .= '</div>';

  return $output;
}

function seotools_dashboard_pageviews_box($gid, $siteURL, $date_range, $enabled_modules) {
  $output = '<h3 class="content">' . t('Page views') . '</h3>';

  $links[] = l(t('report'), 'admin/content/seotools/pageviews');
  $links[] = l(t('analytics'), 'https://www.google.com/analytics/reporting/content', array('query' => "id=$gid", 'attributes' => array('target' => 'googleanalytics')));

  $output .= '<div class="dashboard-links">';
  $output .= implode(' | ', $links);
  $output .= '</div>';

  $output .= seotools_generate_report_top_and_trends('pageviews', t('page views'), $mode, $gid, $siteURL, $date_range, $enabled_modules);
  
  return $output;
}

function seotools_get_data_colors() {
  return array('058DC7','50B432','ED561B','EDEF00');
}

function seotools_format_text_data($text) {
  if(strlen($text) > 40) {
   return substr($text, 0, 40);
  }
  return $text;
}
