<?php
// $Id: contentanalysis.admin.inc,v 1.1.2.4 2010/06/01 21:23:39 tomdude48 Exp $
/**
 * @file * Admin include file. 
*/

/** 
 * Displays the form for the standard settings tab.
 * 
 * @return array 
 * A structured array for use with Forms API. 
*/ 
 function contentanalysis_admin_settings() {
  $params = array(
    'title' => t('Default analyzers'),
    'description' => t('Select the analyzers you want enabled by default.'),
  );
  $form['contentanalysis_default_analyzers'] = contentanalysis_get_analyzer_form_element($params);
  
  $form['contentanalysis_analyzerchecklist'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable analyzer checklist report'),
    '#default_value' => variable_get('contentanalysis_analyzerchecklist', 1)  
  ); 
  
  $form['contentanalysis_node_edit_form_collapsed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Collapse the content analysis fieldset on the node edit form'),
    '#default_value' => variable_get('contentanalysis_node_edit_form_collapsed', 0)  
  );  

  $options = array(    
    'both' => t('Display both dialog and inline reports.'),
    'dialog' => t('Display dialog report only.'),
    'inline' => t('Display inline reports only.'),
    'multibutton' => t('Provide buttons to enable the user to select report options.'),
  );
  
  $form['contentanalysis_node_report_display'] = array(    
    '#type' => 'radios',    
    '#title' => t('Node edit report style'), 
    '#options' => $options,
    '#default_value' => variable_get('contentanalysis_node_report_display', 'both'),     
    '#description' => t('Select the style of report you would like when launching from the node edit form. Dialog is the standard modal report. Inline inserts recommendations directly into the node edit form.')     
  );     
  
  $form['contentanalysis_node_parse_options'] = array(      
    '#type' => 'fieldset',      
    '#title' => t('Node parsing options'),      
    '#collapsible' => TRUE,      
    '#collapsed' => TRUE,    
  );   
  $form['contentanalysis_node_parse_options']['contentanalysis_node_parse_nodetitle_prepend'] = array(    
    '#type' => 'checkbox',    
    '#title' => t('Prepend node title to body'),    
    '#default_value' => variable_get('contentanalysis_node_parse_nodetitle_prepend', CONTENTANALYSIS_NODE_PARSE_NODETITLE_PREPEND_DEFAULT),     
    '#description' => t('Most Drupal sites format node views by putting the node title as a page header above the node body. If your site is formatted this way, check this box. If node titles are not used as headers, uncheck the option.')     
  );   
  $form['contentanalysis_node_parse_options']['contentanalysis_node_parse_nodetitle_tags'] = array(    
    '#type' => 'textfield',    
    '#title' => t('Node title tags'),    
    '#default_value' => variable_get('contentanalysis_node_parse_nodetitle_tags', CONTENTANALYSIS_NODE_PARSE_NODETITLE_TAGS_DEFAULT),     
    '#description' => t('If your node title is included on node views, include any formating tags it is enclosed within. Default is &lt;h2&gt;[node_title]&lt;/h2&gt;')     
  );  
  
  //Add the system buttons to the form
  $form = system_settings_form($form);  

  
  //Overide the theme function back to our own one
  return $form;
}

function contentanalysis_admin_analyzer_settings_form() {
  drupal_set_title(t('Analyzer settings'), PASS_THROUGH);  
	
  $form = contentanalysis_admin_analyzer_settings_element();
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );  
  
  return $form;
}

function contentanalysis_admin_analyzer_settings_element($mode = 'global') {
  drupal_add_library('system', 'ui.slider');
  drupal_add_js(drupal_get_path('module', 'contentanalysis') . '/contentanalysis.js');
  drupal_add_css(drupal_get_path('module', 'contentanalysis') . '/contentanalysis.css');
  $analyzer_defs = contentanalysis_analyzer_info();

  $settings = variable_get('contentanalysis_analyzer_settings', array());
//dsm($analyzer_defs);
  $form = array();
  if ($mode == 'global') {
    $form['#tree'] = TRUE;
  }
  foreach ($analyzer_defs AS $name => $def) {
  	if (isset($def['settings form elements callback'])) {
	    $form[$name] = array(
	      '#type' => 'fieldset',
	      '#title' => $def['title'],
	      //'#description' => t('Check the below boxes to display widgets in node links by content types.'),
	      '#collapsible' => TRUE,
	      '#collapsed' => ($mode == 'global') ? FALSE : TRUE,
	    );
	    $setting = isset($settings[$name]) ? $settings[$name] : NULL;
      $form[$name] = array_merge($form[$name], call_user_func($def['settings form elements callback'], $setting, $analyzer_defs[$name]));
    }
  } 
  
  return $form;
}

function contentanalysis_admin_analyzer_settings_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  unset($values['submit']);
  unset($values['form_build_id']);
  unset($values['form_token']);
  unset($values['form_id']);
  unset($values['op']);
  variable_set('contentanalysis_analyzer_settings', $values);
}
