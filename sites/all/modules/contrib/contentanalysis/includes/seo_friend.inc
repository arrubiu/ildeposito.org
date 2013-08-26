<?php
// $Id: seo_friend.inc,v 1.1.2.2 2010/09/26 17:14:13 tomdude48 Exp $
/**
 * @file * Admin include file. 
*/

/**
 * Implementation of hook_seo_reports().
 */
function contentanalysis_seo_reports() {
  return array(
    'contentanalysis' => array(
      'title' => 'Content Analysis',
      'callback' => 'contentanalysis_seo_friend_report',
      ),
    );
}

function contentanalysis_seo_friend_report() {
  $use_pager = TRUE;
  
  $analyzers_meta = module_invoke_all('contentanalysis_analyzers');
  
  $analyzers = array();
  $rows = array();
  
  $sql = '
	SELECT DISTINCT analyzer 
	FROM {contentanalysis_status}
  ';
  $result = db_query($sql);
  while($a = db_result($result)) {
	$analyzers[$a] = $analyzers_meta[$a]['title'];
  }
  $header = array(
      array('data' => 'nid', 'field' => 'n.nid'),
      array('data' => 'status', 'field' => 'n.status'),
      array('data' => 'node title', 'field' => 'r.title'),
  );
  if(!is_array($analyzers)) {
    drupal_set_message(t('No statuses have been reported by any content analyzers. To generate reports, click the "Analyze content" button from a node edit form.'), 'warning');
	$analyzers = array();
  }
  else {  
    foreach($analyzers AS $aid => $analyzer) {
	  $header[] = array('data' => $analyzer, 'field' => 'as_' . $aid . '.statusi');
      $did = 'as_' . $aid;
      $a_join .= "LEFT JOIN {contentanalysis_status} AS $did ON a.aid = $did.aid AND $did.analyzer = \"$aid\"\n";
      $a_select .= ", $did.statusi AS {$aid}_statusi, $did.score AS {$aid}_score";
    } 
  }  
  $header[] = array('data' => t('ops'));
  
  $nodes = array();
  $page_title_field = '';
  $page_title_join = '';
  if (module_exists('page_title')) {
    $page_title_field = ', p.page_title ';
    $page_title_join = ' LEFT JOIN {page_title} AS p ON n.nid=p.'.seo_friend_get_page_title_id_column();
  }
  $sql = '
      SELECT n.nid, n.status, n.type, r.title, n.sticky ' . $page_title_field . $a_select . ' 
      FROM {node} AS n
	  LEFT JOIN {contentanalysis} AS a ON n.nid = a.nid
	  ' . $a_join . '
      INNER JOIN {node_revisions} AS r ON n.vid=r.vid ' . $page_title_join;
  $sql .= tablesort_sql($header);
  if ($use_pager) {
    $count_sql = '
      SELECT COUNT(n.nid) AS row_count
      FROM {node} AS n
	  LEFT JOIN {contentanalysis} AS a ON n.nid = a.nid
	  ' . $a_join . '
      INNER JOIN {node_revisions} AS r ON n.vid=r.vid '.$page_title_join.
      tablesort_sql($header);
    $pager_num = seo_friend_get_number_variable(SEO_PAGER_NUM, 100);
    $result = pager_query($sql, $pager_num, 0, $count_sql);
  }

  while ($r = db_fetch_object($result)) {
    $data = array();

	$data[] = array('data' => $r->nid, 'class' => 'row-status');
	$data[] = seo_friend_get_node_status($r);
	$data[] = l($r->title, 'node/'.$r->nid);
	foreach($analyzers AS $aid => $analyzer) {
      $value = NULL;
      $class = NULL;
      $scoreh = $aid . '_score';
	  $statush = $aid . '_statusi';
	  if($r->$scoreh) {
	    $dec = ($analyzers_meta[$aid]['score decimals']) ? $analyzers_meta[$aid]['score decimals'] : 1;
        $value = $analyzers_meta[$aid]['score prefix'] . number_format($r->$scoreh, $dec) . $analyzers_meta[$aid]['score suffix'];
      }
      if(is_null($r->$statush)) {
	    $value = ($value) ? $value : t('NA');
		$class = 'status';	
	  }
	  else if($r->$statush == 2) {
        $value = ($value) ? $value : t('OK');
        $class = 'ok';		
      }
      else if($r->$statush == 1) {
        $value = ($value) ? $value : t('warn');
		$class = 'warning';
      }
      else if($r->$statush == 0) {
        $value = ($value) ? $value : t('error');
		$class = 'error';
      }	
	  $data[] = array(
	    'data' => $value,
		'class' => $class,
	  );
	}	
	$data[] = l('Edit', 'node/'.$r->nid.'/edit');
    $rows[] = array('data' =>
      $data,
      'class' => $duplicates ? 'error' : 'ok'
    );
  }

  if (!$rows) {
    $rows[] = array(array('data' => t('No keywords associated with this page.'), 'colspan' => count($header)));
  }  

  $output .= theme('table', $header, $rows, array('id' => 'kwresearch-site-keywords'));
  $output .= theme('pager', NULL, $pager_num, 0);

  return $output;  
}