<?php
/**
 * @file
 * utility to help fiddle with Google Analytics API requests
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_ga_explorer_report() {
  $request = variable_get('intel_ga_explorer_request', '');
  $form['dimensions'] = array(
    '#type' => 'textfield',
    '#title' => t('dimensions'),
    '#description' => t('Enter a value to assign to the event when the CTA is clicked. Must be an whole number.'),
    '#default_value' => (isset($request['dimensions'])) ? implode(',', $request['dimensions']) : '',
    '#maxlength' => 200,
   );
  $form['metrics'] = array(
    '#type' => 'textfield',
    '#title' => t('metrics'),
    '#description' => t('Enter a value to assign to the event when the CTA is clicked. Must be an whole number.'),
    '#default_value' => (isset($request['metrics'])) ? implode(',', $request['metrics']) : '',
    '#maxlength' => 200,
  );
  $form['segment'] = array(
    '#type' => 'textarea',
    '#title' => t('segment'),
    '#description' => t('Enter a value to assign to the event when the CTA is clicked. Must be an whole number.'),
    '#default_value' => (isset($request['segment'])) ? $request['segment'] : '',
    '#rows' => 2,
  );
  $form['filters'] = array(
    '#type' => 'textarea',
    '#title' => t('filters'),
    '#description' => t('Enter a value to assign to the event when the CTA is clicked. Must be an whole number.'),
    '#default_value' => (isset($request['filters'])) ? $request['filters'] : '',
    '#rows' => 2,
  );
  $form['sort_metric'] = array(
    '#type' => 'textfield',
    '#title' => t('sort'),
    '#description' => t('Enter a value to assign to the event when the CTA is clicked. Must be an whole number.'),
    '#default_value' => (isset($request['sort_metric'])) ? $request['sort_metric'] : '',
  );
  $form['start_date'] = array(
    '#type' => 'textfield',
    '#title' => t('start date'),
    '#description' => t('Enter a value to assign to the event when the CTA is clicked. Must be an whole number.'),
    '#size' => 16,
    '#default_value' => (isset($request['start_date'])) ? Date("Y-m-d", $request['start_date']) : Date("Y-m-d", strtotime("-7 days")),
  );
  $form['end_date'] = array(
    '#type' => 'textfield',
    '#title' => t('end date'),
    '#description' => t('Enter a value to assign to the event when the CTA is clicked. Must be an whole number.'),
    '#size' => 16,
    '#default_value' => (isset($request['end_date'])) ? Date("Y-m-d", $request['end_date']) : Date("Y-m-d"),
  );
  $form['max_results'] = array(
    '#type' => 'textfield',
    '#title' => t('max results'),
    '#description' => t('Enter a value to assign to the event when the CTA is clicked. Must be an whole number.'),
    '#size' => 16,
    '#default_value' => (isset($request['max_results'])) ? $request['max_results'] : 50,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  if (!empty($request)) {
  dsm($request); 
    $options = array('refresh' => TRUE); 
    $data = google_analytics_api_report_data($request, $options);
  dsm($data);
  
    $header = array();
    $rows = array();
    if (!empty($data->results) && is_array($data->results)) {
      foreach ($data->results AS $r) {
        $row = array();
        if (!count($header)) {
          foreach ($r AS $k => $e) {
            $header[] = $k;
          }
        }
        foreach ($r AS $k => $e) {
          $row[] = $e;
        }
        $rows[] = $row;
      }
    }
    $vars = array(
      'header' => $header,
      'rows' => $rows,
      'empty' => t('No results found.'),
    );
    $form['report'] = array(
      '#type' => 'markup',
      '#markup' => '<br><h3>Results</h3>' . theme('table', $vars),
    );
  }

  return $form;
}

function intel_ga_explorer_report_submit($form, &$form_state) {
  $values = $form_state['values'];
dsm($values);
  $request = array(
    'dimensions' => array(),
    'metrics' => array(),
    'segment' => '',
    'filters' => '',
    'sort' => '',
    'start_date' => '',
    'end_date' => '',
    'max_results' => '',
  );
  $d = $values['dimensions'];
  $d = str_replace("'", '', $d);
  $d = explode(',', $d);
  foreach ($d AS $i => $e) {
    $request['dimensions'][] = trim($e);
  }
  $d = $values['metrics'];
  $d = str_replace("'", '', $d);
  $d = explode(',', $d);
  foreach ($d AS $i => $e) {
    $request['metrics'][] = trim($e);
  }
  $request['segment'] = str_replace("'", '', $values['segment']);
  $request['filters'] = str_replace("'", '', $values['filters']);
  $request['sort_metric'] = str_replace("'", '', $values['sort_metric']);
  $request['start_date'] = strtotime(str_replace("'", '', $values['start_date']));
  $request['end_date'] = strtotime(str_replace("'", '', $values['end_date']));
  $request['max_results'] = str_replace("'", '', $values['max_results']);
dsm($request);
  variable_set('intel_ga_explorer_request', $request);
  
}

