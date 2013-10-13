<?php

require('../inc/ildeposito_theme_functions.inc.php');

/**
 * Implements template_preprocess_html().
 *
 */
//function ildeposito_found_preprocess_html(&$variables) {
//  // Add conditional CSS for IE. To use uncomment below and add IE css file
//  drupal_add_css(path_to_theme() . '/css/ie.css', array('weight' => CSS_THEME, 'browsers' => array('!IE' => FALSE), 'preprocess' => FALSE));
//
//  // Need legacy support for IE downgrade to Foundation 2 or use JS file below
//  // drupal_add_js('http://ie7-js.googlecode.com/svn/version/2.1(beta4)/IE7.js', 'external');
//}

/**
 * Implements template_preprocess_page
 *
 */
function ildeposito_found_preprocess_page(&$vars) {
  
}

/**
 * Implements template_preprocess_node
 *
 */
function ildeposito_found_preprocess_node(&$vars) {
  
}

/**
 * Implements hook_preprocess_block()
 */
function ildeposito_found_preprocess_block(&$vars) {
  // Convenience variable for classes based on block ID
  $block_id = $variables['block']->module . '-' . $variables['block']->delta;

  // Add classes based on a specific block
  /*switch ($block_id) {
    // System Navigation block
    case 'system-navigation':
      // Custom class for entire block
      $variables['classes_array'][] = 'system-nav';
      // Custom class for block title
      $variables['title_attributes_array']['class'][] = 'system-nav-title';
      // Wrapping div with custom class for block content
      $variables['content_attributes_array']['class'] = 'system-nav-content';
      break;

    // User Login block
    case 'user-login':
      // Hide title
      $variables['title_attributes_array']['class'][] = 'element-invisible';
      break;

    // Example of adding Foundation classes
    case 'block-foo': // Target the block ID
      // Set grid column or mobile classes or anything else you want.
      $variables['classes_array'][] = 'six columns';
      break;
  }*/

  // Add template suggestions for blocks from specific modules.
  /*switch($variables['elements']['#block']->module) {
    case 'menu':
      $variables['theme_hook_suggestions'][] = 'block__nav';
    break;
  }*/
}

function ildeposito_found_preprocess_views_view(&$vars) {
  
}

/**
 * Implements hook_preprocess_button().
 */
//function ildeposito_found_preprocess_button(&$variables) {
//  $variables['element']['#attributes']['class'][] = 'button';
//  if (isset($variables['element']['#parents'][0]) && $variables['element']['#parents'][0] == 'submit') {
//    $variables['element']['#attributes']['class'][] = 'secondary';
//  }
//}

/**
 * Implements hook_css_alter().
 */
function ildeposito_found_css_alter(&$css) {
  // Always remove base theme CSS.
  $theme_path = drupal_get_path('theme', 'zurb_foundation');

  foreach($css as $path => $values) {
    if(strpos($path, $theme_path) === 0) {
      unset($css[$path]);
    }
  }
}

/**
 * Implements hook_js_alter().
 */
function ildeposito_found_js_alter(&$js) {
  // Always remove base theme JS.
  $theme_path = drupal_get_path('theme', 'zurb_foundation');

  foreach($js as $path => $values) {
    if(strpos($path, $theme_path) === 0) {
      unset($js[$path]);
    }
  }
}
