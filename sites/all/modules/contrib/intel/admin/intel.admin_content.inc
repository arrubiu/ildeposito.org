<?php
/**
 * @file
 * Report tabs assciated with nodes
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_node_tab_scorecard($node, $mode = 'entrance') {
  require_once './' . drupal_get_path('module', 'intel') . "/reports/intel.report_scorecard.inc";
  $type_name = node_type_get_name($node);
  drupal_set_title(t('<em>@type</em> scorecard: @title', array('@type' => $type_name, '@title' => $node->title)), PASS_THROUGH);
  
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
  $output .= intel_scorecard_report($filters, 'page', $mode);
  return $output;
}

function intel_node_tab_visitors($node, $mode = 'entrance') {
  require_once './' . drupal_get_path('module', 'intel') . "/reports/intel.report_visitor_list.inc";
  
  $type_name = node_type_get_name($node);
  drupal_set_title(t('<em>@type</em> visitors: @title', array('@type' => $type_name, '@title' => $node->title)), PASS_THROUGH);
  
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
  $output .= intel_visitor_list_report($filters, 'page', $mode);
  return $output;
}

function intel_node_tab_visits($node, $mode = 'pageview') {
  require_once './' . drupal_get_path('module', 'intel') . "/reports/intel.report_visit_list.inc";
  
  $type_name = node_type_get_name($node);
  drupal_set_title(t('<em>@type</em> visitors: @title', array('@type' => $type_name, '@title' => $node->title)), PASS_THROUGH);
  
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
  $output .= intel_visit_list_report($filters, 'page', $mode);
  return $output;
}