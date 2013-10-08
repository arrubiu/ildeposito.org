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

class Render {
  
  /**
   * Extracts a keyed value from a hash array
   * @param $text achor text for the link
   * @param $url the url for the link
   * @param $option array of additional options
   */
  static public function link($text, $url, $options = array()) {
    $href = self::url($url, $options);
    $link = '<a href="' . $href . '"';
    if (isset($options['attributes']) && is_array($options['attributes'])) {
      foreach ($options['attributes'] AS $key => $value) {
        $link .= ' ' . $key . '="' . $value . '"';
      }
    }
    $link .= '>' . $text . '</a>';
    return $link;
  }
  
  static public function url($url, $options) { 
    if (empty($options['absolute'])) {
      $a = explode('//', $url);
      if (count($a) != 2) {
        if (substr($url, 0 , 1) != '/') {
          $url = '/' . $url;
        }
      }
    }
    if (isset($options['query']) && is_array($options['query'])) {
      $url .= '?';
      $count = 0;
      foreach ($options['query'] AS $key => $value) {
        if ($count > 0) {
          $url .= '&';
        }
        $url .= rawurlencode($key) . '=' . rawurlencode($value);
        $count ++;
      }
    }
    if (!empty($options['fragment'])) {
      $url .= '#' . $options['fragment'];
    }
    return $url;
  }
}