<?php
/**
 * Plugin class.
 */


class LinkitViewsPlugin extends LinkitPlugin {

  /**
   * The uniq table name.
   *
   * @var string
   */
  var $table_name;

  /**
   * Initialize this plugin.
   */
  function __construct($plugin, $profile) {
    parent::__construct($plugin, $profile);

    $this->table_name = 'linkit_tmp_view_table_' . rand(0,1000) . rand(0,1000);
  }

  /**
   * Created a temporary table.
   */
  function create_tmp_table() {
    // If this can be done in a more nice way, please tell me.
    $temp_table = 'CREATE TEMPORARY TABLE {' . $this->table_name . '} (human_name VARCHAR(255) NOT NULL, display_title VARCHAR(65) NOT NULL, path VARCHAR(255) NOT NULL)';
    return db_query($temp_table);
  }

  /**
   * Populate the temporary table with display name and path.
   */
  function populate_tmp_table() {
    // Get all displays that is "page" and their path
    $query = db_select('views_view', 'w')
      ->condition('wd.display_plugin', 'page')
      ->fields('wd', array('display_options', 'display_title'))
      ->fields('w', array('human_name'));
    $query->join('views_display', 'wd', 'w.vid = wd.vid');

    $result = $query->execute();

    foreach ($result AS $view) {
      $optinos = unserialize($view->display_options);
      $fields = array(
        'display_title' => $view->display_title,
        'human_name' => $view->human_name,
        'path' => $optinos['path'],
      );
      db_insert($this->table_name)->fields($fields)->execute();
    }
  }

  /**
   * The autocomplete callback function for the Linkit Entity plugin.
   */
  function autocomplete_callback() {
    // Create the tmp table.
    $this->create_tmp_table();

    // Populate the tmp table.
    $this->populate_tmp_table();

    $matches = array();

    $query = db_select($this->table_name, 'tmp')
      ->fields('tmp', array('path', 'display_title', 'human_name'))
      ->condition('tmp.display_title', '%' . db_like($this->serach_string) . '%', 'LIKE')
      ->addTag('linkit_views_autocomplete')
      ->execute();

    foreach ($query AS $view) {
      $matches[] = array(
        'title' => $view->display_title,
        'path' => base_path() . $view->path,
        'description' => t('View: %view', array('%view' => $view->human_name)),
        'group' => t('View pages'),
      );
    }
    return  $matches;
  }
}