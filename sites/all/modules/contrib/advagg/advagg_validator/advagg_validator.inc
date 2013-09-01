<?php

/**
 * @file
 * Advanced aggregation validation module.
 */

/**
 * Test all css files used by AdvAgg.
 *
 * @return array
 *   An array of files with the result from the w3c validator.
 */
function advagg_validator_test_advagg_css($options = array()) {
  // Get list of files.
  $query_files = db_select('advagg_files', 'af')
    ->fields('af', array('filename_hash', 'filename'))
    ->condition('af.filetype', 'css')
    ->orderBy('filename', 'DESC')
    ->execute()
    ->fetchAllKeyed();
  $files = array_values($query_files);

  // Test and return list.
  return advagg_validator_test_css_files($files, $options);
}

/**
 * Recursively scan the drupal webroot and test all css files.
 *
 * @return array
 *   An array of files with the result from the w3c validator.
 */
function advagg_validator_test_all_css($options = array()) {
  // Get list of files.
  $files = advagg_validator_scan_all_dirs('css');

  // Test and return list.
  return advagg_validator_test_css_files($files, $options);
}

/**
 * Recursively scan the drupal webroot for files matching the given extension.
 *
 * @param string $ext
 *   Usually css or js.
 * @return array
 *   An array of files.
 */
function advagg_validator_scan_all_dirs($ext) {
  $options = array(
    'nodirmask' => '/(\.git|.*\/files*)/'
  );
  $output = advagg_validator_file_scan_directory(DRUPAL_ROOT, '/.*\.' . $ext . '$/', $options);
  $files = array();
  foreach ($output as $values) {
    $files[] = str_replace(DRUPAL_ROOT . '/', '', $values->uri);
  }
  return $files;
}

/**
 * Test all given files with the w3c validator.
 *
 * @return array
 *   An array of files with the result from the w3c validator.
 */
function advagg_validator_test_css_files($files, $options = array()) {
  $output = array();
  foreach ($files as $filename) {
    // Skip missing files.
    if (!file_exists($filename)) {
      continue;
    }

    $file_contents = file_get_contents($filename);
    $lines = file($filename);
    $filename_hash = drupal_hash_base64($filename);
    $content_hash = drupal_hash_base64($file_contents);
    $update = FALSE;

    // See if this file needs to be scanned.
    $file_ok = db_select('advagg_validator', 'av')
      ->fields('av', array('content_hash', 'data'))
      ->condition('filename_hash', $filename_hash)
      ->condition('filetype', 'css')
      ->execute()
      ->fetchAllKeyed();
    if (!empty($file_ok)) {
      foreach ($file_ok as $content_hash_db => $serialized_data) {
        if ($content_hash_db == $content_hash) {
          $output[$filename] = unserialize($serialized_data);
          continue 2;
        }
      }
      $update = TRUE;
    }

    // Run jigsaw.w3.org validator.
    $output[$filename]['jigsaw.w3.org'] = advagg_validator_test_css_file_w3c($filename, $options);

    // Get extra context for errors.
    if (!empty($output[$filename]['jigsaw.w3.org']['errors'])) {
      foreach ($output[$filename]['jigsaw.w3.org']['errors'] as $key => &$value) {
        if (isset($value['line'])) {
          $value['linedata'] = $lines[($value['line']-1)];
          if (strlen($value['linedata']) > 512) {
            unset($value['linedata']);
          }
        }
      }
    }
    if (!empty($output[$filename]['jigsaw.w3.org']['warnings'])) {
      foreach ($output[$filename]['jigsaw.w3.org']['warnings'] as $key => &$value) {
        if (isset($value['line'])) {
          $value['linedata'] = $lines[$value['line']-1];
          if (strlen($value['linedata']) > 512) {
            unset($value['linedata']);
          }
        }
      }
    }

    // Save data.
    if (empty($output[$filename]['jigsaw.w3.org']['error'])) {
      $record = array(
        'filename' => $filename,
        'filename_hash' => $filename_hash,
        'content_hash' => $content_hash,
        'filetype' => 'css',
        'data' => $output[$filename],
      );
      if ($update) {
        drupal_write_record('advagg_validator', $record, array('filename_hash'));
      }
      else {
        drupal_write_record('advagg_validator', $record);
      }
    }
  }
  return $output;
}

/**
 * Given a CSS file, test to make sure it is valid CSS.
 *
 * @param string $filename
 *   The name of the file.
 * @param array $validator_options
 *   List of options to pass along to the CSS Validator.
 *
 * @return array
 *   Info from the w3c server.
 */
function advagg_validator_test_css_file_w3c($filename, &$validator_options = array()) {
//   // Get public URL for file.
//   $test_url = file_create_url($filename);
//   $parse = @parse_url($test_url);
//
//   // Get IP Address.
//   if (ip2long($parse['host']) !== FALSE) {
//     $ip = $parse['host'];
//   }
//   else {
//     $ip = gethostbyname($parse['host']);
//   }
//   // If IP is not externally routable, send raw text instead of uri.
//   if (ip2long($ip) === FALSE || advagg_validator_reserved_ip($ip)) {
//     $validator_options['text'] = file_get_contents($filename);
//   }
//   else {
//     $validator_options['uri'] = $test_url;
//   }
  $validator_options['text'] = file_get_contents($filename);

  // Add in defaults.
  $validator_options += array(
    'output' => 'soap12',
    'warning' => '1',
    'profile' => 'css3',
    'usermedium' => 'all',
    'lang' => 'en',
  );

  // Build request URL.
  // API Documentation http://jigsaw.w3.org/css-validator/api.html
  $request_url = 'http://jigsaw.w3.org/css-validator/validator';
  $query = http_build_query($validator_options, '', '&');
  $url = $request_url . '?' . $query;

  // Send request.
  $result = drupal_http_request($url);
  if (!empty($result->data) && $result->code == 200) {
    // Parse XML & return info.
    $return = advagg_validator_parse_soap_response_w3c($result->data);
    $return['filename'] = $filename;
    if (isset($validator_options['text'])) {
      unset($validator_options['text']);
    }
    $return['options'] = $validator_options;
    return $return;
  }

  return array('error' => t('W3C Server did not return a 200 or request data was empty.'));
}

/**
 * Parse an XML response from the validator.
 *
 * This function parses a SOAP 1.2 response XML string from the validator.
 *
 * @param string $XML
 *   The raw SOAP 1.2 XML response from the validator.
 *
 * @return array
 *   Info from the w3c server.
 */
function advagg_validator_parse_soap_response_w3c($XML) {
  $doc = new DOMDocument();
  $response = array();

  // Try to load soap 1.2 XML response, and suppress warning reports if any.
  if (!@$doc->loadXML($XML)) {
    // Could not load the XML document
    return $response;
  }

  // Get the standard CDATA elements.
  $cdata = array('uri', 'checkedby', 'csslevel', 'date');
  foreach ($cdata as $var) {
    $element = $doc->getElementsByTagName($var);
    if ($element->length) {
      $response[$var] = $element->item(0)->nodeValue;
    }
  }

  // Handle the element validity and get errors if not valid.
  $element = $doc->getElementsByTagName('validity');
  if ($element->length && $element->item(0)->nodeValue == 'true') {
    $response['validity'] = TRUE;
  }
  else {
    $response['validity'] = FALSE;
    $errors = $doc->getElementsByTagName('error');
    foreach ($errors as $error) {
      $response['errors'][] = advagg_validator_dom_extractor($error);
    }
  }

  // Get warnings.
  $warnings = $doc->getElementsByTagName('warning');
  foreach ($warnings as $warning) {
    $response['warnings'][] = advagg_validator_dom_extractor($warning);
  }

  // Return response array.
  return $response;
}

/**
 * Extract info from the DOMNode Object.
 *
 * @param object $dom
 *   DOMNode Class
 *
 * @return array
 *   Key Value pair from the DOM Node.
 */
function advagg_validator_dom_extractor($dom) {
  $node = $dom->firstChild;
  $output = array();
  do {
    $text = trim($node->nodeValue);
    if (!empty($text)) {
      $key = str_replace('m:', '', $node->nodeName);
      $output[$key] = $text;
    }
  } while ($node = $node->nextSibling);
  return $output;
}

/**
 * Finds all files that match a given mask in a given directory.
 *
 * Directories and files beginning with a period are excluded; this
 * prevents hidden files and directories (such as SVN working directories)
 * from being scanned.
 *
 * @param $dir
 *   The base directory or URI to scan, without trailing slash.
 * @param $mask
 *   The preg_match() regular expression of the files to find.
 * @param $options
 *   An associative array of additional options, with the following elements:
 *   - 'nomask': The preg_match() regular expression of the files to ignore.
 *     Defaults to '/(\.\.?|CVS)$/'.
 *   - 'nomask': The preg_match() regular expression of the dirs to ignore.
 *     Defaults to '/(\.git)/'.
 *   - 'callback': The callback function to call for each match. There is no
 *     default callback.
 *   - 'recurse': When TRUE, the directory scan will recurse the entire tree
 *     starting at the provided directory. Defaults to TRUE.
 *   - 'key': The key to be used for the returned associative array of files.
 *     Possible values are 'uri', for the file's URI; 'filename', for the
 *     basename of the file; and 'name' for the name of the file without the
 *     extension. Defaults to 'uri'.
 *   - 'min_depth': Minimum depth of directories to return files from. Defaults
 *     to 0.
 * @param $depth
 *   Current depth of recursion. This parameter is only used internally and
 *   should not be passed in.
 *
 * @return
 *   An associative array (keyed on the chosen key) of objects with 'uri',
 *   'filename', and 'name' members corresponding to the matching files.
 */
function advagg_validator_file_scan_directory($dir, $mask, $options = array(), $depth = 0) {
  // Merge in defaults.
  $options += array(
    'nomask' => '/(\.\.?|CVS)$/',
    'nodirmask' => '/(\.git)/',
    'callback' => 0,
    'recurse' => TRUE,
    'key' => 'uri',
    'min_depth' => 0,
  );

  $options['key'] = in_array($options['key'], array('uri', 'filename', 'name')) ? $options['key'] : 'uri';
  $files = array();
  if (is_dir($dir) && $handle = opendir($dir)) {
    while (FALSE !== ($filename = readdir($handle))) {
      if (!preg_match($options['nomask'], $filename) && $filename[0] != '.') {
        $uri = "$dir/$filename";
        $uri = file_stream_wrapper_uri_normalize($uri);
        if (is_dir($uri) && $options['recurse'] && !preg_match($options['nodirmask'], $uri)) {
          // Give priority to files in this folder by merging them in after any subdirectory files.
          $files = array_merge(advagg_validator_file_scan_directory($uri, $mask, $options, $depth + 1), $files);
        }
        elseif ($depth >= $options['min_depth'] && preg_match($mask, $filename)) {
          // Always use this match over anything already set in $files with the
          // same $$options['key'].
          $file = new stdClass();
          $file->uri = $uri;
          $file->filename = $filename;
          $file->name = pathinfo($filename, PATHINFO_FILENAME);
          $key = $options['key'];
          $files[$file->$key] = $file;
          if ($options['callback']) {
            $options['callback']($uri);
          }
        }
      }
    }

    closedir($handle);
  }

  return $files;
}

/**
 * Returns TRUE if the IP is a reserved one.
 *
 * @see http://stackoverflow.com/questions/14125735/how-to-know-if-an-ip-is-external-or-not/14125871#14125871
 * @see http://en.wikipedia.org/wiki/Reserved_IP_addresses
 *
 * @param $ip
 *   IP address string.
 * @return
 *   TRUE or FALSE.
 */
function advagg_validator_reserved_ip($ip) {
  $ip_long = sprintf('%u', ip2long($ip));

  $reserved_ips = array(
    '0'          => '16777215',   // 000.000.000.000 - 000.255.255.255
    '167772160'  => '184549375',  // 100.000.000.000 - 010.255.255.255
    '1681915904' => '1686110207', // 100.064.000.000 - 100.127.255.255
    '2130706432' => '2147483647', // 127.000.000.000 - 127.255.255.255
    '2851995648' => '2852061183', // 169.254.000.000 - 169.254.255.255
    '2886729728' => '2887778303', // 172.016.000.000 - 172.031.255.255
    '3221225472' => '3221225479', // 192.000.000.000 - 192.000.000.007
    '3221225984' => '3221226239', // 192.000.002.000 - 192.000.002.255
    '3232235520' => '3232301055', // 192.168.000.000 - 192.168.255.255
    '3323068416' => '3323199487', // 198.018.000.000 - 198.019.255.255
    '3325256704' => '3325256959', // 198.051.100.000 - 198.051.100.255
    '3405803776' => '3405804031', // 203.000.113.000 - 203.000.113.255
    '3758096384' => '4026531839', // 224.000.000.000 - 239.255.255.255
  );
  foreach ($reserved_ips as $ip_start => $ip_end) {
    if (($ip_long >= $ip_start) && ($ip_long <= $ip_end)) {
      return TRUE;
    }
  }
  return FALSE;
}
