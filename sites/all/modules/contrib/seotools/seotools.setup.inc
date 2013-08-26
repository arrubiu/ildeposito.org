<?php
// $Id$

/**
 * @file
 * Admin page callback for the seotools module.
 */

/*
 * TODO: finish wizard
 */
function seotools_admin_setup($step = 0) {
  if (!$step) {
    $step = 0;
  }
  $output = render(drupal_get_form('seotools_setup_' . $step .'_form'));
  return $output;
}

/** 
 * Checks if dependencies are installed
 * @param $form
 * @param $form_state
 */
function seotools_setup_0_form($form, &$form_state) {
  // run checks here if needed
  drupal_goto('admin/config/search/seotools/setup/1');
  
  return $form;
}
/**
 * Select social media profiles
 * @param $form
 * @param $form_state
 */
function seotools_setup_1_form($form, $form_state) {

	//$alchemy_apikey = '471d78ee2b56b5f4d746b46d21c6fff731666721';
	//dsm(preg_match('/^([A-Fa-f0-9]{2}){20}$/', $alchemy_apikey));
	
  drupal_set_title(t('SEO Tools setup'));
  $form = array();
  $instructions = t('Use this form to setup services accounts for SEO Tools.');

  $form['instruc'] = array(
    '#markup' => $instructions,
  );
 
  $form['setup_mode'] = array(
    '#type' => 'value',
    '#value' => 1,
  );
  
  // Google Analytics setup
  if (module_exists('googleanalytics')) {
	  include_once(drupal_get_path('module', 'googleanalytics') . '/googleanalytics.admin.inc');
	  $f = googleanalytics_admin_settings_form($form_state);
	  $description = '';
	  if (preg_match('/^UA-\d{4,}-\d+$/', $f['account']['googleanalytics_account']['#default_value'])) {
	    $description = '<div class="messages status">' . t('Your Google Analytics account is set.') . '</div>' . $description;
	    $f['account']['googleanalytics_account']['#type'] = 'item';
	    $f['account']['googleanalytics_account']['#markup'] = $f['account']['googleanalytics_account']['#default_value'];
	    $f['account']['googleanalytics_account']['#description'] = '';
	    $f['googleanalytics_set'] = array(
	      '#type' => 'value',
	      '#value' => '1',
	    );
	  }
	  $form['googleanalytics'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Google Analytics setup'),
	    '#collapsible' => TRUE,
	    '#collapsed' => FALSE,
	    '#description' => $description,
	  );
	  unset($f['tracking_title']);
	  unset($f['tracking']);
	  unset($f['googleanalytics_custom_var']);
	  unset($f['advanced']);
	  unset($f['actions']);
	  unset($f['#theme']);
	  unset($f['#submit']);
	  $f['googleanalytics_account'] = $f['account']['googleanalytics_account'];
	  unset($f['account']);
	  $form['googleanalytics'] = array_merge($form['googleanalytics'], $f);
  }

  // WordStream setup
  if (module_exists('wordstream')) {
    include_once(drupal_get_path('module', 'wordstream') . '/wordstream.admin.inc');
    $f = wordstream_admin_settings(array(), $form_state);
    $description = t('Wordstream gives you access to live keyword data.');
    if (isset($f['wordstream_credits_per_month']['#markup']) && $f['wordstream_credits_per_month']['#markup']) {
      $description = '<div class="messages status">' . t('Your WordStream account is setup correctly.') . '</div>' . $description;
    	unset($f['wordstream_password']); 
      $f['wordstream_username']['#type'] = 'item';
      $f['wordstream_username']['#markup'] = $f['wordstream_username']['#default_value'];
      $f['wordstream_username']['#description'] = '';
      $f['wordstream_set'] = array(
        '#type' => 'value',
        '#value' => '1',
      );
    }
    $form['wordstream'] = array(
      '#type' => 'fieldset',
      '#title' => t('Wordstream setup'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#description' => $description,
    );
  
    unset($f['wordstream_cache_time']);
    unset($f['wordstream_stats_report_options']);
    unset($f['actions']);
    unset($f['#theme']);
    unset($f['#submit']);
  
    $form['wordstream'] = array_merge($form['wordstream'], $f);
  }

  // Alchemy setup
  include_once(drupal_get_path('module', 'alchemy') . '/alchemy.admin.inc');
  $f = alchemy_admin_settings(array(), $form_state);
  $description = t('Alchemy analyzes content to extract terms, entities, concepts and more.');
  if (preg_match('/^([A-Fa-f0-9]{2}){20}$/', $f['alchemy_apikey']['#default_value'])) {
    $description = '<div class="messages status">' . t('Your Alchemy api key is set.') . '</div>' . $description;
    $f['alchemy_apikey']['#type'] = 'item';
    $f['alchemy_apikey']['#markup'] = $f['alchemy_apikey']['#default_value'];
    $f['alchemy_apikey']['#description'] = '';
    $f['alchemy_set'] = array(
      '#type' => 'value',
      '#value' => '1',
    );
  }
  $form['alchemy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Alchemy setup'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => $description,
  );
  unset($f['alchemy_usecurl']);
  unset($f['actions']);
  unset($f['#theme']);
  unset($f['#submit']);
  $form['alchemy'] = array_merge($form['alchemy'], $f);
  
  $form['actions'] = array(
    '#type' => 'actions', 
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );
  $form['#theme'] = 'system_settings_form';

  return $form;
}

function seotools_setup_1_form_validate($form, &$form_state) {
	$values = $form_state['values'];

  // validate Google Analytics account
	if (module_exists('googleanalytics')) {
	  if (!isset($values['googleanalytics_set']) && !preg_match('/^UA-\d{4,}-\d+$/', $form_state['values']['googleanalytics_account'])) {
	    form_set_error('googleanalytics_account', t('A valid Google Analytics Web Property ID is case sensitive and formatted like UA-xxxxxxx-yy.'));
	  } 	
	}
	
	// validate WordStream account
	if (module_exists('wordstream')) {
  	if (!isset($values['wordstream_set'])) {
  	  $wordstream = wordstream_include_api_class($values['wordstream_username'], $values['wordstream_password']);
  	  $account = 0;
  	  if ($wordstream) {
  	    $ret = $wordstream->getAPICredits();
  	    if ($ret->credits_per_month) {
  	    	$account = 1;
  	    }  
  	  }
  	  if (!$account) {
  	    form_set_error('wordstream_username', t('Unable to log in to WordStream. Please enter a valid WordStream API username and password.'));
  	  }
  	}
	}
	
  // validate Google Analytics account
  if (!isset($values['alchemy_set']) && !preg_match('/^([A-Fa-f0-9]{2}){20}$/', $form_state['values']['alchemy_apikey'])) {
    form_set_error('alchemy_apikey', t('Alchemy API key is invalid.'));
  }   
}

function seotools_setup_1_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  if (module_exists('googleanalytics')) {
	  if (!isset($values['googleanalytics_set'])) {
	    variable_set('googleanalytics_account', $values['googleanalytics_account']);
	  }
  }
  if (module_exists('wordstream')) {
    if (!isset($values['wordstream_set'])) {
    	variable_set('wordstream_username', $values['wordstream_username']);
    	variable_set('wordstream_password', $values['wordstream_password']);
    }
  }
  if (!isset($values['alchemy_set'])) {
    variable_set('alchemy_apikey', $values['alchemy_apikey']);
  }

  drupal_set_message(t('API account information has been saved.'));
  drupal_goto('admin/config/search/seotools/setup/2');
}

/**
 * Select social media profiles
 * @param $form
 * @param $form_state
 */
function seotools_setup_2_form($form, &$form_state) {
  // clear wordstream error message
  drupal_get_messages('error');	
	
  $msg = t('Congradulations, the Drupal SEO Tools suite is intalled and ready for use.');
  $msg .= '<h3>' . t('Next steps') . '</h3>';
  $items[] = t('If you have list of targeted keywords for your site, !import_link.',
    array(
      '!import_link' => l(t('import your keywords'), 'admin/structure/kwresearch/keyword_list/import'),
    )
  );
  $items[] = t('Discover targeted keywords for your site through !kwreserach_link.',
    array(
      '!kwreserach_link' => l(t('keyword research'), 'admin/structure/kwresearch/keyword_report'),
    )
  );
  $items[] = t('Analyze and optimize your content for the search engines using !contentanalysis_link.',
    array(
      '!contentanalysis_link' => l(t('content analysis'), 'admin/content/insight'),
    )
  );
  $msg .= theme('item_list', array('items' => $items));
  
	$form['done'] = array(
	  '#markup' => $msg,
	);

  return $form;
}