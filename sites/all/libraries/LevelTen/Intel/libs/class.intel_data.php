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

class IntelData {
  
  /**
   * Extracts a keyed value from a hash array
   * @param array | stdClass $subject  associative array or stdClass to extract data from
   * @param $namespace
   * @param string $keys - dot delimited key sequence
   * @param $value - the value to add insert
   */
  static public function setVar(&$subject, $key = '', $value = '', $options = array()) {
    if (empty($key)) {
      return $subject = $value;
    }
    $s = array(
      $subject,
    );
    $keys = explode('.', $key);
    for ($i = 0; $i < count($keys); $i++) {
      $k = $keys[$i];

      $notIssetInit = array();
      if (count($keys) == ($i+1)) {
        $notIssetInit = '';
      }
      if (is_object($s[$i])) {
        if (!isset($s[$i]->$k)) {
          $s[$i]->$k = $notIssetInit;
        }
        if (count($keys) == ($i+1)) {
          $s[$i]->$k = self::assignIntelValue($s[$i]->$k, $value);
        }
        else {
          if (!is_array($s[$i]->$k)) {
            $s[$i]->$k = array(
              '_value' => $s[$i]->$k,
            );
          }
          $s[] = $s[$i]->$k;
        }
      }
      else {
        // check if k should be an int index
        //$l = (int)$k;
        //if (($k == (string)$l)) {
        //  $k = $l;
        //}
        if (!isset($s[$i][$k])) {
          $s[$i][$k] = $notIssetInit;
        }
        if (count($keys) == ($i+1)) {
          $s[$i][$k] = self::assignIntelValue($s[$i][$k], $value);
        }
        else {
          if (!is_array($s[$i][$k])) {
            $s[$i][$k] = array(
              '_value' => $s[$i][$k],
            );
          }
          $s[] = $s[$i][$k];
        }
      }
    }
    for ($i = count($keys)-1; $i > 0; $i--) {
      $s[$i-1][$keys[$i-1]] = $s[$i];
    }
    return $s[0];
  }
  
  static public function assignIntelValue($var, $value) {
    return $value;
  }
  
  static public function getVar($subject, $key = '', $options = array()) {
    if (empty($key)) {
      return $subject;
    }
    $s = array(
      $subject,
    );
    $keys = explode('.', $key);
    for ($i = 0; $i < count($keys); $i++) {
      $k = $keys[$i];

      if (is_object($s[$i])) {
        if (!isset($s[$i]->$k)) {
          return null;
        }
        if (count($keys) == ($i+1)) {
          return $s[$i]->$k;
        }
        else {
          $s[] = $s[$i]->$k;
        }
      }
      else {
        if (!isset($s[$i][$k])) {
          return null;
        }
        if (count($keys) == ($i+1)) {
          return $s[$i][$k];
        }
        else {
          $s[] = $s[$i][$k];
        }
      }
    }
    return null;
  }
  
  public function toString() {

  }
}