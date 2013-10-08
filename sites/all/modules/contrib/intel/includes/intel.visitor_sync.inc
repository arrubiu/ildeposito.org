<?php
/**
 * @file
 * Support for syncing visitor data accross various data sources
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_sync_visitordata($vtk, $request = array()) {  
  
  $visitor = intel_visitor_load($vtk);
  $statuses = array();
  $statuses['intel_ga'] = intel_ga_sync_visitordata($visitor);
  foreach (module_implements('intel_sync_visitordata') AS $module) {
    $function = $module . '_intel_sync_visitordata';
    $statuses[$module] = $function($visitor, $request);
  }  

  return $statuses;
}

function intel_work_sync_visitor_request_queue($runtime = 15) {
  intel_queue_sync_visitor_requests();

  $end = time() + $runtime;
  $queue = DrupalQueue::get('intel_sync_visitor_requests');
  while (time() < $end && ($item = $queue->claimItem())) {
    if (!empty($_GET['debug'])) {
      dsm('syncing from queue:');
      dsm($item);
    }
    intel_sync_visitor_request_worker($item->data);
    $queue->deleteItem($item);
  }
}

function intel_queue_sync_visitor_requests() {
  $items = variable_get('intel_sync_visitor_requests', array());
  if (count($items)) {
    $queue = DrupalQueue::get('intel_sync_visitor_requests');
    foreach ($items AS $i => $item) {
      if ($item->run_after < time()) {
        $queue->createItem($item);
        unset($items[$i]);
      }
    }
    variable_set('intel_sync_visitor_requests', $items);  
  }   
}



function intel_sync_visitor_request_worker($item) {
  static $requeues;
  if (!isset($requeues)) {
    $requeues = variable_get('intel_sync_visitor_requests', array());
  }
  // if run_after has not occured, requeue the item
  if ($item->run_after > time()) {
    $requeues[$item->vtk] = $item;
    variable_set('intel_sync_visitor_requests', $requeues);
    return;
  }
  $statuses = intel_sync_visitordata($item->vtk, $item); 
  $success = 1;
  // check status of each hook
  foreach ($statuses AS $module => $flag) {
    if (!$flag) {
      $success = 0;
      break;
    }
  }
  if (!$success) {
    if ($item->attempts >= ((!empty($_GET['debug'])) ? 10 : 4)) {
      //watchdog('l10i sync visitor major fail', t('Data could not be synced after 5 attempts. Canceling sync.') . "<br>\n<br>\n" . print_r($item, 1));
      return;
    }
    $item->attempts++;
    $item->run_after = time() + ((!empty($_GET['debug'])) ? 30 : 300);  // delay for at least 5 minutes
    $requeues[$item->vtk] = $item;
    variable_set('intel_sync_visitor_requests', $requeues);
  }
}

/**
 * Implements intel_sync_visitordata
 * @param unknown_type $visitor
 */
function intel_ga_sync_visitordata(&$visitor) {
dsm($visitor);
  require_once drupal_get_path('module', 'intel') . "/includes/intel.ga.inc";
  $gadata = intel_fetch_analytics_visitor_meta_data($visitor->vtkid);
  if (empty($gadata)) {
    return FALSE;
  }
//dsm($visitor); //dsm($gadata);  
  
  $visitor->setVar('data', 'location', $gadata['location']);
  $visitor->setVar('data', 'environment', $gadata['environment']);
  $visitor->setVar('ext', 'ga', $gadata);
  $visitor->merge();

  return TRUE;
}

function intel_calculate_distance($lat1, $lon1, $lat2, $lon2, $miles = TRUE) {
  $pi80 = M_PI / 180;
  $lat1 *= $pi80;
  $lon1 *= $pi80;
  $lat2 *= $pi80;
  $lon2 *= $pi80;
 
  $r = 6372.797; // mean radius of Earth in km
  $dlat = $lat2 - $lat1;
  $dlon = $lon2 - $lon1;
  $a = sin($dlat / 2) * sin($dlat / 2) + cos($lat1) * cos($lat2) * sin($dlon / 2) * sin($dlon / 2);
  $c = 2 * atan2(sqrt($a), sqrt(1 - $a));
  $km = $r * $c;
 
  return ($miles ? ($km * 0.621371192) : $km);
}