<?php
// $Id: seotools.admin.inc,v 1.1.2.3 2011/01/05 22:29:29 tomdude48 Exp $
/**
 * @file * Admin include file. 
*/

/** 
 * Displays the form for the standard settings tab.
 * 
 * @return array 
 * A structured array for use with Forms API. 
*/ 

function seotools_admin_settings() {
	$form['msg'] = array(
	  '#markup' => t('Settings not implemented yet. Coming soon.'),
	);
	return $form;
}

function xseotools_admin_settings() {
  global $base_url;
  $form['seotools_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Analytics Base Url'),
    '#default_value' => variable_get('seotools_base_url', $base_url),
    '#description' => t('If you have a different url on google_analytics, enter it here (defaults to base_url)'),
  );
  
  $rows_options = array(
    0 => t('none'),
    5 => 5,
    10 => 10,
    20 => 20,
    50 => 50,
    100 => 100,
    250 => 250,
    500 => 500,
  );
  $style_options = array(
    'simple' => t('Simple'),
    'full' => t('Full'),
  );
  $ids = array(
    'keywords' => t('keywords'),
    'entrances' => t('entrances'),
    'sources' => t('sources'),
    'referrers' => t('referrers'),
    'pageviews' => t('page views'),
  );
  $form['reports'] = array(
    '#type' => 'fieldset',
    '#title' => t('Report settings'),
    '#collapsible' => TRUE,
  );
  foreach($ids AS $id => $label) {
    $form['reports'][$id] = array(
      '#type' => 'fieldset',
      '#title' => $label . ' ' . t('report'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );  
    $form['reports'][$id]['seotools_report_top_' . $id . '_dashboard_style'] = array(
      '#type' => 'select',
      '#title' => t('Top %label dashboard report style', array('%label' => $label)),
      '#options' => $style_options,
      '#default_value' => variable_get('seotools_report_top_' . $id . '_dashboard_style', SEOTOOLS_REPORT_DASHBOARD_STYLE_DEFAULT),
    );
    $form['reports'][$id]['seotools_report_top_' . $id . '_dashboard_rows'] = array(
      '#type' => 'select',
      '#title' => t('Top %label dashboard report rows', array('%label' => $label)),
      '#options' => $rows_options,
      '#default_value' => variable_get('seotools_report_top_' . $id . '_dashboard_rows', SEOTOOLS_REPORT_DASHBOARD_ROWS_DEFAULT),
    );
    $form['reports'][$id]['seotools_report_trend_' . $id . '_dashboard_style'] = array(
      '#type' => 'select',
      '#title' => t('Trend %label dashboard report style', array('%label' => $label)),
      '#options' => $style_options,
      '#default_value' => variable_get('seotools_report_trend_' . $id . '_dashboard_style', SEOTOOLS_REPORT_DASHBOARD_STYLE_DEFAULT),
    );
    $form['reports'][$id]['seotools_report_trend_' . $id . '_dashboard_rows'] = array(
      '#type' => 'select',
      '#title' => t('Trend %label dashboard report rows', array('%label' => $label)),
      '#options' => $rows_options,
      '#default_value' => variable_get('seotools_report_trend_' . $id . '_dashboard_rows', SEOTOOLS_REPORT_DASHBOARD_ROWS_DEFAULT),
    );
    $form['reports'][$id]['seotools_report_top_' . $id . '_style'] = array(
      '#type' => 'select',
      '#title' => t('Top %label report style', array('%label' => $label)),
      '#options' => $style_options,
      '#default_value' => variable_get('seotools_report_top_' . $id . '_style', SEOTOOLS_REPORT_STYLE_DEFAULT),
    );
    $form['reports'][$id]['seotools_report_top_' . $id . '_rows'] = array(
      '#type' => 'select',
      '#title' => t('Top %label report rows', array('%label' => $label)),
      '#options' => $rows_options,
      '#default_value' => variable_get('seotools_report_top_' . $id . '_rows', SEOTOOLS_REPORT_ROWS_DEFAULT),
    );
    $form['reports'][$id]['seotools_report_trend_' . $id . '_style'] = array(
      '#type' => 'select',
      '#title' => t('Trend %label report style', array('%label' => $label)),
      '#options' => $style_options,
      '#default_value' => variable_get('seotools_report_trend_' . $id . '_style', SEOTOOLS_REPORT_STYLE_DEFAULT),
    );
    $form['reports'][$id]['seotools_report_trend_' . $id . '_rows'] = array(
      '#type' => 'select',
      '#title' => t('Trend %label report rows', array('%label' => $label)),
      '#options' => $rows_options,
      '#default_value' => variable_get('seotools_report_trend_' . $id . '_rows', SEOTOOLS_REPORT_ROWS_DEFAULT),
    );
  }
  
  return system_settings_form($form);
}
