<?php
/**
 * @file
 * Support for adding intelligence to pages and processing form submissions
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_page_alter(&$page) {
  require_once drupal_get_path('module', 'intel') . "/includes/intel.ga.inc"; 
  
  global $user; 
  
  $path_is_admin = path_is_admin(current_path());
  
  $ga_va = array();
  if ($user->uid && !empty($_COOKIE['__utmv'])) {
    if (intel_include_library_file('class.visitor.php')) {
      $ga_va = \LevelTen\Intel\ApiVisitor::extractCookieVa();
    }
  }  

  $is_landingpage = 0;
  
  $entity = '';
  $entity_settings = variable_get('intel_page_attributes_entity_settings', array());
  $visitor_attrs = array();
  $page_attrs = array();
  $l10i_var_action = array(
    'method' => '_setIntelVar',
    'scope' => 'page',
    'namespace' => 'analytics',
  );
  // Add section and content type custom vars  
  if (arg(0) == 'node') {
    $entity = menu_get_object();

    if ($entity) {
      $entity_type = 'node';
      $entity_bundle = $entity->type;
      if (isset($entity_settings[$entity_type][$entity_bundle])) {
        $page_entity_settings = $entity_settings[$entity_type][$entity_bundle];
      }  
      $page_attrs['pt'] = $entity->created;
      $page_attrs['et'] = 'n';
      $page_attrs['ct'] = str_replace('enterprise_', '', $entity->type); // trim enterprise namespace in Open Enterprise
    }
  }
  elseif (arg(0) == 'user') {
    $entity = menu_get_object('user');
    if ($entity) {
      $entity_type = 'user';
      $entity_bundle = 'und';
      $s = variable_get('intel_page_attributes_entity_settings', array());
      if (isset($entity_settings[$entity_type][$entity_bundle])) {
        $page_entity_settings = $entity_settings[$entity_type][$entity_bundle];
      } 
      $page_attrs['pt'] = $entity->created;
      $page_attrs['et'] = 'u';
  
      if (!isset($entity_settings['track_page_uid'])) {
        $entity_settings['track_page_uid'] = 'u';
      }
    }
  }
  // TODO support for taxomony terms
  
  // do field operations
  if ($entity) { 
    $lang = !empty($entity->language) ? $entity->language : LANGUAGE_NONE;
    $fields_info = field_info_instances($entity_type, $entity_bundle);
//dsm($entity);
//dsm($entity_settings);
//dsm($page_entity_settings);
//dsm($fields_info);

    // track entity uid (e.g. node author)
    if (!isset($page_entity_settings['track_page_uid']) || $page_entity_settings['track_page_uid']) {
      $key = !empty($page_entity_settings['track_page_uid']) ? $page_entity_settings['track_page_uid'] : 'a';
      if ($key == 1) {
        $key = 'a';
      }
      $page_attrs[$key] = $entity->uid;
    } 
    
    // track page intent
    $intent = INTEL_PAGE_INTENT_DEFAULT;
    if ($path_is_admin) {
      $intent = 'a';
    }
    if (!empty($page_entity_settings['page_intent'])) {
      $intent = $page_entity_settings['page_intent'];
    }
    if (!empty($entity->field_page_intent[$lang][0]['value']) && ($entity->field_page_intent[$lang][0]['value'] != '_default')) {
      $intent = $entity->field_page_intent[$lang][0]['value'];
    }
    if ($intent) {
      $page_attrs['i'] = array(
        $intent => '',
      );
      if ($intent == 'l') {
        $is_landingpage = 1;
      }     
    }

    // track page taxonomy terms
    $l10i_var_action['value'] = '';
    foreach ($fields_info AS $key => $field) {
      if (isset($entity->{$key}[$lang][0]['tid'])) {
        $field_info = field_info_field($key);
        $vocab_name = $field_info['settings']['allowed_values'][0]['vocabulary'];
        if (!empty($entity_settings['taxonomy'][$vocab_name]['track_page_terms'])) {
          foreach ($entity->{$key}[$lang] AS $t) {
            $page_attrs['t'] = array(
              $t['tid'] => '',
            );
          }
        }
      }
    }
    
    // set custom page attributes if page_attribute_col field exists
    if (!empty($entity->field_page_attribute_col[$lang]) && is_array($entity->field_page_attribute_col[$lang])) {
      foreach ($entity->field_page_attribute_col[$lang] AS $i => $e) {
        $collection = field_collection_item_load($e['value']);
        $keys = explode('.', $collection->field_page_attribute[$lang][0]['value']);
        $value = isset($collection->field_page_attribute_value[$lang][0]['value']) ? $collection->field_page_attribute_value[$lang][0]['value'] : '';
        if (count($keys) == 1) {  // flag and scalar values
          $page_attrs[$keys[0]] = $value; 
        } 
        else {
          if (!isset($page_attrs[$keys[0]])) {
            $page_attrs[$keys[0]] = array();
          }
          $page_attrs[$keys[0]][$keys[1]] = $value;
        }        
      }
    }
    
      // set custom visitor attributes if visitor_attribute_col field exists
    if (!empty($entity->field_visitor_attribute_col[$lang]) && is_array($entity->field_visitor_attribute_col[$lang])) {
      foreach ($entity->field_visitor_attribute_col[$lang] AS $i => $e) {
        $collection = field_collection_item_load($e['value']);
        $keys = explode('.', $collection->field_visitor_attribute[$lang][0]['value']);
        $value = isset($collection->field_visitor_attribute_value[$lang][0]['value']) ? $collection->field_visitor_attribute_value[$lang][0]['value'] : '';
        if (count($keys) == 1) {  // flag and scalar values
          $visitor_attrs[$keys[0]] = $value; 
        } 
        else {
          if (!isset($visitor_attrs[$keys[0]])) {
            $visitor_attrs[$keys[0]] = array();
          }
          $visitor_attrs[$keys[0]][$keys[1]] = $value;
        }        
      }
    }    
  }
  
  // set user role visitor attribute
  // only when user is logged in (otherwise page caching will cause errors)
  if ($user->uid) {
//dsm($user);
//dsm($ga_va);
    $cur = isset($ga_va['r']) ? $ga_va['r'] : array();
    foreach ($user->roles AS $i => $l) {
      // don't send anonomous role
      if ($i == 1) {
        //continue;
      }
      if (!isset($cur[$i])) { 
        if (!isset($visitor_attrs['r'])) {
          $visitor_attrs['r'] = array();
        }
        $visitor_attrs['r'][$i] = '';
      }     
    }
  }
  
//dsm($page_attrs); 
//dsm($visitor_attrs);   
  $l10i_var_action = array(
    'method' => '_setIntelVar',
    'scope' => 'page',
    'namespace' => 'analytics',
  );
  foreach ($page_attrs AS $key => $value) {
    if (is_array($value)) {
      foreach ($value AS $key2 => $value2) {
        $l10i_var_action['keys'] = "$key.$key2";
        $l10i_var_action['value'] = $value2;
        intel_add_page_intel_push($l10i_var_action);
      }
    }
    else {
      $l10i_var_action['keys'] = $key;
      $l10i_var_action['value'] = $value;
      intel_add_page_intel_push($l10i_var_action);      
    }
  }
  
  $l10i_var_action['scope'] = 'visitor';
  foreach ($visitor_attrs AS $key => $value) {
    if (is_array($value)) {
      foreach ($value AS $key2 => $value2) {
        $l10i_var_action['keys'] = "$key.$key2";
        $l10i_var_action['value'] = $value2;
        intel_add_page_intel_push($l10i_var_action);
      }
    }
    else {
      $l10i_var_action['keys'] = $key;
      $l10i_var_action['value'] = $value;
      intel_add_page_intel_push($l10i_var_action);      
    }
  }
  

  
  intel_check_form_submission($page);
  
  // check form processing
  $track_forms = 1;
  if (isset($node->type) && ($node->type == 'webform')) {
    // check if page is a webform submit validation
    if (!empty($_POST['form_id']) && (substr($_POST['form_id'], 0, 20) == 'webform_client_form_')) {
      $track_forms = 0;
    }
  }
  
  //if (isset($node->type) && ($node->type == 'enterprise_landingpage')) {
  //  $is_landingpage = 1;
  //}
  
  
  global $base_root, $base_path; 

  $js = array(
    'intel' => array(
      'script_domain' => $base_root . $base_path,
      'module_path' => drupal_get_path('module', 'intel'),
      'system_path' => $_GET['q'],
      'page_title' => !empty($node->title) ? $node->title : '',
      'track_analytics' => 0,
      'track_adhoc_ctas' => 'track-cta',
      'track_adhoc_events' => 'track-event',
      'track_forms' => $track_forms,
      'is_landingpage' => $is_landingpage,
      'pushes' => intel_get_page_intel_pushes(),
      'scorings' => intel_get_scorings(),
    ),
    'disqus' => array(
      'callback_onnewcomment' => 'l10iDisqus.trackComment',
    ),
  );
//dsm(intel_get_page_intel_pushes());
  if ($ga_domain = variable_get('intel_domain_name', '')) {
    $js['intel']['ga']['_setDomainName'] = $ga_domain;
  }
  
  // Get page status code for visibility filtering.
  $id = variable_get('googleanalytics_account', '');
  $status = drupal_get_http_header('Status');
  $trackable_status_codes = array(
    '403 Forbidden',
    '404 Not Found',
  );
  $track = 1;
  if (!(_googleanalytics_visibility_pages() || in_array($status, $trackable_status_codes)) && _googleanalytics_visibility_user($user)) {
    $track = 0;
    $js['intel']['track_analytics'] = 0;
  } 
  if (path_is_admin(current_path())) {
    $track = 0;  
  }
  if (!$track) {    
    $js['intel']['track_forms'] = 0;
    $js['intel']['track_adhoc_ctas'] = 0;
    $js['intel']['track_adhoc_events'] = 0;
  }
  else {
    $scripts = intel_intel_scripts();
    $enabled = variable_get('intel_intel_scripts_enabled', array());
    foreach ($scripts AS $key => $script) {
      if (!empty($enabled[$key]) || (!isset($enabled[$key]) && !empty($script['enabled']))) {
        drupal_add_js($script['path']);
      }
    }
  }

  
  if (!empty($_GET['debug'])) {
    if ($_GET['debug'] == 'ie9') {
      $script = "http://ie.microsoft.com/testdrive/HTML5/CompatInspector/inspector.js";
      drupal_add_js($script, array('scope' => 'header', 'type' => 'external', 'weight' => -10, 'group' => JS_LIBRARY));
    }
  }
  
  $script = intel_get_js_embed('l10i', 'local');
  drupal_add_js($script, array('type' => 'inline', 'scope' => 'header'));

  /**
   * check admin alter enhancements
   */
  if ($_GET['q'] == 'admin/content') {
    drupal_add_css(drupal_get_path('module', 'intel') . '/css/intel.report.css');
    drupal_add_js(drupal_get_path('module', 'intel') . '/js/intel.admin_content_alter.js');
  }
  if ($_GET['q'] == 'admin/content/cta') {
    drupal_add_js(drupal_get_path('module', 'intel') . '/js/intel.admin_content_cta_alter.js');
  }

  drupal_alter('intel_page_settings_js', $js, $page);
//dsm($js);
  drupal_add_js($js, 'setting');
}

function intel_add_page_intel_push($push, $index = '') {
  return intel_page_intel_pushes('add', $push, $index);
}

function intel_get_page_intel_pushes() {
  return intel_page_intel_pushes('get');
}

function intel_page_intel_pushes($action = 'get', $push = array(), $index = '') {
  static $pushes = array();
  if ($action == 'add') {
    if (!$index) {
      $index = 'i' . count($pushes);
    }
    $pushes[$index] = $push; 
  }
  return array_values($pushes);
}

/**
 * Sanitizes event tracking data that is being put into javascript.
 */
function _intel_ga_event_sanitize_events($ga_events) {
  if (is_array($ga_events)) {
    foreach ($ga_events as $i => $event) {
      foreach ($event as $j => $e) {
        $ga_events[$i][$j] = filter_xss($e);
      }
    }
    return $ga_events;
  }
  else {
    return array();
  }
}

/**
 * Implements hook_page_alter().
 */


function intel_get_js_embed($type = 'intel', $mode = 'external', $version = 'latest', $terminator = "") {
  $script = '';
  $debug = 0;
  $l10i_ga_account = variable_get('intel_ga_account', '');
  $l10i_domain_name = variable_get('intel_domain_name', '');
  $l10i_ga_tracker_prefix = variable_get('intel_ga_tracker_prefix', 'l10i');
  $api_level = variable_get('intel_api_level', '');
  if ($l10i_ga_account && !$l10i_ga_tracker_prefix) {
    $l10i_ga_tracker_prefix = 'l10i';
  }

  $wrap = ($mode == 'external') ? 1 : 0;
  if ($version == 'simple') {
    $wrap = 0;
    $script .= '<script>' . $terminator;
  }
  if (($type == 'ga') || ($type == 'combined')) {
    $library_tracker_url = '.google-analytics.com/ga.js';
    $library_cache_url = 'http://www' . $library_tracker_url;
    if (variable_get('googleanalytics_cache', 0) && $url = _googleanalytics_cache($library_cache_url)) {   
      $ga_src = 'ga.src = "' . $url . $query_string . '";';
    }
    else {
      $ga_src = "ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';";
    }
    $gaid = variable_get('googleanalytics_account', '');
       
    $script .= "var _gaq = _gaq || [];" . $terminator;
    $script .= "_gaq.push(['_setAccount', '$gaid']);" . $terminator;
    if ($l10i_domain_name) {
      $script .= "_gaq.push(['_setDomainName', '$l10i_domain_name']);" . $terminator;
    }
    $script .= "_gaq.push(['_trackPageview']);" . $terminator;
    $script .= "(function() {" . $terminator;
    $script .= "var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;" . $terminator;
    $script .= $ga_src . $terminator;
    $script .= "var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);" . $terminator;
    $script .= "})();" . $terminator;
  }
  if ($api_level && (($type == 'l10i') || ($type == 'combined'))) {
    list($proto, $host_root) = explode('//', $GLOBALS['base_url']);
    $library_path = libraries_get_path('LevelTen') . 'Intel/scripts';
    //$api_hostpath = variable_get('intel_l10iapi_hostpath', '');
    $api_url = variable_get('intel_l10iapi_url', '');
    
    if (!$api_url) {
      $api_url = INTEL_L10IAPI_URL;
    }
    $data_mode = (variable_get('intel_api_level', 'free') == 'free') ? 0 : 1;
    $a = explode('//', $api_url);
    $api_hostpath = $a[1];
    $api_pid = variable_get('intel_l10iapi_profileid', '');
    $sv = (variable_get('intel_debug_mode', 0)) ? '' : '.min';
    //$script .= "// LevelTen Intelligence" . $terminator;
    $script .= "var _l10iq = _l10iq || [];" . $terminator;
    $script .= "var _intel = _intel || [];" . $terminator;    
    $script .= "_l10iq.push(['_setTrackerPrefix', '$l10i_ga_tracker_prefix']);" . $terminator;  
    $script .= "_l10iq.push(['_setAccount', '$l10i_ga_account']);" . $terminator; 
    if ($l10i_domain_name) {
      $script .= "_l10iq.push(['_setDomainName', '$l10i_domain_name']);" . $terminator;
    }
    $script .= "_l10iq.push(['_setApiUrl', '$api_url/']);" . $terminator; 
    $script .= "_l10iq.push(['_setDataMode', $data_mode]);" . $terminator;  
    //$script .= "_l10iq.push(['_setOptions', Drupal.settings.intel]);" . $terminator;  
    
    if ($version == 'latest') {
      $fr = ($debug) ? " + '?t=' + new Date().getTime()" : ''; 
      $script .= "(function() {" . $terminator;
      $script .= "var l10i = document.createElement('script'); l10i.type = 'text/javascript'; l10i.async = true;" . $terminator;
      $script .= "l10i.src = ('https:' == document.location.protocol ? 'https://' : 'http://') + '$api_hostpath/js/l10i_1$sv.js'$fr;" . $terminator;
      $script .= "var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(l10i, s);" . $terminator;
      $script .= "})();" . $terminator;

      if (0) { // use combined l10i.js
        $script .= "(function() {" . $terminator;
        $script .= "var l10il = document.createElement('script'); l10il.type = 'text/javascript'; l10il.async = true;" . $terminator;
        $script .= "l10il.src = ('https:' == document.location.protocol ? 'https://' : 'http://') + '$api_hostpath/js/intel$sv.js'$fr;" . $terminator;
        //$script .= "l10il.src = ('https:' == document.location.protocol ? 'https://' : 'http://') + '$host_root/$library_path/intel$sv.js'$fr;" . $terminator;
        $script .= "var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(l10il, s);" . $terminator;
        $script .= "})();" . $terminator;
      }
    }
    elseif ($version == 'simple') {
      $script .= '</script>' . $terminator;
      $script .= '<script src="http://' . $api_hostpath . '/js/l10i_1' . $sv . '.js"></script>' . $terminator;
      if (0) { // use combined l10i.js
        $script .= '<script src="http://' . $api_hostpath . '/js/intel.js"></script>' . $terminator;
      }
    }
  }
  if ($wrap) {
    $script = '<script>' . $script . '</script>'; 
  }
  return $script;
}

/**
 * Implements hook_js_alter()
 * Compile intel settings and pass to l10iq via _setOptions
 * @param unknown_type $javascript
 */

function intel_js_alter(&$javascript) {
  $options = array();
  if (!empty($javascript['settings']['data']) && is_array($javascript['settings']['data'])) {
    foreach ($javascript['settings']['data'] AS $i => $v) {
      if (!empty($v['intel'])) {
        $options[] = $v['intel'];
      }
    }
  }
  $i = 0;
  while (isset($javascript[$i])) {
    if (substr($javascript[$i]['data'], 0, 10) == 'var _l10iq') {
      $json = drupal_json_encode(drupal_array_merge_deep_array($options));
      $javascript[$i]['data'] .= "_l10iq.push(['_setOptions', $json]);";  
      break;
    }    
    $i++;
  }
}

/*
function intel_js_alter(&$javascript) {
  // TODO check the best way to do these things. Why does ga use the style of embed they do for ga.js? Should we follow that style?
  // add new tracking codes
  list($proto, $host_root) = explode('//', $GLOBALS['base_url']);
  $module_path = drupal_get_path('module', 'intel');
  $weight = -99;
  $scope = 'header';
  $script0 = "var _gaq = _gaq || [];\n";
  $script = intel_get_js_embed('l10i', 'local');
  
  // find and remove "_trackPageview"
  for ($i = 0; !empty($javascript[$i]); $i++) {
    if (strpos($javascript[$i]['data'], 'var _gaq') === 0) {
//dsm($javascript[$i]);
      $ga_found = TRUE;
      // remove trackPageview so we can insert custom vars first
      $javascript[$i]['data'] = str_replace('_gaq.push(["_trackPageview"]);', '', $javascript[$i]['data']);
      //$weight = $javascript[$i]['weight']+1;
      $scope = $javascript[$i]['scope'];
      $script0 = '';
   }
  }
  // TODO this is probably not the best way to do this. Research proper way.
  $javascript[] = array(
    'scope' => $scope,
    'type' => 'inline',
    'group' => 0,
    'every_page' => TRUE,      
    'weight' => $weight,
    'cache' => TRUE,
    'defer' => FALSE,
    'preprocess' => TRUE,
    'data' => $script0 . $script, 
  );
} 
*/

function intel_check_form_submission($page) {
  // check for webform submission
  $track = array(
    'category_id' => '',
    'value' => '', 
    'submission_path' => '',
    'form_title' => '',
  );
  $link_query = array();
  $submission = intel_submission_construct();
  $submission_data = array();
  // fire hook for modules to report if a form has been submitted by setting $submission->type
  foreach (module_implements('intel_form_submission_check') AS $module) {
    $function = $module . '_intel_form_submission_check';
    $function($submission, $submission_data, $track, $link_query);
  }
  if (empty($submission->type)) {
    return;
  }
  
  require_once drupal_get_path('module', 'intel') . "/includes/intel.ga.inc";
  $visitor = intel_visitor_load();
  if (!empty($visitor->vtk)) {
    try {
      $visitor->apiLoad();
    }
    catch (Exception $e) {
      // do nothing
    }
  }

  $vars = array(
    'type' => $submission->type,
    'fid' => $submission->fid,
    'fsid' => $submission->fsid,
  );
  $submission0 = intel_submission_load_by_vars($vars);

  // TODO check this data for a while to assure uniqueness of fsids, then exit if previous submission exists.
  if (!empty($submission0->sid)) {
    // form submission already created
    $vars = array(
      '!submission0' => print_r($submission0, 1),
      '!get' => print_r($_GET, 1),
      '!cookie' => print_r($_COOKIE, 1),
    );
    watchdog('intel', "form already submitted on form submission. <br>\n submission0=!submission0<br>\n<br>\nget=!get<br>\n<br>\ncookie=!cookie", $vars, WATCHDOG_DEBUG);  
    return '';
  }
  
  $a = explode('//', $GLOBALS['base_url']);
  $host = $a[1];
  
//dsm($page);  
//dsm($wf_node);
//dsm($_COOKIE);
  // check thankyou page settings
  $node = menu_get_object();
//dsm($node);
  if (!empty($node) && isset($node->field_track_submission[$node->language][0]['value'])) {
    $track['category_id'] = $node->field_track_submission[$node->language][0]['value'];
  }
  if (!empty($node) && isset($node->field_track_submission_value[$node->language][0]['value'])) {
    $track['value'] = $node->field_track_submission_value[$node->language][0]['value'];
  }
  $submission->response_page_path = url($_GET['q']);
  $submission->response_page_host = $host;
  if (!empty($node)) {
    $submission->response_page_id = $node->nid; 
  }
  
  $scorings = intel_get_scorings();
  $submit_context = array();
  $cta_context = array();
    
  // if vid not set on visitor, save to create vid
  if (!empty($visitor->vtk) && empty($visitor->vid)) {
    $visitor->save();
  }
  $submission->vid = $visitor->vid;

  if (!empty($visitor->apiVisitor->vtk)) {
    $fsi = $visitor->getVar('api_session', 'form_submit', '_updated'); 
    if (empty($fsi)) {
      $fsi = $visitor->getFlag('lfs');  // _updated is a better key for cross site forms
    }
    $submit_context = $visitor->getVar('api_session', 'form_submit', $fsi);
    if (!empty($submit_context)) {
      $referrer = !empty($submit_context['system_path']) ? $submit_context['system_path'] : $submit_context['location'];
      // strip query string
      $a = explode("?", $referrer);
      $referrer = $a[0];
      $urlc = parse_url($submit_context['location']);
//dsm($urlc);
      $submission->form_page_host = $urlc['host'];
      $submission->form_page_path = $urlc['path'];

      if (!empty($submit_context['system_path'])) {
        $a = explode('/', $submit_context['system_path']);
        $lp_node = node_load($a[1]);
        $submission->form_page_id = $lp_node->nid;
        // check if redirect set
        if (isset($lp_node->language)) {
          $url = '';      
          if (isset($lp_node->field_thankyou[$lp_node->language][0]['target_id'])) {
            $url = 'node/' . $lp_node->field_thankyou[$lp_node->language][0]['target_id'];
          }
          elseif (isset($lp_node->field_url_redirect[$lp_node->language][0]['url'])) {
            $url = trim($lp_node->field_url_redirect[$lp_node->language][0]['url']);
          }
          if ($url && ($url != $_GET['q'])) {
            $options = array('query' => $link_query);
            drupal_goto($url, $options);
            exit;
          }
        }
      }

      if (!empty($submit_context['is_landingpage'])) {
        $category = t('Landing page conversion') . '!';
        $track_conversion_value = (isset($scorings['landing_page_conversion'])) ? $scorings['landing_page_conversion'] : 0;      

        if (isset($lp_node->field_track_conversion)) {
          $track_conversion = $node->field_track_submission[$node->language][0]['value'];
          if (strpos($track_conversion, 'conversion') !== FALSE) {
            $category = t('Landing page conversion');
          }
          elseif (strpos($track_conversion, 'conversion!') === FALSE) {
            $category = '';
          }
        }
        if (isset($lp_node->field_track_conversion_value) && (trim($lp_node->field_track_conversion_value) == '')) {
          $track_conversion_value = $node->field_track_submission_value[$node->language][0]['value'];
        }

        if ($category) {     
          $call = array(
            'method' => '_addIntelEvent',
            'event' => 'pageshow',
            'selector' => 'body',
            'category' => $category,
            'action' => !empty($submit_context['page_title']) ? $submit_context['page_title'] : (!empty($lp_node->title) ? $lp_node->title : ''),
            'label' => $referrer,
            'value' => $track_conversion_value,
            'noninteraction' => FALSE,
            'location' => !empty($submit_context['location']) ? $submit_context['location'] : (!empty($lp_node->nid) ? url("node/{$lp_node->title}") : ''),
          );
          intel_add_page_intel_push($call);
        }
      }
      //unset($visitor->session_data['form_submit'][$fsi]);
      
      // check if CTA was used to get there
      $cta_clicks = $visitor->getVar('api_session', 'cta_click');
      if (!empty($cta_clicks) && is_array($cta_clicks)) {
        foreach ($cta_clicks AS $index => $click) {
          // filter "meta" elements
          if (substr($index, 0, 1) == '_') {
            continue;
          }
          if ($referrer = $click['href']) {
            $cta_context = $click;
            $value = (isset($scorings['cta_conversion'])) ? $scorings['cta_conversion'] : 0;
            if (substr($click['label'], 0, 6) == 'block/') {
              // TODO make work with both blocks and beans
              $delta = substr($click['label'], 6);
              $submission->cta_id = $delta;
              $meta = cta_bean_meta_load($delta);
              if (isset($meta['data']['ga_event']['conversion']['value'])) {
                $value = $meta['data']['ga_event']['conversion']['value'];
              }
            }
            $call = array(
              'method' => '_addIntelEvent',
              'event' => 'pageshow',
              'selector' => 'body',
              'category' => t('CTA conversion!'),
              'action' => $click['action'],
              'label' => $click['label'],
              'value' => $value,
              'noninteraction' => FALSE,
              'location' => $click['location'],
            );    
            intel_add_page_intel_push($call);
            $urlc = parse_url($click['location']);
            $submission->cta_page_host = $urlc['host'];
            $submission->cta_page_path = $urlc['path'];
            $a = explode('/', $click['system_path']);
            $submission->cta_page_id = $a[1];              
            break;
          }
        }
      }
    }
  }

//dsm($track_submission); 
//dsm($track_submission_value);  
//dsm($scorings);
//dsm('track0=');dsm($track);
  $scoreing_meta = intel_init_scoring();
//dsm($scoreing_meta);
  if ($track['category_id'] == 'form_submission') {
    $category = t('Form submission');
    $track['value'] = ($track['value']) ? $track['value'] : 0;
  }
  elseif (isset($scoreing_meta[$track['category_id']])) {
    $category = $scoreing_meta[$track['category_id']]['eventcategory'] . '+';
    $track['value'] = ($track['value']) ? $track['value'] : $scorings[$track['category_id']];
  }
  else {
    $category = t('Form submission') . '!';
    $track['value'] = ($track['value']) ? $track['value'] : $scorings['form_submission'];
  }
  
  // add L10iVisitor object to visitor for alter hooks
  drupal_alter('intel_submission', $submission, $visitor, $submit_context, $cta_context);
//dsm('$submission='); dsm($submission);
  if (!empty($submission->vid)) {
    $sid = intel_submission_save($submission);
  }
  
  if (!$track['submission_path']) {
    $track['submission_path'] = 'submission/' . $sid;
  }
//dsm('track1=');dsm($track);
  $call = array(
    'method' => '_addIntelEvent',
    'event' => 'pageshow',
    'selector' => 'body',
    'category' => $category,
    'action' => $track['form_title'],
    'label' => $track['submission_path'],
    'value' => $track['value'],
    'noninteraction' => FALSE,
    'location' => !empty($submit_context['location']) ? $submit_context['location'] : (!empty($lp_node->nid) ? url("node/{$lp_node->nid}") : ''),
  );
  //drupal_alter('intel_page_intel_push', $call, 'form_submit', $visitor, $submit_context);
  intel_add_page_intel_push($call);
//dsm('page_intel_push=');dsm($call);
  // add known attribute
  if (!empty($visitor->email)) {
    $call = array(
      'method' => '_setIntelVar',
      'scope' => 'visitor',
      'namespace' => 'analytics',
      'keys' => 'k',
      'value' => '',
    );
    intel_add_page_intel_push($call);
  }
  $context = 'form_submit';
  if (empty($visitor->contact_created) && !empty($visitor->email)) {
    $visitor->setContactCreated(time());
  }
  $visitor->setLastActivity(time());
  $vars = array(
    'submit_context' => $submit_context,
    'submission' => $submission,
  );
  drupal_alter('intel_visitor', $visitor, $context, $vars);
//dsm('$visitor='); dsm($visitor->getProperties());
  if (!empty($visitor->vid)) {
    intel_visitor_save($visitor);
  }    
  
  // queue to sync visitor data
  intel_add_visitor_sync_request($visitor->vtk);

  // temp code to track submission for testing
  $vars = array(
    '!submit_context' => print_r($submit_context, 1),
    '!visitor' => print_r($visitor->getVisitor(), 1),
    '!submission' => print_r($submission, 1),
    '!get' => print_r($_GET, 1),
    '!cookie' => print_r($_COOKIE, 1),
  );
  watchdog('intel', "form submission on form submission. <br>\n visitor=!visitor <br>\n<br>\nsubmission=!submission <br>\n<br>\nsubmit_context=!submit_context <br>\n<br>\nget=!get <br>\n<br>\ncookie=!cookie", $vars, WATCHDOG_DEBUG);  
  
  if (!empty($_GET['debug'])) {
    dsm('$submit_context='); dsm($submit_context);
    dsm('$visitor='); dsm($visitor->getVisitor());
    dsm('$submission='); dsm($submission);
  }
}