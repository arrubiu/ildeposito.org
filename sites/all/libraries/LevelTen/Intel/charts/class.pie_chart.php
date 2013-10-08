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

class PieChart extends Chart {
  
  public function __construct($data = array(), $options = array(), $settings = array()) {
    if (count($options) == 0) {
      $options = $this->getDefaultOptions();
    }
    if (count($settings) == 0) {
      $settings = $this->getDefaultSettings();
    }    
    parent::__construct($data, $options, $settings);
    $this->setMaxRowCount(8);
  }
  
  function getDefaultOptions() {
    $options = array(
      'sliceVisibilityThreshold' => 0.025,
      'sort' => 'desc',
      'colors' => $this->chartColors,
    );
    $options['chartArea'] = array(
      'top' => 20,
      'left' => 0,
      'width' => "100%",
      'height' => 160,
    );
    return $options;
  }
  
  function getDefaultSettings() {
    $settings = array(
      'cols' => array(),
      'sort' => 1,
      'div_height' => '200px',
      'div_width' => '100%',
    );
    return $settings;  
  }   
 
  function renderOutput() {
    static $vis_loaded;

    $data = $this->data;

    if (!empty($this->settings['sort'])) {
      usort($data, array($this, 'usortChartData'));
    }
    
    if (!empty($this->settings['useTotal'])) {
      $data = $this->applyDataThreshold($data, $this->settings['total'], $this->options['sliceVisibilityThreshold']);
      unset($this->options['sliceVisibilityThreshold']);
    }
    
    if (empty($this->settings['cols']) || (count($this->settings['cols']) != 2)) {
      array_unshift($data, array('Items', 'Value')); 
    }
    
    $datajson = drupal_json_encode($data);
    $optionsjson = drupal_json_encode($this->options);
    $settingsjson = drupal_json_encode($this->settings);
    $script = "_chart['piechart-{$this->chartIndex}'] = [$datajson, $optionsjson, $settingsjson];";   
    $output = '<script>' . $script . '</script>';
    $output .= '<div id="piechart-' . $this->chartIndex . '" style="height: ' . $this->settings['div_height'] .'; width: ' . $this->settings['div_width'] .';"></div>';  
    return $output;
  }
  
  protected function usortChartData($a, $b) {
    return ($a[1] < $b[1]);
  }

  protected function applyDataThreshold($data, $total, $sliceVisibilityThreshold) {
    $fdata = array();
    $all = 0;
    $i = 0;
    foreach ($data AS $d) {
      if (($d[1]/$total) > $sliceVisibilityThreshold) {
        $fdata[] = $d;
        $all += $d[1];
      }
      $i++;
      if (($i+1) >= $this->maxRowCount) {
        break;
      }
    }
    // if only one remaining slice contains last value to reach total use it
    if ((count($data) == (count($fdata) + 1)) && (($all + $fdata[$i]) == $total)) {
      $fdata[] = $fdata[$i];
    }
    // otherwise attach other slice
    else {
      $fdata[] = array(t('other'), ($total - $all));
    }
    return $fdata;
  }
  
}