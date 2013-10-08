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
require_once 'class.chart.php';

class BubbleChart extends Chart {
  
  public function __construct($style = 'default', $data = array(), $options = array(), $settings = array()) {
    if (count($options) == 0) {
      $options = $this->getDefaultOptions($style );
    }
    if (count($settings) == 0) {
      $settings = $this->getDefaultSettings($style );
    }    
    parent::__construct($data, $options, $settings);
  }
  
  function getDefaultOptions($style = 'default') {
    if ($style == 'postsTimeline') {
      $options = array(
        'colors' => $this->chartColors,
        'chartArea' => array(
          'left' => 50,
          'top' =>  30,
          'width' => "100%",
          'height' => 150,
        ),
        'bubble' => array(
          'textStyle' => array(
            'color' => 'none',
          ),
          'opacity' => .7,          
        ),
        'hAxis' => array(
          'baselineColor' => '#FFFFFF',
          'gridlines' => array('color' => '#DDDDDD', 'count' => 5),
          'textPosition' => 'none',
        ),
        'vAxis' => array(
          'minValue' => 0,
          'baselineColor' => '#AAAAAA',
          'gridlines' => array('color' => '#EEEEEE', 'count' => 3),
          'format' => '#,###',
        ),
      );      
    } else {
      $options = array(
        'chartArea' => array(
          'left' => 50,
          'top' =>  30,
          'width' => "100%",
          'height' => 185,
        ),
        'bubble' => array(
          'textStyle' => array(
            'color' => 'none',
          ),
          'opacity' => 1,
        ),
        'sizeAxis' => array(
          'minSize' => 5,
          'maxSize' => 5,
        ),
      );
    }
    return $options;
  }
  
  function getDefaultSettings($style = 'default') {
    if ($style == 'postsTimeline') {
      $settings = array(
        'cols' => array(),
        'div_height' => '200px',
        'div_width' => '100%',
        'formatters' => array()
      );
      $settings['formatters'][] = array(
        'name' => 'NumberDateFormat',
        'options' => array(
          'pattern' => 'MMM d h:m aa',
        ),
        'columnIndex' => 1,
      );
    }
    else {
      $settings = array(
        'cols' => array(),
        'div_height' => '200px',
        'div_width' => '100%',
      );      
    }
    return $settings;  
  }   
 
  function renderOutput() {
    static $vis_loaded;

    $data = $this->data;

    $vMax = 0;
    $hMax = 0;
    if (!empty($this->settings['plotThreshold'])) {
      $ci = $this->settings['plotThreshold']['columnIndex'];
      $minValue = $this->settings['plotThreshold']['minValue'];
      foreach ($data AS $row) {
        if ($row[$ci] > $minValue) {
          if ($row[1] > $hMax) {
            $hMax = $row[1];
          }
          if ($row[2] > $vMax) {
            $vMax = $row[2];
          }
        }
      }
      $this->setOption('hAxis.viewWindow.max', $hMax);
      $this->setOption('vAxis.viewWindow.max', $vMax);
    }    
    
    $datajson = drupal_json_encode($data);
    $optionsjson = drupal_json_encode($this->options);
    $settingsjson = drupal_json_encode($this->settings);
    $script = "_chart['bubblechart-{$this->chartIndex}'] = [$datajson, $optionsjson, $settingsjson];";    
    
    $output = '<script>' . $script . '</script>';
    $output .= '<div id="bubblechart-' . $this->chartIndex . '" style="height: ' . $this->settings['div_height'] .'; width: ' . $this->settings['div_width'] .';"></div>';  
    return $output;
  }  
}