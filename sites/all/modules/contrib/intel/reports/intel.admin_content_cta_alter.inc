<?php
/**
 * @file
 * admin > content > calls to action enhancements
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_admin_content_cta_alter_js($cta_type = '') {
  require_once drupal_get_path('module', 'intel') . "/includes/intel.ga.inc";
  require_once drupal_get_path('module', 'intel') . "/includes/intel.page_data.inc";
  intel_include_library_file('ga/class.ga_model.php');
  intel_include_library_file("reports/class.report_view.php");
  
  $steps = array();
  $request = array(
    'dimensions' => array('ga:eventCategory', 'ga:eventAction', 'ga:eventLabel'),
    'metrics' => array('ga:totalEvents', 'ga:uniqueEvents', 'ga:eventValue'),
    'sort_metric' => '-ga:totalEvents',
    'start_date' => strtotime("-31 days"),
    'end_date' => strtotime("Yesterday"),
    'max_results' => 1000,
    'filter' => 'ga:eventCategory=~^cta *', // TODO this filter seems not to be working
  );

//dsm($request);  
  $data = google_analytics_api_report_data($request);
//dsm($data);

  $ctas = array();
  if (!empty($data->results) && is_array($data->results)) {
    foreach ($data->results AS $r) {
      $ctaid = '/' . $r['eventLabel'];
      if (!isset($ctas[$ctaid])) {
        $ctas[$ctaid] = array(
          'impressions' => array(
            'total' => 0,
            'unique' => 0,
          ),
          'clicks' => array(
            'total' => 0,
            'unique' => 0,
          ),
          'conversions' => array(
            'total' => 0,
            'unique' => 0,
          ),
        );
      }
      $cat = strtolower($r['eventCategory']);
      if (substr($cat, -1) == '!') {
        $cat = substr($cat, 0, -1);
      }
//dsm($cat);
      if ($cat == 'cta impression') {
        $ctas[$ctaid]['impressions']['total'] = $r['totalEvents'];
        $ctas[$ctaid]['impressions']['unique'] = $r['uniqueEvents'];
      }
      if ($cat == 'cta click') {
        $ctas[$ctaid]['clicks']['total'] = $r['totalEvents'];
        $ctas[$ctaid]['clicks']['unique'] = $r['uniqueEvents'];
      }
      if ($cat == 'cta conversion') {
        $ctas[$ctaid]['conversions']['total'] = $r['totalEvents'];
        $ctas[$ctaid]['conversions']['unique'] = $r['uniqueEvents'];
      }
      //$rows['/' . $r['eventLabel']] = '<td class="insight-pageviews">' . number_format($r['pageviews']) . '</td><td class="insight-entrances">' . number_format($r['entrances']) . '</td><td class="insight-goal-value">' . number_format($r['goalValueAll']) . '</td>';
    }
  }
  $rows = array();
  foreach ($ctas AS $cid => $data) {
    $row = '<td>' . number_format($data['impressions']['total']) . '</td>';
    $row .= '<td>' . number_format($data['clicks']['total']) . '</td>';
    if ((int)$data['impressions']['total']) {
      $row .= '<td>' . number_format(100 * $data['clicks']['total']/$data['impressions']['total'], 1) . '%</td>';
    }
    else {
      $row .= '<td>-</td>';
    }
    $row .= '<td>' . number_format($data['conversions']['total']) . '</td>';
    if ((int)$data['impressions']['total']) {
      $row .= '<td>' . number_format(100 * $data['conversions']['total']/$data['impressions']['total'], 1) . '%</td>';
    }
    else {
      $row .= '<td>-</td>';
    }
    $rows[$cid] = $row;
  }
  $output['rows'] = $rows;
  $output['rowcount'] = count($rows);

  drupal_json_output($output);
}