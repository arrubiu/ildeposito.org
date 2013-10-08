<?php

/**
 * @file
 * Helper functions for reports
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function theme_intel_table_visitor_id($vars) {
  $visitor = $vars['visitor'];
  if (empty($var['link_options'])) {
    $var['link_options'] = array();
  }
  $options = array(
    'attributes' => array(
      'class' => array(),
    ),
  );
  $var['link_options'] += $options;
  if (!empty($visitor->name)) {
    $vars['link_options']['attributes']['class'][] = 'known-visitor';
    return theme_intel_table_visitor_name($vars);
  }
  else {
    $vars['link_options']['attributes']['class'][] = 'anonymous-visitor';
    return l($visitor->vtkid, 'visitor/' . $visitor->vtkid, $vars['link_options']);
  }
}

function theme_intel_table_visitor_name($vars) {
  $visitor = $vars['visitor'];
  $link = isset($var['link']) ? $var['link'] : 1;
  $link_options = !empty($var['link_options']) ? $var['link_options'] : array();
  $title = '';
  if (!empty($visitor->data['company'])) {
    $title .= (($title) ? ', ' : '') . t('Company') . ': ' . $visitor->data['company'];
  }
  if (!empty($visitor->data['title'])) {
    $title .= (($title) ? ', ' : '') . t('Title') . ': ' . $visitor->data['title'];
  }
  $link_options += array(
    'attributes' => array(
      'title' => $title,
    ),
  );
  $name = (!empty($visitor->name)) ? $visitor->name : '(not set)';
  if ($link && !empty($visitor->vid)) {
    return l($name, 'visitor/' . $visitor->vid, $link_options);
  }
  else {
    return $name;
  }
}

function theme_intel_table_visitor_email($vars) {
  $visitor = $vars['visitor'];
  $link_options = !empty($var['link_options']) ? $var['link_options'] : array();
  $title = '';
  if (!empty($visitor->data['website'])) {
    $title .= (($title) ? ', ' : '') . t('Website') . ': ' . $visitor->data['website'];
  }
  if (!empty($visitor->data['phone'])) {
    $title .= (($title) ? ', ' : '') . t('Phone') . ': ' . $visitor->data['phone'];
  }
  $link_options += array(
    'attributes' => array(
      'title' => $title,
    ),
  );
  return l($visitor->email, 'mailto:' . $visitor->email, $link_options);
}

function theme_intel_table_visitor_location($vars) {
  $visitor = $vars['visitor'];
  $link_options = !empty($var['link_options']) ? $var['link_options'] : array();
  $output = '';
  if (!empty($visitor->data['location'])) {
    $output .= '<div title="' . $visitor->data['location']['city'] . ', ' . $visitor->data['location']['region'] . '">';
    $output .= $visitor->data['location']['country'];
    $output .= '</div>';
  }
  return $output;
}