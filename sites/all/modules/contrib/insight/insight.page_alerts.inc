<?php 
/**
 * Menu callback: content administration.
 */
function insight_page_alerts_page($form, $form_state, $include = 'active') {
  drupal_add_css(drupal_get_path('module', 'insight') . '/insight.admin.css');
  
  //$form['filter'] = insight_page_report_filter_form();
  $form['#submit'][] = 'insight_page_report_filter_form_submit';
  $form['admin'] = insight_page_alerts($include);

  return $form;
}

/**
 * Form builder: Builds the node administration overview.
 */
function insight_page_alerts($include = 'active') {

	
  $analyzer_defs = insight_analyzer_info(TRUE);
  $content_reports = $analyzer_defs['#meta']['reports_by_type']['content'];
  $report_defs = $analyzer_defs['#meta']['reports'];
  unset($analyzer_defs['#meta']);
  
  // Build the sortable table header.
  $header = array(
    'level' => array('data' => t('Level'), 'field' => 'a.status'),
    //'active' => array('data' => t('Active'), 'field' => 'a.active'),
    'message' => array('data' => t('Message'), 'field' => 'a.message'),
    'report' => array('data' => t('Report'), 'field' => 'a.report'),
    'node' => array('data' => t('Node'), 'field' => 'a.nid')
    //'author' => t('Author'),
    //'status' => array('data' => t('Status'), 'field' => 'n.status'),
    //'changed' => array('data' => t('Updated'), 'field' => 'n.changed', 'sort' => 'desc')
  );
  $header['operations'] = array('data' => t('Operations'));

  $query = db_select('insight_alert', 'a')->extend('PagerDefault')->extend('TableSort');
  
  insight_page_report_build_filter_query($query);
 
  $query
    ->fields('a')
    ->condition('a.report', $content_reports)
    ->limit(50)
    ->orderByHeader($header);
  
  $n_alias = $query->innerJoin('node', 'n', '%alias.nid = a.nid');
  $query->addField($n_alias, 'title', 'node_title');  
    
  if($include != 'all') {
  	$v = ($include == 'active') ? 1 : (($include == 'ignore' ? 0 : -1));
  	$query->condition('a.active', $v);
  	$r_alias = $query->innerJoin('insight_report', 'r', '%alias.irid = a.irid');
  	$query->condition('r.active', $v);
  } 
 
  $alerts = $query  
    ->execute()
    ->fetchAll();

  // Prepare the list of nodes.
  $destination = drupal_get_destination();
  $options = array();
  foreach ($alerts as $alert) {
  	$node = new stdClass();
  	$node->nid = $alert->nid;
  	$status = 'message';
  	$level_vars = array(
  	  'path' => 'misc/message-24-message.png',
  	  'alt' => 'message',
  	);
  	if ($alert->status == 1) {
      $level_vars['path'] = 'misc/message-24-warning.png';  
      $level_vars['alt'] = 'warning';  
      $status = 'warning';  		
  	}
    elseif ($alert->status == 0) {
      $level_vars['path'] = 'misc/message-24-error.png';  
      $level_vars['alt'] = 'error'; 
      $status = 'error';       
    }
    $options[$alert->iaid]['data'] = array(
      'level' => theme('image', $level_vars),
      //'active' => $alert->active,
      'message' => $alert->message,
      'report' => l($report_defs[$alert->report]['title'], 'admin/reports/insight/report/' .  $alert->irid, array('query' => drupal_get_destination())),
      'node' => l($alert->node_title, 'node/' .  $alert->nid, array('query' => drupal_get_destination())),
    );
    //$options[$alert->iaid]['class'] = array($status);

    // Build a list of all the accessible operations for the current node.
    $operations = array();
    if ($alert->active == 1) {
      $operations['dismiss'] = array(
        'title' => t('dismiss'),
        'href' => 'admin/reports/insight/alert/active/' . $alert->iaid . '/dismiss',
        'query' => $destination,
      ); 	    
    	$operations['ignore'] = array(
	      'title' => t('ignore'),
	      'href' => 'admin/reports/insight/alert/active/' . $alert->iaid . '/ignore',
	      'query' => $destination,
	    );    	
    }
    elseif ($alert->active == 0) {
      $operations['activate'] = array(
        'title' => t('activate'),
        'href' => 'admin/reports/insight/alert/active/' . $alert->iaid . '/activate',
        'query' => $destination,
      );      	
    }
    $options[$alert->iaid]['data']['operations'] = array(
      'data' => array(
        '#theme' => 'links',
        '#links' => $operations,
        '#attributes' => array('class' => array('links', 'inline')),
      ),
    );
  }

  // Only use a tableselect when the current user is able to perform any
  // operations.
  if (FALSE && $admin_access) {
    $form['alerts'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#empty' => t('No active content alerts.'),
    );
  }
  // Otherwise, use a simple table.
  else {
    $form['alerts'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $options,
      
      '#empty' => t('No active content alerts.'),
    );
  }

  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

function theme_insight_report_value($variables) {
	$value = $variables['value'];

	$status = 'none';
	$active = '';
	$score = '';
	if (isset($value['irid'])) {
		$score = $value['score'];
		if ($value['status'] == 2) {
			$status = 'complete';
			$score = ($score) ? $score : 'P';
		}
		elseif ($value['status'] == 1) {
	    $status = 'warning';
	    $score = ($score) ? $score : 'W';
	  }
	  elseif ($value['status'] == 0) {
	    $status = 'error';
	    $score = ($score) ? $score : 'F';
	  }
	  if (is_numeric($score)) {
	  	$score = $score . '%';
	  }
	  $active = ($value['active']) ? 'active' : 'inactive';
	}
	else {
		$score = 'NA';
	}
	$output = '<div id="insight-report-value-' . $value['irid'] . '" class="insight-report-value ' . $status . ' ' . $active . '" title="' . strip_tags($value['help']) . '">';
	$output .= $score;
	$output .= '</div>';
	$output = l($output, 'admin/reports/insight/report/' .  $value['irid'], array('html' => TRUE, 'query' => drupal_get_destination()));
	return $output;
}

/**
 * List node administration filters that can be applied.
 */
function insight_page_report_filters() {
  // Regular filters
  $filters['status'] = array(
    'title' => t('status'),
    'options' => array(
      '[any]' => t('any'),
      'status-1' => t('published'),
      'status-0' => t('not published'),
      'promote-1' => t('promoted'),
      'promote-0' => t('not promoted'),
      'sticky-1' => t('sticky'),
      'sticky-0' => t('not sticky'),
    ),
  );
  // Include translation states if we have this module enabled
  if (module_exists('translation')) {
    $filters['status']['options'] += array(
      'translate-0' => t('Up to date translation'),
      'translate-1' => t('Outdated translation'),
    );
  }

  $filters['type'] = array(
    'title' => t('type'),
    'options' => array(
      '[any]' => t('any'),
    ) + node_type_get_names(),
  );

  // Language filter if there is a list of languages
  if ($languages = module_invoke('locale', 'language_list')) {
    $languages = array(LANGUAGE_NONE => t('Language neutral')) + $languages;
    $filters['language'] = array(
      'title' => t('language'),
      'options' => array(
        '[any]' => t('any'),
      ) + $languages,
    );
  }
  return $filters;
}

/**
 * Apply filters for node administration filters based on session.
 *
 * @param $query
 *   A SelectQuery to which the filters should be applied.
 */
function insight_page_report_build_filter_query(SelectQueryInterface $query) {
  // Build query
  $filter_data = isset($_SESSION['node_overview_filter']) ? $_SESSION['node_overview_filter'] : array();
  foreach ($filter_data as $index => $filter) {
    list($key, $value) = $filter;
    switch ($key) {
      case 'status':
        // Note: no exploitable hole as $key/$value have already been checked when submitted
        list($key, $value) = explode('-', $value, 2);
      case 'type':
      case 'language':
        $query->condition('n.' . $key, $value);
        break;
    }
  }
}

function insight_page_report_filter_form() {
  $session = isset($_SESSION['node_overview_filter']) ? $_SESSION['node_overview_filter'] : array();
  $filters = insight_page_report_filters();

  $i = 0;
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only items where'),
    '#theme' => 'exposed_filters__node',
  );
  foreach ($session as $filter) {
    list($type, $value) = $filter;
    if ($type == 'term') {
      // Load term name from DB rather than search and parse options array.
      $value = module_invoke('taxonomy', 'term_load', $value);
      $value = $value->name;
    }
    elseif ($type == 'language') {
      $value = $value == LANGUAGE_NONE ? t('Language neutral') : module_invoke('locale', 'language_name', $value);
    }
    else {
      $value = $filters[$type]['options'][$value];
    }
    $t_args = array('%property' => $filters[$type]['title'], '%value' => $value);
    if ($i++) {
      $form['filters']['current'][] = array('#markup' => t('and where %property is %value', $t_args));
    }
    else {
      $form['filters']['current'][] = array('#markup' => t('where %property is %value', $t_args));
    }
    if (in_array($type, array('type', 'language'))) {
      // Remove the option if it is already being filtered on.
      unset($filters[$type]);
    }
  }

  $form['filters']['status'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('clearfix')),
    '#prefix' => ($i ? '<div class="additional-filters">' . t('and where') . '</div>' : ''),
  );
  $form['filters']['status']['filters'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filters')),
  );
  foreach ($filters as $key => $filter) {
    $form['filters']['status']['filters'][$key] = array(
      '#type' => 'select',
      '#options' => $filter['options'],
      '#title' => $filter['title'],
      '#default_value' => '[any]',
    );
  }

  $form['filters']['status']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['filters']['status']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => count($session) ? t('Refine') : t('Filter'),
  );
  if (count($session)) {
    $form['filters']['status']['actions']['undo'] = array('#type' => 'submit', '#value' => t('Undo'));
    $form['filters']['status']['actions']['reset'] = array('#type' => 'submit', '#value' => t('Reset'));
  }

  drupal_add_js('misc/form.js');

  return $form;
}

/**
 * Process result from node administration filter form.
 */
function insight_page_report_filter_form_submit($form, &$form_state) {
  $filters = node_filters();
  switch ($form_state['values']['op']) {
    case t('Filter'):
    case t('Refine'):
      // Apply every filter that has a choice selected other than 'any'.
      foreach ($filters as $filter => $options) {
        if (isset($form_state['values'][$filter]) && $form_state['values'][$filter] != '[any]') {
          // Flatten the options array to accommodate hierarchical/nested options.
          $flat_options = form_options_flatten($filters[$filter]['options']);
          // Only accept valid selections offered on the dropdown, block bad input.
          if (isset($flat_options[$form_state['values'][$filter]])) {
            $_SESSION['node_overview_filter'][] = array($filter, $form_state['values'][$filter]);
          }
        }
      }
      break;
    case t('Undo'):
      array_pop($_SESSION['node_overview_filter']);
      break;
    case t('Reset'):
      $_SESSION['node_overview_filter'] = array();
      break;
  }
}