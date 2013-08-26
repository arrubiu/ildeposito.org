<?php

/**
 * @file
 * Admin include file.
 */

/**
 * Generates site keywords report page
 * @param str $mode - filters keywords return. Settings are all|site|page
 */
function kwresearch_keywords_list_page($mode = 'site') {
  kwresearch_input_get_as_filters();

  drupal_add_css(drupal_get_path('module', 'kwresearch') . '/kwresearch.css');
  drupal_add_js(drupal_get_path('module', 'kwresearch') . '/kwresearch.js');

  $output = "";
  // create site keyword data for js

  /*
  $site_kw = array();
  $sql = '
    SELECT * FROM {kwresearch_keyword}
    WHERE priority > 0
  ';
  $res = db_query($sql);

  while ($r = $res->fetchObject()) {
    $site_kw[$r->keyword] = array(
      'kid' => (int) $r->kid,
      'priority' => (int) $r->priority,
      'value' => (int) $r->value,
      'page_count' => (int) $r->page_count,
    );
  }
  */

  if ($mode == 'page') {
    drupal_set_title('Page keywords');
  }
  elseif ($mode == 'site') {
    drupal_set_title('Site keywords');
  }
  else {
    drupal_set_title('All keywords');
  }
  $filter = kwresearch_build_filter_query();
  $rows = array();
  //return 'debug';

  $output .= render(drupal_get_form('kwresearch_filter_form'));
  //dsm($filter);


  $def_values = kwresearch_get_site_report_data_options_defaults();
  $data_options = variable_get('kwresearch_site_report_data_options', $def_values);
  $column_th = kwresearch_get_report_data_options('site', TRUE);

  $header = array(
    array(
      'data' => t('Keyword'),
      'field' => 'k.keyword',
      'sort' => 'asc',
    ),
    array(
      'data' => t('Priority'),
      'field' => 'k.priority',
    ),
    array(
      'data' => t('Value'),
      'field' => 'k.value',
    ),
    array(
      'data' => t('Set by'),
      'field' => 'u.name',
    ),
    array(
      'data' => t('Pages'),
      'field' => 'k.page_count',
    ),
  );
  if (module_exists('linkintel')) {
    $header[] = array(
      'data' => t('Link target'),
      'field' => 'r.path',      
    );
  }
  if (is_array($data_options)) {
    foreach ($data_options as $k => $v) {
      $f = $k;
      if ($k == 'google_dailyest' || $k == 'yahoo_dailyest' || $k == 'bing_dailyest') {
        $f = 'daily_volume';
      }
      if ($v) {
      	if(isset($column_th[$k])) {
	        $header[] = array(
	          'data' => $column_th[$k],
	          'field' => 'k.' . $f,
	        );
      	}
      }
    }
  }

  // note cannot put a line break in pager_query sql statements

  /*
   $sql = 'SELECT k.*, u.name AS username FROM {kwresearch_keyword} k LEFT JOIN {users} u ON u.uid = k.uid';
   $tablesort = tablesort_sql($header);
   if (!empty($filter['where'])) {
   $sql = $sql ." WHERE " . (($mode == 'site') ? 'k.priority > 0 AND ' : '') . $filter['where'] . $tablesort;
   $result = pager_query($sql, 100, 0, NULL, $filter['args']);
   }
   else {
   if ($mode == 'site') {
   $sql .= ' WHERE k.priority > 0';
   }
   elseif ($mode == 'page') {
   $sql .= ' WHERE k.page_count > 0';
   }
   $result = pager_query($sql . $tablesort, 100);
   }
   */
  $options['mode'] = $mode;
  $result = kwresearch_load_filtered_keyword_result($filter, $options, $header);
  $priorities = kwresearch_get_priority_options();

  $analysis = array();
  $analysis['analysis'] = array();
  $analysis['meta'] = array(
    'searches_max' => 0,
    'bid_max' => 0,
  );

  while ($r = $result->fetchAssoc()) {
    $analysis['analysis'][$r['keyword']] = $r;
    $analysis['analysis'][$r['keyword']]['_searches'] = $r['daily_volume'];
    $analysis['analysis'][$r['keyword']]['_competition'] = $r['competition'];
    $analysis['analysis'][$r['keyword']]['_bid'] = $r['bid'];
    if ($r['daily_volume'] > $analysis['meta']['searches_max']) {
      $analysis['meta']['searches_max'] = $r['daily_volume'];
    }
    if ($r['bid'] > $analysis['meta']['bid_max']) {
      $analysis['meta']['bid_max'] = $r['bid'];
    }

    if (!isset($site_kw[$r['keyword']]) || !$site_kw[$r['keyword']]) {
      $site_kw[$r['keyword']] = array(
        'kid' => (int) $r['kid'],
        'priority' => (int) $r['priority'],
        'value' => (int) $r['value'],
        'page_count' => (int) $r['page_count'],
      );
    }
  }
  if (is_array($analysis['analysis']) && !empty($analysis['analysis'])) {
    foreach ($analysis['analysis'] as $keyword => $values) {
      $row = array();
      $row[] = kwresearch_format_report_data_value(array('term' => $keyword));
      $row[] = array(
        'data' => ($values['priority'] >= 0) ? $priorities[$values['priority']] : '-',
        'class' => array('site_priority'),
      );
      $row[] = array(
        'data' => ($values['value'] >= 0) ? t('$') . number_format($values['value'], 2)  : '-',
        'class' => array('value'),
      );
      $row[] = array(
        'data' => ($values['username']) ? l($values['username'], 'user/' . $values['uid']) : '-',
        'class' => array('user'),
      );
      $row[] = array(
        //'data' => l(number_format($values['page_count']), 'admin/content/kwresearch/keyword_pages/' . $values['kid'], array('query' => 'destination=admin/content/kwresearch/keyword_list' . (($mode == 'site') ? '/site' : ''))),
        'data' => l(number_format($values['page_count']), 'admin/structure/kwresearch/keyword_pages/' . $values['kid'], array('query' => array('destination' => 'admin/structure/kwresearch/keyword_list'))),
        'class' => array('page_count'),
      );
      if (module_exists('linkintel')) {
        $row[] = (!isset($values['link_request_path'])) ? '-' : l($values['link_request_path'], $values['link_request_path']);
      }
      foreach ($data_options as $k => $v) {
        if ($v) {
          $values['_meta'] = $analysis['meta'];
          if (!$r = kwresearch_format_report_data_value($values, $keyword, $k)) {
            if (is_array($sources)) {
              foreach ($sources as $aid => $source) {
                if ($source['site_report_values_callback'] && ($r = call_user_func($source['site_report_values_callback'], $values, $keyword, $k))) {
                  break;
                }
              }
            }
          }
          $row[] = $r;
        }
      }
      $rows[] = array(
        'data' => $row,
        'class' => array('kwresearch'),
        'id' => 'kid-' . $values['kid'],
      );
    }
  }

  if (!$rows) {
    $rows[] = array(array(
        'data' => t('No keywords available.'),
        'colspan' => count($header),
      ));
  }
  $vars = array(
    'header' => $header, 
    'rows' => $rows, 
    'attributes' => array('id' => 'kwresearch-site-keywords')
  );
  $output .= theme('table', $vars);
  //pager_default_initialize($total, 1, $element = 0);
  $output .= theme('pager');
  $site_priority_options = kwresearch_get_priority_options();
  drupal_add_js(
    array('kwresearch' => array(
      'form' => 'admin_keyword_list',
      'analyze_path' => base_path() . 'admin/structure/kwresearch/keyword_report/',
      'keyword_edit_path' => base_path() . 'admin/structure/kwresearch/keyword_list/edit/',
      'return_destination' => 'admin/structure/kwresearch/keyword_list' . (($mode != 'all') ? '/' . $mode : ''),
      'toggle_site_keyword_callback' => base_path() . 'kwresearch/toggle_site_keyword_js',
      'delete_site_keyword_callback' => base_path() . 'kwresearch/delete_site_keyword_js',
      'module_path' => base_path() . drupal_get_path('module', 'kwresearch'),
      'enable_site_keyword_tool' => user_access('kwresearch admin site keywords'),
      'site_keywords_data' => isset($site_kw) ? $site_kw : '',
      'site_priority_options' => $site_priority_options,
    )), array('type' => 'setting', 'scope' => JS_DEFAULT));
  return $output;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function kwresearch_input_get_as_filters() {
  //dsm($_GET['filters']);

  if (isset($_GET['filters']) && $_GET['filters']) {
    $_SESSION['kwresearch_overview_filter'] = json_decode($_GET['filters'], TRUE);
  }
}

/**
 * Build query for site keywords report filters based on session.
 */
function kwresearch_build_filter_query() {
  //dsm($_SESSION['kwresearch_overview_filter']);  

  if (empty($_SESSION['kwresearch_overview_filter'])) {
    return;
  }

  $filters = kwresearch_filters();

  // Build query

  $where = $args = array();
  //dsm($_SESSION['kwresearch_overview_filter']);

  foreach ($_SESSION['kwresearch_overview_filter'] as $key => $filter) {
    //dsm($filters[$key]);

    //dsm($filter);

    $filter_where = array();
    if ($filters[$key]['type'] == 'select') {
      if (!is_array($filter)) {
        $filter = array($filter);
      }
      foreach ($filter as $value) {
        $filter_where[] = $filters[$key]['where'];
        $args[] = $value;
      }
    }
    elseif ($filter) {
      $filter_where[] = $filters[$key]['where'];
      if ($key == 'keyword_includes') {
        $args[] = '%' . $filter  . '%';
      }
      else {
        $args[] = $filter;
      }
    }
    if (!empty($filter_where)) {
      $where[] = '(' . implode(' OR ', $filter_where) . ')';
    }
  }
  $where = !empty($where) ? implode(' AND ', $where) : '';

  return array(
    'where' => $where,
    'args' => $args,
  );
}

/**
 * Return form for site keyword list filters.
 *
 */
function kwresearch_filter_form($form) {
  $session = &$_SESSION['kwresearch_overview_filter'];
  $session = is_array($session) ? $session : array();
  $filters = kwresearch_filters();

  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter keywords'),
    '#theme' => 'dblog_filters',
    '#collapsible' => TRUE,
    '#collapsed' => empty($session),
  );
  foreach ($filters as $key => $filter) {
    if ($filter['type'] == 'textfield') {
      $form['filters']['status'][$key] = array(
        '#title' => $filter['title'],
        '#type' => 'textfield',
        '#size' => (isset($filter['size'])) ? $filter['size'] : 8,
      );
    }
    elseif ($filter['type'] == 'select') {
      $form['filters']['status'][$key] = array(
        '#title' => $filter['title'],
        '#type' => 'select',
        '#multiple' => TRUE,
        '#size' => 6,
        '#options' => $filter['options'],
      );
    }
    elseif ($filter['type'] == 'markup') {
      $form['filters']['status'][$key] = array(
        '#type' => $filter['type'],
        '#value' => $filter['value'],
      );
    }
    if (!empty($session[$key])) {
      $form['filters']['status'][$key]['#default_value'] = $session[$key];
    }
  }

  $form['filters']['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
  );
  if (!empty($session)) {
    $form['filters']['buttons']['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset'),
    );
  }

  return $form;
}

/**
 * Returns filters for site keywords report
 */
function kwresearch_filters() {
  $filters = array();

  $options = kwresearch_get_priority_options();
  $filters['keyword_includes'] = array(
    'title' => t('Includes'),
    'type' => 'textfield',
    'size' => 60,
    'where' => 'k.keyword LIKE "%s"',
  );
  $filters['priority'] = array(
    'title' => t('Priority'),
    'type' => 'select',
    'where' => 'k.priority = %d',
    'options' => $options,
  );

  $filters['value0'] = array(
    'type' => 'markup',
    'value' => '<div id="value-fields-wrapper">',
  );
  $filters['value_min'] = array(
    'title' => t('Min value'),
    'type' => 'textfield',
    'where' => 'k.value >= %d',
  );
  $filters['value_max'] = array(
    'title' => t('Max value'),
    'type' => 'textfield',
    'where' => 'k.value <= %d',
  );
  $filters['value1'] = array(
    'type' => 'markup',
    'value' => '</div>',
  );

  $filters['page_count0'] = array(
    'type' => 'markup',
    'value' => '<div id="page_count-fields-wrapper">',
  );
  $filters['page_count_min'] = array(
    'title' => t('Min pages'),
    'type' => 'textfield',
    'where' => 'k.page_count >= %d',
  );
  $filters['page_count_max'] = array(
    'title' => t('Max pages'),
    'type' => 'textfield',
    'where' => 'k.page_count <= %d',
  );
  $filters['page_count1'] = array(
    'type' => 'markup',
    'value' => '</div>',
  );

  $filters['daily0'] = array(
    'type' => 'markup',
    'value' => '<div id="daily-fields-wrapper">',
  );
  $filters['daily_min'] = array(
    'title' => t('Min daily volume'),
    'type' => 'textfield',
    'where' => 'k.daily_volume >= %d',
  );
  $filters['daily_max'] = array(
    'title' => t('Max daily volume'),
    'type' => 'textfield',
    'where' => 'k.daily_volume <= %d',
  );
  $filters['daily1'] = array(
    'type' => 'markup',
    'value' => '</div>',
  );

  return $filters;
}

/**
 * Validate result from site keyword report filter form.
 */
function kwresearch_filter_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Filter') 
     && empty($form_state['values']['keyword_includes'])
     && empty($form_state['values']['priority']) 
     && empty($form_state['values']['value_min'])
     && empty($form_state['values']['value_max'])
     && empty($form_state['values']['daily_min'])
     && empty($form_state['values']['daily_max'])
  ) {
    form_set_error('type', t('You must select something to filter by.'));
  }
}

/**
 * Process result from site keywords report filter form.
 */
function kwresearch_filter_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];
  $filters = kwresearch_filters();
  switch ($op) {
    case t('Filter'):
      foreach ($filters as $name => $filter) {
        if (isset($form_state['values'][$name])) {
          $_SESSION['kwresearch_overview_filter'][$name] = $form_state['values'][$name];
        }
      }
      break;
    case t('Reset'):
      $_SESSION['kwresearch_overview_filter'] = array();
      break;
  }
  return 'admin/structure/kwresearch/site_keywords';
}

/**
 * enables total dailyest by default
 */
function kwresearch_get_site_report_data_options_defaults() {
  //$def_values['total_dailyest'] = 'total_dailyest';
  $def_values['daily_volume'] = 'daily_volume';
  return $def_values;
}
