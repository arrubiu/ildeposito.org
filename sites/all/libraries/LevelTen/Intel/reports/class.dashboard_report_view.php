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
require_once 'class.report_view.php';
require_once __DIR__ . '/../charts/class.line_chart.php';
require_once __DIR__ . '/../charts/class.table_chart.php';
require_once __DIR__ . '/../charts/class.pie_chart.php';
require_once __DIR__ . '/../charts/class.column_chart.php';
require_once __DIR__ . '/../charts/class.bubble_chart.php';

class DashboardReportView extends ReportView {
  private $tableRowCount = 10;
  private $objectives = array();
  
  function __construct() {
    parent::__construct();
  }
  
  function setTableRowCount($rowCount) {
    $this->tableRowCount = $rowCount;
  }
  
  function setObjective($key, $value) {
    $this->objectives[$key] = $value;
  }
  
  function getTrafficCategories() {
    $c = array(
      'direct' => 'direct',
      'organic search' => 'organic',
      'social network' => 'social',
      'referral link' => 'referral',      
      'feed' => 'feed',
    );
    return $c;
  }
  
  function getConversionGoals() {
    $g = array(
      'n6' => 'ToFu conversion',
      'n7' => 'MoFu conversion',
      'n8' => 'BoFu conversion',
      'n1' => 'Contact form',
    );
    return $g;
  }
  
  function getEngagementEvents() {
    $e = array(
      'Social share!' => 'social shares',
      'Comment!' => 'comments',
      //'CTA click!' => 'cta clicks',
    );
    return $e;
  }
  
  function renderReport() {
    $output = '';
    $data = $this->data;

    $startDate = $this->dateRange['start'];
    $endDate = $this->dateRange['end'];
    $daysInMonth = $this->dateRange['days'];
    $cur_days = (ceil(time() - $startDate) /24/60) / 60; // get current days + hours into this month
    if ($cur_days > $daysInMonth) {
      $cur_days = $daysInMonth;
    }
    $cur_days_per = $cur_days / $daysInMonth;
    $reportModes = $this->modes;
    $targets = $this->targets;
    $indexBy = $this->params['indexBy'];
    $indexByLabel = $this->params['indexByLabel'];
    $daysLastMonth = $this->data['lastmonth']['daterange']['days'];
    $cmpinc = array(
      'entrances_obj' => $targets['entrances_per_month'] / $daysInMonth,
      'leads_obj' => $targets['leads_per_month'] / $daysInMonth,
      'posts_obj' => $targets['posts_per_month'] / $daysInMonth,
      'entrances_lm' => $this->data['lastmonth']['_all']['entrance']['entrances'] / $daysLastMonth,
      'leads_lm' => $this->data['lastmonth']['_all']['leads'] / $daysLastMonth,
      'posts_lm' => $this->data['lastmonth']['_all']['post']['published'] / $daysLastMonth,
      'pageviews_lm' => $this->data['lastmonth']['_all']['entrance']['pageviews'] / $daysLastMonth,
    );
  
    $entrances_chart = new LineChart('objectives');
    //$entrances_chart->setOption('title', 'Performance');
    $entrances_chart->addColumn('date', 'day');
    $entrances_chart->addColumn('number', 'objective');
    $entrances_chart->addColumn('number', 'actual');
    
    $leads_chart = new LineChart('objectives');
    //$leads_chart->setOption('title', 'Performance');
    $leads_chart->addColumn('date', 'day');
    $leads_chart->addColumn('number', 'objective');
    $leads_chart->addColumn('number', 'actual');
    
    $conversions_linechart = new LineChart('objectives');
    //$leads_chart->setOption('title', 'Performance');
    $conversions_linechart->addColumn('date', 'day');
    $conversions_linechart->addColumn('number', 'objective');
    $conversions_linechart->addColumn('number', 'actual');
    
    $trafficCategories = $this->getTrafficCategories();
    $entrances_source_chart = new ColumnChart('objectives');
    //$entrances_source_chart->setOption('title', 'Traffic sources');
    $entrances_source_chart->addColumn('date', 'day');
    foreach ($trafficCategories AS $k => $v) {
      $entrances_source_chart->addColumn('number', $v);
    }
    $entrances_source_chart->addColumn('number', 'other');
    
    $leads_source_chart = new ColumnChart('objectives');
    //$leads_source_chart->setOption('title', 'Traffic sources');
    $leads_source_chart->addColumn('date', 'Day');
    foreach ($trafficCategories AS $k => $v) {
      $leads_source_chart->addColumn('number', $v);
    }
    
    $conversionGoals = $this->getConversionGoals();
    $conversion_goals_chart = new ColumnChart('objectives');
    //$leads_source_chart->setOption('title', 'Traffic sources');
    $conversion_goals_chart->addColumn('date', 'Day');
    foreach ($conversionGoals AS $k => $v) {
      $conversion_goals_chart->addColumn('number', $v);
    }
    
    $post_timeline = new BubbleChart('postsTimeline');
    $post_timeline->addColumn('string', 'Title');
    $post_timeline->addColumn('number', 'Posted');
    $post_timeline->addColumn('number', 'Daily post #');
    $post_timeline->addColumn('string', 'Type');
    $post_timeline->addColumn('number', 'Value/day');
    //$jsStartDate = 1000 * ($startDate + 12 * 60 * 60); // javascript time is in milliseconds. Add 12 hours of time to get to line up with regular dates
    //$jsEndDate = 1000 * ($endDate - 12 * 60 * 60); // javascript time is in milliseconds. Add 12 hours of time to get to line up with regular dates
    $post_timeline->setOption('hAxis.minValue', 1000 * $startDate);
    $post_timeline->setOption('hAxis.maxValue', 1000 * $endDate);
    $ticks = array();
    $ticks[] = 1000 * $startDate;
    $jsDate = (1000 * $startDate);
    for ($i = 0; $i < 4; $i++) {
      $jsDate += (7 * 24 * 60 * 60 * 1000) + (6 * 60 * 60 * 1000);
      $ticks[] = $jsDate;
    }
    $ticks[] = 1000 * $endDate;
    $post_timeline->setOption('hAxis.ticks', $ticks);
    
    $engagementEvents = $this->getEngagementEvents();
    $engagement_events_chart = new ColumnChart('objectives');
    //$leads_source_chart->setOption('title', 'Traffic sources');
    $engagement_events_chart->addColumn('date', 'Day');
    foreach ($engagementEvents AS $k => $v) {
      $engagement_events_chart->addColumn('number', $v);
    }
    
    //$entrances_summary = new TableChart();
    //$entrances_summary->addColumn('string', '');
    //$entrances_summary->addColumn('string', 'vs Objective');
    //$entrances_summary->addColumn('string', 'vs Last month');

    $value_str = '';
    $this->sortData('by_score_then_entrances', $indexBy);
    
    $index0 = date("Ym", $startDate);
    $time = $startDate;
    $entrances_obj = 0;
    $leads_obj = 0;
    $entrances = 0;
    $leads = 0; 
    $conversions = 0;   
    for ($i = 1; $i <= ($daysInMonth); $i++) {
      $index = $index0 . (($i<10) ? '0' : '') . $i;
      $jstime = 1000*$time;
      $d = $data['date'][$index];
      $date = date("M j", $time);
      
      $entrances += !empty($d['entrance']['entrances']) ? $d['entrance']['entrances'] : 0;
      $leads += !empty($d['lead']['leads']) ? $d['lead']['leads'] : 0;
      $entrances_obj += $cmpinc['entrances_obj'];
      $leads_obj += $cmpinc['leads_obj'];
      
      $entrances_chart->newWorkingRow();
      $entrances_chart->addRowItem($jstime);
      $entrances_chart->addRowItem(round($entrances_obj));
      $value = ($i <= ($cur_days+1)) ? (int)$entrances : null;
      $entrances_chart->addRowItem($value);
      $entrances_chart->addRowToSettings();
      
      $leads_chart->newWorkingRow();
      $leads_chart->addRowItem($jstime);
      $leads_chart->addRowItem(round($leads_obj));
      $value = ($i <= ($cur_days+1)) ? (int)$leads : null;
      $leads_chart->addRowItem($value);
      $leads_chart->addRowToSettings();
      
      $entrances_source_chart->newWorkingRow();
      $entrances_source_chart->addRowItem($jstime);
      $sum = 0;
      foreach ($trafficCategories AS $k => $v) {
        $sum += $value = !empty($d['trafficcategory'][$k]) ? (int)$d['trafficcategory'][$k]['entrance']['entrances'] : 0;
        $entrances_source_chart->addRowItem($value);
      }
      $value = (int)$d['trafficcategory']['_all']['entrance']['entrances'] - $sum;
      $entrances_source_chart->addRowItem($value);
      $entrances_source_chart->addRowToSettings();
      
      $leads_source_chart->newWorkingRow();
      $leads_source_chart->addRowItem($jstime);
      foreach ($trafficCategories AS $k => $v) {
        $value = !empty($d['lead']['trafficcategory'][$k]) ? (int)$d['lead']['trafficcategory'][$k] : 0;
        $leads_source_chart->addRowItem($value);
      }
      $leads_source_chart->addRowToSettings();
      
      $conversion_goals_chart->newWorkingRow();
      $conversion_goals_chart->addRowItem($jstime);
      foreach ($conversionGoals AS $k => $v) {
        $value = !empty($d['entrance']['goals'][$k]) ? (int)$d['entrance']['goals'][$k]['completions'] : 0;
        $conversions += $value;
        $conversion_goals_chart->addRowItem($value);
      }
      $conversion_goals_chart->addRowToSettings();
      
      $conversions_linechart->newWorkingRow();
      $conversions_linechart->addRowItem($jstime);
      $conversions_linechart->addRowItem(round($leads_obj));
      $conversions_linechart->addRowItem($conversions);
      $conversions_linechart->addRowToSettings();
      
      $di = 1;
      if (isset($d['post']) && is_array($d['post'])) {
        foreach ($d['post'] AS $id => $post) {
          $post_timeline->newWorkingRow();
          $post_timeline->addRowItem($post['path']);
          $post_timeline->addRowItem(1000*$post['created']);
          $post_timeline->addRowItem($di);
          $post_timeline->addRowItem($post['type']);
          $value = null;
          if (isset($data['content'][$post['host'].$post['path']])) {
            $value = $data['content'][$post['host'].$post['path']]['score'] / ((time() - $post['created']) / 24 / 60 / 60);
          }
          $post_timeline->addRowItem(round($value, 2));
          $post_timeline->addRowToSettings();
          if ($di > $max_posts_in_day) {
            $max_posts_in_day = $di;
          }
          $di++;
        }
      }
      
      $engagement_events_chart->newWorkingRow();
      $engagement_events_chart->addRowItem($jstime);
      foreach ($engagementEvents AS $k => $v) {
        $value = !empty($d['entrance']['events'][$k]) ? (int)$d['entrance']['events'][$k]['totalValuedEvents'] : 0;
        $engagement_events_chart->addRowItem($value);
      }
      $engagement_events_chart->addRowToSettings();
      
      $time += 60*60*24;

    }
    $post_timeline->setOption('vAxis.maxValue', $max_posts_in_day + 1);
    $output = '';
    
    $totals = $data['date']['_all'];
    
    $mostr = date('M', $startDate);
    
    $entrances_summary = '';
    $entrances_summary .= '<div class="summary-box">';
    $entrances_summary .= '<div class="key-metric-box">';
    $entrances_summary .= '<div class="key-metric-value">' . number_format($totals['entrance']['entrances']) . '</div>'; 
    $entrances_summary .= '<div class="key-metric-desc">visitors in ' . $mostr . '</div>'; 
    $entrances_summary .= '</div>';
    $entrances_summary .= '<div class="key-metric-change-box">';
    $mark = $cur_days_per * $targets['entrances_per_month'];
    $entrances_summary .= '<div class="key-metric-change-value">' . $this->formatDeltaValue($totals['entrance']['entrances'], $mark) . '</div>'; 
    $entrances_summary .= '<div class="key-metric-change-desc">vs. objective</div>';
    $mark = $cur_days_per * $data['lastmonth']['_all']['entrance']['entrances'];
    $entrances_summary .= '<div class="key-metric-change-value">' . $this->formatDeltaValue($totals['entrance']['entrances'], $mark) . '</div>'; 
    $entrances_summary .= '<div class="key-metric-change-desc">vs. last month</div>';  
    $entrances_summary .= '</div>';
    $entrances_summary .= '</div>';
    
    $entrances_summary .= '<div class="summary-box">';
    $entrances_summary .= '<div class="key-metric-box">';
    $entrances_summary .= '<div class="key-metric-value">' . number_format($totals['entrance']['pageviews']) . '</div>'; 
    $entrances_summary .= '<div class="key-metric-desc">pageviews in  ' . $mostr . '</div>'; 
    $entrances_summary .= '</div>';
    $entrances_summary .= '<div class="key-metric-change-box">';
    $mark = $cur_days_per * $data['lastmonth']['_all']['entrance']['pageviews'];
    $entrances_summary .= '<div class="key-metric-change-value">' . $this->formatDeltaValue($totals['entrance']['pageviews'], $mark) . '</div>'; 
    $entrances_summary .= '<div class="key-metric-change-desc">vs. last month</div>';
    $entrances_summary .= '</div>';
    $entrances_summary .= '</div>';
    
    $leads_summary = '';
    $leads_summary .= '<div class="summary-box">';
    $leads_summary .= '<div class="key-metric-box">';
    $leads_summary .= '<div class="key-metric-value">' . number_format($totals['lead']['leads']) . '</div>'; 
    $leads_summary .= '<div class="key-metric-desc">new contacts in  ' . $mostr . '</div>'; 
    $leads_summary .= '</div>';
    $leads_summary .= '<div class="key-metric-change-box">';
    $mark = $cur_days_per * $targets['leads_per_month'];
    $leads_summary .= '<div class="key-metric-change-value">' . $this->formatDeltaValue($totals['lead']['leads'], $mark) . '</div>'; 
    $leads_summary .= '<div class="key-metric-change-desc">vs. objective</div>';
    $mark = $cur_days_per * $data['lastmonth']['_all']['lead']['leads'];
    $leads_summary .= '<div class="key-metric-change-value">' . $this->formatDeltaValue($totals['lead']['leads'], $mark) . '</div>'; 
    $leads_summary .= '<div class="key-metric-change-desc">vs. last month</div>';  
    $leads_summary .= '</div>';
    $leads_summary .= '</div>';
    
    $leads_summary .= '<div class="summary-box">';
    $leads_summary .= '<div class="key-metric-box">';
    $leads_summary .= '<div class="key-metric-value">' . number_format($totals['entrance']['goalCompletionsAll']) . '</div>'; 
    $leads_summary .= '<div class="key-metric-desc">conversions in ' . $mostr . '</div>'; 
    $leads_summary .= '</div>';
    $leads_summary .= '<div class="key-metric-change-box">';
    $mark = $cur_days_per * $data['lastmonth']['_all']['entrance']['goalCompletionsAll'];
    $leads_summary .= '<div class="key-metric-change-value">' . $this->formatDeltaValue($totals['entrance']['goalCompletionsAll'], $mark) . '</div>'; 
    $leads_summary .= '<div class="key-metric-change-desc">vs. last month</div>';
    //$leads_summary .= '<div class="key-metric-change-value">' . number_format($cur_leads_objective - $totals['entrance']['newVisits']) . '</div>'; 
    //$leads_summary .= '<div class="key-metric-change-desc">vs. last month</div>';  
    $leads_summary .= '</div>';
    $leads_summary .= '</div>';
    
    $posts_summary = '';
    $posts_summary .= '<div class="summary-box">';
    $posts_summary .= '<div class="key-metric-box">';
    $posts_summary .= '<div class="key-metric-value">' . number_format($totals['post']['published']) . '</div>'; 
    $posts_summary .= '<div class="key-metric-desc">new posts in  ' . $mostr . '</div>'; 
    $posts_summary .= '</div>';
    $posts_summary .= '<div class="key-metric-change-box">';
    $mark = $cur_days_per * $targets['posts_per_month'];
    $posts_summary .= '<div class="key-metric-change-value">' . $this->formatDeltaValue($totals['post']['published'], $mark) . '</div>'; 
    $posts_summary .= '<div class="key-metric-change-desc">vs. objective</div>';
    $mark = $cur_days_per * $data['lastmonth']['_all']['post']['published'];
    $posts_summary .= '<div class="key-metric-change-value">' . $this->formatDeltaValue($totals['post']['published'], $mark) . '</div>'; 
    $posts_summary .= '<div class="key-metric-change-desc">vs. last month</div>';  
    $posts_summary .= '</div>';
    $posts_summary .= '</div>';
    
    $value = 0;
    $last_mo = 0;
    foreach ($engagementEvents AS $k => $v) {
      $value += !empty($totals['entrance']['events'][$k]) ? (int)$totals['entrance']['events'][$k]['totalValuedEvents'] : 0;
      $last_mo += !empty($data['lastmonth']['_all']['entrance']['events'][$k]) ? (int)$data['lastmonth']['_all']['entrance']['events'][$k]['totalValuedEvents'] : 0;
    }
    $posts_summary .= '<div class="summary-box">';
    $posts_summary .= '<div class="key-metric-box">';
    $posts_summary .= '<div class="key-metric-value">' . number_format($value) . '</div>'; 
    $posts_summary .= '<div class="key-metric-desc">engagement events in  ' . $mostr . '</div>'; 
    $posts_summary .= '</div>';
    $posts_summary .= '<div class="key-metric-change-box">';
    $mark = $cur_days_per * $last_mo;
    $posts_summary .= '<div class="key-metric-change-value">' . $this->formatDeltaValue($value, $mark) . '</div>'; 
    $posts_summary .= '<div class="key-metric-change-desc">vs. last month</div>';  
    $posts_summary .= '</div>';
    $posts_summary .= '</div>';
    
    
    $output .= '<div id="content-section" class="report-section">';
    $output .= '<h3>Traffic</h3>'; 
    $output .= '<div class="pane-left-30">';    
    $output .= $entrances_summary;
    $output .= '</div>';
    $output .= '<div class="pane-spacer">&nbsp;</div>';
    $output .= '<div class="pane-right-70">';
    $output .= $entrances_chart->renderOutput();
    $output .= $entrances_source_chart->renderOutput();
    $output .= '</div>'; 
    $output .= '</div>'; 
    
    $output .= '<div id="content-section" class="report-section">';
    $output .= '<h3>Conversion</h3>'; 
    $output .= '<div class="pane-left-30">';    
    $output .= $leads_summary;
    $output .= '</div>';
    $output .= '<div class="pane-spacer">&nbsp;</div>';
    $output .= '<div class="pane-right-70">';
    //$output .= $conversions_linechart->renderOutput();
    $output .= $leads_chart->renderOutput();
    //$output .= $leads_source_chart->renderOutput();
    $output .= $conversion_goals_chart->renderOutput();
    $output .= '</div>';
    $output .= '</div>'; 

    $output .= '<div id="content-section" class="report-section">';
    $output .= '<h3>Content &amp; engagement</h3>'; 
    $output .= '<div class="pane-left-30">';    
    $output .= $posts_summary;
    $output .= '</div>';
    $output .= '<div class="pane-spacer">&nbsp;</div>';
    $output .= '<div class="pane-right-70">';
    $output .= $post_timeline->renderOutput();
    $output .= $engagement_events_chart->renderOutput();
    $output .= '</div>';
    $output .= '</div>';  
    
    $output .= '</div>'; 
    
    $output .= 'generated by <a href="http://levelten.net" target="_blank">LevelTen Intelligence</a>';
    
    return '<div id="intel-report">' . $output . '</div>';    
  }
  
  function formatDeltaValue($val1, $val0, $decimals = 0, $percent_decimals = 1) {
    $delta = $val1 - $val0;
    $output = '';
    if ($delta >= 0) {
       $pre = '<span class="delta-value-positive"><img src="/' . $this->libraryUri . '/icons/delta_value_positive.png" width="16" height="16"></span>+'; 
       $per_pre = '+';
    }
    else {
       $pre = '<span class="delta-value-negative"><img src="/' . $this->libraryUri . '/icons/delta_value_negative.png" width="16" height="16"></span>-'; 
       $per_pre = '-';
    }
    
    $output .= '<span class="delta-value-value">' . $pre . str_replace('-', '', number_format($delta, $decimals)) . '</span>';
    $per = 0;
    if ($val0 != 0) {
      $per = 100 * (($val1 / $val0) -1);
    }
    $output .= '<span class="delta-value-percentage"> (' . $per_pre . str_replace('-', '', number_format($per, $percent_decimals)) . '%)</span>';
    return $output;
  }

}

