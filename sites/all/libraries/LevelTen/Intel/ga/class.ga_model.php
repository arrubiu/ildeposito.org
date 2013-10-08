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
if (!empty($_GET['debug'])) {
  require_once __DIR__ . '/../libs/class.debug.php';
}

class GAModel {
  public  $data = array();
  public  $filters;
  public  $gaFilters = array();
  public  $customFilters = array(
    'filter' => '',
    'segement' => '',
  );
  public  $context;
  private $start_date;
  private $end_date;
  public  $settings;
  public  $pathQueryFilters = array();
  private $pageAttributeFilter = array();
  private $requestCallback = '';
  private $requestCallbackOptions = array();
  private $dataIndexCallbacks = array();
  private $debug = 0;
  private $reportModes = array();
  private $requestDefault = array(
      'dimensions' => array(),
      'metrics' => array(),
      'sort' => '',
      'start_date' => 0,
      'end_date' => 0,
      'filters' => '',
      'segment' => '',
      'max_results' => 50,  
  );
  private $requestSettings = array(
    'type' => 'pageviews',
    'subType' => 'value',
    'indexBy' => 'date',
    'subIndexBy' => '',
    'details' => 0,
    'sortType' => '',
    'excludeGoalFields' => 0,
  );
  
  function __contruct() {
    
  }
  
  function setDateRange($start_date, $end_date) {
    $this->start_date = $start_date;
    $this->end_date = $end_date;
    $this->requestDefault['start_date'] = $start_date;
    $this->requestDefault['end_date'] = $end_date;
  }
  
  function setRequestSetting($param, $value) {
    $this->requestSettings[$param] = $value;
  }
  
  function setRequestDefaultParam($param, $value) {
    $this->requestDefault[$param] = $value;
  }
  
  function setRequestCallback ($callback, $options = array()) {
    $this->requestCallback = $callback;
    $this->requestCallbackOptions = $options;    
  }
  
  function setDataIndexCallback($index, $callback) {
    $this->dataIndexCallbacks[$index] = $callback;
  }
  
  function setReportModes($modes) {
    if (is_string($modes)) {
      $modes = explode('.', $modes);
    }
    $this->reportModes = $modes;
  }
  
  function setDebug($debug) {
    $this->debug = $debug;
    if ($this->debug && !method_exists('Debug::printVar')) {
      require_once __DIR__ . '/../libs/class.debug.php';
    }
  }
  
  function buildFilters($filters, $context = 'site') {
    $gasegments = array();
    $gafilters = array();
    $gapaths = array(
      'pagePath' => '',
      'landingPagePath' => '',
    );

    if (!empty($filters['page'])) {
      $a = explode(":", $filters['page']);
      $path = $a[1]; 
      // TODO remove this dependency
      $pathfilter = $this->formatPathFilter($path);
      $landingpagefilter = str_replace('pagePath', 'landingPagePath', $pathfilter);
      
      if ($context == 'page') {
        $gapaths['pagePath'] = $pathfilter;
        $gapaths['landingPagePath'] = str_replace('pagePath', 'landingPagePath', $landingpagefilter);
      }
      else {
        if ($a[0] == 'landingPagePath') {
          $gafilters['page'] = $landingpagefilter;
        }
        else {
          $gafilters['page'] = $pathfilter;
        }
      }
    }
    
    if (!empty($filters['event'])) {
      $gasegments['event'] = "ga:eventCategory=~^" . $filters['event'];
    }
    
    if (!empty($filters['trafficsource'])) {
      $a = explode(":", $filters['trafficsource']);
      $gafilters['trafficsource'] = "ga:{$a[0]}=={$a[1]}";
    }
    
    if (!empty($filters['location'])) {
      $a = explode(":", $filters['location']);
      $gafilters['location'] = "ga:{$a[0]}=={$a[1]}";
      if (($a[0] == 'country') || ($a[0] == 'region') || ($a[0] == 'city') || ($a[0] == 'metro')) {
        $this->settings['location_dimension_level'] = 'region';
      }
    }
      
    if (!empty($filters['visitor'])) {
      $a = explode(":", $filters['visitor']);
      $vtk = $a[1]; 
      //$gasegments['visitor'] = "ga:customVarValue5==" . $vtk;
      $gafilters['visitor'] = "ga:customVarValue5==" . $vtk;
    }
  
    if (!empty($filters['visitor-attr'])) {
      $a = str_replace(':', '=', $filters['visitor-attr']);
      $query = l10insight_build_ga_filter_from_serialized_customvar($a);
      //$ga_segments['visitor-attr'] = "dynamic::ga:customVarValue3=" . $query;
    } 
    $this->gaFilters = array(
      'filters' => $gafilters,
      'segments' => $gasegments,
      //'filter' => implode(";", $gafilters),
      //'segment' => implode(";", $gasegments),
      'paths' => $gapaths,
    );
  }
  /**
   * 
   * @param $item
   * @param $type: valid values = 'filter' or 'segement'
   */
  function addGAFilter($item, $type = 'filter') {
    if ($type == 'segment') {
      $this->gaFilters['segements'][] = $item;
      //$this->gaFilters['segement'] =  implode(";", $this->gaFilters['segements']);
    }
    else if ($type == 'filter') {
      $this->gaFilters['filters'][] = $item;
      //$this->gaFilters['filter'] =  implode(";", $this->gaFilters['filters']);      
    }
  }
  
  function setPageAttributeFilter($filter) {
    $this->pageAttributeFilter = $filter;
  }
  
  function applyFiltersToRequest($request) {
    if ($this->gaFilters['filter']) {
      $request['filters'] .= (($request['filters']) ? ';' : '') . $this->gaFilters['filter'];
    }
    if ($this->gaFilters['segment']) {
      $request['segment'] .= (($request['segment']) ? ';' : '') . $this->gaFilters['segment'];
    }
    return $request;
  }
  
  function setCustomFilter($string, $type = 'filter') {
    $this->customFilters[$type] = $string;
  }
  
  //function loadFeedData($type, $indexBy = '', $details = 0, $max_results = 100, $results_index = 0) {
  function loadFeedData($type = '', $indexBy = '', $details = 0) {
    // format the ga request array
    $request = $this->getRequestArray($type, $indexBy, $details);
    if ($this->debug) { Debug::printVar($request); }
    
    // call dyanmic function to fetch data from ga
    if ($this->requestCallback) {
      $func = $this->requestCallback;
      $feed = $func($request, $this->requestCallbackOptions);
    }
    if ($this->debug) { Debug::printVar($feed); }
    
    // parse data into $this->data
    $this->addFeedData($feed, $type, $indexBy, $details);
    if ($this->debug) { Debug::printVar($this->data); }

    return $this->data;
  }
  
  //function getRequestArray($type, $sub_type = 'value_desc', $indexBy = '', $details = 0, $max_results = 100, $results_index = 0) {
  function getRequestArray($type = '', $indexBy = '', $details = 0) {
    $request = $this->requestDefault;
    $settings = $this->requestSettings;
    $type = ($type) ? $type : $settings['type'];
    $types = explode('_', $type);
    $subType = $settings['subType'];
    $indexBy = ($indexBy) ?  $indexBy : $settings['indexBy'];
    $subIndexBy = $settings['subIndexBy'];
    $details = ($details) ? $details : $settings['details'];
    $reportModes = $this->reportModes;
    
    $filters = $this->gaFilters['filters'];
    $segments = $this->gaFilters['segments'];
//Debug::printVar($filters);
    if ($type == 'pageviews') {
      if (($reportModes[0] == 'social') || ($reportModes[0] == 'seo')) {
        //$request['metrics'] = array('ga:pageviews', 'ga:pageviewsPerVisit', 'ga:timeOnPage', 'ga:exits', 'ga:totalEvents');
        //$request['sort'] = '-ga:totalEvents,-ga:pageviews';
        $request['metrics'] = array('ga:pageviews', 'ga:pageviewsPerVisit', 'ga:timeOnPage', 'ga:exits');
        $request['sort'] = '-ga:pageviews';
      }
      else {
        $request['metrics'] = array('ga:pageviews', 'ga:pageviewsPerVisit', 'ga:timeOnPage', 'ga:exits', 'ga:goalValueAll', 'ga:goalCompletionsAll');
        $request['sort'] = '-ga:goalValueAll,-ga:pageviews';
      }
    }
    else if ($type == 'entrances') {
      if (($reportModes[0] == 'social') || ($reportModes[0] == 'seo')) {
        //$request['dimensions'][] = 'ga:hasSocialSourceReferral';
        //$request['metrics'] = array('ga:entrances', 'ga:newVisits', 'ga:pageviewsPerVisit', 'ga:timeOnSite', 'ga:bounces');
        //$request['sort'] = '-ga:hasSocialSourceReferral,-ga:entrances';
        $request['metrics'] = array('ga:entrances', 'ga:newVisits', 'ga:pageviewsPerVisit', 'ga:timeOnSite', 'ga:bounces', 'ga:goalValueAll', 'ga:goalCompletionsAll');
        $request['sort'] = '-ga:entrances';
      }
      else {
        $request['metrics'] = array('ga:entrances', 'ga:newVisits', 'ga:pageviewsPerVisit', 'ga:timeOnSite', 'ga:bounces', 'ga:goalValueAll', 'ga:goalCompletionsAll');
        $request['sort'] = '-ga:goalValueAll,-ga:entrances';
      }    
    }
    else if ($type == 'pageviews_valuedevents') {
      $request['metrics'] = array('ga:totalEvents', 'ga:uniqueEvents', 'ga:eventValue');
      if ($reportModes[0] == 'landingpage') {
        $filters[] = "ga:eventCategory=~^Landing page";
        $request['sort'] = '-ga:totalEvents';
      }
      else if ($reportModes[0] == 'social') {
        $filters[] = "ga:eventCategory=~^Social";
        $request['sort'] = '-ga:totalEvents';
      }
      else {
        $filters[] = "ga:eventCategory=~^*!$";
        $request['sort'] = '-ga:eventValue,-ga:totalEvents';
      }
    }
    else if ($type == 'entrances_valuedevents') {
      $request['metrics'] = array('ga:totalEvents', 'ga:uniqueEvents', 'ga:eventValue');
      $filters[] = "ga:eventCategory=~^*!$";
      $request['sort'] = '-ga:eventValue,-ga:totalEvents';
    }
    else if ($type == 'pageviews_goals') {
      foreach ($details AS $id) {
        $request['metrics'][] = "ga:goal{$id}Completions";
        $request['metrics'][] = "ga:goal{$id}Value";
      }
    }
    else if ($type == 'entrances_goals') {
      foreach ($details AS $id) {
        $request['metrics'][] = "ga:goal{$id}Completions";
        $request['metrics'][] = "ga:goal{$id}Value";
      }
    }
    else if ($type == 'eventsource_events') {
      $request['dimensions'][] = 'ga:eventCategory';
      $request['dimensions'][] = 'ga:eventAction';
      $request['dimensions'][] = 'ga:eventLabel';
      //$request['dimensions'][] = 'ga:pagePath';
      $request['metrics'] = array('ga:totalEvents', 'ga:uniqueEvents', 'ga:eventValue');
      $request['sort'] = '-ga:totalEvents';
    }
    else if ($type == 'visit_info') {
       $request['dimensions'][] = 'ga:country';
       $request['dimensions'][] = 'ga:medium';
       $request['dimensions'][] = 'ga:socialNetwork';
       $request['metrics'] = array('ga:entrances', 'ga:goalValueAll'); 
       if ($reportModes[0] == 'visit') {  // visit.recent report
         $request['dimensions'][] = 'ga:visitCount';
         $request['dimensions'][] = 'ga:customVarValue4';
       }
       $request['sort'] = '-ga:goalValueAll,-ga:entrances';
       if ($this->gaFilters['paths']['pagePath']) {
         $segments[] = $this->gaFilters['paths']['pagePath'];
       }
    }
    
    if (($types[0] == 'entrances') && ($this->gaFilters['paths']['landingPagePath'])) {
      $filters[] = $this->gaFilters['paths']['landingPagePath'];
    }
    if (($types[0] == 'pageviews') && ($this->gaFilters['paths']['pagePath'])) {
      $filters[] = $this->gaFilters['paths']['pagePath'];
    }    
    
    $request = $this->applyFiltersToRequest($request);
    if ($indexBy == 'date') {
      $request['dimensions'][] = 'ga:date';
      $dimention_count++;
      // TODO do real days calculation
      //$request['max_results'] = 30 * $items;  
    }
    else if ($indexBy == 'content') {
      $request['dimensions'][] = 'ga:hostname';
      if ($types[0] == 'entrances') {
        $request['dimensions'][] = 'ga:landingPagePath';
      }
      else {
        $request['dimensions'][] = 'ga:pagePath';
      }
      //$request['max_results'] = 4 * $items;  
    } 
    else if ($indexBy == 'pagePath') {
      if ($types[0] == 'entrances') {
        $request['dimensions'][] = 'ga:landingPagePath';
      }
      else {
        $request['dimensions'][] = 'ga:pagePath';
      }
      //$request['max_results'] = 4 * $items;  
    }
    else if ($indexBy == 'visitor') {
      $request['dimensions'][] = 'ga:customVarValue5';
    }
    else if ($indexBy == 'visit') {
      $request['dimensions'][] = 'ga:customVarValue5';
      $request['dimensions'][] = 'ga:visitCount';
      if ($reportModes[1] == 'recent') {
        $request['dimensions'][] = 'ga:customVarValue4';
        $request['sort'] = '-ga:customVarValue4';  
        if ($type == 'entrances') {
          $filter[] = 'ga:entrances>0';
        }      
      }
      //$request['segment'] = (!empty($request['segment']) ? ';' . $this->gaFilters['paths']['pagePath'] : ''); 
    }
    else if ($indexBy == 'trafficsources') {
      $request['dimensions'][] = 'ga:medium';
      $request['dimensions'][] = 'ga:source';
      $request['dimensions'][] = 'ga:referralPath';
      $request['dimensions'][] = 'ga:keyword';
      $request['dimensions'][] = 'ga:socialNetwork';
      $request['dimensions'][] = 'ga:campaign';     
    }
    else if ($indexBy == 'trafficcategory') {
      $request['dimensions'][] = 'ga:medium';
      $request['dimensions'][] = 'ga:socialNetwork';
    }
    else if ($indexBy == 'searchKeyword') {
      $request['dimensions'][] = 'ga:medium';
      $request['dimensions'][] = 'ga:keyword';
      $filters[] = 'ga:medium==organic';
    }
    else if ($indexBy == 'searchEngine') {
      $request['dimensions'][] = 'ga:medium';
      $request['dimensions'][] = 'ga:source';
      $filters[] = 'ga:medium==organic';
    }
    else if ($indexBy == 'referralHostpath') {
      $request['dimensions'][] = 'ga:source';
      $request['dimensions'][] = 'ga:referralPath';
    }
    else if ($indexBy == 'landingpage') {
      $filters[] = "ga:eventCategory=~^Landing page";
    } else if ($indexBy == 'author') {
      $request['dimensions'][] = 'ga:customVarValue1';
      $filters[] = 'ga:customVarValue1=@&a=';
      $filters[] = 'ga:pagePath=@/';  // this entry forces the goal value up to previous pages
    }    
    else if (!empty($indexBy)) {
      $request['dimensions'][] = 'ga:' . $indexBy;
    }
    
    if ($subIndexBy) {
      if ($subIndexBy == 'trafficcategory') {
        $request['dimensions'][] = 'ga:medium';
        $request['dimensions'][] = 'ga:socialNetwork';
      } 
      else if ($subIndexBy == 'socialNetwork') {
        $filters[] = 'ga:socialNetwork!=(not set)';  
        $request['sort'] = '-ga:goalValueAll,-ga:entrances'; 
        $request['dimensions'][] = 'ga:socialNetwork';
      } 
      else if ($subIndexBy == 'organicSearch') {
        $request['dimensions'][] = 'ga:medium';
        $request['metrics'][] = 'ga:organicSearches';
        $filters[] = 'ga:medium==organic';
        $request['sort'] = '-ga:organicSearches'; 
      }     
      else if ($subIndexBy == 'searchKeyword') {
        $request['dimensions'][] = 'ga:medium';
        $request['dimensions'][] = 'ga:keyword';
        $request['metrics'][] = 'ga:organicSearches';
        $filters[] = 'ga:medium==organic';
        $filters[] = 'ga:keyword!@(not '; 
        $request['sort'] = '-ga:organicSearches'; 
      }
      else {
        $request['dimensions'][] = 'ga:' . $subIndexBy;
      }
      
    }

    if ($details) {
      if ($type == 'pageviews' && (!in_array('ga:pagePath', $request['dimensions']))) {
        $request['dimensions'][] = 'ga:pagePath';
      }
      if (($type == 'entrances_valuedevents') || ($type == 'pageviews_valuedevents')) {
        $request['dimensions'][] = 'ga:eventCategory';
      }
      if (($type == 'entrances_goals') || ($type == 'pageviews_goals')) {
        
      }      
    } 
    $request['filters'] = $this->customFilters['filter'] . (($this->customFilters['filter'] && count($filters)) ? ';' : '') . implode(';', $filters);
    if (count($segments) || $this->customFilters['segment']) {
      $request['segment'] = 'dynamic::' . $this->customFilters['segment'] . (($this->customFilters['segment'] && count($segments)) ? ';' : '') . implode(';', $segments);
    }
    return $request;
  }
  
  function addFeedData($feed, $type = '', $indexBy = '', $details = 0) {
    if (empty($feed->results) || !is_array($feed->results)) {
      return;
    }
    $settings = $this->requestSettings;
    $type = ($type) ? $type : $settings['type'];
    $subType = $settings['subType'];
    $indexBy = ($indexBy) ?  $indexBy : $settings['indexBy'];
    $subIndexBy = !empty($settings['subIndexBy']) ? $settings['subIndexBy'] : '';
    $details = ($details) ? $details : $settings['details'];
    if (!isset($this->data[$indexBy])) {
      $this->data[$indexBy] = $this->initIndexDataStruc();
    }
    
    $prime_index = $indexBy;
    if ($prime_index == 'trafficsources') {
      $sub_indexes = $this->getTrafficsourcesSubIndexes();
    }
    else {
      $sub_indexes = array('-');
    }
    
    if (!$prime_index) {
      $prime_index = 'site';
    }

    foreach ($sub_indexes AS $sub_index) {
      if ($sub_index != '-') {
        $d = $this->data[$prime_index][$sub_index];
        $curIndex = $sub_index;
        if (!isset($this->data[$prime_index][$sub_index])) {
          $this->data[$prime_index][$sub_index] = $this->initIndexDataStruc();
        }
      }
      else {
        $d = $this->data[$prime_index];
        $curIndex = $prime_index;
      }
      switch ($type) {
        case 'pageviews':
          $d = $this->addPageviewFeedData($d, $feed, $curIndex, $subIndexBy);
          break;
        case 'entrances':
          $d = $this->addEntranceFeedData($d, $feed, $curIndex, $subIndexBy);
          break;
        case 'pageviews_valuedevents':
          $d = $this->addValuedeventsFeedData($d, $feed, $curIndex, 'pageview');
          break;
        case 'entrances_valuedevents':
          $d = $this->addValuedeventsFeedData($d, $feed, $curIndex, 'entrance');
          break;
        case 'pageviews_goals':
          $d = $this->addGoalsFeedData($d, $feed, $curIndex, 'pageview', $details);
          break;
        case 'entrances_goals':
          $d = $this->addGoalsFeedData($d, $feed, $curIndex, 'entrance', $details);
          break;
        case 'eventsource_events':
          $d = $this->addEventsourceEventFeedData($d, $feed, $curIndex, 'pageview');
          break;
        case 'visit_info':
          $d = $this->addVisitInfoFeedData($d, $feed, $curIndex, 'entrance', $details);
          break;
      }
      if ($sub_index != '-') {
        $this->data[$prime_index][$sub_index] = $d;
      }
      else {
        $this->data[$prime_index] = $d;
      }      
    }  
  }
  
  function addPageviewFeedData($d, $feed, $indexBy, $subIndexBy) {
    if (!isset($d['_all']['pageview'])) {
      $d['_all']['pageview'] = $this->initPageviewDataStruc();
      $d['_totals']['pageview'] = $this->initPageviewDataStruc();      
    }
    $this->_addPageviewFeedDataRow($d['_totals']['pageview'], $feed->totals);
    foreach($feed->results AS $row) {
      if (!$index = $this->initFeedIndex($row, $indexBy, $d, $pagePath)) {
        continue;
      }
      if (!isset($d[$index]['pageview'])) {
        $d[$index]['pageview'] = $this->initPageviewDataStruc();
      }
      $keys = array('_all', $index);
      foreach ($keys AS $k) {
        $this->_addPageviewFeedDataRow($d[$k]['pageview'], $row);
      }
    }
    return $d;     
  }
  
  function _addPageviewFeedDataRow(&$data, $row) {
    $data['pageviews'] += $row['pageviews']; 
    $data['pageviewsPerVisit'] += ($row['pageviews'] * $row['pageviewsPerVisit']);
    $data['timeOnPage'] += $row['timeOnPage'];
    $data['sticks'] += ($row['pageviews'] - $row['exits']);           
    $data['goalValueAll'] += !empty($row['goalValueAll']) ? $row['goalValueAll'] : 0;
    $data['goalCompletionsAll'] += !empty($row['goalCompletionsAll']) ? $row['goalCompletionsAll'] : 0;
    return $data;    
  }
  
  function addEntranceFeedData($d, $feed, $indexBy, $subIndexBy = '') {
    if (!isset($d['_all']['entrance'])) {
      $d['_all']['entrance'] = $this->initEntranceDataStruc();
      $d['_totals']['entrance'] = $this->initEntranceDataStruc();
    }
    if ($subIndexBy && !isset($d['_all']['entrance'][$subIndexBy])) {
      $d['_all']['entrance'][$subIndexBy] = $this->initEntranceDataStruc();
    }
    $this->_addEntranceFeedDataRow($d['_totals']['entrance'], $feed->totals);
    foreach($feed->results AS $row) {
      if (!$index = $this->initFeedIndex($row, $indexBy, $d, $pagePath)) {
        continue;
      }
      $subIndex = $this->initFeedIndex($row, $subIndexBy);
      if (!isset($d[$index]['entrance'])) {
        $d[$index]['entrance'] = $this->initEntranceDataStruc();
      }
      if ($subIndexBy) {
        if (!isset($d[$index][$subIndexBy])) {
          $d[$index][$subIndexBy] = array('_all' => array());
          $d[$index][$subIndexBy]['_all']['entrance'] = $this->initEntranceDataStruc();
        }
        if ($subIndex && !isset($d[$index][$subIndexBy][$subIndex])) {
          $d[$index][$subIndexBy][$subIndex] = array('entrance' => $this->initEntranceDataStruc());
          $d[$index][$subIndexBy][$subIndex]['i'] = $subIndex;         
        }
      }
      
      if ($subIndexBy) {
        if ($subIndex) {
          $this->_addEntranceFeedDataRow($d[$index][$subIndexBy][$subIndex]['entrance'], $row);
        }
        $this->_addEntranceFeedDataRow($d[$index][$subIndexBy]['_all']['entrance'], $row);
        $this->_addEntranceFeedDataRow($d['_all'][$subIndexBy]['entrance'], $row);
      }
      else {
        $this->_addEntranceFeedDataRow($d[$index]['entrance'], $row);
        $this->_addEntranceFeedDataRow($d['_all']['entrance'], $row);
      }
    }
    return $d;     
  }
  
  function _addEntranceFeedDataRow(&$data, $row) {
    $data['entrances'] += $row['entrances'];
    $data['newVisits'] += $row['newVisits'];
    $data['pageviews'] += !empty($row['pageviews']) ? $row['pageviews'] : ($row['entrances'] * $row['pageviewsPerVisit']); 
    $data['pageviewsPerVisit'] += ($row['entrances'] * $row['pageviewsPerVisit']);
    $data['timeOnSite'] += $row['timeOnSite'];
    $data['sticks'] += ($row['entrances'] - $row['bounces']);           
    $data['goalValueAll'] += !empty($row['goalValueAll']) ? $row['goalValueAll'] : 0;
    $data['goalCompletionsAll'] += !empty($row['goalCompletionsAll']) ? $row['goalCompletionsAll'] : 0;
    if (!empty($row['customVarValue4'])) {
      $data['timestamp'] = $row['customVarValue4'];
    }
    return $data;   
  }
  
  function addValuedeventsFeedData($d, $feed, $indexBy, $mode = 'entrance') {
    if (!isset($d['_all'][$mode])) {
      $d['_all'][$mode] = $this->{'init' . $mode . 'DataStruc'}();
      $d['_totals'][$mode] = $this->{'init' . $mode . 'DataStruc'}();      
    }
    $d['_totals'][$mode]['events']['_all'] = $this->_addValuedeventsFeedDataRow($d['_totals'][$mode]['events']['_all'], $feed->totals);
    foreach($feed->results AS $row) {
      if (!$index = $this->initFeedIndex($row, $indexBy, $d, $pagePath)) {
        continue;
      }
      if (!isset($d[$index][$mode])) {
        $d[$index][$mode] = $this->{'init' . $mode . 'DataStruc'}();
      }
      $keys = array('_all', $index);
      foreach ($keys AS $k) {
        if (isset($row['eventCategory'])) {
          $eventCateogry = $row['eventCategory'];
          if (!isset($d[$k][$mode]['events'][$eventCateogry ])) {
            $d[$k][$mode]['events'][$eventCateogry ] = $this->initEventsDataStruc();
            $d[$k][$mode]['events'][$eventCateogry]['i'] = $eventCateogry;
          }
          $d[$k][$mode]['events'][$eventCateogry] = $this->_addValuedeventsFeedDataRow($d[$k][$mode]['events'][$eventCateogry], $row);
        }
        $d[$k][$mode]['events']['_all'] = $this->_addValuedeventsFeedDataRow($d[$k][$mode]['events']['_all'], $row);
      }
    }
    return $d;      
  }
  
  function _addValuedeventsFeedDataRow($data, $row) {
    $data['value'] += $row['eventValue'];
    $data['totalValuedEvents'] += $row['totalEvents'];
    $data['uniqueValuedEvents'] += $row['uniqueEvents'];
    return $data;   
  }
  
  function addGoalsFeedData($d, $feed, $indexBy, $mode = 'entrance', $details) {
    if (!isset($d['_all'][$mode])) {
      $d['_all'][$mode] = $this->{'init' . $mode . 'DataStruc'}();
      $d['_totals'][$mode] = $this->{'init' . $mode . 'DataStruc'}(); 
    }
    foreach ($details AS $id) {
      $d['_totals'][$mode]['goals']['_all'] = $this->_addValuedeventsFeedDataRow($d['_totals'][$mode]['goals']['_all'], $feed->totals, $id);
    }
    foreach($feed->results AS $row) {
      if (!$index = $this->initFeedIndex($row, $indexBy, $d, $pagePath)) {
        continue;
      }
      if (!isset($d[$index][$mode])) {
        $d[$index][$mode] = $this->{'init' . $mode . 'DataStruc'}();
      }
      $keys = array('_all', $index);
      foreach ($keys AS $k) {
        foreach ($details AS $id) {
          if (!isset($d[$k][$mode]['goals']["n$id"])) {
            $d[$k][$mode]['goals']["n$id"] = $this->initGoalsDataStruc();
            $d[$k][$mode]['goals']["n$id"]['i'] = "n$id";
          }
          $d[$k][$mode]['goals']["n$id"] = $this->_addGoalsFeedDataRow($d[$k][$mode]['goals']["n$id"], $row, $id);
          $d[$k][$mode]['goals']['_all'] = $this->_addGoalsFeedDataRow($d[$k][$mode]['goals']['_all'], $row, $id);
        }
      }
    }
    return $d;      
  }
  
  function _addGoalsFeedDataRow($data, $row, $id) {
    $data["completions"] += $row["goal{$id}Completions"];
    $data["value"] += $row["goal{$id}Value"];
    return $data;   
  }
  
  function addVisitInfoFeedData($d, $feed, $indexBy, $mode = 'entrance', $details) {
    $keyOps = array(
      'entrances' => 0, 
      'goalValueAll' => 0, 
      'customVarValue5' => 0,
    );
    foreach($feed->results AS $row) {
      $index = $this->initFeedIndex($row, $indexBy);
      if (!isset($d[$index]['visitinfo'])) {
        $d[$index]['visitinfo'] = array();
      }
      foreach ($row AS $key => $value) {
        if (!isset($keyOps[$key]) ||  $keyOps[$key]) {
          $d[$index]['visitinfo'][$key] = $value;
        }
      }
      if (isset($row['medium'])) {
        $d[$index]['visitinfo']['trafficcategory'] = $this->initFeedIndex($row, 'trafficcategory');
      } 
      $d[$index]['visitinfo']['location'] = $this->initFeedIndex($row, 'location');     
    }
    return $d;
  }
  
  function addEventsourceEventFeedData($d, $feed, $indexBy) {
    if (!isset($d['_all'])) {
      $d['_all'] = $this->initPageviewDataStruc();
      $d['_totals'] = $this->initPageviewDataStruc();      
    }
    $d['_totals']['events']['_all'] = $this->_addEventsourceEventFeedDataRow($d['_totals'][$mode]['events']['_all'], $feed->totals);

    foreach($feed->results AS $row) {
      if (!$index = $this->initFeedIndex($row, $indexBy, $d)) {
        continue;
      }
      if (!isset($d[$index])) {
        $d[$index] = $this->initPageviewDataStruc();        
      }
      if (!isset($d[$index]['title'])) {
        $d[$index]['title'] = $row['eventAction'];
        $d[$index]['url'] = $row['eventLabel'];
      }
      $keys = array('_all', $index);
      foreach ($keys AS $k) {
        if (isset($row['eventCategory'])) {
          $eventCateogry = $row['eventCategory'];
          if (!isset($d[$k]['events'][$eventCateogry])) {
            $d[$k]['events'][$eventCateogry ] = $this->initEventsDataStruc();
            $d[$k]['events'][$eventCateogry]['i'] = $eventCateogry;
          }
          $d[$k]['events'][$eventCateogry] = $this->_addEventsourceEventFeedDataRow($d[$k]['events'][$eventCateogry], $row);
        }
        $d[$k]['events']['_all'] = $this->_addEventsourceEventFeedDataRow($d[$k]['events']['_all'], $row);
      }
    }
    return $d;      
  }
  
  function _addEventsourceEventFeedDataRow($data, $row) {    
    $data['totalEvents'] += $row['totalEvents'];
    $data['uniqueEvents'] += $row['uniqueEvents'];
    if (substr($row['eventCategory'], -1) == '!') {
      $data['value'] += $row['eventValue'];
      $data['totalValuedEvents'] += $row['totalEvents'];
      $data['uniqueValuedEvents'] += $row['uniqueEvents'];
    }
    return $data;   
  }
  
  function initFeedIndex(&$row, $indexBy, &$d = array(), &$pagePath = '') {
    if (!$indexBy) {
      return '';
    }
    $pagePath = !empty($row['pagePath']) ? $this->filterPagePath($row['pagePath']) : '';
    $landingPagePath = !empty($row['landingPagePath']) ? $this->filterPagePath($row['landingPagePath']) : '';
    $path = ($landingPagePath) ? $landingPagePath : $pagePath;
    if (!empty($this->dataIndexCallbacks[$indexBy])) {
      $func = $this->dataIndexCallbacks[$indexBy];
      $index = $func($row);
    } 
    else if ($indexBy == 'content') {
      $index = $row['hostname'] . $path;
    }
    else if ($indexBy == 'pagePath') {
      $index = $path;
    }
    else if ($indexBy == 'referralHostpath') {
      $index = ($row['referralPath'] != '(not set)') ? $row['source'] . $row['referralPath'] : FALSE;
    }
    else if ($indexBy == 'referralPath') {
      $index = ($row['referralPath'] != '(not set)') ? $row['referralPath'] : FALSE;
    }
    else if ($indexBy == 'socialNetwork') {
      $index = ($row['socialNetwork'] != '(not set)') ? $row['socialNetwork'] : FALSE;
    }
    else if ($indexBy == 'searchEngine') {
      if ($row['medium'] == 'organic') {
        $index = (!empty($row['source']) && ($row['source'] != '(not set)')) ? $row['source'] : FALSE;
      }
      else {
        $index = FALSE;
      }
    }
    else if ($indexBy == 'keyword') {
      $index = ($row['keyword'] != '(not set)') ? $row['keyword'] : FALSE;
    }
    else if (($indexBy == 'searchKeyword') || ($indexBy == 'organicSearch')) {
      if ($row['medium'] == 'organic') {
        $index = (!empty($row['keyword']) && ($row['keyword'] != '(not set)')) ? $row['keyword'] : FALSE;
      }
      else {
        $index = FALSE;
      }
    }
    else if ($indexBy == 'campaign') {
      $index = ($row['campaign'] != '(not set)') ? $row['campaign'] : FALSE;
    }
    else if ($indexBy == 'trafficcategory') {
      $index = $this->determineTrafficCategoryIndex($row);
    }
    else if ($indexBy == 'landingpage') {
      $index = $row['eventLabel'];
      // strip query string
      $a = explode('?', $index);
      // strip protocal
      $a = explode('//', $a[0]);
      $index = (count($a) == 2) ? $a[1] : $a[0];
    }
    else if ($indexBy == 'visitor') {
      $index = $row['customVarValue5'];
    }
    else if ($indexBy == 'visit') {
      $index = $row['customVarValue5'] . '-' . $row['visitCount'];
    }
    else if ($indexBy == 'location') {
      if (isset($row['city']) && isset($row['region'])) {
        $index = $row['city'] . ', ' . $row['region'] . (isset($row['country']) ? ' ' . $row['country'] : '');
      }
      else if (isset($row['country'])) {
        $index = $row['country'];
      }
    }
    else if ($indexBy == 'author') {
      $decoded = '';
      $data = $this->unserializeCustomVar($row['customVarValue1'], $decoded);
      $row['customVarValue1'] = $decoded;
      $index = $data['a'];
    }
    else if ($indexBy == 'site') {
      return 'site';
    }
    else {
      $index = $row[$indexBy];
    }
    if ($index && !isset($d[$index])) {
      $d[$index] = array();
      $d[$index]['i'] = $index;
    }
    return $index;
  }
  
  function determineTrafficCategoryIndex($row) {
    if (!empty($row['socialNetwork']) && ($row['socialNetwork'] != '(not set)')) {
      return 'social network';
    }  
    if (!empty($row['hasSocialSourceReferral']) && ($row['hasSocialSourceReferral'] != 'Yes')) {
      return 'social network';
    } 
    if ($row['medium'] == 'facebook') {
      return 'social network';
    } 
    if ($row['medium'] == 'twitter') {
      return 'social network';
    } 
    if ($row['medium'] == 'linkedin') {
      return 'social network';
    } 
    if ($row['medium'] == '(none)') {
      return 'direct';
    }
    if ($row['medium'] == 'organic') {
      return 'organic search';
    }
    if ($row['medium'] == 'email') {
      return 'email';
    }
    if ($row['medium'] == 'referral') {
      return 'referral link';
    }
    if ($row['medium'] == 'feed') {
      return 'feed';
    }  
    return 'other';
  }
  
  function getTrafficsourcesSubIndexes() {
    $s = array(
      'medium', 
      'source', 
      'referralHostpath', 
      'searchKeyword', 
      'socialNetwork', 
      'campaign', 
      'trafficcategory'
    );
    return $s;
  }
  
  function initIndexDataStruc() {
    $a = array(
      '_all' => array(),
      '_totals' => array(),
    );
    return $a;
  }
  
  function initEntranceDataStruc() {
    $a = array(
      'events' => $this->initEventsDataArrayStruc(),
      'goals' => $this->initGoalsDataArrayStruc(),
      'entrances' => 0,
      'newVisits' => 0,
      'pageviews' => 0,
      'pageviewsPerVisit' => 0,
      'timeOnSite' => 0,
      'sticks' => 0,
      'goalValueAll' => 0,
      'goalCompletionsAll' => 0,
    );
    return $a;
  }
  
  function initPageviewDataStruc() {
    $a = array(
      'events' => $this->initEventsDataArrayStruc(),
      'goals' => $this->initGoalsDataArrayStruc(),
      'pageviews' => 0,
      'pageviewsPerVisit' => 0,
      'timeOnPage' => 0,
      'sticks' => 0,
      'goalValueAll' => 0,
      'goalCompletionsAll' => 0,
    );
    return $a; 
  }
  
  function initEventsDataArrayStruc() {
    $a = array();
    $a['_all'] = $this->initEventsDataStruc();
    return $a;
  }
  
  function initEventsDataStruc() {
    $a = array(
      'value' => 0,
      'totalEvents' => 0,
      'uniqueEvents' => 0,
      'totalValuedEvents' => 0,
      'uniqueValuedEvents' => 0,
    );
    return $a;
  }
  
  function initGoalsDataArrayStruc() {
    $a = array();
    $a['_all'] = $this->initGoalsDataStruc();
    return $a;
  }
  
  function initGoalsDataStruc() {
    $a = array(
      'value' => 0,
      'completions' => 0,
    );
    return $a;
  }
  
  function formatPathFilter($path, $type = '', $bestMatch = FALSE) {
    $f = (($type == 'landingpage') || ($type == 'landingPagePath')) ? 'landingPagePath' : 'pagePath';
    $path = urldecode($path);
    if ($bestMatch) {
      $filter = 'ga:' . $f . '=~' . preg_quote(substr($path, -100)) . '(#.*)?$';
      return $filter;
    }
    if (strlen($path) <= 120) {
      $filter = 'ga:' . $f . '=~^' . preg_quote($path) . '(#.*)?$';
    }
    else {
      $filter = 'ga:' . $f . '=@' . $path . ';ga:' . $f . '=~' . preg_quote(substr($path, -100)) . '(#.*)?$';
    }
    return $filter;
  }
  
  function unserializeCustomVar($str, $decoded_str = '') {
    $decoded_str = html_entity_decode($str);
    $a = explode("&", $decoded_str);
    $data = array();
    foreach ($a AS $i => $e) {
      $kv = explode("=", $e);
      if (empty($kv[0])) {
          continue;
      }
      if (count($kv) == 2) {
        $data[$kv[0]] = $kv[1];
      }
      else {
        $data[$kv[0]] = '';
      }
    }
    return $data;
  }
  
  function filterPagePath($path) {
    $path = html_entity_decode($path);
    $filter_queries = array(
      'sid',  // webform's submission id
      'submissionGuid', // HubSpot's form ids
      'hsCtaTracking', // HubSpot CTA tracking
      '_hsenc',  // HubSpot code
      '_hsmi', // HubSpot code
      '__hstc',
      '__hssc',    
    );
    $a = explode('?', $path);
    $query = '';
    if (!empty($a[1])) {
      $b = explode('&', $a[1]);
      foreach ($b AS $c) {
        $d = explode('=', $c);
        if (!in_array($d[0], $filter_queries)) {
          $query .= (($query) ? '&' : '') . $c;
        }   
      }
    }
    if ($query) {
      $path = $a[0] . "?$query"; 
    }
    else {
      $path = $a[0];
    }
    return $path;
  }
  
  function formatGtRegexFilter($param, $number, $key = '') {
    $k = ($key) ? "&$key=" : "^";
    $end = ($key) ? '&' : "$";
    $nstr = (string)$number;
    $num_arr = str_split($nstr);
    $digits = count($num_arr);
    $regex = $param . '=~' . $k . '\d{' . ($digits+1) . '\,}' . $end;  
    $p = '';
    foreach ($num_arr AS $i => $digit) {
      $digit = (int)$digit;
      if ($digit < 9) {
        $regex .= ',' . $param .  '=~' . $k . $p;
        if ((1 + $digit) == 9) {
          $regex .= '9';
        }
        else { 
          $regex .= '[' . (1 + $digit) . '-9]';
        }
        if ($i < ($digits - 1)) {
          $regex .= '\d{' . ($digits - 1 - $i) . '}' . $end;
        }
        else {
          $regex .= $end;
        }
      }
      $p .= (string)$digit; 
    }
    return $regex;  
  }
  
  function formatNltRegexFilter($param, $number) {
    $nstr = (string)$number;
    $num_arr = str_split($nstr);
    $digits = count($num_arr);
    $regex = $param . '!~^\d{0\,' . ($digits-1) . '}$';  
    $p = '';
    foreach ($num_arr AS $i => $digit) {
      $digit = (int)$digit;
      if ($digit > 0) {
        $regex .= ';' . $param .  '!~^' . $p;
        if (($digit - 1) == 0) {
          $regex .= '0';
        }
        else { 
          $regex .= '[0-' . ($digit - 1) . ']';
        }
        if ($i < ($digits - 1)) {
          $regex .= '\d{' . ($digits - 1 - $i) . '}$';
        }
        else {
          $regex .= '$';
        }
      }
      $p .= (string)$digit; 
    }
    return $regex;  
  }  
  
}