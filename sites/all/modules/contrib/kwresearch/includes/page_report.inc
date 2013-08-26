<?php

/**
 * @file
 * Admin include file.
 */

/**
 * Generates table of keywords associated with a pages
 *
 * @param int|str $pid - page id; the nid (int) or path (str) of the page
 */
function kwresearch_page_keywords_page($pid, $mode = NULL) {
  drupal_add_css(drupal_get_path('module', 'kwresearch') . '/kwresearch.css');
  kwresearch_set_admin_theme();
  $query = db_select('kwresearch_page_keyword', 'pk');
  drupal_set_title('Page keywords');
  if ($mode == 'node') {
    $pid = $pid->nid;
  }
  if ($pid > 0) {
    $node = node_load($pid);
    $path = 'node/' . $pid;
    $query->condition('pk.nid', $pid);
  }
  else {
    $path = $pid;
    $query->condition('pk.path', $pid);
  }
  $output = t('Page: !page', 
    array(
    '!page' => l($path, $path),
  )      
  );

  $rows = array();

  //dsm($filter);

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
    //array(
    //  'data' => t('Set by'),
    //  'field' => 'u.name',
    //),
  );
  
  $linkintel_exists = module_exists('linkintel');
  if ($linkintel_exists) {
    $header[] = array(
      'data' => t('Link target'),
      //'field' => 'k.value',
    ); 
    $l = $query->leftJoin('linkintel_request', 'l', "l.kid = pk.kid");
    $query->addField('l', 'path', 'link_target_path');   
  }
  $header[] =  array(
      'data' => t('Total Daily'),
      'field' => 'k.daily_volume',
    );
  $header[] = array('data' => t('Operations'));

  /*
  $sql = '
    SELECT pk.priority AS page_priority, pk.uid AS page_uid, k.*, u.name AS username, up.name AS page_username
    FROM {kwresearch_page_keyword} pk
    JOIN {kwresearch_keyword} k ON pk.kid = k.kid
    LEFT JOIN {users} u ON u.uid = k.uid
    LEFT JOIN {users} up ON up.uid = pk.uid
    WHERE ' . $where . '
  ';
  $tablesort = tablesort_sql($header);
  $sql = $sql . $tablesort;
  $result = pager_query($sql, 100, 0, NULL, $pid);
  */
  
  $k  = $query->innerJoin('kwresearch_keyword', 'k', '%alias.kid = pk.kid');
  $u  = $query->leftJoin('users', 'u', '%alias.uid = k.uid');
  $up = $query->leftJoin('users', 'up', '%alias.uid = pk.uid');
  $query->fields($k);
  $query->addField('pk', 'priority', 'page_priority');
  $query->addField('pk', 'uid', 'page_uid');
  $query->addField($u, 'name', 'username');
  $query->addField($up, 'name', 'page_username');
  $query->extend('PagerDefault')
    ->limit(100);
  $query->extend('TableSort')
    ->orderByHeader($header);
  $result = $query->execute();

  
  
  $priorities = kwresearch_get_priority_options();
  $dest = 'admin/structure/kwresearch/page_keywords/' . $pid;
  if ($mode == 'node') {
    $dest = 'node/' . $pid . '/kwresearch';
  }
  $lo = array('query' => array('destination' => $dest)); 
  $lo2 = $lo;
  $lo2['query']['link_request_url'] = $path;
  if (isset($node->title)) {
    $lo2['query']['link_request_title'] = $node->title;
  }
  while ($r = $result->fetchObject()) {
    $ops = l(t('edit page keyword'), 'admin/structure/kwresearch/page_keywords_edit/' . $pid . '/' . $r->kid, $lo)
      . ' | ' . l(t('edit keyword'), 'admin/structure/kwresearch/keyword_list/edit/' . $r->kid, $lo);
    $row = array(
      'data' => array(
        // Cells
        check_plain($r->keyword),
        $priorities[$r->page_priority],
        //($r->page_uid > 0) ? l($r->page_username, 'user/' . $r->page_uid) : '-',
        ($r->priority > 0) ? $priorities[$r->priority] : '-',
        ($r->value >= 0) ?  t('$') . number_format($r->value, 2) : '-',
        //($r->uid > 0) ? l($r->username, 'user/' . $r->uid) : '-',
      ),
      'class' => array('kwresearch'),
    );
    if ($linkintel_exists) {
      $row['data'][] = (!isset($r->link_target_path)) ? '-' : (($r->link_target_path == $path) ? 'this' : l($r->link_target_path, $r->link_target_path));
      $ops .= ' | ' . l(t('set link request'), 'admin/structure/kwresearch/keyword_list/edit/' . $r->kid, $lo2);
    }
    $row['data'][] = ($r->daily_volume >= 0) ? number_format($r->daily_volume) : '-';
    $row['data'][] = $ops;

    $rows[] = $row;
  }

  if (!$rows) {
    $rows[] = array(array(
        'data' => t('No keywords associated with this page.'),
        'colspan' => count($header),
      ));
  }
  $vars = array(
    'header' => $header, 
    'rows' => $rows, 
    'attributes' => array('id' => 'kwresearch-site-keywords'),
  );
  $output .= theme('table', $vars);
  $output .= theme('pager', array('tags' => NULL, 'element' => 0));

  $output .= l(t('Add page keyword'), 'admin/structure/kwresearch/page_keywords_edit/' . $pid, $lo);

  return $output;
}
