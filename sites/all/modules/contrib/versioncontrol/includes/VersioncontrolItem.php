<?php
/**
 * @file
 * Item class
 */

/**
 * Represent an Item (a.k.a. item revisions)
 *
 * Files or directories inside a specific repository, including information
 * about the path, type ("file" or "directory") and (file-level)
 * revision, if applicable. Most item revisions, but probably not all of
 * them, are recorded in the database.
 */
abstract class VersioncontrolItem extends VersioncontrolEntity {
  protected $_id = 'item_revision_id';

  /**
   * DB identifier.
   *
   * @var    int
   */
  public $item_revision_id;

  /**
   * Operation identifier.
   *
   * @var    int
   */
  public $vc_op_id;

  /**
   * The path of the item.
   *
   * @var    string
   */
  public $path;

  /**
   * Deleted status.
   *
   * @var    boolean
   */
  public $deleted;

  /**
   * A specific revision for the requested item, in the same VCS-specific
   * format as $item->revision. A repository/path/revision combination is
   * always unique, so no additional information is needed.
   *
   * @var    string
   */
  public $revision;

  public $source_item_revision_id;

  /**
   * The VersioncontrolItem representing the previous revision of this file
   * or directory.
   *
   * @var VersioncontrolItem
   */
  protected $sourceItem;

  /**
   * For a single item (file or directory) in a commit, or for branches
   * and tags. Either
   * VERSIONCONTROL_ACTION_{ADDED,MODIFIED,MOVED,COPIED,MERGED,DELETED,
   * REPLACED,OTHER}
   *
   * @var    array
   */
  public $action;

  public $line_changes_added;

  public $line_changes_removed;

  /**
   * The type of the item. Either
   * VERSIONCONTROL_ITEM_{FILE,DIRECTORY,FILE_DELETED,DIRECTORY_DELETED}.
   */
  public $type;

  /**
   * FIXME: ?
   */
  private static $successor_action_priority = array(
    VERSIONCONTROL_ACTION_MOVED => 10,
    VERSIONCONTROL_ACTION_MODIFIED => 10,
    VERSIONCONTROL_ACTION_COPIED => 8,
    VERSIONCONTROL_ACTION_MERGED => 9,
    VERSIONCONTROL_ACTION_OTHER => 1,
    VERSIONCONTROL_ACTION_DELETED => 1,
    VERSIONCONTROL_ACTION_ADDED => 0, // does not happen, guard nonetheless
    VERSIONCONTROL_ACTION_REPLACED => 0, // does not happen, guard nonetheless
  );

  /**
   * Return TRUE if the given item is an existing or an already deleted
   * file, or FALSE if it's not.
   */
  public function isFile() {
    if ($this->type == VERSIONCONTROL_ITEM_FILE
      || $this->type == VERSIONCONTROL_ITEM_FILE_DELETED) {
        return TRUE;
      }
    return FALSE;
  }

  /**
   * Return TRUE if the given item is an existing or an already deleted
   * directory, or FALSE if it's not.
   */
  public function isDirectory() {
    if ($this->type == VERSIONCONTROL_ITEM_DIRECTORY
      || $this->type == VERSIONCONTROL_ITEM_DIRECTORY_DELETED) {
        return TRUE;
      }
    return FALSE;
  }

  /**
   * Return TRUE if the given item is marked as deleted, or FALSE if it exists.
   */
  public function isDeleted() {
    if ($this->type == VERSIONCONTROL_ITEM_FILE_DELETED
      || $this->type == VERSIONCONTROL_ITEM_DIRECTORY_DELETED) {
        return TRUE;
      }
    return FALSE;
  }

  /**
   * Retrieve this item revisions under the given limits.
   *
   * Only one direct source or successor of each item will be retrieved, which
   * means that you won't get parallel history logs. Version Control API does
   * not support multiple item source items anymore.
   *
   * @param $successor_item_limit
   *   The maximum amount of successor items to retrieve.
   * @param $source_item_limit
   *   The maximum amount of source items to retrieve.
   *
   * @return
   *   An array containing the list of items which are the history of this
   *   object, including also this object. Each element has its (file-level)
   *   item revision as key as value.
   *
   *   The array is sorted in reverse (e.g., chronological) order, so the newest
   *   revision(think newest as closer to the tip) comes first.
   *
   *   NULL is returned if the given item is not under version control(not in
   *   database yet), or was not under version control at the time of the given
   *   revision, or if no history could be retrieved for any other reason.
   */
  public function getHistory($successor_item_limit = NULL, $source_item_limit = NULL) {
    // Items without revision have no history, don't even try to fetch it.
    if (empty($this->revision)) {
      return NULL;
    }
    // If we don't yet know the item_revision_id (required for db
    // queries), try to retrieve it. If we don't find it, we can't go on
    // with this function.
    if (!$this->fetchItemRevisionId()) {
      return NULL;
    }

    // Make sure we don't run into infinite loops when passed bad
    // arguments.
    if (is_numeric($successor_item_limit) && $successor_item_limit < 0) {
      $successor_item_limit = 0;
    }
    if (is_numeric($source_item_limit) && $source_item_limit < 0) {
      $source_item_limit = 0;
    }

    $history_successor_items = $this->getSuccessorItems($successor_item_limit);
    // We want the recent revisions first, so reverse the successor array.
    $history_successor_items = array_reverse($history_successor_items, TRUE);

    $history_source_items = $this->getSourceItems($source_item_limit);

    return $history_successor_items + array($this->revision => $this) + $history_source_items;
  }

  /**
   * Find (recursively) all source items within the source item limit.
   *
   * @param $source_item_limit
   *   The maximum amount of source items to retrieve.
   *
   * @return
   *   An array containing the list of items which precedes this object in the
   *   history. Each element has its (file-level) item revision as key as value.
   */
  public function getSourceItems($source_item_limit = NULL) {
    // Make sure we don't run into infinite loops when passed bad
    // arguments.
    if (is_numeric($source_item_limit) && $source_item_limit < 0) {
      $source_item_limit = 0;
    }

    $history_source_items = array();

    if (!isset($source_item_limit) || ($source_item_limit > 0)) {
      if ($source_item = $this->getSourceItem()) {
        // This item parent items.
        $history_source_items[$source_item->revision] = $source_item;
        if (isset($source_item_limit)) {
          --$source_item_limit;
        }
        // More family.
        $more_parents = $source_item->getSourceItems($source_item_limit);
        $history_source_items = array_merge($history_source_items, $more_parents);
      }
      // Else no more source items to retrieve.
    }

    return $history_source_items;
  }

  /**
   * Find (recursively) all children items within the successor item limit.
   *
   * @param $successor_item_limit
   *   The maximum amount of successor items to retrieve.
   *
   * @return
   *   An array containing the list of items which are newest revisions of this
   *   object in the history. Each element has its (file-level) item revision
   *   as key as value.
   */
  public function getSuccessorItems($successor_item_limit = NULL) {
    // Make sure we don't run into infinite loops when passed bad
    // arguments.
    if (is_numeric($successor_item_limit) && $successor_item_limit < 0) {
      $successor_item_limit = 0;
    }

    $history_successor_items = array();

    if (!isset($successor_item_limit) || ($successor_item_limit > 0)) {
      if ($successor_item = $this->getSuccessorItem()) {
        // This item successor items.
        $history_successor_items[$successor_item->revision] = $successor_item;
        if (isset($successor_item_limit)) {
          --$successor_item_limit;
        }
        // More family.
        $more_children = $successor_item->getSuccessorItems($successor_item_limit);
        $history_successor_items = array_merge($history_successor_items, $more_children);
      }
      // Else no more successor items to retrieve.
    }

    return $history_successor_items;
  }

  /**
   * Make sure that the 'item_revision_id' database identifier is among
   * an item's properties, and if it's not then try to add it.
   *
   * @return
   *   TRUE if the 'item_revision_id' exists after calling this
   *   function, FALSE if not.
   */
  public function fetchItemRevisionId() {
    if (!empty($this->item_revision_id)) {
      return TRUE;
    }
    $id = db_result(db_query(
      "SELECT item_revision_id FROM {versioncontrol_item_revisions}
    WHERE repo_id = %d AND path = '%s' AND revision = '%s'",
    $this->repository->repo_id, $this->path, $this->revision
  ));
    if (empty($id)) {
      return FALSE;
    }
    $this->item_revision_id = $id;
    return TRUE;
  }

  /**
   * Check if the @p $path_regexp applies to the path of the given @p
   * $item.
   *
   * This function works just like preg_match(), with the single
   * difference that it also accepts a trailing slash for item paths if
   * the item is a directory.
   *
   * @return
   *   The number of times @p $path_regexp matches. That will be either 0
   *   times (no match) or 1 time because preg_match() (which is what
   *   this function uses internally) will stop searching after the first
   *   match.
   *   FALSE will be returned if an error occurred.
   */
  public function pregMatch($path_regexp) {
    $path = $this->path;

    if ($this->isDirectory() && $path != '/') {
      $path .= '/';
    }
    return preg_match($path_regexp, $path);
  }

  /**
   * Print out a "Bad item received from VCS backend" warning to
   * watchdog.
   */
  protected function badItemWarning($message) {
    watchdog('special', "<p>Bad item received from VCS backend: !message</p>
      <pre>Item object: !item\n</pre>", array(
        '!message' => $message,
        '!item' => print_r($this, TRUE),
      ), WATCHDOG_ERROR
    );
  }

  /**
   * Retrieve the parent (directory) item of a given item.
   *
   * @param $parent_path
   *   NULL if the direct parent of the given item should be retrieved,
   *   or a parent path that is further up the directory tree.
   *
   * @return
   *   The parent directory item at the same revision as the given item.
   *   If $parent_path is not set and the item is already the topmost one
   *   in the repository, the item is returned as is. It also stays the
   *   same if $parent_path is given and the same as the path of the
   *   given item. If the given directory path does not correspond to a
   *   parent item, NULL is returned.
   */
  public function getParentItem($parent_path = NULL) {
    if (!isset($parent_path)) {
      $path = dirname($this->path);
    }
    elseif ($this->path == $parent_path) {
      return $this;
    }
    elseif ($parent_path == '/' || strpos($this->path . '/', $parent_path . '/') !== FALSE) {
      $path = $parent_path;
    }
    else {
      return NULL;
    }

    $revision = '';
    if (in_array(VERSIONCONTROL_CAPABILITY_DIRECTORY_REVISIONS, $this->getBackend()->capabilities)) {
      $revision = $this->revision;
    }

    $build_data = array(
      'type' => VERSIONCONTROL_ITEM_DIRECTORY,
      'path' => $path,
      'revision' => $revision,
      'repository' => $this->repository,
    );
    $parent_item = $this->getBackend()->buildEntity('item', $build_data);

    return $parent_item;
  }

  /**
   *
   */
  public function getSourceItem() {
    if (!empty($this->sourceItem)) {
      if ($this->sourceItem instanceof VersioncontrolItem) {
        // Simple case - the item is loaded, so return it.
        return $this->sourceItem;
      }
      else {
        // Some invalid data got into $this->sourceItem - pop a warning.
        throw new Exception('VersioncontrolItem contains a non-VersioncontrolItem as its source item.', E_WARNING);
      }
    }
    elseif (!empty($this->source_item_revision_id)) {
      // Item isn't loaded, but should exist. Load it, save it, and return.
      return $this->sourceItem = $this->getBackend()->loadEntity('item', $this->source_item_revision_id);
    }
    else {
      return FALSE;
    }
  }

  public function getSuccessorItem() {
    return $this->getBackend()->loadEntity('item', array(), array('source_item_revision_id' => $this->item_revision_id));
  }


  public function setSourceItem(VersioncontrolItem $item) {
    $this->sourceItem = $item;
  }

  public function update($options = array()) {
    if (empty($this->item_revision_id)) {
      // This is supposed to be an existing item, but has no item_revision_id.
      throw new Exception('Attempted to update a Versioncontrol item which has not yet been inserted in the database.', E_ERROR);
    }

    // Append default options.
    $options += $this->defaultCrudOptions['update'];

    if (!empty($options['source item update'])) {
      $this->determineSourceItemRevisionID();
    }

    // Make sure repository id is set for drupal_write_record().
    if (empty($this->repo_id)) {
      $this->repo_id = $this->repository->repo_id;
    }
    drupal_write_record('versioncontrol_item_revisions', $this, 'item_revision_id');

    // Let the backend take action.
    $this->backendUpdate($options);

    // Everything's done, invoke the hook.
    module_invoke_all('versioncontrol_entity_item_update', $this);
    return $this;
  }

  public function insert($options = array()) {
    if (!empty($this->item_revision_id)) {
      // This is supposed to be a new item, but has an item_revision_id already.
      throw new Exception('Attempted to insert a Versioncontrol item which is already present in the database.', E_ERROR);
    }

    // Append default options.
    $options += $this->defaultCrudOptions['insert'];

    if (empty($this->source_item_revision_id)) {
      $this->determineSourceItemRevisionID();
    }

    // Make sure repository id is set for drupal_write_record().
    if (empty($this->repo_id)) {
      $this->repo_id = $this->repository->repo_id;
    }
    drupal_write_record('versioncontrol_item_revisions', $this);

    $this->backendInsert($options);

    // Everything's done, invoke the hook.
    module_invoke_all('versioncontrol_entity_item_insert', $this);
    return $this;
  }

  /**
   * Calculate the appropriate contents for $this->source_item_revision_id, if
   * any, based on the contents of $this->sourceItem.
   *
   * // FIXME this is colosally hacky right now. right now it just inserts if the data is available, there is ZERO discovery
   */
  protected function determineSourceItemRevisionID() {
    if ($this->sourceItem instanceof VersioncontrolItem) {
      if (!isset($this->sourceItem->item_revision_id)) {
        $this->sourceItem->insert();
      }
      $this->source_item_revision_id = $this->sourceItem->item_revision_id;
    }
  }

  public function delete($options = array()) {
    // Append default options.
    $options += $this->defaultCrudOptions['delete'];

    db_delete('versioncontrol_item_revisions')
      ->condition('item_revision_id', $this->item_revision_id)
      ->execute();

    $this->backendDelete($options);

    module_invoke_all('versioncontrol_entity_item_delete', $this);
  }

  /**
   * Get the user-visible version of an item's revision identifier, as
   * plaintext.
   * By default, this function simply returns $item['revision'].
   *
   * Version control backends can, however, choose to implement their own
   * version of this function, which for example makes it possible to cut
   * the SHA-1 hash in distributed version control systems down to a
   * readable length.
   *
   * @param $format
   *   Either 'full' for the original version, or 'short' for a more
   *   compact form.
   *   If the revision identifier doesn't need to be shortened, the
   *   results can be the same for both versions.
   */
  public function formatRevisionIdentifier($format = 'full') {
    return $this->getBackend()->formatRevisionIdentifier($this->revision, $format);
  }
}
