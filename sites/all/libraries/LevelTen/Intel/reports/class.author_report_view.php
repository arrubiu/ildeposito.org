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
require_once __DIR__ . '/../charts/class.table_chart.php';
require_once __DIR__ . '/../charts/class.pie_chart.php';
require_once __DIR__ . '/../charts/class.bubble_chart.php';

class AuthorReportView extends ReportView {
  private $tableRowCount = 10;
  
  function __construct() {
    parent::__construct();
  }
  
  function setTableRowCount($rowCount) {
    $this->tableRowCount = $rowCount;
  }
  
  function renderReport() {
    $output = '';
    $startDate = $this->dateRange['start'];
    $endDate = $this->dateRange['end'];
    $reportModes = $this->modes;
    $targets = $this->targets;
    $indexBy = 'author';
    $indexByLabel = 'Author';
  
    $table = new TableChart('entrances_pageview_value_indicators');
    $table->setColumnElement(0, 'label', 'Authors');
    $table->insertColumn(1, 'number', 'Posts');
    $table->setOption('sortColumn', 4);
    $table->removeColumn(8);

    $entrs_pie_chart = new PieChart();
    $entrs_pie_chart->addColumn('string', $indexByLabel);
    $entrs_pie_chart->setSetting('useTotal', 1);

    $entrs_pie_chart->setOption('title', 'Entrances');
    $entrs_pie_chart->addColumn('number', 'Entrances');
    $entrs_pie_chart->setSetting('total', $this->data[$indexBy]['_totals']['entrance']['entrances']);
    
    $value_pie_chart = new PieChart();
    $value_pie_chart->setOption('title', 'Value');
    $value_pie_chart->addColumn('string', 'Page');
    $value_pie_chart->addColumn('number', 'Entrances');
    $value_pie_chart->setSetting('useTotal', 1);
    //$total = !empty($this->data['content']['_totals']['score']) ? $this->data[$indexBy]['_totals']['score'] : $this->data[$indexBy]['_all']['score'];
    $total = $this->data[$indexBy]['_all']['score'];
    $value_pie_chart->setSetting('total', $total);
    
    $bubble_chart = new BubbleChart();
    $item = array(
      'type' => 'string',
      'label' => 'Page',
    );
    $bubble_chart->addColumn($item);
    
    $item = array(
      'type' => 'number',
      'label' => 'Value/entr',
      'pattern' => '#,###.##',
    );
    $bubble_chart->addColumn($item);
    $item = array(
      'type' => 'number',
      'label' => 'Entr/day',
      'pattern' => '#,###.#',
    );
    $bubble_chart->addColumn($item);
    $hAxis = array(
      'title' => t('Value/entrance'),
      'format' => '#,###.##',  
    );
    $bubble_chart->setOption('hAxis', $hAxis);
    $vAxis = array(
      'title' => t('Entrances/day'),
      'format' => '#,###.#',
    );
    $bubble_chart->setOption('vAxis', $vAxis);
    
    $item = array(
      'type' => 'number',
      'label' => 'Value/day',
      'pattern' => '#,###.##',
    );
    $bubble_chart->addColumn($item);

    $chartArea = array(
      'left' => 50,
      'top' =>  30,
      'width' => "95%",
      'height' => 330,
    );
    $bubble_chart->setOption('chartArea', $chartArea);

    $colorAxis = array(
      'minValue' => $targets['value_per_page_per_day_warning'],
      'maxValue' => $targets['value_per_page_per_day'],
      'colors' => array(
        $this->chartColors[2],
        $this->chartColors[3],
        $this->chartColors[1],
      ),
    );
    $bubble_chart->setOption('colorAxis', $colorAxis);
    $bubble_chart->setSetting('div_height', '400px');

    $value_str = '';
    $this->sortData('by_score_then_entrances', $indexBy);
    foreach($this->data[$indexBy] AS $n => $d) {
      if (empty($d['i']) || (substr($d['i'], 0 , 1) == '_')) { continue; } 
      
      $entrances = !empty($d['entrance']['entrances']) ? $d['entrance']['entrances'] : 0;
      $pageviews = !empty($d['entrance']['pageviews']) ? $d['entrance']['pageviews'] : 0;
      $pageviews = round($pageviews);
      $value = round($d['score'], 2);
      $days = $this->dateRange['days'];
      $itemLabel = $this->formatRowString($d['author']['name'], 60);

      $table->newWorkingRow();
      $table->addRowItem(render::link($itemLabel, $d['author']['profile_url']));

      $table->addRowItem((int)$d['author']['published_nodes']);
      $table->addRowItem($entrances);
      
      $table->addRowItem($pageviews);
      $table->addRowItem($value);
        
      $format = $this->renderValueScore(array('value' => $value, 'type' => 'value_per_page_per_day', 'number_of_days' => $days, 'title' => $title), $value_str);
      $table->addRowItem((float)$value_str, $format);
      
      if ($entrances) {
        $format = $this->renderValueScore(array('value' => $entrances, 'type' => 'entrances_per_page_per_day', 'number_of_days' => $days), $value_str);
        $table->addRowItem((float)$value_str, $format);
        
        $format = $this->renderValueScore(array('value' => ($value / $entrances), 'type' => 'value_per_page_per_entrance'), $value_str);
        $table->addRowItem((float)$value_str, $format);
      }
      else {
        $table->addRowItem(0);
        $table->addRowItem(0);
      }
 
      //$table->addRowItem(implode(' ', $d['links']));
      $table->addRow();
      
        $entrs_pie_chart->addRow(array($itemLabel, $entrances));
        
        $value_pie_chart->addRow(array($itemLabel, $value));
      
      if (($indexBy != 'searchKeyword') ||  ($itemLabel != '(not provided)')) {
        $vpe = ($entrances) ? $value/$entrances : 0;
        $epd = ($entrances/$days);
        $bubble_chart->addRow(array($itemLabel, round($vpe, 2), round($epd, 1), round($value/$days, 2)));
      }
      if ($table->curRowCount >= $this->tableRowCount) {
        break;
      }
    }
    $bubble_chart->setSetting('plotThreshold', array('columnIndex' => 2, 'minValue' => 1));

    $output = '';
    $output .= '<div id="content-section" class="report-section">';
    $output .= '<div class="pane-left-40">';
    $output .= $entrs_pie_chart->renderOutput();
    $output .= $value_pie_chart->renderOutput();
    $output .= '</div>';
    $output .= '<div class="pane-spacer">&nbsp;</div>';
    $output .= '<div class="pane-right-60">';
    $output .= $bubble_chart->renderOutput();
    $output .= '</div>'; 
    $output .= '</div>';   
    
    $output .= '<div id="content-section" class="report-section">';
    $output .= '<h3>' . t('Traffic sources') . '</h3>';
    //$output .= $out_table; 
    $output .= $table->renderOutput();
    $output .= '</div>';  
    
    $output .= 'generated by <a href="http://levelten.net" target="_blank">LevelTen Intelligence</a>';
    
    return '<div id="intel-report">' . $output . '</div>';
  }
}