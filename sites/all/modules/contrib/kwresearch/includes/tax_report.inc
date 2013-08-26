<?php

/**
 * @file
 * Generates taxonomy page keyword report on node edit form
 */

/**
 * AJAX handler to refresh tax report
 */
function kwresearch_keywords_tax_report_js() {

  $output = array();
  $form = kwresearch_keyword_tax_report_form($_POST['keywords'], $_POST['vid']);
  $output['report']['output'] = drupal_render($form);
  $output['inputs']['vid'] = $_POST['vid'];

  drupal_json_output($output);
}

/**
 * Generates tax report form api field
 *
 * @param str|array $keywords - list of keywords to include in report as CSV or array of keywords
 * @param int $vid - vocabulary id
 */
function kwresearch_keyword_tax_report_form($keywords, $vid) {
  $form['kwresearch-tax-report-' . $vid] = array(
    '#type' => 'item',
    '#title' => t('Keyword report'),
    '#markup' => kwresearch_keywords_tax_report($keywords),
    '#prefix' => '<div id="kwresearch-tax-report-' . $vid . '" class="kwresearch-tax-report kwresearch-tax-report-' . $vid . '">',
    '#suffix' => '</div>',
    '#weight' => $weight++,
  );
  return $form;
}

/**
 * Generates report for taxonomies
 *
 * @param str|array $keywords - list of keywords to include in report as CSV or array of keywords
 */
function kwresearch_keywords_tax_report($keywords) {

  $output = '';
  $query = db_select('kwresearch_keyword', 'k');
  $rows = array();
  if (!is_array($keywords)) {
    $keywords = explode(',', $keywords);
  }
  //$kws = '';

  $kws_a = array();
  $processed = array();
  foreach ($keywords as $keyword) {
    $keyword = strtolower(trim($keyword));
    if (!$keyword) {
      continue;
    }
    $processed[$keyword] = 0;
    //$kws .= (($kws)?',':'') . '"' . $keyword . '"'; 

    $kws_a[] = $keyword;
  }
  $header = array(
    array(
      'data' => t('Keyword'),
      'field' => 'k.keyword',
    ),
    array(
      'data' => t('Page priority'),
      'field' => 'pk.priority',
      'sort' => 'desc',
    ),
    //array(
    //  'data' => t('Set by'),
    //  'field' => 'up.name',
    //),
    array(
      'data' => t('Site priority'),
      'field' => 'k.priority',
    ),
    array(
      'data' => t('Value'),
      'field' => 'k.value',
    ),
   // array(
    //  'data' => t('Set by'),
    //  'field' => 'u.name',
   // ),
    array(
      'data' => t('Pages'),
      'field' => 'k.page_count',
    ),

    //array('data' => t('Operations')),
  );
  $linkintel_exists = module_exists('linkintel');
  if ($linkintel_exists) {
    $header[] = array(
      'data' => t('Link target'),
      //'field' => 'k.value',
    ); 
    $l = $query->leftJoin('linkintel_request', 'l', "l.kid = k.kid");
    $query->addField('l', 'path', 'link_target_path');   
  }
  $header[] = array(
      'data' => t('Total Daily'),
      'field' => 'k.daily_volume',
    );

  if ($kws_a) {

    $pk  = $query->leftJoin('kwresearch_page_keyword', 'pk', 'pk.kid = k.kid');
    $u  = $query->leftJoin('users', 'u', 'u.uid = k.uid');
    $up = $query->leftJoin('users', 'up', 'up.uid = pk.uid');
    $query->fields('k');
    $query->addField('pk', 'priority', 'page_priority');
    $query->addField('pk', 'uid', 'page_uid');
    $query->addField($u, 'name', 'username');
    $query->addField($up, 'name', 'page_username');
    $query->condition('k.keyword', $kws_a, 'IN');
    $query->extend('PagerDefault')
      ->limit(100);
    $query->extend('TableSort')
      ->orderByHeader($header);
    $result = $query->execute();    

    $priorities = kwresearch_get_priority_options();
    while ($r = $result->fetchObject()) {
      $processed[$r->keyword] = 1;
      $row = array(
        'data' => array(
          // Cells
          check_plain($r->keyword),
          ($r->page_priority > 0) ? $priorities[$r->page_priority] : '-',
          //($r->page_username == NULL) ? '-' : l($r->page_username, 'user/' . $r->page_uid),
          ($r->priority > 0) ? $priorities[$r->priority] : '-',
          ($r->value >= 0) ?  t('$') . number_format($r->value, 2) : '-',
          //($r->username == NULL) ? '-' : l($r->username, 'user/' . $r->uid),
          ($r->page_count == NULL) ? '-' : l(number_format($r->page_count), 'admin/structure/kwresearch/keyword_pages/' . $r->kid, array('target' => '_blank')),
          
          //l(t('stats'), 'admin/structure/kwresearch/keyword_report/' . $r->keyword, array('attributes' => array('target' => '_blank'))) . ' | ' .
          //l(t('pages'), 'admin/structure/kwresearch/keyword_pages/' . $r->kid, array('attributes' => array('target' => '_blank'))),
        ),
        // Attributes for tr
        'class' => array("kwresearch"),
      );
      if ($linkintel_exists) {
        $row['data'][] = (!isset($r->link_target_path)) ? '-' : (($r->link_target_path == arg(0) . '/' . arg(1)) ? 'this' : l($r->link_target_path, $r->link_target_path));
        //$ops .= ' | ' . l(t('set link request'), 'admin/structure/kwresearch/keyword_list/edit/' . $r->kid, $lo2);
      }
      $row['data'][] = ($r->daily_volume == NULL) ? '-' : number_format($r->daily_volume);
      $rows[] = $row;
    }
    foreach ($processed as $keyword => $v) {
      if (!$v) {
        $rows[] = array(
          'data' => array(
            // Cells
            check_plain($keyword),
            t('No data'),
            '',
            //'',
            '',
            //'',
            '',
            '',
            l(t('stats'), 'admin/structure/kwresearch/keyword_report/' . $keyword, array('attributes' => array('target' => '_blank'))),
          ),
          // Attributes for tr
          'class' => array("kwresearch"),
        );
      }
    }
  }
  if (!count($rows)) {
    $rows[] = array(array(
        'data' => t('No keywords were found.'),
        'colspan' => count($header),
      ));
  }

  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'kwresearch-tax-keywords')));
  //$output .= theme('pager', NULL, 100, 0);


  return $output;
}
