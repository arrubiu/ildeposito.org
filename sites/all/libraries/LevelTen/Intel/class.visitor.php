<?php
/**
 * @file
 * @author  Tom McCracken <tomm@levelten.net>
 * @version 1.0
 * @copyright 2013 LevelTen Ventures
 * 
 * @section LICENSE
 * All rights reserved. Do not use without permission.
 * 
 */
namespace LevelTen\Intel;

require_once 'class.apiclient.php';

class ApiVisitor {
	protected $vtk;
	protected $apiVisitor;
	protected $apiClient;
	protected $cookies;

  public function __construct($vtk = '', $apiClientProperties = array()) {
    $this->apiClient = new ApiClient($apiClientProperties);
    $this->vtk = ($vtk == '') ? $this->extractVtk() : $vtk; 
    $this->cookies['va'] = $this->extractCookieVa();
  }
	
  public function load($params = array()){
  	$endpoint = 'visitor/load';
    if (empty($params['vtk'])) {
      $params['vtk'] = $this->vtk;
    }
  	try {
  	  $ret = $this->apiClient->getJSON($endpoint, $params);
  	  $this->apiVisitor = (object)$ret['visitor'];
  		return $this->apiVisitor;
  	} 
  	catch (Exception $e) {
  	  throw new Exception('Unable to load visitor: ' . $e);
  	}
  }
    
  public static function extractVtk() {
    if (!empty($_COOKIE['l10ivtk'])) {
      return $_COOKIE['l10ivtk'];
    }
    return '';
  }
  
  public static function extractCookieVa() {
    if (!empty($_COOKIE['__utmv'])) {
      $a = explode('3=va=', $_COOKIE['__utmv']);
      if (empty($a[1])) {
        return array();
      }
      $a = explode('^', $a[1]);
      return self::unserializeCustomVar($a[0]);      
    }
    return array();
  }
  
  public function getVtk() {
    return $this->vtk;
  }
  
  public function getVisitor() {
    return $this->apiVisitor;
  }
  
  public function getVar($scope, $namespace = 'default', $keys = '') {
    $data = $this->apiVisitor->{$scope . '_data'};
    if (empty($data[$namespace])) {
      return null;
    }
    $data = $data[$namespace];
    require_once 'libs/class.intel_data.php';
    return IntelData::getVar($data, $keys);
  }
  
  public function setVar($scope, $namespace, $keys, $value) {
    $data = $this->apiVisitor->{$scope . '_data'};
    if (empty($data[$namespace])) {
      return FALSE;
    }
    $data = $data[$namespace];
    require_once 'libs/class.intel_data.php';
    $this->apiVisitor->{$scope . '_data'}[$namespace] = IntelData::setVar($data, $keys, $value);
  }
  
  public function getFlags($scope = '') {
    static $cached;
    if (!empty($cached[$scope])) {
      return $cached;
    }
    $flags = array();
    if (!empty($this->apiVisitor_data['flags'])) {
      $flags += $this->apiVisitor_data['flags'];
    }
    if (!empty($this->session_data['flags'])) {
      $flags += $this->session_data['flags'];
    }
    if (!empty($_COOKIE['l10i_f'])) {
      $elms = $this->decodeCookieElements($_COOKIE['l10i_f']);
      if (is_array($elms)) {
        $flags += $elms;
      }
    }
    $cached[$scope] = $flags;
    return $flags;
  }
  
  public function getFlag($name, $scope = '') {
    $flags = $this->getFlags();
    if (!empty($flags[$name])) {
      return $flags[$name];
    }
    return null;
  }
  
  public static function encodeCookieElements ($elements) {
    $str = '';
    foreach ($elements AS $k => $v) {
      if (!$k) {
        continue;
      }
      $str .= $k . '=' . $v + '^';
    }
    $str = substr($str, 0, -1);
    return $str;
  }
   
  public static function decodeCookieElements($str) {
    $a = explode('^', $str);
    $elements = array();
    foreach ($a AS $e) {
      $b = explode('=', $e);
      $elements[$b[0]] = $b[1];
    }
    return $elements;
  }
  
  public static function  unserializeCustomVar($str) {
    $str = urldecode($str);
    $obj = array();
    $a = explode('&', $str);
    foreach ($a AS $i => $v) {
      $b = explode('=', $v);
      if ($b[0] == '') {
        continue;
      }
      $k = explode('.', $b[0]);
      if ((count($k) > 1) && (!isset($obj[$k[0]]))) {
        $obj[$k[0]] = array();
      }
      if (count($b) == 2) {
        if (count($k) > 1) {
          $obj[$k[0]][$k[1]] = (float) $b[1];
        }
        else {
          $obj[$k[0]] = (float) $b[1];
        }
      }
      else {
        if (count($k) > 1) {
          $obj[$k[0]][$k[1]] = '';
        }
        else {
          $obj[$k[0]] = '';
        }
      }
    }
    return $obj;
  }
  
  public function __toString() {
    if (!empty($_GET['debug'])) {
      return print_r($this->apiVisitor, 1);
    }
    else {
      return 'Visitor: ' . $this->vtk;
    }
  }
}