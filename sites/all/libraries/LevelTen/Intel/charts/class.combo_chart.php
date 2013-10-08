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

class ComboChart extends Chart {
  
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
    if ($style == 'mini') {

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
          'showTextEvery' => 1,
          'format' => 'MMM d',
          'gridlines' => array('color' => '#FFFFFF'),
          'baselineColor' => '#FFFFFF',
        ),
      );
    }
    return $options;
  }
  
  function getDefaultSettings($style = 'default') {
    if ($style == 'mini') {
  
    }
    else {
      $settings= array(
        'div_height' => "250px",
        'div_width' => "100%",
      );
      $settings['formatters'][] = array(
        'name' => 'NumberDateFormat',
        'options' => array(
          'pattern' => 'MMM d',
        ),
        'columnIndex' => 0,
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
    $chartType = 'combochart';
    $script = "_chart['$chartType-{$this->chartIndex}'] = [$datajson, $optionsjson, $settingsjson];";    

    $output = '<script>' . $script . '</script>';
    $output .= '<div id="' . $chartType . '-' . $this->chartIndex . '" style="height: ' . $this->settings['div_height'] .'; width: ' . $this->settings['div_width'] .';"></div>';  
    return $output;
  }  
}