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

class LineChart extends Chart {
  
  public function __construct($style = 'default', $data = array(), $options = array(), $settings = array()) {
    if (count($options) == 0) {
      $options = $this->getDefaultOptions($style);
    }
    if (count($settings) == 0) {
      $settings = $this->getDefaultSettings($style);
    }    
    parent::__construct($data, $options, $settings);
  }
  
  function getDefaultOptions($style = 'default') {
    if ($style == 'mini_sparkline') {
      $options = array(
        'chartArea' => array(
          'left' => 0,
          'top' =>  0,
          'width' => 100,
          'height' => 25,
        ),
        'legend' => array(
          'position' => 'none',
        ),
        'hAxis' => array(
          'showTextEvery' => 0,
          'gridlines' => array('count' => 0, 'color' => '#FFFFFF'),
          'baselineColor' => "#FFFFFF",
        ),
        'vAxis' => array(
          'gridlines' => array('count' => 0),
          'baselineColor' => "#FFFFFF",
        ),
        'areaOpacity' => 0.1,
        'tooltip' => array(
          'trigger' => 'none',
        ),
      );
    }
    else if ($style == 'objectives') {
      $colors = $this->chartColors;
      array_unshift($colors, '#DDDDDD');
      $options = array(
        'chartArea' => array(
          'left' => 50,
          'top' =>  30,
          'width' => "100%",
          'height' => 150,
        ),
        'legend' => array(
          'position' => 'in',
          'textStyle' => array(
            'color' => '#888888',
            'fontSize' => 10,
          ),
        ),
        'hAxis' => array(
          'baselineColor' => '#FFFFFF',
          'slantedText' => false,
          'showTextEvery' => 1,
          'maxTextLines' => 0,
          'format' => 'MMM d',
          'gridlines' => array('color' => '#DDDDDD'),
        ),
        'vAxis' => array(
          'baselineColor' => '#AAAAAA',
          'gridlines' => array('color' => '#EEEEEE', 'count' => 3),
          'format' => '#,###',
        ),
        'titlePosition' => 'out',
        'colors' => $colors,
        'pointSize' => 6,
      );
    }
    else {
      $options = array(
        'chartArea' => array(
          'left' => 50,
          'top' =>  20,
          'width' => "100%",
          'height' => 185,
        ),
        'legend' => array(
          'position' => 'bottom',
        ),
        'hAxis' => array(
          'slantedText' => false,
          'showTextEvery' => 7,
        ),
        'colors' => $this->chartColors,
      );
    }
    return $options;
  }
  
  function getDefaultSettings($style = 'default') {
    if ($style == 'mini_sparkline') {
      $settings = array(
        'div_height' => "25px",
        'div_width' => "100px",
        'chart_type' => 'areachart',
        'resize' => 0,
      );
    }
    else if ($style == 'objectives') {
      $settings= array(
        'div_height' => "185px",
        'div_width' => "100%",
        'chart_type' => 'areachart',
      );    
    }
    else {
      $settings= array(
        'div_height' => "185px",
        'div_width' => "100%",
        'chart_type' => 'linechart',
      );
    }
    return $settings;  
  }   
 
  function renderOutput() {
    static $vis_loaded;

    $data = $this->data;

    $datajson = drupal_json_encode($data);
    $optionsjson = drupal_json_encode($this->options);
    $settingsjson = drupal_json_encode($this->settings);
    $chartType = $this->settings['chart_type'];
    $script = "_chart['$chartType-{$this->chartIndex}'] = [$datajson, $optionsjson, $settingsjson];"; 
       
    $output = '<script>' . $script . '</script>';
    $output .= '<div id="' . $chartType . '-' . $this->chartIndex . '" style="height: ' . $this->settings['div_height'] .'; width: ' . $this->settings['div_width'] .';"></div>';  
    return $output;
  }  
}