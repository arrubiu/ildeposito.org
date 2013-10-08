<?php

function intel_disqus_admin_config($form, $form_state) {
  $form = array_merge($form, intel_disqus_admin_config_form());
  return system_settings_form($form);
}

function intel_disqus_admin_config_form() {
  $form = array();
  $form['intel_disqus_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Secret key'),
    '#default_value' => variable_get('intel_disqus_secret_key', ''),
    '#description' => t('Enter your Secret Key from Disqus. Requires a registered DISQUS API application. Create one (free) at http://disqus.com/api/applications/'),
  );  
  $form['intel_disqus_access_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Acess token'),
    '#default_value' => variable_get('intel_disqus_access_token', ''),
    '#description' => t('Enter your Access Token from Disqus. Admin access tokens are required to get the email address. They can be found at http://disqus.com/api/applications/'),
  ); 
  return $form;
}

function intel_disqus_visitor_page($visitor, $action = '') {
  
  $visitor_name = (!empty($visitor->name)) ? $visitor->name : '[No Name]';
  drupal_set_title(t('Disqus profile: @title', array('@type' => $visitor_name, '@title' => $visitor_name)), PASS_THROUGH);
  
  $output = '';  
  
  if (!empty($_GET['debug'])) {
    dsm($visitor->getProperties());
  }
  $ext_data = $visitor->ext_data;
  if (empty($ext_data['disqus']['profileUrl']) 
      && (!empty($ext_data['disqus']['last_commentid']))
    ) {
    intel_disqus_intel_sync_visitordata($visitor);
    $visitor->load();
    $ext_data = $visitor->ext_data;
    drupal_set_message(t('Disqus data resynced.'));
  }
  
  if (empty($ext_data['disqus']['profileUrl'])) {
    drupal_set_message('This contact has not been linked to a Disqus profile.', 'error');
    $output = 'Unable to fetch profile from Disqus.';
    return $output;
  }
  
  if ($action == 'launch') {
    //$script = "window.open('{$visitor->ext_data['hubspot']['profile_url']}', 'hubspot');";
    //drupal_add_js($script, array('type' => 'inline', 'scope' => 'header'));
    drupal_goto($visitor->ext_data['disqus']['profileUrl']);
  }

$script = <<<EOD
jQuery('#contact-iframe').load(function() {
  this.style.height = this.contentWindow.document.body.offsetHeight + 'px';
});
EOD;
  $output .= '<style>iframe #contact-iframe { visibility:hidden; }</style>';
  //drupal_add_js($script, array('type' => 'inline', 'scope' => 'header'));
  $output .= '<iframe src="' . $visitor->ext_data['disqus']['profileUrl'] . '" id="contact-iframe" scrolling="no" frameborder="0" style="width: 100%; height: 2500px;"></iframe>';
  drupal_add_js($script, array('type' => 'inline', 'scope' => 'header'));
  
  
  return $output;
}