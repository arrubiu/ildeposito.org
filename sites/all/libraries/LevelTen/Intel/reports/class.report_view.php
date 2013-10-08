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
require_once __DIR__ . '/../libs/class.render.php';

class ReportView {
  public  $data = array();
  public  $model = array();
  protected $modes = array();
  protected $params = array();
  protected $dateRange = array();
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
  protected $chartColorsCompliments = array(
    array('#AADFF3', '#D1F2FF'),
    array('#7FCF67', '#A2E090'),
  );
  protected $statusColors = array(
    'complete' => '#50B432',
    'warning' =>  '#EDEF00',
    'error' =>    '#F75701',
  );
  protected $statusColorsBackground = array(
    'complete' => '#B9E1AD',
    'warning' =>  '#F7F899',
    'error' =>    '#FBBB99',
  );
  protected $targets;
  protected $goals;
  protected $pagesMeta = array();
  protected $pageMetaCallback;
  protected $libraryUri = '';
  
  function __construct() {
    
  }
  
  function setModel($model) {
    $this->model = $model;
  }
  
  function setData($data) {
    $this->data = $data;
  }
  
  function setModes($modes) {
    $this->modes = $modes;
  }
  
  function setParam($key, $value) {
    $this->params[$key] = $value;
  }
  
  function setTargets($targets) {
    $this->targets = $targets;
  }
  
  function setTarget($key, $value) {
    $this->targets[$key] = $value;
  }
  
  function setGoals($goals) {
    $this->goals = $goals;
  }
  
  function setGoal($key, $value) {
    $this->goals[$key] = $value;
  }
  
  function setDateRange($startDate, $endDate) {
    $this->dateRange['start'] = $startDate;
    $this->dateRange['end'] = $endDate;
    $this->dateRange['days'] = round(($endDate - $startDate)/60/60/24);  
  }
  
  function setLibraryUri($uri) {
    $this->libraryUri = $uri;
  }
  
  
  function sortData($type, $index = '') {
    $data = ($index) ? $this->data[$index] : $this->data;
    @uasort($data, array($this, 'usort_' . $type));  // note: @ is to deal with a php bug that reports false errors. See: http://stackoverflow.com/questions/3235387/usort-array-was-modified-by-the-user-comparison-function
    if ($index) {
      $this->data[$index] = $data;
    } else {
      $this->data = $data;
    }
  }
  
  function usort_by_score_then_entrances($a, $b) {
    if ($a['score'] == $b['score']) {
      return ($a['entrance']['entrances'] < $b['entrance']['entrances']) ? 1 : -1; 
    }
    return ($a['score'] < $b['score']) ? 1 : -1; 
  }
  
  function usort_by_value_then_completions($a, $b) {
    if ($a['value'] == $b['value']) {
      return ($a['completions'] < $b['completions']) ? 1 : -1; 
    }
    return ($a['value'] < $b['value']) ? 1 : -1;  
  }
  
  function usort_by_value_then_totalValuedEvents($a, $b) {
    if ($a['value'] == $b['value']) {
      return ($a['totalValuedEvents'] < $b['totalValuedEvents']) ? 1 : -1; 
    }
    return ($a['value'] < $b['value']) ? 1 : -1;  
  }
  
  function usort_entrances($a, $b) {
    return ($a['entrance']['entrances'] < $b['entrance']['entrances']) ? 1 : -1; 
  }
  
  function formatRowString($text, $stoplen = 40) {
    if(strlen($text) > ($stoplen + 4)) {
     return substr($text, 0, $stoplen) . '...';
    }
    return $text;    
  }
  
  static function renderSparklineValueElement($vars) {
    $data = $vars['data'];
    $keys = explode('.', $vars['keys']);
    $keys2 = FALSE;
    if (!empty($vars['keys2'])) {
      $keys2 = explode('.', $vars['keys2']);
      $keys_operator = $vars['keys_operator'];
    }

    $value_prefix = '';
    $value_suffix = '';
    if (!empty($vars['format'])) {
      $format = $vars['format'];
    }
    $title = $vars['title'];
    $id = (!empty($vars['id'])) ? " id=\"{$vars['id']}\"" : '';
    
    $sparkline = new LineChart('mini_sparkline');
    $sparkline->addColumn('date', 'Day');
    $sparkline->addColumn('number', $title);
    if ($vars['linecolor']) {
      $sparkline->setOption('colors', array($vars['linecolor']));
    }
    
    $rows = array();
    foreach ($data AS $day => $d) {
      if (substr($day, 0 ,1) == '_') {
        continue;
      }
      
      $ts = strtotime($day);
      $jstime = 1000*$ts;
   
      $sparkline->newWorkingRow();
      $sparkline->addRowItem($jstime);

      $value = $d;
      foreach ($keys AS $key) {
        $value = $value[$key];
      }
      if ($keys2) {
        $value2 = $d;
        foreach ($keys2 AS $key) {
          $value2 = $value2[$key];
        }      
        $value = self::evalValueExpression($value, $value2, $keys_operator);
      }
      if ($format['type'] == 'percentage') {
        $sparkline->addRowItem(round(100 * $value, $format['decimals']));      
      }
      else if ($format['type'] == 'money') {
        $sparkline->addRowItem(round($value, $format['decimals'])); 
      }
      else {
        $sparkline->addRowItem($value);
      }
      $sparkline->addRowToSettings();
    }
    
    $total = $vars['total'];
    $style = '';
    if (!empty($vars['bgcolor'])) {
      $style = ' style="background-color: ' . $vars['bgcolor'] . ';"';
    }
    $output = '';
    $output .= '<div' . $id . ' class="report-summary-element">';
    $output .= '<div class="report-summary-element-chart">';
    $output .= $sparkline->renderOutput();
    $output .= '</div>';
    $output .= '<div class="report-summary-element-value"' . $style . '>';
    $output .= $value_prefix . $total . $value_suffix . ' <span class="label">' . $title . '</span>';
    $output .= '</div>';
    $output .= '</div>';
    
    return $output;
  }
  
  static function evalValueExpression($value1, $value2, $operator) {
    if ($operator == '+') {
      return $value1 + $value2;
    }
    if ($operator == '-') {
      return $value1 - $value2;
    }
    if ($operator == '*') {
      return $value1 * $value2;
    }
    if ($operator == '/') {
      if ($value2 == 0) {
        return 0;
      }
      return $value1 / $value2;
    }
  }
  
  static function formatDeltaTime($secs) {
    $s = floor($secs%60);
    $str = (($s < 10) ? '0' : '') . $s;
    $m = floor($secs/60);
    if ($m == 0) {
      return "0:$str";
    }
    elseif ($m < 60) {
      return "$m:$str";
    }
    else {
      $m = floor($m%60);
      $str = (($m < 10) ? '0' : '') . $m . ":" . $str;
      $h = floor($secs/3600); 
      return "$h:$str";
    }
  }
  
  function formatValueScoreTitle($value, $start_date, $end_date, $created = 0) {
    $days_included = ($end_date - $start_date) / 86400;
    $title = number_format($value, 2) . " value in " . round($days_included, 1) . " days. (" . date("n/j/y", $start_date) . " - " . date("n/j/y", $end_date) . ")";
    if ($created) {
      $title .= " Created " . format_interval($end_date - $created) . " ago.";
    } 
    return $title; 
  }
  
  /**
   * Produces HTML for score indicator values
   * @param array $vars
   * @param string $value_str
   * @param array $targets required if used as a static method
   */
  function renderValueScore($vars, &$value_str, $targets = null) {
    $value = $vars['value'];
    $type = $vars['type'];
    $title_attr = (!empty($vars['title'])) ? ' title="' . $vars['title'] . '"' : '';
    $number_of_days = 1;
    if (!empty($vars['number_of_days'])) {
      $number_of_days = $vars['number_of_days'];
    }  
    if (!isset($targets)) {
      $targets = $this->targets;
    }
  
    $value_str = number_format($value / $number_of_days, 2);
    
    $value_status = 'error';
    if ($type == 'value_per_day') {      
      if ($value >= $targets['value_per_visit_warning']) {
        $value_status = 'warning';
      }
      if ($value >= $targets['value_per_visit']) {
        $value_status = 'complete';
      }   
    }
    
    // page scoring
    if ($type == 'value_per_page_per_day') {      
      if (($value / $number_of_days) >= $targets['value_per_page_per_day_warning']) {
        $value_status = 'warning';
      }
      if (($value / $number_of_days) >= $targets['value_per_page_per_day']) {
        $value_status = 'complete';
      }   
    }
    
    if ($type == 'value_per_page_per_entrance') {      
      if ($value >= $targets['value_per_page_per_entrance_warning']) {
        $value_status = 'warning';
      }
      if ($value >= $targets['value_per_page_per_entrance']) {
        $value_status = 'complete';
      }   
    }
    
    if ($type == 'entrances_per_page_per_day') {      
      if (($value / $number_of_days) >= $targets['entrances_per_page_per_day_warning']) {
        $value_status = 'warning';
      }
      if (($value / $number_of_days) >= $targets['entrances_per_page_per_day']) {
        $value_status = 'complete';
      } 
      $decimal = ($number_of_days == 1) ? 0 : 1;
      $value_str = number_format($value / $number_of_days, $decimal); 
    }

    if ($type == 'value_per_visit') {      
      if (($value) >= $targets['value_per_visit_warning']) {
        $value_status = 'warning';
      }
      if (($value) >= $targets['value_per_visit']) {
        $value_status = 'complete';
      } 
    }
    $title_attr = '';
    
    if ($vars['value_placehoder']) {
      $value = $vars['value_placehoder'];
    }
    else {
      $value = $value_str;
    }

    $out = '<div' . $title_attr . ' class="intel-report-value active ' . $value_status . '">' . $value . '</div>';
    if (!empty($vars['href'])) {
      $out = render::link($out, $vars['href'], array('html' => 1));
    }
    return '<div' . $title_attr . ' class="intel-report-value active ' . $value_status . '">' . $value . '</div>';
  }
  
  function setPageMetaCallback($func) {
    $this->pageMetaCallback = $func;
  }
  
  function getPageMeta($path) {
    if (!isset($this->pagesMeta[$path])) {
      if (!empty($this->pageMetaCallback)) {
        $func = $this->pageMetaCallback;
        $this->pagesMeta[$path] = $func($path);
      }
      else {
        $this->pagesMeta[$path] = FALSE;
      }
    }  
    return $this->pagesMeta[$path];
  }
  
  static function getPageScoreDates($start_date, $end_date, $created = 0) {
    $start = ($created > $start_date) ? $created : $start_date;
    $days_included = ($end_date - $start) / 86400;
    $score_dates = array(
      'start' => $start,
      'end' => $end_date,
      'created' => $created,
      'days' => $days_included,
    );
    return $score_dates;
  }
}

class ReportPageHeader {
  private static $addScriptCallback;
  
  static function setAddScriptCallback ($func) {
    self::$addScriptCallback = $func;
  }
  
  static function addScript($script, $type = 'file') {
    if (self::$addScriptCallback) {
      $func = self::$addScriptCallback;
      $func($script, $type);
    } 
  } 
}
