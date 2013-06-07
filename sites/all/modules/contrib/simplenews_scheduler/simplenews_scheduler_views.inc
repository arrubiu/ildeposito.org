<?php

/**
 * @file simplenews_scheduler_views.inc
 * Views support for simplenews
 */

/**
 * Implementation of hook_views_tables
 */
function simplenews_scheduler_views_tables() {
  $tables['simplenews_scheduler'] = array(
    'name' => 'simplenews_scheduler',
    'filters' => array(
      'node.created' => array(
        'name' => t('Simplenews schedule: node created'),
        'list' => 'simplenews_scheduler_handler_newsletters',
        'list-type' => 'list',
        'handler' => 'simplenews_scheduler_filter_value',
        'operator' => 'simplenews_scheduler_handler_operator_ca',
        'value-type' => 'array',
        'help' => t('Select the newsletter to filter against, this will filter nodes that have been created AFTER the latest <i>edition</i> of this newsletter'),
      ),
    ),
  );
  return $tables;
}


function simplenews_scheduler_handler_newsletters() {
  
  $list = array();
  
  $result = db_query("SELECT ss.*,n.title FROM {simplenews_scheduler} ss JOIN {node} n ON n.nid = ss.snid GROUP BY snid");
  while($row = db_fetch_array($result)) {
    $list[$row['snid']]="Newsletter: ".$row['title'];
  }
  
  if(sizeof($list) ==0) {
    drupal_set_message('No current newsletter found to filter against, you should create a simplenews newsletter first.'); 
  }
  
  
  return $list;
}


function simplenews_scheduler_filter_value($op, $filter, $filterinfo, &$query) {
  
  // get oldest last_run time of the selected newsletter
  $result=db_query("SELECT ss.*,n.created FROM {simplenews_scheduler} ss
                      LEFT JOIN {node} n on n.nid = ss.snid
                      WHERE ss.snid IN (%s) 
                      ORDER BY ss.last_run 
                      LIMIT 0,1",implode(',',$filter['value']));
  $last_run = db_fetch_array($result);
  
  // then it hasnt run yet, so we use the creation date of the newsletter parent instead
  $trigger_time = $last_run['last_run'] > 0 ? $last_run['last_run'] : $last_run['created'];
  $query->add_field('created', 'node');
  $query->add_where("node.created %s %d", $filter['operator'], $trigger_time);
}


function simplenews_scheduler_handler_operator_ca() {
  return array('>' => t("After Most Recent Edition Of"),'<' => t("Before Most Recent Edition Of"));
}

// any view that has this as a filter should be invalidate cache
function simplenews_scheduler_views_pre_query(&$view) {
  foreach($view->filter as $i => $filter) {
    if( $filter['field'] == 'simplenews_scheduler.node.created') {
      $view->is_cacheable = false;
    }
  }
}