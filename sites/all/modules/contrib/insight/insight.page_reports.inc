<?php 

require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'node') . "/node.admin.inc";
/**
 * Menu callback: content administration.
 */
function insight_page_report($form, $form_state) {
  drupal_add_css(drupal_get_path('module', 'insight') . '/insight.admin.css');
  
  $form['filter'] = insight_page_report_filter_form();
  $form['#submit'][] = 'insight_page_report_filter_form_submit';
  $form['admin'] = insight_page_report_pages();

  return $form;
}

/**
 * Form builder: Builds the node administration overview.
 */
function insight_page_report_pages() {

	// TODO set admin_access correctly
	$admin_access = TRUE;
	
  // Build the 'Update options' form.
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#attributes' => array('class' => array('container-inline')),
    '#access' => $admin_access,
  );
  $options = array();
  //foreach (module_invoke_all('node_operations') as $operation => $array) {
  foreach (insight_node_operations() as $operation => $array) {
    $options[$operation] = $array['label'];
  }
  $form['options']['operation'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#title_display' => 'invisible',
    '#options' => $options,
    '#default_value' => 'approve',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#validate' => array('node_admin_nodes_validate'),
    '#submit' => array('node_admin_nodes_submit'),
  );
	
  // Enable language column if translation module is enabled or if we have any
  // node with language.
  $multilanguage = (module_exists('translation') || db_query_range("SELECT 1 FROM {node} WHERE language <> :language", 0, 1, array(':language' => LANGUAGE_NONE))->fetchField());

  $analyzer_defs = insight_analyzer_info();
  
  // Build the sortable table header.
  $header = array(
    'title' => array('data' => t('Title'), 'field' => 'n.title'),
    'type' => array('data' => t('Type'), 'field' => 'n.type'),
    //'author' => t('Author'),
    //'status' => array('data' => t('Status'), 'field' => 'n.status'),
    //'changed' => array('data' => t('Updated'), 'field' => 'n.changed', 'sort' => 'desc')
  );
  if ($multilanguage) {
    $header['language'] = array('data' => t('Language'), 'field' => 'n.language');
  }
  $report_defs = array();
  $report_short_titles = array();
  foreach ($analyzer_defs AS $analyzer_name => $analyzer_def) {
  	if (isset($analyzer_def['reports'])) {
  		foreach ($analyzer_def['reports'] AS $report_name => $report_def) {
  			$report_defs[$report_name] = $report_def;
  			$report_short_titles[$report_def['short title']] = $report_name . '.score';
  	    $header[$report_name] = array('data' => $report_def['short title'], 'field' => $report_name . '.status');
  		}
  	}
  }
  $header['operations'] = array('data' => t('Operations'));

  $query = db_select('node', 'n')->extend('PagerDefault')->extend('TableSort');
  insight_page_report_build_filter_query($query);

  if (!user_access('bypass node access')) {
    // If the user is able to view their own unpublished nodes, allow them
    // to see these in addition to published nodes. Check that they actually
    // have some unpublished nodes to view before adding the condition.
    if (user_access('view own unpublished content') && $own_unpublished = db_query('SELECT nid FROM {node} WHERE uid = :uid AND status = :status', array(':uid' => $GLOBALS['user']->uid, ':status' => 0))->fetchCol()) {
      $query->condition(db_or()
        ->condition('n.status', 1)
        ->condition('n.nid', $own_unpublished, 'IN')
      );
    }
    else {
      // If not, restrict the query to published nodes.
      $query->condition('n.status', 1);
    }
  }
  $query
    ->fields('n')
    ->limit(50)
    ->groupBy('n.nid')
    ->orderByHeader($header);
  // if sorted by report status, add report score as second sort
  if (isset($_GET['order'])  && isset($_GET['sort']) && isset($report_short_titles[$_GET['order']])) {
    $query->orderBy($report_short_titles[$_GET['order']], $_GET['sort']);
  }
  
  foreach ($report_defs AS $name => $def) {
    $alias[$name] = $query->leftJoin('insight_report', $name, "n.nid = %alias.nid AND %alias.name = '$name'");
    $query->addField($alias[$name], 'irid', $name . '_irid');
    $query->addField($alias[$name], 'active', $name . '_active');
    $query->addField($alias[$name], 'status', $name . '_status');
    $query->addField($alias[$name], 'score', $name . '_score');
    $query->addField($alias[$name], 'help', $name . '_help');
  }
  
  
  $nodes = $query  
    ->execute()
    ->fetchAll();

  // Prepare the list of nodes.
  $languages = language_list();
  $destination = drupal_get_destination();
  $options = array();
  foreach ($nodes as $node) {
    $l_options = $node->language != LANGUAGE_NONE && isset($languages[$node->language]) ? array('language' => $languages[$node->language]) : array();
    $options[$node->nid] = array(
      'title' => array(
        'data' => array(
          '#type' => 'link',
          '#title' => $node->title,
          '#href' => 'node/' . $node->nid,
          '#options' => $l_options,
          '#suffix' => ' ' . theme('mark', array('type' => node_mark($node->nid, $node->changed))),
        ),
      ),
      'type' => check_plain(node_type_get_name($node)),
      //'author' => theme('username', array('account' => $node)),
      //'status' => $node->status ? t('published') : t('not published'),
      //'changed' => format_date($node->changed, 'short'),
    );

    if ($multilanguage) {
      if ($node->language == LANGUAGE_NONE || isset($languages[$node->language])) {
        $options[$node->nid]['language'] = $node->language == LANGUAGE_NONE ? t('Language neutral') : t($languages[$node->language]->name);
      }
      else {
        $options[$node->nid]['language'] = t('Undefined language (@langcode)', array('@langcode' => $node->language));
      }
    }
    foreach ($report_defs AS $name => $def) {
    	$v = array(
    	  'irid' => $node->{$name . '_irid'},
    	  'active' => $node->{$name . '_active'},
    	  'score' => $node->{$name . '_score'},
    	  'status' => $node->{$name . '_status'},
    	  'help' => $node->{$name . '_help'},
    	  'type' => $name,
    	);
      $options[$node->nid][$name] = theme_insight_report_value(array('value' => $v, 'report_def' => $report_defs[$name]));
    }
    // Build a list of all the accessible operations for the current node.
    $operations = array();
    if (TRUE && node_access('update', $node)) {
      $operations['analyze'] = array(
        'title' => t('analyze'),
        'href' => 'admin/reports/insight/autoanalyze/node/' . $node->nid,
        'query' => $destination,
      );
    }
    if (node_access('update', $node)) {
      $operations['edit'] = array(
        'title' => t('edit'),
        'href' => 'node/' . $node->nid . '/edit',
        'query' => $destination,
      );
    }
    $options[$node->nid]['operations'] = array();
    if (count($operations) > 1) {
      // Render an unordered list of operations links.
      $options[$node->nid]['operations'] = array(
        'data' => array(
          '#theme' => 'links__node_operations',
          '#links' => $operations,
          '#attributes' => array('class' => array('links', 'inline')),
        ),
      );
    }
    elseif (!empty($operations)) {
      // Render the first and only operation as a link.
      $link = reset($operations);
      $options[$node->nid]['operations'] = array(
        'data' => array(
          '#type' => 'link',
          '#title' => $link['title'],
          '#href' => $link['href'],
          '#options' => array('query' => $link['query']),
        ),
      );
    }
  }

  // Only use a tableselect when the current user is able to perform any
  // operations.
  if ($admin_access) {
    $form['nodes'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#empty' => t('No content available.'),
    );
  }
  // Otherwise, use a simple table.
  else {
    $form['nodes'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $options,
      '#empty' => t('No content available.'),
    );
  }

  $form['pager'] = array('#markup' => theme('pager'));

  return $form;
}

function theme_insight_report_value($variables) {
	$value = $variables['value'];
	$report_def = $variables['report_def']; 

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
	  if ($report_def['score type'] == 'percentage') {
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
  $filters = insight_page_report_filters();
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