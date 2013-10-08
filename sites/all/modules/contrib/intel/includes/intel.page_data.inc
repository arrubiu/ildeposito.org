<?php
/**
 * @file
 * Provides meta data about site pages
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

function intel_parse_href($href, $location = '') {
  global $base_url, $base_path;
  // removed urls that cause errors
  if (substr($href, 0, 10) == '/404.html?') {
    return FALSE;
  }
  
  // remove trailing slash
  if (substr($href, -1) == '/') {
    $href = substr($href, 0, -1);
  }
  $params = array(
    'location' => $href,
  );
  $is_external = 0;

  $urlc = parse_url($href);
  
  $a = explode('//', $base_url);
  $internal_domains = array(
    $a[1] => $a[1],
  );
  
  $locc = parse_url($location);
  $loc_domain = '';
  $loc_root = '';
  if (!empty($locc['host'])) {
    $loc_domain = $locc['host'] . ((!empty($locc['port'])) ? ':' . $locc['port'] : '');
    if (!empty($locc['scheme'])) {
      $loc_root = $locc['scheme'] . '//' . $loc_domain;
    }    
  }  
  
  // absolute url
  if (!empty($urlc['scheme'])) {
    $is_external = 1;
    $href_domain = $urlc['host'] . ((!empty($urlc['port'])) ? ':' . $urlc['port'] : '');
    foreach ($internal_domains AS $idom) {
      if ($idom == $href_domain) {
        $is_external = 0;
        break;
      }
    }    
  }
  // internal url
  if (!$is_external) {
    // is homepage
    if (empty($urlc['path'])) {
      $params['system_path'] = variable_get('site_frontpage', 'node');
      $params['system_alias'] = '';
      return $params; 
    }
    $path = $urlc['path'];
    $source = drupal_lookup_path('source', $path);
    if ($source) {
      $alias = $path;
    }
    elseif (strpos($path, $base_path) === 0) {
      $p = substr($path, strlen($base_path));
      $source = drupal_lookup_path('source', $p);
      if ($source) {
        $alias = $p;
      }
    }
    if (!$source) {
      $source = $path;
    }

    $item = menu_get_item($source);
    if (empty($item) && (strpos($source, $base_path) === 0)) {
      $source = substr($source, strlen($base_path));
      $item = menu_get_item($source);
    }
    if ($item) {
      $params['system_path'] = $source;
      if (!empty($alias)) {
        $params['system_alias'] = $alias;
      } 
      else {
        $alias = drupal_lookup_path('alias', $source);
        if (!empty($alias)) {
          $params['system_alias'] = $alias;
        }         
      }
    }
    if (empty($urlc['scheme'])) {
      if (substr($params['location'], 0 , 1) == '/') {
        $params['location'] = $loc_root . $params['location'];
      }
      else {
        $params['location'] = $loc_root . '/' . $params['location'];
      }
    }
    
  }
  return $params; 
}

function intel_get_nid_from_path($url) {
  $nids = &drupal_static(__FUNCTION__);

  if (!isset($nids)) {
    $nids = array();
  }
  if (isset($nids[$url])) {
    return $nids[$url];
  }
  $params = intel_parse_href($url);
  if (!empty($params['system_path']) && (substr($params['system_path'], 0, 5) == 'node/')) {
    $a = explode('/', $params['system_path']);
    $nids[$url] = (int)$a[1];
    return $nids[$url];
  }
  return FALSE;    
}

function intel_get_page_meta_callback($path) {
  return intel_get_node_meta_from_path($path);
}

function intel_get_node_meta_from_path($url) {
  if ($nid = intel_get_nid_from_path($url)) {    
    $meta = intel_get_node_meta($nid);
    $meta->intent = intel_get_page_intent($nid, 'nid');    
    return $meta;
  }
  return FALSE;
}

function intel_get_node_meta($nid) {
  $query = db_select('node', 'n')
    ->fields('n')
    ->condition('nid', $nid);
  return $query->execute()->fetchObject();  
}

function intel_get_node_created($url) {
  if ($nid = intel_get_nid_from_path($url)) {
    $query = db_select('node', 'n')
      ->fields('n', array('created'))
      ->condition('nid', $nid);
    return $query->execute()->fetchField();    
  }
  return FALSE;
}

function intel_get_node_title($url) {
  $params = intel_parse_href($url);
  if (!empty($params['system_path']) && (substr($params['system_path'], 0, 5) == 'node/')) {
    $a = explode('/', $params['system_path']);
    $nid = $a[1];
    $query = db_select('node', 'n')
      ->fields('n', array('title'))
      ->condition('nid', $nid);
    return $query->execute()->fetchField();
  }
  return FALSE;    
}
/**
 * Returns the page intent of a url
 * TODO change this so that page intent is based on GA page attribute
 * @param unknown_type $id
 * @param unknown_type $id_type
 * @param unknown_type $return
 */
function intel_get_page_intent($id, $id_type = '', $return = 'key') {
  $intents = intel_get_page_intents();
  $key = '';
  if (is_string($id) || ($id_type == 'url')) {
    $params = intel_parse_href($id);
    if ($params['system_path']) {
      if ((substr($params['system_path'], 0, 5) == 'node/')) {
        $a = explode('/', $params['system_path']);
        $nid = $a[1];
        $node_meta = intel_get_node_meta($nid);
      }
      elseif (path_is_admin($params['system_path'])) {
        $key = 'a';
      }
    }
    
  }
  elseif (is_int($id) || $id_type == 'nid') {
     $node_meta = intel_get_node_meta($id);
  }
  elseif (is_object($id) || $id_type == 'node') {
     $node_meta = $id;
  }
  if (empty($node_meta)) {
    return FALSE;
  }
  if (
    ($node_meta->type == 'enterprise_blog')
    || ($node_meta->type == 'enterprise_audio') 
    || ($node_meta->type == 'enterprise_video')
    || ($node_meta->type == 'enterprise_wiki')
  ) {
    $key =  't';
  }
  elseif (($node_meta->type == 'enterprise_landingpage') || ($node_meta->type == 'webform')) {
    $key =  'l';
  }
  elseif ($node_meta->type == 'enterprise_thankyou') {
    $key =  'u';
  }
  else {
    $key = 'i';
  }
  drupal_alter('intel_page_intent_key', $key, $id, $id_type);
  if ($return == 'key') {
    return $key;
  }
  else {
    return $intents[$key];
  }
}