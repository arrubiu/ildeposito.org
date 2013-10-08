<?php
function intel_linkedin_visitor_page($visitor, $action = '') {
  
  $visitor_name = (!empty($visitor->name)) ? $visitor->name : '[No Name]';
  drupal_set_title(t('LinkedIn profile: @title', array('@type' => $visitor_name, '@title' => $visitor_name)), PASS_THROUGH);
  
  $output = '';  
  
  if ($action == 'launch') {
    //$script = "window.open('{$visitor->ext_data['hubspot']['profile_url']}', 'hubspot');";
    //drupal_add_js($script, array('type' => 'inline', 'scope' => 'header'));
    drupal_goto($visitor->data['linkedin']['profile_url']);
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