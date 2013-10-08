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

class Debug {
  
  /**
   * prints variables including
   * @param $var: any variable
   * @param int $mode: 0: print to screen, 1: return print string, 2: log 
   */
  static public function printVar($var, $mode = 0) {
    if (function_exists('intel_print_var')) {
      intel_print_var($var, $mode);
    }
    else {
      if ($mode == 1) {
        return print_r($var, 1);
      }
      else {
        print_r($var);
      }
    }
  }
}