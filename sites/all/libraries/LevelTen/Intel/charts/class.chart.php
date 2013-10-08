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

class Chart {
  public  $data;
  public  $options;
  public  $settings;
  public  $chartIndex;
  public static $chartCount = 0;
  public $curRowCount = 0;
  public $maxRowCount = 10;
  public $workingRow;
  protected $chartColors = array(
    '#058DC7',
    '#50B432',
    '#F75701',
    '#EDEF00',
    '#24CBE5',
    '#64E572',
    '#FF9655',
    '#FFF263',
  ); 
  protected $reportView;
  
  public function __construct($data = array(), $options = array(), $settings = array()) {
    $this->chartIndex = self::$chartCount;
    self::$chartCount++;
    $this->data = $data;
    $this->options = $options;
    $this->settings = $settings;
    if (self::$chartCount == 1) {
      //ReportPageHeader::addScript('https://www.google.com/jsapi', 'file');
      //ReportPageHeader::addScript("google.load('visualization', '1', {packages: ['corechart']});var _chart = _chart || [];", 'inline');
      //ReportPageHeader::addScript("charts/charts.js", 'file');      
    }
  }
  
  function setData($data) {
    $this->data = $data;
  }
  
  function getData() {
    return $this->data; 
  }
  
  function setVar(&$data, $keys, $value) {
    require_once dirname(__FILE__) . '/../libs/class.intel_data.php';
    $data = IntelData::setVar($data, $keys, $value);
    return;
    $keys = explode('.', $keys);
    if (count($keys) == 1) {
      $data[$keys[0]] = $value;
    }
    else if (count($keys) == 2) {
      if (!isset($data[$keys[0]])) {
        $data[$keys[0]] = array();
      }
      $data[$keys[0]][$keys[1]] = $value;
    }  
    else if (count($keys) == 3) {
      if (!isset($data[$keys[0]])) {
        $data[$keys[0]] = array();
      }
      if (!isset($data[$keys[0]][$keys[1]])) {
        $data[$keys[0]][$keys[1]] = array();
      }

      $data[$keys[0]][$keys[1]][$keys[2]] = $value;
    }  
  }
  
  function setOptions($options) {
    $this->options = $options;
  }
  
  function setOption($keys, $value) {
    $this->setVar($this->options, $keys, $value);
  }
  
  function getOptions() {
    return $this->options; 
  }
  
  function setSettings($settings) {
    $this->settings = $settings;
  }
  
  function setSetting($key, $value) {
    $this->settings[$key] = $value;
  }
  
  function setMaxRowCount($rowCount) {
    $this->maxRowCount = $rowCount;
  }
  
  function setColumns($columns) {
    $this->settings['cols'] = $columns;
  }
  
  function formatColumnItem($type, $label = '', $id = '', $role = '', $pattern = '') {
    $item = array(
      'type' => $type,
    );
    if ($label) {
      $item['label'] = $label;
    }
    if ($id) {
      $item['id'] = $id;
    }
    if ($role) {
      $item['role'] = $pattern;
    }
    if ($pattern) {
      $item['pattern'] = $pattern;
    }
    return $item;
  }
  
  /**
   * 
   * @param $columnIndex
   * @param $arg0
   */
  function setColumnItem($columnIndex, $item, $label = '', $id = '', $role = '', $pattern = '') {
    if (is_string($item)) {
      $item = $this->formatColumnItem($item, $label, $id, $role, $pattern);
    }
    $this->settings['cols'][$columnIndex] = $item;
  }

  
  function addColumn($item, $label = '', $id = '', $role = '', $pattern = '') {
    if (is_string($item)) {
      $item = $this->formatColumnItem($item, $label, $id, $role, $pattern);
    }
    $this->settings['cols'][] = $item;
  }
  
  function insertColumn($columnIndex, $item, $label = '', $id = '', $role = '', $pattern = '') {
    if (is_string($item)) {
      $item = $this->formatColumnItem($item, $label, $id, $role, $pattern);
    } 
    array_splice($this->settings['cols'], $columnIndex, 0, array($item));
  }
  
  function removeColumn($columnIndex) {
    array_splice($this->settings['cols'], $columnIndex, 1);
  }
  
  function updateColumn($columnIndex, $item, $label = '', $id = '', $role = '', $pattern = '') {
    if (is_string($item)) {
      $item = $this->formatColumnItem($item, $label, $id, $role, $pattern);
    }
    $this->settings['cols'][$columnIndex] = $item;
  }
  
  function setColumnElement($columnIndex, $name, $value) {
    $this->settings['cols'][$columnIndex][$name] = $value;
  }
  
  /**
   * Resets the workingRow
   */
  function newWorkingRow() {
    $this->workingRow = array();
  }
  
  /**
   * Adds a row to the table data. 
   * @param row to add or leave blank to add workingRow
   */
  function addRow($row = '', $container = 'data') {
    $this->data[] = ($row) ? $row : $this->workingRow;
    $this->curRowCount = (count($this->data));
  }
  
  function addRowToSettings($row = '') {
    if (!isset($this->settings['rows'])) {
      $this->settings['rows'] = array();
    }
    $this->settings['rows'][] = ($row) ? $row : $this->workingRow;
    $this->curRowCount = (count($this->data));
  }
  
  function addRowItem($item) {
    $this->workingRow[] = $item;
  }
  
}