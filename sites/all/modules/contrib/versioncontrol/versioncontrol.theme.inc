<?php
/**
 * @file
 * Theme functions for Version Control API.
 */

/**
 * Return a rendered visual diffstat.
 *
 * @param $variables
 *   An associative array containing:
 *   - places
 *   - result
 *
 * @todo: Documentation for arguments.
 */
function theme_versioncontrol_diffstat($variables) {
  $places = $variables['places'];
  $result = $variables['result'];
  $output = '';
  drupal_add_css(drupal_get_path('module', 'versioncontrol') . '/versioncontrol.css');
  for ($i = 0; $i++, $i <= $places;) {
    if ($result['add'] != 0) {
      $output .= '<span class="plus">+</span>';
      $result['add']--;
      continue;
    }
    if ($result['remove'] != 0) {
      $output .= '<span class="minus">-</span>';
      $result['remove']--;
      continue;
    }
    $output .= '<span class="no-op"> </span>';
  }
  return '<span class="versioncontrol-diffstat clear-block">' . $output . '</span>';
}

/**
 * Generate an RSS item element for one versioncontrol operation.
 */
function theme_versioncontrol_view_row_operation_rss($variables) {
  $row = $variables['row'];
  $output = '<item>';
  $output .= '<title>' . $row->title . '</title>';
  $output .= '<link>' . $row->link . '</link>';
  $output .= '<description>' . check_plain($row->description) . '</description>';
  $output .= empty($row->elements) ? '' : format_xml_elements($row->elements);
  $output .= '</item>';
  return $output;
}

/**
 * Return a the username of a VCS account.
 *
 * @param $variables
 *   An associative array containing:
 *   - uid: The Drupal user id of the user. If this is 0, the corresponding
 *     Drupal user naturally can't be retrieved, with all implications for
 *     displaying the username.
 *   - username: The VCS username for the account.
 *   - repository: The repository where this account is registered.
 *   - options: An array of options that further influence the output format:
 *     - 'prefer_drupal_username': By default, this function tries to get the
 *        corresponding Drupal user for the supplied uid and returns the
 *        "real" username rather than the given one. If this is set to FALSE,
 *        the given VCS username is always returned.
 *     - 'format': By default, the username will be linked to the user page
 *        (for Drupal users) or to the commit log page containing the user's
 *        commits (for unassociated accounts). If 'plaintext', the username
 *        will be returned without markup.
 *     - 'include_repository_name': By default, an account that is not
 *        associated to a Drupal user will get the repository name appended in
 *        order to make for a unique account descriptor. If this option is set
 *        to TRUE, the repository name will be suppressed anyways.
 */
function theme_versioncontrol_account_username($variables) {
  $uid = $variables['uid'];
  $username = $variables['username'];
  $repository = $variables['repository'];
  $options = $variables['options'];

  $prefer_drupal_username = isset($options['prefer_drupal_username'])
  ? $options['prefer_drupal_username']
  : TRUE;
  $format = isset($options['format']) ? $options['format'] : 'html';

  if ($uid && $prefer_drupal_username) {
    $user = user_load($uid);

    if ($user && $prefer_drupal_username) {
      return ($format == 'html') ? theme('username', $user) : $user->name;
    }
  }

  if (!empty($options['include_repository_name'])) {
    $username = t('!user @ !repository', array(
      '!user' => $username,
      '!repository' => $repository->name,
    ));
  }
  if ($format == 'html' && module_exists('commitlog')) {
    $url = url('commitlog', array(
      'query' => array('username' => $username, 'repo' => $repository['repo_id']),
    ));
    return l($username, $url);
  }
  return $username;
}

/**
 * Return a table of contributors for the specified per-user statistics.
 *
 * @param $variables
 *   An associative array containing:
 *   - statistics:  An array of statistics objects as returned by
 *     versioncontrol_get_operation_statistics(), grouped by at least uid and
 *     optionally repo_id/username columns.
 *   - options: An array of optional further options. Currently, the only
 *     supported array key is 'constraints' which contains the operation
 *     constraints used to determine these statistics. If given, the "Commits"
 *     column in the table will link to the contributor's commits in addition to
 *     displaying the commit count.
 */
function theme_versioncontrol_user_statistics_table($variables) {
  $statistics = $variables['statistics'];
  $options = $variables['options'];
  $header = array(t('User'), t('Last commit'), t('First commit'), t('Commits'));
  $rows = array();

  foreach ($statistics as $user_stats) {
    $last_operation_date = t('!time ago', array(
      '!time' => format_interval(time() - $user_stats->last_operation_date, 1),
    ));
    $first_operation_date = t('!time ago', array(
      '!time' => format_interval(time() - $user_stats->first_operation_date, 1),
    ));
    $total_operations = format_plural(
    $user_stats->total_operations, '1 commit', '@count commits'
    );

    if (isset($options['constraints']) && module_exists('commitlog')) {
      if (isset($user_stats->repo_id) && isset($user_stats->username)) {
        $options['constraints']['repo_ids'] = array($user_stats->repo_id);
        $options['constraints']['usernames'] = array($user_stats->username);
      }
      else {
        $options['constraints']['uids'] = array($user_stats->uid);
      }
      $total_operations = l($total_operations, commitlog_get_url($options['constraints']));
    }

    $rows[] = array(
    theme('versioncontrol_user_statistics_account', array('user_stats' => $user_stats)),
    $last_operation_date,
    $first_operation_date,
    $total_operations,
    );
  }
  return theme('table', $header, $rows);
}

/**
 * Return a condensed item list of contributors for the specified per-user
 * statistics. An empty string is returned if the given array is empty.
 *
 * @param $variables
 *   An associative array containing:
 *   - statistics: An array of statistics objects as returned by
 *     versioncontrol_get_operation_statistics(), grouped by at least uid and
 *     optionally repo_id/username columns.
 *   - more_link: flag to include or not the more link.
 */
function theme_versioncontrol_user_statistics_item_list($variables) {
  $statistics = $variables['statistics'];
  $more_link = isset($variables['more_link']) ? $variables['more_link'] : NULL;
  $items = array();

  if (empty($statistics)) {
    return '';
  }
  drupal_add_css(drupal_get_path('module', 'versioncontrol') . '/versioncontrol.css');

  foreach ($statistics as $user_stats) {
    $item = '<div class="versioncontrol-committer-item">';
    $item .= t('!committer - !commit-count', array(
      '!committer' => theme('versioncontrol_user_statistics_account', array('user_stats' => $user_stats)),
      '!commit-count' => '<span class="versioncontrol-commit-count">'
    . format_plural($user_stats->total_operations, '1 commit', '@count commits')
    . '</span>',
    ));

    if (!empty($user_stats->first_operation_date)) {
      // has committed yet?
      $item .= '<div class="versioncontrol-commit-times">';
      $item .= t('last: !last_time ago, first: !first_time ago', array(
        '!last_time' => format_interval(time() - $user_stats->last_operation_date, 1),
        '!first_time' => format_interval(time() - $user_stats->first_operation_date, 1),
      ));
      $item .= '</div>';
    }
    $item .= '</div>';
    $items[] = $item;
  }

  $output = theme('item_list', $items);
  if (!empty($more_link)) {
    $output .= $more_link;
  }
  return $output;
}

/**
 * Given a single statistics object (including uid for the Drupal user and
 * optionally a repo_id/username combination), return a themed version of the
 * corresponding user.
 *
 * @param $variables
 *   An associative array containing:
 *   - user_stats
 *
 * @todo: Documentation for arguments.
 */
function theme_versioncontrol_user_statistics_account($variables) {
  $user_stats = $variables['user_stats'];
  if (isset($user_stats->repo_id) && isset($user_stats->username)) {
    $repository = versioncontrol_repository_load($user_stats->repo_id);
    $theme_variables = array(
      'uid' =>  $user_stats->uid,
      'username' => $user_stats->username,
      'repository' => $repository,
      'options' => array('include_repository_name' => TRUE),
    );
    return theme('versioncontrol_account_username', $theme_variables);
  }
  else {
    $committer = user_load($user_stats->uid);
    return theme('username', $committer);
  }
}
