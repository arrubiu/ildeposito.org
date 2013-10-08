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
require_once 'class.exception.php';

class ApiProperty {

  protected $pid;
	protected $apiProperty;
	protected $apiClient;

  public function __construct($pid = '', $apiClientProperties = array()) {
    $this->apiClient = new ApiClient($apiClientProperties);
    $this->pid = $pid; 
  }
	
  public function load($params = array(), $data = array()){
  	$endpoint = 'property/load';
    if (empty($params['pid'])) {
      $params['pid'] = $this->pid;
    }
  	try {
  	  $ret = $this->apiClient->getJSON($endpoint, $params, $data);
  	  $this->apiProperty = (object)$ret['property'];
  		return $this->apiProperty;
  	} 
  	catch (L10IntelException $e) {
  		throw new L10IntelException('Unable to load property: ' . $e);
  	}
  }
  
  public function save($params = array(), $data = array()){
    $endpoint = 'property/save';
    if (empty($params['pid'])) {
      $params['pid'] = $this->pid;
    }
    try {
      $ret = $this->apiClient->getJSON($endpoint, $params, $data);
      if (isset($ret['property'])) {
        $this->apiProperty = (object)$ret['property'];
      }
      else {
        throw new L10IntelException('Property not returned from API. msg: ' . $ret['message']);
      }
    } 
    catch (L10IntelException $e) {
      throw new L10IntelException('Unable to save property: ' . $e);
    }
  }
    
  public function getPtkid() {
    return $this->ptkid;
  }
  
  public function getProperty() {
    return $this->apiProperty;
  }
  
  public function __toString() {
    if (!empty($_GET['debug'])) {
      return print_r($this->apiProperty, 1);
    }
    else {
      return 'Property: ' . $this->ptk;
    }
  }
}