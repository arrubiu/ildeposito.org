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
require_once 'class.exception.php';
if (!empty($_GET['debug'])) {
  require_once 'libs/class.debug.php'; 
}

class ApiClient {
    protected $apiKey;
    protected $apiUrl = 'http://api.leveltendesign.com/v1/intel';
    protected $apiConnector = '';
    protected $apiUrlCallMethod = 'curl';
    protected $isTest = FALSE;
    protected $host;
    protected $path;
    protected $userAgent = 'LevelTen\Intel\ApiClient';  

    /**
     * The HTTP code for a successful request
     */
    const STATUS_OK = 200;

    /**
     * The HTTP code for bad request
     */
    const STATUS_BAD_REQUEST = 400;

    /**
     * The HTTP code for unauthorized
     */
    const STATUS_UNAUTHORIZED = 401;

    /**
     * The HTTP code for resource not found
     */
    const STATUS_NOT_FOUND = 404;

    /**
    * Constructor.
    *
    * @param $HAPIKey: String value of HubSpot API Key for requests
    **/
    public function __construct($properties = array()) {        
      foreach ($properties AS $prop => $value) {
        if (isset($this->$prop)) {
          $this->$prop = $value;
        }
      }      
      $this->host = !empty($_SERVER['HTTP_HOST']) ? $_SERVER['HTTP_HOST'] : '';
      $this->path = !empty($_SERVER['REQUEST_URI']) ? $_SERVER['REQUEST_URI'] : '';
    }
    
    public function getJSON($endpoint, $params = array(), $data = array()) {
      if (!$this->apiUrl && !$this->apiConnector) {
        return FALSE;
      } 
      $url = $this->getJSONUrl($endpoint, $params); 
      
      $data_str = '';
      if (is_array($data) && count($data)) {
        foreach ($data AS $key => $value) {
          $data_str .= $key.'='.$value.'&';
        }
        $data_str = substr($data_str, 0, -1);
      }
      if (!empty($_GET['debug'])) {
        Debug::printVar($url);
        Debug::printVar($params);
        Debug::printVar($data);
      }
      if ($this->apiUrlCallMethod == 'none') {
        $retjson = '{}';
        $errno = 0;
      }
      else if ($this->apiUrlCallMethod == 'file_get_contents') {
        $retjson = file_get_contents($url);
        $errno = 0;
      }
      else if ($this->apiConnector) {
        $get = $params;
        $get['q'] = $endpoint;
        $get['return'] = 'data';
        include_once $this->apiConnector;
        $ret = \l10iapi\init($get, $data);
        return $ret;
      } else {
         // intialize cURL and send POST data
        $ch = curl_init();
        if ($data_str) {
          curl_setopt($ch, CURLOPT_POST, true);
          curl_setopt($ch, CURLOPT_POSTFIELDS, $data_str);
        }
        else {
          curl_setopt($ch, CURLOPT_POST, false);
        }
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_USERAGENT, $this->userAgent);
        curl_setopt($ch, CURLOPT_REFERER, $this->host . $this->path);
        //curl_setopt($ch, CURLOPT_URL, "");
        //curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json'));
        curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/x-www-form-urlencoded'));
        if (!empty($this->apiUrl['httpauth_userpwd'])) {
          curl_setopt($ch, CURLOPT_USERPWD, $this->apiUrl['httpauth_userpwd']);
          curl_setopt($ch, CURLOPT_HTTPAUTH, CURLAUTH_ANY );
        }
        $retjson = curl_exec($ch);
        $errno = curl_errno($ch);
        $error = curl_error($ch);
        //$this->setLastStatusFromCurl($ch);
        curl_close($ch);
      }
      if ($errno > 0) {
          throw new \Exception ('cURL error: ' . $error);
      } else {
          $ret = json_decode($retjson, true);
          if (empty($ret['status'])) {
            $ret = (strlen($retjson) > 210) ? substr($retjson, 0, 200) . '...' : $retjson;
            throw new \Exception ('API response error. returned: ' . $ret);
          }
          return $ret;
      }
    }
    
    /**
    * Creates the url to be used for the api request
    *
    * @param endpoint: String value for the endpoint to be used (appears after version in url)
    * @param params: Array containing query parameters and values
    *
    * @returns String
    **/
    public function getJSONUrl($endpoint, $params) {
      $url = $this->apiUrl;
      $url .= 'index.php?q=' . $endpoint;
      if (!empty($params)) {
        $url .= '&' . $this->encodeQueryParams($params);
      }
      return $url;
    }

    /**
     * Converts array into query string parameters
     * 
     * @param array $params: 
     */
    public function encodeQueryParams($params) {
      $str = array();
      foreach($params AS $k => $v) {
        $str[] = urlencode($k) . "=" . urlencode($v);
      }
      return implode("&", $str);     
    }





        /**
    * Executes HTTP POST request with JSON as the POST body
    *
    * @param URL: String value for the URL to POST to
    * @param fields: Array containing names and values for fields to post
    *
    * @returns: Body of request result
    *
    * @throws HubSpot_Exception
    **/


    /**
    * Executes HTTP POST request with XML as the POST body
    *
    * @param URL: String value for the URL to POST to
    * @param fields: Array containing names and values for fields to post
    *
    * @returns: Body of request result
    *
    * @throws HubSpot_Exception
    **/
    protected function execute_xml_post_request($url, $body) {

        // intialize cURL and send POST data
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_POST, true);
        curl_setopt($ch, CURLOPT_POSTFIELDS, $body);
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_USERAGENT, $this->userAgent);    // new
        //curl_setopt($ch, CURLOPT_VERBOSE, 1);
        curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/atom+xml'));
        $output = curl_exec($ch);
        $errno = curl_errno($ch);
        $error = curl_error($ch);
        $this->setLastStatusFromCurl($ch);
        curl_close($ch);
        if ($errno > 0) {
            throw new HubSpot_Exception ('cURL error: ' + $error);
        } else {
            return $output;
        }
    }

    /**
    * Executes HTTP PUT request
    *
    * @param URL: String value for the URL to PUT to
    * @param body: String value of the body of the PUT request
    *
    * @returns: Body of request result
    *
    * @throws HubSpot_Exception
    **/
    protected function execute_put_request($url, $body) {
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_USERAGENT, $this->userAgent);    // new
        curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json','Content-Length: ' . strlen($body)));
        //curl_setopt($ch, CURLOPT_VERBOSE, 1);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_setopt($ch, CURLOPT_POSTFIELDS,$body);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
        $result = curl_exec($ch);
        $apierr = curl_errno($ch);
        $errmsg = curl_error($ch);
        $this->setLastStatusFromCurl($ch);
        curl_close($ch);
        if ($apierr > 0) {
            throw new HubSpot_Exception('cURL error: ' + $errmsg);
        } else {
            return $result;
        }
    }

    /**
    * Executes HTTP PUT request with XML as the PUT body
    *
    * @param URL: String value for the URL to PUT to
    * @param body: String value of the body of the PUT request
    *
    * @returns: Body of request result
    *
    * @throws HubSpot_Exception
    **/
    protected function execute_xml_put_request($url, $body) {
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_USERAGENT, $this->userAgent);    // new
        curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/atom+xml','Content-Length: ' . strlen($body)));
        //curl_setopt($ch, CURLOPT_VERBOSE, 1);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_setopt($ch, CURLOPT_POSTFIELDS,$body);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
        $result = curl_exec($ch);
        $apierr = curl_errno($ch);
        $errmsg = curl_error($ch);
        $this->setLastStatusFromCurl($ch);
        curl_close($ch);
        if ($apierr > 0) {
            throw new HubSpot_Exception('cURL error: ' + $errmsg);
        } else {
            return $result;
        }
    }

    /**
    * Executes HTTP DELETE request
    *
    * @param URL: String value for the URL to DELETE to
    * @param body: String value of the body of the DELETE request
    *
    * @returns: Body of request result
    *
    * @throws HubSpot_Exception
    **/
    protected function execute_delete_request($url, $body) {
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_USERAGENT, $this->userAgent);    // new
        curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json','Content-Length: ' . strlen($body)));
        //curl_setopt($ch, CURLOPT_VERBOSE, 1);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_setopt($ch, CURLOPT_POSTFIELDS,$body);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
        $result = curl_exec($ch);
        $apierr = curl_errno($ch);
        $errmsg = curl_error($ch);
        $this->setLastStatusFromCurl($ch);
        curl_close($ch);
        if ($apierr > 0) {
            throw new HubSpot_Exception('cURL error: ' + $errmsg);
        } else {
            return $result;
        }
    }

    /**
    * Converts an array into url friendly list of parameters
    *
    * @param params: Array of parameters (name=>value)
    *
    * @returns String of url friendly parameters (&name=value&foo=bar)
    *
    **/
    protected function arrayToParams($params) {
        $paramstring = '';
        if ($params != null) {
            foreach ($params as $parameter => $value) {
                 $paramstring = $paramstring . '&' . $parameter . '=' . urlencode($value);
            }
        }
        return $paramstring;
    }

    /**
    * Utility function used to determine if variable is empty
    *
    * @param s: Variable to be evaluated
    *
    * @returns Boolean
    **/
    protected function isBlank ($s) {
        if ((trim($s)=='')||($s==null)) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * Sets the status code from a curl request
     *
     * @param resource $ch
     */
    protected function setLastStatusFromCurl($ch) {
        $info = curl_getinfo($ch);
        $this->lastStatus = (isset($info['http_code'])) ? $info['http_code'] : null;
    }

}