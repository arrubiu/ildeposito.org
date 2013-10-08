<?php
/**
 * @file
 * Administration of visitors
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_visitor_tab_scorecard($visitorid) {
  if (!intel_api_access()) {
    $output = intel_api_access_error($vars = array());
    return $output;
  }
  require_once drupal_get_path('module', 'intel') . "/reports/intel.report_scorecard.inc";  
 
  $visitor = intel_visitor_load($id);
  
  if ($visitor->getVar('ext', 'ga') && !$visitor->getVar('data', 'environment')) {
    require_once drupal_get_path('module', 'intel') . "/includes/intel.visitor_sync.inc";
    require_once drupal_get_path('module', 'intel') . "/includes/intel.ga.inc";
    intel_ga_sync_visitordata($visitor);
    drupal_set_message(t('Google Analytics data resynced.'));
  }
  
  drupal_set_title(t('Visitor scorecard: @title', array('@title' => $visitor->getLabel())), PASS_THROUGH);
 
  $filters = array(
   'visitor' => 'visitorid:' . $visitor->vtkid,
  );
 
  $output = '';
  $output .= intel_scorecard_report($filters, 'visitor'); 
 
  return $output;
}


function intel_visitor_tab_clickstream($id) {
  if (!intel_api_access()) {
    $output = intel_api_access_error($vars = array());
    return $output;
  }
  
  // TODO re-org clickstream report
  $file = drupal_get_path('module', 'intel') . "/reports/intel.report_visitor_clickstream.inc";
  if (file_exists($file)) {
    require_once $file;
  }
  else {
    drupal_set_message(t('Clickstream report not found. Comming soon.'));
    return '';
  }

  $visitor = intel_visitor_load($id);

  if ($visitor->getVar('ext', 'ga') && !$visitor->getVar('data', 'environment')) {
    require_once drupal_get_path('module', 'intel') . "/includes/intel.visitor_sync.inc";
    require_once drupal_get_path('module', 'intel') . "/includes/intel.ga.inc";
    intel_ga_sync_visitordata($visitor);
    drupal_set_message(t('Google Analytics data resynced.'));
  }
  
  drupal_set_title(t('Clickstream: @title', array('@title' => $visitor->getLabel())), PASS_THROUGH);
  
  $output = '';
  $output .= intel_visitor_clickstream($visitor->vtkid);
  
  return $output;
}

function intel_visitor_tab_submissions($visitorid) {
  require_once './' . drupal_get_path('module', 'intel') . "/admin/intel.admin_submission.inc";

  $visitor = intel_visitor_load_by_visitorid($visitorid, array());  
  
  $visitor_name = (!empty($visitor->name)) ? $visitor->name : $visitorid;
  drupal_set_title(t('Clickstream: @title', array('@type' => $visitor_name, '@title' => $visitor_name)), PASS_THROUGH);
  
  $output = '';
  $output .= intel_visitor_clickstream($visitorid);
  
  return $output;  
}

function intel_visitor_page($id) {
  if (!intel_api_access()) {
    $output = intel_api_access_error($vars = array());
    return $output;
  }
  $output = ''; 
  
  $visitor = intel_visitor_load($id); 

  drupal_set_title(t('Visitor: @title', array('@title' => $visitor->getLabel())), PASS_THROUGH);

  if (!$visitor->getVid()) {
    $msg = t('No contact data for this visitor was found locally.');
    $msg .= ' ' . t('This is likely becaused the visitor has not submitted a site form yet.');
    $msg .= "<br>\n" . t('You can still view data from Google Analytics using the !scorecard and !clickstream tabs.', array(
      '!scorecard' => l(t('Scorecard'), 'visitor/' . $visitorid . '/scorecard'),
      '!clickstream' => l(t('Clickstream'), 'visitor/' . $visitorid . '/clickstream'),
    ));
    drupal_set_message(check_plain($msg), 'warning');
  }
  else {
    $form = drupal_get_form('intel_visitor_contact_data_form', $visitor);
    $output = render($form);
  }
  if (!empty($_GET['debug'])) {
    try {
      $visitor->apiLoad();
    }
    catch (Exception $e) {
      drupal_set_message(t('Unable to load API visitor data'), 'warning');
    }
    dsm('$visitor=');
    dsm($visitor->getProperties());
  }
  return $output;  
}

function intel_visitor_contact_data_form($form, &$form_state, $visitor) {
  $form_state['visitor'] = $visitor;
//dsm($visitor->getProperties());  
  $visitor_data = $visitor->data;
  
  $mode = 'view';
  $form = array();
  
  $form['data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact data'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  
  if (!empty($visitor_data['contact']['photo'])) {
    $form['data']['photo'] = array(
      '#type' => ($mode == 'view') ? 'item' : 'textfield',
      '#title' => '',
      '#markup' => theme_intel_contact_property(array('type' => 'photo', 'data' => $visitor_data['contact']['photo'])),
    );
  }
  if (!empty($visitor_data['contact']['firstname'])) {
    $form['data']['firstname'] = array(
      '#type' => ($mode == 'view') ? 'item' : 'textfield',
      '#title' => 'firstname',
      '#markup' => theme_intel_contact_property(array('type' => 'firstname', 'data' => $visitor_data['contact']['firstname'])),
    );
  }
  if (!empty($visitor_data['contact']['lastname'])) {
    $form['data']['lastname'] = array(
      '#type' => ($mode == 'view') ? 'item' : 'textfield',
      '#title' => 'lastname',
      '#markup' => theme_intel_contact_property(array('type' => 'lastname', 'data' => $visitor_data['contact']['lastname'])),
    );
  }
  if (!empty($visitor->email)) {
    $form['data']['email'] = array(
      '#type' => ($mode == 'view') ? 'item' : 'textfield',
      '#title' => 'email',
      '#markup' => l($visitor->email, 'mailto:' . $visitor->email),
    );
  }
  $excludes = array('photo', 'firstname', 'lastname');
  foreach ($visitor_data['contact'] AS $key => $data) {
    if (in_array($key, $excludes)) { 
      continue; 
    }
    $markup = theme_intel_contact_property(array('type' => $key, 'data' => $data));
    if ($markup) {
      $form['data'][$key] = array(
        '#type' => ($mode == 'view') ? 'item' : 'textfield',
        '#title' => check_plain($key),
        '#markup' => $markup,
      );
    }
  }
  $form['updated'] = array(
    '#type' => 'item',
    '#title' => t('Last updated'),
    '#markup' => date("Y-m-d H:i"),
  );
  return $form;
}

function theme_intel_contact_property($vars) {
  $type = $vars['type'];
  $data = $vars['data'];
  
  $output = '';
  if ($type == 'photo') {
    $data = iconv('UTF-8', 'ASCII//TRANSLIT', $data);
//dsm($data);
    $data = str_replace('\\', '/', $data);
//dsm($data);
//dsm(ord('\\'));
//dsm(ord(substr($data, 6, 1)));
    $output = '<img src="' . $data . '">';
  }
  elseif ($type == 'website') {
    if ($data) {
      $output = l(str_replace('http://', '', $data), $data, array('attributes' => array('target' => 'disqus')));
    }
  }
  elseif ($type == 'location') {
    $output =  "{$data['city']}, {$data['region']}<br>\n{$data['country']}";
  }
  elseif ($type == 'environment') {
    $output = t('Browser') . ": {$data['browser']} v{$data['browserVersion']}<br>\n";
    $output .= t('OS') . ": {$data['operatingSystem']} v{$data['operatingSystemVersion']}<br>\n";
  }
  elseif ($type == 'disqus') {
    $output = l($data['profileUrl'], $data['profileUrl'], array('attributes' => array('target' => 'disqus')));
  }
  elseif ($data) {
    $output = $data;
  }
  if ($output) {
    return '<div class="property-' . drupal_clean_css_identifier($type) . '">' . $output . '</div>';
  }
  return FALSE;
}

function intel_admin_people_contacts() {
  require_once drupal_get_path('module', 'intel') . "/admin/intel.admin_theming.inc";
  $output = "";

  $api_level = variable_get('intel_api_level', '');
  
  $header = array();
  $header[] = array(
    'data' => t('Name'),
    'field' => 'v.name',
  );
  $header[] = array(
    'data' => t('Email'),
    'field' => 'v.email',
  );
  if ($api_level == 'pro') {
    $header[] = array(
      'data' => t('Location'),
    );
  }
  $header[] = array(
    'data' => t('Contact created'),
  );
  $header[] = array(
    'data' => t('Last activity'),
    'field' => 'v.last_activity',
    'sort' => 'desc',
  );
  $header[] = array(
    'data' => t('Operations'),
  );

  $options = array();
  $filter['conditions'] = array();
  $filter['conditions'][] = array('v.email', "", '!=');
  $result = intel_load_filtered_visitor_result($filter, $options, $header, 50);

  $rows = array();
  while ($r = $result->fetchObject()) {
    $r->data = intel_unserialize($r->data);
    $r->ext_data = unserialize($r->ext_data);
    $row = array();
    $row[] = theme_intel_table_visitor_name(array('visitor' => $r));
    $row[] = theme_intel_table_visitor_email(array('visitor' => $r));
    if ($api_level == 'pro') { 
      $row[] = theme_intel_table_visitor_location(array('visitor' => $r));
    }
    $row[] = ((time() - $r->contact_created) > 172800) ? format_date($r->contact_created, 'short') : format_interval(time() - $r->contact_created) . ' ' . t('ago');
    $row[] = ((time() - $r->last_activity) > 172800) ? format_date($r->last_activity, 'short') : format_interval(time() - $r->last_activity) . ' ' . t('ago');
    $ops = '';
    $ops .= l(t('Clickstream'), 'visitor/' . $r->vid . '/clickstream');
    if (!empty($r->ext_data['hubspot']['profile_url'])) {
      $ops .= ' | ' . l(t('HubSpot'), 'visitor/' . $r->vid . '/hubspot');
    }
    $row[] = $ops;
    $rows[] = $row;
  }

  $vars = array(
    'header' => $header, 
    'rows' => $rows, 
    'attributes' => array('id' => 'kwresearch-site-keywords')
  );
  $output .= theme('table', $vars);
  //pager_default_initialize($total, 1, $element = 0);
  $output .= theme('pager');

  return $output;
}



function intel_admin_people_visitors() {
  require_once drupal_get_path('module', 'intel') . "/admin/intel.admin_theming.inc";
  $output = "";

  $header = array(
    array(
      'data' => t('Visitor id'),
      'field' => 'v.visitorid',
    ),
    array(
      'data' => t('Location'),
    ),
    array(
      'data' => t('Last updated'),
      'field' => 'v.updated',
      'sort' => 'desc',
    ),
    array(
      'data' => t('Operations'),
    ),
  );

  $options = array();
  $filter['conditions'] = array();
  $result = intel_load_filtered_visitor_result($filter, $options, $header, 50);

  $rows = array();
  while ($r = $result->fetchObject()) {
    $r->data = intel_unserialize($r->data);
    $r->ext_data = unserialize($r->ext_data);
//dsm($ext_data);
    $row = array();
    $row[] = theme_intel_table_visitor_id(array('visitor' => $r));
    $row[] = theme_intel_table_visitor_location(array('visitor' => $r));
    $row[] = format_interval(time() - $r->updated) . ' ' . t('ago');
    $ops = l(t('Clickstream'), 'visitor/' . $r->visitorid . '/clickstream');
    if (!empty($r->ext_data['hubspot']['profile_url'])) {
      $ops .= ' | ' . l(t('HubSpot'), 'visitor/' . $r->visitorid . '/hubspot');
    }
    $row[] = $ops;
    $rows[] = $row;
  }

  $vars = array(
    'header' => $header, 
    'rows' => $rows, 
    'attributes' => array('id' => 'kwresearch-site-keywords')
  );
  $output .= theme('table', $vars);
  //pager_default_initialize($total, 1, $element = 0);
  $output .= theme('pager');

  return $output;
}