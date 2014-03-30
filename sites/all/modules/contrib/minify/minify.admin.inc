<?php

/**
 * Menu callback to generate overview form
 */
function minify_js_callback() {
  if (!function_exists('curl_init')) {
    form_set_error('null', t('CURL library not avaliable. In order to use Minify please install CURL library.'));
  }

  $cache_data = variable_get('minify_captured_js', array());

  $options = array();
  $actual_size_bytes = 0;
  $minified_size_bytes = 0;
  if (!empty($cache_data)) {
    $attributes = array('attributes' => array('target' => '_blank'));

    foreach ($cache_data as $key => $value) {
      $actual_size_bytes += $value['original_size'];
      $minified_size_bytes += $value['minified_size'];
      
      $refresh_link = l('Re-minify', 
        'admin/config/development/performance/minifyjs/refresh', 
        array('query' => array('file' => $key), 'attributes' => array('title' => 'Regenerate the minified JS file.'))
      );

      $revert_link = l('Revert', 
        'admin/config/development/performance/minifyjs/revert', 
        array('query' => array('file' => $key), 'attributes' => array('title' => 'Revert back to original state.'))
      );

      $file_path_links = 'Original - ' . l($key, $key, $attributes) . (($value['status']) 
          ? ('<br />' . 'Minified - ' . l($value['minified_file_path'], $value['minified_file_path'], $attributes)) 
          : ''
        );
        
      $minify = l('Minify', 
        'admin/config/development/performance/minifyjs/refresh', 
        array('query' => array('file' => $key), 'attributes' => array('title' => 'Minify it.')));

      $options[$key] = array(
        'file_name' => $value['file_name'],
        'file_path' => $file_path_links,
        'status' => ('' == $value['minified_file_path']) ? 'Uncompressed' : 'Minified',
        'original_size' => ('' == $value['original_size']) ? 'N/A' : $value['original_size'] . ' bytes',
        'minified_size' => ('' == $value['minified_size']) ? 'N/A' : $value['minified_size'] . ' bytes',
        'operations' => ($value['status']) ? $refresh_link . ' | ' . $revert_link : $minify
      );
    }
    $actual_size_bytes = $actual_size_bytes / 1024;
    $minified_size_bytes = $minified_size_bytes / 1024;
  }
  $header = array(
    'file_name' => t('File name'),
    'file_path' => t('File path'),
    'status' => t('Status'),
    'original_size' => t('Original size'),
    'minified_size' => t('Minified size'),
    'operations' => t('Operations'),
  );
  $form['js'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => '<b>' . t('JavaScript files not found, please visit some random pages at front end to capture JavaScript files.') . '</b>',
  );
  $form['size_info'] = array(
    '#prefix' => '<p>',
    '#markup' => t('Actual size: <b>@total_size KB</b>.<br />Minified size: <b>@minified_size KB</b>.', array('@total_size' => number_format($actual_size_bytes, 2), '@minified_size' => number_format($minified_size_bytes, 2))),
    '#suffix' => '</p>',
  );
  $form['minify'] = array(
    '#type' => 'submit',
    '#value' => t('Minify'),
    '#validate' => array('minify_js_submit'),
  );
  $form['clear_minify_cache'] = array(
    '#type' => 'submit',
    '#value' => t('Clear minify cache'),
    '#validate' => array('minify_clear_js_cache'),
  );
  
  return $form;
}

/**
 * Submit function to handle overview for submission
 */
function minify_js_submit($form, &$form_state) {
  $cache_data = variable_get('minify_captured_js', array());

  /* Filter out non-selected values */
  $scripts = array_filter($form_state['values']['js']);

  foreach ($scripts as $script) {
    _minify_process_minify($script, $cache_data);
  }
}

function minify_clear_js_cache($form, &$form_state) {
  $minify_dir = variable_get('file_public_path', conf_path() . '/files') . '/minify';
  $files = file_scan_directory($minify_dir, '/.*\.*$/');
  foreach ($files as $key => $value) {
    drupal_unlink($key);
  }
  variable_del('minify_captured_js');
  variable_set('minify_js', 0);
  watchdog('minify', 'Minify cache cleared.', array(), WATCHDOG_NOTICE);
  drupal_set_message(t('Minify cache cleared.'));
  drupal_goto('admin/config/development/performance/minifyjs');
}

/**
 * Helper function to process minify call
 */
function _minify_process_minify($script, &$cache_data) {
  $js_code = urlencode(trim(file_get_contents(drupal_realpath($script))));
  $post_data = _minify_get_post_fields($js_code);
  $response = _minify_send_request($post_data);
  if (isset($response['response'])) {
    $response_obj = $response['response'];

    if (!isset($response_obj->warnings) && !isset($response_obj->serverErrors)) {
      $min_js_path = _minify_construct_min_js_path($script);
      if (file_put_contents($min_js_path, $response_obj->compiledCode)) {

        watchdog('minify', '%old_path minified successfully as %new_path.', array('%old_path' => $script, '%new_path' => $min_js_path), WATCHDOG_NOTICE);
        drupal_set_message(t('%old_path minified successfully as %new_path.', array('%old_path' => $script, '%new_path' => $min_js_path)));

        $cache_data[$script]['minified_file_path'] = $min_js_path;
        $cache_data[$script]['original_size'] = $response_obj->statistics->originalSize;
        $cache_data[$script]['minified_size'] = $response_obj->statistics->compressedSize;
        $cache_data[$script]['status'] = true;
        /* Update the cache in each iteration to avoid errors */
        variable_set('minify_captured_js', $cache_data);
      } //File save if end
    } else if (isset($response_obj->warnings)) {
      $warning = $response_obj->warnings[0]->warning;
      watchdog('minify', 'Failed to generate minified JS. Error: %warning', array('%warning' => $warning), WATCHDOG_ERROR);
      form_set_error('null', t('Failed to generate minified JS. Error: %warning', array('%warning' => $warning)));
    } else if (isset($response_obj->serverErrors)) {
      watchdog('minify', 'Server error, Too many compiles performed recently. Try again later.', array(), WATCHDOG_ERROR);
      form_set_error('null', t('Server error, Too many compiles performed recently. Try again later.'));
    }
  } // Response isset if end

}

/**
 * Helper function to construct post request data
 */
function _minify_get_post_fields($js_code) {
  $post_data_array = array();
  $post_data_array[] = 'js_code=' . $js_code;
  $post_data_array[] = 'compilation_level=WHITESPACE_ONLY';
  $post_data_array[] = 'output_format=json';
  $post_data_array[] = 'warning_level=DEFAULT';
  $post_data_array[] = 'use_closure_library=' . true;
  $post_data_array[] = 'output_info=warnings';
  $post_data_array[] = 'output_info=errors';
  $post_data_array[] = 'output_info=compiled_code';
  $post_data_array[] = 'output_info=statistics';
  /* Prepare POST request query string */
  return implode('&', $post_data_array);
}

/**
 * Helper function to send CURL request
 */
function _minify_send_request($post_data) {
  if (function_exists('curl_init')) {
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_URL, "closure-compiler.appspot.com/compile");
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($curl, CURLOPT_POSTFIELDS, $post_data);
    curl_setopt($curl, CURLOPT_POST, true);
    $response = json_decode(curl_exec($curl));
    $httpcode = curl_getinfo($curl, CURLINFO_HTTP_CODE);
    curl_close($curl);
    return array('response' => $response, 'http_code' => $httpcode);
  }
}

/**
 * Helper function to construct minified js path
 */
function _minify_construct_min_js_path($script) {
  $minify_js_dir = variable_get('file_public_path', conf_path() . '/files') . '/minify/';
  if (!is_dir($minify_js_dir)) {
    drupal_mkdir($minify_js_dir);
  }
  $path_parts = pathinfo($script);
  $file_name = $path_parts['filename'] . '.min.' . $path_parts['extension'];
  return $minify_js_dir . $file_name;
}

/**
 * Helper function to remove minified js from cache
 */
function _minify_js_revert_callback() {
  $cache_data = variable_get('minify_captured_js', array());
  if (!empty($cache_data)) {
    $key = $_GET['file'];
    if (isset($cache_data[$key])) {
      /* Reset cache data record to prevent use of minified js */
      $minified_file_path = $cache_data[$key]['minified_file_path'];
      $cache_data[$key]['minified_file_path'] = '';
      $cache_data[$key]['original_size'] = 0;
      $cache_data[$key]['minified_size'] = 0;
      $cache_data[$key]['status'] = false;
      
      /* Set status flag, if even single javascript is minified */
      $status_flag = false;
      foreach ($cache_data as $key => $value) {
        if ($cache_data[$key]['status']) {
          $status_flag = true;
        }
      }
      
      /* Delete variable when, even single javascript is not minified to uncheck checkbox from performance page */
      if (!$status_flag) {
        variable_del('minify_js');
      }

      variable_set('minify_captured_js', $cache_data);
      
      /* delete the file */
      drupal_unlink($minified_file_path);

      $path_parts = pathinfo($key);
      $file_name = $path_parts['filename'] . '.min.' . $path_parts['extension'];
      watchdog('minify', '%file_name reverted successfully.', array('%file_name' => $file_name), WATCHDOG_NOTICE);
      drupal_set_message(t('%file_name reverted successfully.', array('%file_name' => $file_name)));
    }
  }
  drupal_goto('admin/config/development/performance/minifyjs');
}

/**
 * Helper function to regenerate minified js
 */
function _minify_js_refresh_callback() {
  $file = $_GET['file'];
  $cache_data = variable_get('minify_captured_js', null);
  _minify_process_minify($file, $cache_data);
  drupal_goto('admin/config/development/performance/minifyjs');
}