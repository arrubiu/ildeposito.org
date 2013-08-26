<?php 

function insight_report_form($form, $form_state, $report) {
	drupal_add_css(drupal_get_path('module', 'contentanalysis') . '/contentanalysis.css'); 
  $analyzer_defs = insight_analyzer_info(TRUE);
  $report_defs = $analyzer_defs['#meta']['reports'];
    
	$title = t('%name report', array('%name' => $report_defs[$report['name']]['title']));
  drupal_set_title($title, PASS_THROUGH);

  $form_state['report'] = $report;
  $form['#attached']['css'][drupal_get_path('module', 'insight') . '/insight.admin.css'] = array();

  if ($report['nid']) {
	  $form['for'] = array(
	    '#type' => 'markup',
	    '#markup' => t('for') . ': ' . l(substr(url('node/' . $report['nid']), 1), 'node/' . $report['nid']),
	  ); 	
  }
   
  // Show the thumbnail preview.
  $form['report'] = array(
    '#type' => 'markup',
    '#markup' => $report['report'],
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $report['active'] ? t('Ignore report') : t('Re-activate report'),
  );
  $destination = drupal_get_destination();
  $form['back'] = array(
    '#markup' => l(t('Back'), $destination['destination']),
  );
  
  
  
  return $form;
}

function insight_report_form_submit($form, $form_state) {
  $report = $form_state['report'];
  $analyzer_defs = insight_analyzer_info(TRUE);
  $report_defs = $analyzer_defs['#meta']['reports'];
  
  if ($form_state['values']['submit'] == 'Ignore report') {
  	insight_report_ignore($report['irid']);
  	$msg = t('%name report has been de-activated for !link', 
  	  array(
  	    '%name' => $report_defs[$report['name']]['title'],
  	    '!link' => l('node/' . $report['nid'], 'node/' . $report['nid']),
  	  )
  	);
  	drupal_set_message($msg);
  }
  else {
  	insight_report_activate($report['irid']);
    $msg = t('%name report has been re-activated for !link', 
      array(
        '%name' => $report_defs[$report['name']]['title'],
        '!link' => l('node/' . $report['nid'], 'node/' . $report['nid']),
      )
    );
    drupal_set_message($msg);
  }
  
  //dsm($form_state);
  
  return;
}

function insight_alert_active_operation($alert, $op) {
	//dsm($alert);
	//dsm($op);
  $analyzer_defs = insight_analyzer_info(TRUE);
  $report_defs = $analyzer_defs['#meta']['reports'];

	if (function_exists('insight_alert_' . $op)) {
		call_user_func('insight_alert_' . $op, $alert['iaid']);
		$msg = t('@report_title report has been @op.',
		  array(
		    '@report_title' => $report_defs[$alert['report']]['title'],
		    '@op' => ($op == 'dismiss') ? 'removed' : (($op == 'ignore') ? 'marked ignore' : 'activated'),
		  )
		);
		drupal_set_message($msg);
	}
	drupal_goto($_GET['destination']);
}

function insight_autoanalyze_node_operation($node) {
	insight_contentanalysis_autoanalyze($node->nid);
	
  $msg = t('@node content was analyzed.',
    array(
      '@nid' => l($node->title, 'node/' . $node->nid),
    )
  );

	drupal_goto($_GET['destination']);
}