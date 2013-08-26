<?php
// $Id$

/**
 * @file
 * Admin page callback for the insight module.
 */

function insight_admin_settings_form() {
	$analyzer_defs = insight_analyzer_info(TRUE);

	$analyzer_defs_meta = $analyzer_defs['#meta'];
	unset($analyzer_defs['#meta']);
  $form['contentanalysis'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content analysis'),
    //'#description' => t('Check the below boxes to display widgets in node links by content types.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );	
  $options = array();
//dsm($analyzer_defs_meta);
  foreach ($analyzer_defs_meta['analyzers_by_type']['content'] AS $analyzer_name) {
  	$options[$analyzer_name] = $analyzer_defs[$analyzer_name]['title'];
  }
  $form['contentanalysis']['insight_contentanalysis_autorun_analyzers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Auto run analyzers'),
    '#description' => t('Check any analyzers you want to enable for auto run analysis.'),
    '#options' => $options,
    '#default_value' => variable_get('insight_contentanalysis_autorun_analyzers', array()),
  ); 
  $form['contentanalysis']['insight_contentanalysis_autorun'] = array(
    '#markup' => '<label>' . t('Auto run event triggers') . '</label>',
  );
  
  $form['contentanalysis']['insight_contentanalysis_autorun_on_nodesave'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto analyze on node save'),
    '#description' => t('Content analysis will be run whenever a node is saved.'),
    '#default_value' => variable_get('insight_contentanalysis_autorun_on_nodesave', INSIGHT_CONTENTANALYSIS_AUTORUN_ON_NODESAVE_DEFAULT),
  ); 

  $form['contentanalysis']['insight_contentanalysis_autorun_on_cron'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto analyze on cron'),
    '#description' => t('Content analysis will be run when cron runs.'),
    '#default_value' => variable_get('insight_contentanalysis_autorun_on_cron', INSIGHT_CONTENTANALYSIS_AUTORUN_ON_CRON_DEFAULT),
  ); 
  
  return system_settings_form($form);
}

/**
 * Builds and returns the insight settings form.
 */
function insight_admin_api_settings() {
	$apikey = variable_get('insight_apikey', '');
	if (!$apikey) {
		
	}
	
  $form['insight_apikey'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => variable_get('insight_apikey', ''),
    //'#description' => t('This is an example setting.'),
    '#required' => TRUE,
  );
  
  if ($apikey) {
    $perms = insight_api_query_permissions();
    $form['acctstatus_hdr'] = array(
      '#type' => 'markup',
      '#markup' => '<h3>' . t('Account Permissions') . '</h3>', 
    );
    $statuses = array(
      'get_all_words_popularity' => t('Get all words popularity'),
      'get_embedded_phrase_popularity' => t('Get embedded phrase popularity'),
      'get_exact_phrase_popularity' => t('Get exact phrase popularity'),
      'get_plurals' => t('Get plurals'),
      'get_lateral_keyphrases' => t('Get lateral keyphrases'),
      'get_thesaurus_keyphrases' => t('Get thesaurus keyphrases'),
    );
    foreach ($statuses AS $k => $v) {
      $enabled = 'N';
      if ($perms[$k]) {
        $limit = $perms[$k]['result_limit'];
        if ($limit > 0) {
          $enabled = 'Y (limit ' . $limit . ')';
        }
      }
      $form['wordtracker_' . $k] = array(
        '#type' => 'item',
        '#title' => $v, 
        '#value' => "Enabled: " . $enabled,
      );
    }
  }
  return system_settings_form($form);
}

function insight_admin_alerts_settings() {
	$report_defs = insight_report_info();
	$settings = variable_get('insight_alerts_settings', array());

	$form['#tree'] = TRUE;
	foreach ($report_defs AS $name => $def) {
		$form[$name] = array(
      '#type' => 'fieldset',
      '#title' => $def['title'] . ' ' . t('report'),
      //'#description' => t('Check the below boxes to display widgets in node links by content types.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $settings = isset($settings[$name]) ? $settings[$name] : NULL;
    if (isset($def['alerts settings callback'])) {
      $form[$name] = array_merge($form[$name], call_user_func($def['settings form elements callback'], $settings, $report_defs[$name]));
    }
  } 
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );   
  return $form;
}

function insight_admin_alerts_settings_submit($form, &$form_state) {
	$values = $form_state['values'];
	unset($values['submit']);
	unset($values['form_build_id']);
	unset($values['form_token']);
	unset($values['form_id']);
	unset($values['op']);
	variable_set('insight_alerts_settings', $values);
}

function insight_admin_alerts_settings_seo_fields( $settings) {
	$form['minscore'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Minimum score threshold'),
	  '#description' => t('Triggers an alert if SEO score is below the given threshold. Set to 0 to disable.'),
	  '#size' => 4,
	  '#field_suffix' => '% (0-100)',
	  '#default_value' => isset($settings['minscore']) ? $settings['minscore'] : 50,
	);
	return $form;
}

function insight_admin_alerts_settings_links_fields( $settings) {
  $form['external_links_require_nofollow'] = array(
    '#type' => 'checkbox',
    '#title' => t('External links must have rel=nofollow'),
    '#description' => t('Triggers alter if any external link does not contain a rel=nofollow.'),
    '#default_value' => isset($settings['external_links_require_nofollow']) ? $settings['external_links_require_nofollow'] : 0,
  );
  $form['external_links_require_new_window'] = array(
    '#type' => 'checkbox',
    '#title' => t('External links should open in new window/tab'),
    '#description' => t('Triggers alter if any external link is not set to open in a new window or tab.'),
    '#default_value' => isset($settings['external_links_require_nofollow']) ? $settings['external_links_require_new_window'] : 0,
  );
  return $form;
}