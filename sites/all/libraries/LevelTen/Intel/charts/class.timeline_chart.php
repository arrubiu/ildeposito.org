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

class TimelineChart extends Chart {
  
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
    if ($style == 'objectives') {
      $options = array(
        'showRowLabels' => false,
        'avoidOverlappingGridLines' => false,
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
    if ($style == 'mini') {
      $settings = array(
        'div_height' => "25px",
        'div_width' => "100%",
        'chart_type' => 'areachart',
        'resize' => 0,
      );
    }
    else if ($style == 'objectives') {
      $settings= array(
        'div_height' => "200px",
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

    if (!isset($vis_loaded)) {
      $script = "google.load('visualization', '1', {packages: ['timeline']});";
      drupal_add_js($script, array('type' => 'inline', 'scope' => 'header'));    
      $vis_loaded = 1;
    }   

    $datajson = drupal_json_encode($data);
    $optionsjson = drupal_json_encode($this->options);
    $settingsjson = drupal_json_encode($this->settings);
    $chartType = $this->settings['chart_type'];
    $script = "_chart['$chartType-{$this->chartIndex}'] = [$datajson, $optionsjson, $settingsjson];";    
    drupal_add_js($script, array('type' => 'inline', 'scope' => 'header'));
    $output = '<div id="' . $chartType . '-' . $this->chartIndex . '" style="height: ' . $this->settings['div_height'] .'; width: ' . $this->settings['div_width'] .';"></div>';  
    return $output;
  }  
}