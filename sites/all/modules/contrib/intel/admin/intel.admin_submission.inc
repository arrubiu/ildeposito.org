<?php
/**
 * @file
 * Administration of submission data
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_submission_page($sid) {
  
  $submission = intel_submission_load($sid);
  $visitor = intel_visitor_load((int)$submission->vid);
  //if (!empty($submission->visitorid)) {
    //$visitor = intel_visitor_load_by_visitorid($submission->visitorid);
  //}
  $type = str_replace('_', ' ', $submission->type);
  drupal_set_title(t('@type submission', array('@type' => $type)), PASS_THROUGH);  
//dsm($submission);
  $output = '';
  
  $form = array();
  
  // todo encapsulate this back into hook in module or add field to store in submission table
  $link = '';
  if ($submission->type == 'webform') {
    $link = l(t('View submission details'), "node/{$submission->fid}/submission/{$submission->fsid}");
  }
  elseif ($submission->type == 'disqus_comment') {
    $link = l(t('View comment'), substr($submission->form_page_path, 1), array( 'fragment' => "comment-{$submission->fsid}"));
  }
  
  if ($link) {
    $form['data']['photo'] = array(
      '#type' => 'markup',
      '#markup' => $link . "<br>\n<br>\n",
    );
  }
  
  if ($visitor->name) {
    $form['submitted_by'] = array(
      '#type' => 'item',
      '#title' => t('Submitted by'),
      '#markup' => l($visitor->name, 'visitor/' . $visitor->vtkid),
    );
  }
  elseif ($visitor->visitorid) {
    $form['submitted_by'] = array(
      '#type' => 'item',
      '#title' => t('Submitted by'),
      '#markup' => l($visitor->getLabel(), 'visitor/' . $visitor->vtkid),
    );
  }
  else {
    $form['submitted_by'] = array(
      '#type' => 'item',
      '#title' => t('Submitted by'),
      '#markup' => t('(not set)'),
    );    
  }
  
  $form['submitted_at'] = array(
    '#type' => 'item',
    '#title' => t('Submitted at'),
    '#markup' => date("Y-m-d H:i"),
  ); 

  $url = "http://" . $submission->response_page_host . $submission->response_page_path;
  if ($submission->response_page_id) {
    $url = 'node/' . $submission->response_page_id;
  }
  $form['reponse_page'] = array(
      '#type' => 'item',
      '#title' => t('Response page'),
      '#markup' => l(url($url), $url),
  );
  
  if ($submission->form_page_path) {
    $url = "http://" . $submission->form_page_host . $submission->form_page_path;
    if ($submission->form_page_id) {
      $url = 'node/' . $submission->form_page_id;
    }
    $markup = l(url($url), $url);
  }
  else {
    $markup = '(not set)';
  }  
  $form['form_page'] = array(
    '#type' => 'item',
    '#title' => t('Form page'),
    '#markup' => $markup,
  );

  if ($submission->cta_page_path) {
    $url = "http://" . $submission->cta_page_host . $submission->cta_page_path;
    if ($submission->form_page_id) {
      $url = 'node/' . $submission->cta_page_id;
    }
    $markup = l(url($url), $url);
  }
  else {
    $markup = '(not set)';
  }  
  $form['cta_page'] = array(
    '#type' => 'item',
    '#title' => t('CTA page'),
    '#markup' => $markup,
  ); 

  if ($submission->cta_id) {
    $url = 'block/' . $submission->cta_id;
    $markup = l(url($url), $url);
  }
  else {
    $markup = '(not set)';
  }  
  $form['cta'] = array(
    '#type' => 'item',
    '#title' => t('CTA clicked'),
    '#markup' => $markup,
  );   
  
  $output = render($form);  
  
  return $output;
}

function intel_admin_people_submissions($filter = array()) {
  require_once drupal_get_path('module', 'intel') . "/admin/intel.admin_theming.inc";
  $output = "";
  $api_level = variable_get('intel_api_level', '');
  $header = array();
  $header[] = array(
    'data' => t('Name'),
    'field' => 'v.name',
  );
  if ($api_level == 'pro') {
    $header[] = array(
      'data' => t('Location'),
    );
  }
  $header[] = array(
      'data' => t('Submitted'),
      'field' => 's.submitted',
      'sort' => 'desc',
  );
  $header[] = array(
    'data' => t('Type'),
    'field' => 's.type',
  );
  $header[] = array(
    'data' => t('Operations'),
  );

  if (empty($filter['conditions'])) {
    $filter['conditions'] = array(
      array('s.vid', 0, '!='),
    );
  }
  $options = array();
  $result = intel_load_filtered_submission_result($filter, $options, $header, 50);

  $hs_portal_id = variable_get('hubspot_portalid', '');
  
  $rows = array();
  while ($r = $result->fetchObject()) {
//dsm($r->name);
//dsm($r);
    $visitor = (object) array(
      'vid' => $r->vid,
      'vtkid' => $r->vtkid,
      'name' => $r->name,
      'email' => $r->email,
      'data' => unserialize($r->visitor_data),
      'ext_data' => unserialize($r->visitor_ext_data),
    );
 //dsm($visitor);
    $row = array();
    $row[] = theme_intel_table_visitor_name(array('visitor' => $visitor));
    if ($api_level == 'pro') {      
      $row[] = theme_intel_table_visitor_location(array('visitor' => $visitor));
    }
    $row[] = ((time() - $r->submitted) > 172800) ? format_date($r->submitted, 'short') : format_interval(time() - $r->submitted) . t(' ago');
    $row[] = $r->type;
    $ops = l(t('meta'), 'submission/' . $r->sid);
    if ($r->type == 'webform') {
      $ops .= ' | ' . l(t('data'), 'node/' . $r->fid . '/submission/' . $r->sid);
    }
    elseif ($r->type == 'hubspot') {
      //$ops .= l(t('Submission'), 'https://app.hubspot.com/forms/' . $hs_portal_id . '/form/' . $r->fid . '/submissions/');
    }
    if (!empty($visitor->ext_data['hubspot']['profile_url'])) {
      //$ops .= ' | ' . l(t('HubSpot'), 'visitor/' . $visitor->visitorid . '/hubspot');
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