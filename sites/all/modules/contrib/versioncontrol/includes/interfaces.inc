<?php
/**
 * @file
 *   Contains the interfaces that must be implemented for each VCS entity controller.
 */

interface VersioncontrolEntityInterface {
  public function build($args = array());
  public function save($options = array());

  public function getBackend();

  /**
   * Insert a new entity into the database, then invoke relevant hooks, if any.
   */
  public function insert($options = array());

  /**
   * Update an existing entity's record in the database, then invoke relevant
   * hooks, if any.
   */
  public function update($options = array());

  /**
   * Delete an entity from the database, along with any of its dependent data.
   */
  public function delete($options = array());
}

interface VersioncontrolUserMapperInterface {
  /**
   * Map the author of the passed VersioncontrolOperation object to a Drupal
   * uid, or FALSE if no uid mapping could be made.
   *
   * @param VersioncontrolOperation $commit
   *   The commit to be mapped.
   * @return mixed
   *   Either a uid (int), or FALSE if the mapping failed.
   */
  public function mapAuthor(VersioncontrolOperation $commit);

  /**
   * Map the committer of the passed VersioncontrolOperation object to a Drupal
   * uid, or FALSE if no uid mapping could be made.
   *
   * @param VersioncontrolOperation $commit
   *   The commit to be mapped.
   * @return mixed
   *   Either a uid (int), or FALSE if the mapping failed.
   */
  public function mapCommitter(VersioncontrolOperation $commit);
}

interface VersioncontrolAuthHandlerInterface {
  public function setRepository(VersioncontrolRepository $repository);

  /**
   * Determine whether the specified user has any access at all to the
   * repository.
   *
   * @param int $uid
   *   The uid of the Drupal user to be checked.
   *
   * @return bool
   *   Boolean indicating access approved (TRUE) or denied (FALSE)
   */
  public function authAccess($uid);

  /**
   * Determine whether the specified user has access to create new branches in
   * the repository.
   *
   * @param int $uid
   *   The uid of the Drupal user to be checked.
   * @param VersioncontrolBranch $branch
   *   The VersioncontrolBranch object representing the branch against which
   *   authorization checks should be made.
   *
   * @return bool
   *   Boolean indicating access approved (TRUE) or denied (FALSE)
   */
  public function authBranchCreate($uid, VersioncontrolBranch $branch);

  /**
   * Determine whether the specified user has access to delete the specified
   * branch in the repository.
   *
   * @param int $uid
   *   The uid of the Drupal user to be checked.
   * @param VersioncontrolBranch $branch
   *   The VersioncontrolBranch object representing the branch against which
   *   authorization checks should be made.
   *
   * @return bool
   *   Boolean indicating access approved (TRUE) or denied (FALSE)
   */
  public function authBranchDelete($uid, VersioncontrolBranch $branch);

  /**
   * Determine whether the specified user has access to write to the specified
   * branch in the repository.
   *
   * @param int $uid
   *   The uid of the Drupal user to be checked.
   * @param VersioncontrolBranch $branch
   *   The VersioncontrolBranch object representing the branch against which
   *   authorization checks should be made.
   *
   * @return bool
   *   Boolean indicating access approved (TRUE) or denied (FALSE)
   */
  public function authBranchUpdate($uid, VersioncontrolBranch $branch);

  /**
   * Determine whether the specified user has access to create new tags in the
   * repository.
   *
   * @param int $uid
   *   The uid of the Drupal user to be checked.
   * @param VersioncontrolTag $tag
   *   The VersioncontrolTag object representing the tag against which
   *   authorization checks should be made.
   *
   * @return bool
   *   Boolean indicating access approved (TRUE) or denied (FALSE)
   */
  public function authTagCreate($uid, VersioncontrolTag $tag);

  /**
   * Determine whether the specified user has access to delete the specified
   * tag in the repository.
   *
   * @param int $uid
   *   The uid of the Drupal user to be checked.
   * @param VersioncontrolTag $tag
   *   The VersioncontrolTag object representing the tag against which
   *   authorization checks should be made.
   *
   * @return bool
   *   Boolean indicating access approved (TRUE) or denied (FALSE)
   */
  public function authTagDelete($uid, VersioncontrolTag $tag);

  /**
   * Determine whether the specified user has access to update or modify
   * the specified tag in the repository.
   *
   * @param int $uid
   *   The uid of the Drupal user to be checked.
   * @param VersioncontrolTag $tag
   *   The VersioncontrolTag object representing the tag against which
   *   authorization checks should be made.
   *
   * @return bool
   *   Boolean indicating access approved (TRUE) or denied (FALSE)
   */
  public function authTagUpdate($uid, VersioncontrolTag $tag);

  /**
   * Retrieve any errors messages that have been enqueued during auth checking.
   *
   * Most of the authorization methods will enqueue messages to indicate the
   * reason for rejecting access. These messages may be useful for logging, or
   * to provide as feedback to the user.
   *
   * @return array
   *   Array of strings with the messages.
   */
  public function getErrorMessages();
}

interface VersioncontrolWebviewerUrlHandlerInterface {

  /**
   * Retrieve the URL of the repository viewer that displays the main
   * view of the repository.
   *
   * @return
   *   The repository view URL of the associated repository.
   */
  public function getRepositoryViewUrl();

  /**
   * Retrieve the URL of the repository viewer that displays the given commit
   * in the corresponding repository.
   *
   * @param $revision
   *   The revision on the commit operation whose view URL should be retrieved.
   *
   * @return
   *   The commit view URL corresponding to the given arguments.
   *   An empty string is returned if no commit view URL has been defined,
   *   or if the commit cannot be viewed for any reason.
   */
  public function getCommitViewUrl($revision);

  /**
   * Retrieve the URL of the repository viewer that displays the commit log
   * of the given item in the corresponding repository. If no such URL has been
   * specified by the user, the appropriate URL from the Commit Log module is
   * used as a fallback (if that module is enabled).
   *
   * @param $item
   *   The item whose log view URL should be retrieved.
   * @param $current_label
   *   The current label being shown, if applicable.
   *
   * @return
   *   The item log view URL corresponding to the given arguments.
   *   An empty string is returned if no item log view URL has been defined
   *   (and if not even Commit Log is enabled), or if the item cannot be viewed
   *   for any reason.
   */
  public function getItemLogViewUrl($item, $current_label = NULL);

  /**
   * Retrieve the URL of the repository viewer that displays the contents of the
   * given item in the corresponding repository.
   *
   * @param $item
   *   The item whose view URL should be retrieved.
   * @param $current_label
   *   The current label being shown, if applicable.
   *
   * @return
   *   The item view URL corresponding to the given arguments.
   *   An empty string is returned if no item view URL has been defined,
   *   or if the item cannot be viewed for any reason.
   */
  public function getItemViewUrl($item, $current_label = NULL);

  /**
   * Retrieve the URL of the repository viewer that displays the diff between
   * two given files in the corresponding repository.
   *
   * @param $file_item_new
   *   The new version of the file that should be diffed.
   * @param $file_item_old
   *   The old version of the file that should be diffed.
   * @param $current_label
   *   The current label being shown, if applicable.
   *
   * @return
   *   The diff URL corresponding to the given arguments.
   *   An empty string is returned if no diff URL has been defined,
   *   or if the two items cannot be diffed for any reason.
   */
  public function getDiffUrl($file_item_new, $file_item_old, $current_label = NULL);
}

/**
 * Interface defining the behavior for the classes used by views set plugins.
 *
 * Views sets are wrappers around groups of views that VCAPI uses to ease the
 * process of determining the most appropriate view (either generic or
 * backend-specific) to use in a given situation.  A views set plugin represents
 * something that would, under most circumstances, be a single view, but because
 * vcapi has its various backends, it needs the group. Plugins implementing this
 * interface are responsible for the logic of that multiplexing.
 */
interface VersioncontrolViewsSetInterface {
  /**
   * Derive the appropriate view for this set based on the data in a
   * VersioncontrolEntity object.
   *
   * @param VersioncontrolEntity $entity
   *   The entity from which a view should be derived.
   */
  public function getViewNameByEntity(VersioncontrolEntityInterface $entity);

  /**
   * Retrieve the appropriate view based on an explicitly known backend.
   *
   * @param mixed $backend
   *   Either a VersioncontrolBackend object, or the short name that uniquely
   *   refers to a backend.
   */
  public function getViewNameByBackend($backend);

  public function getSetName();

  public function getDefaultViews($vcs = '');

  public function getBaseView();

  /**
   * \o/
   */
  public function setSet($data);
}

interface VersioncontrolViewsGlobalSetInterface extends VersioncontrolViewsSetInterface {
  /**
   * Retrieve the appropriate view, typically based on some environment data.
   *
   * Global views sets are, under most circumstances, sensitive only to whether
   * or not VCAPI is operating in single backend mode (as defined by the
   * global $conf variable). Thus, they tend not to need an argument to derive
   * the appropriate view.
   */
  public function getViewName();
}


interface VersioncontrolRepositoryManagerWorkerInterface {

  /**
   * Set the repository object to be used by this plugin object.
   */
  public function setRepository(VersioncontrolRepository $repository);

  public function create();

  public function delete();

  /**
   * Save the repository to the database.
   *
   * Some operations may or may not necessitate updating vcapi's db record for
   * the attached repository. Including this as an atomic operation allows the
   * caller to dictate whether or not a save should take place.
   *
   */
  public function save();
}

/**
 * Interface defining the behavior of a versioncontrol history synchronizer
 * plugin.
 *
 * History synchronizers are responsible for getting raw backend repository data
 * into the database for direct use in the versioncontrol suite. This interface
 * defines methods for doing so.
 */
interface VersioncontrolRepositoryHistorySynchronizerInterface {
  /**
   * Indicates that VersioncontrolOperation's labels data member should include
   * mapping with branches.
   */
  const MAP_COMMIT_BRANCH_RELATIONS = 0x01;

  /**
   * Indicates that VersioncontrolOperation's labels data member should include
   * mapping with tags.
   */
  const MAP_COMMIT_TAG_RELATIONS = 0x02;

  /**
   * Syncronization error for locked repository.
   */
  const SYNC_ERROR_LOCKED = 0x001;

  /**
   * Set the repository object to be used by this plugin object.
   */
  public function setRepository(VersioncontrolRepository $repository);

  /**
   * Ensure the database's representation of the repository data is entirely
   * in sync with the repository.
   *
   * This is the most complex parsing option, as the log parser must essentially
   * "diff" the db against the repository data and synchronize only that which
   * is different, leaving that which already exists alone.
   *
   * @param array $options
   *   An array with options for the synchronization. Possible keys:
   *   - 'operation_labels_mapping': Bitmask describing how to map operation
   *     labels. Valid flags are:
   *     #- VersioncontrolRepositoryHistorySynchronizerInterface::MAP_COMMIT_BRANCH_RELATIONS
   *     #- VersioncontrolRepositoryHistorySynchronizerInterface::MAP_COMMIT_TAG_RELATIONS.
   *
   * @return
   *   TRUE on success, FALSE on failure.
   *
   * @throws VersioncontrolLockedRepositoryException
   *   The repository was locked. Probably another syncronization execution is
   *   in porgress.
   * @throws VersioncontrolSynchronizationException
   *   There was an unrecoverable problem during the syncronization execution.
   */
  public function syncFull($options);

  /**
   * Perform an initial parse on a repository, bringing the db from empty all
   * the way fully up to date.
   *
   * @param array $options
   *   An array with options for the synchronization. Possible keys:
   *   - 'operation_labels_mapping': Bitmask describing how to map operation
   *     labels. Valid flags are:
   *     #- VersioncontrolRepositoryHistorySynchronizerInterface::MAP_COMMIT_BRANCH_RELATIONS
   *     #- VersioncontrolRepositoryHistorySynchronizerInterface::MAP_COMMIT_TAG_RELATIONS.
   *
   * @return
   *   TRUE on success, FALSE on failure.
   *
   * @throws VersioncontrolLockedRepositoryException
   *   The repository was locked. Probably another syncronization execution is
   *   in porgress.
   * @throws VersioncontrolSynchronizationException
   *   There was an unrecoverable problem during the syncronization execution.
   */
  public function syncInitial($options);

  /**
   * Perform a targeted sync based on information about an incoming data event
   * as represented by a VersioncontrolEvent object.
   *
   * Unlike syncFull() and syncInitial() methods, implementations of this
   * method should make no attempt to ensure exact mirroring between the
   * repository and the database; it should assume the indicated incoming data
   * is the complete and exclusive set of new/missing repository data to be
   * added to the database.
   *
   * Implementations are, however, responsible for ensuring that the provided
   * VersioncontrolEvent object gets updated and re-saved after synchronization
   * is complete, as needed. A typical such requirement would be creating and
   * updating foreign key references in the event to data created during the
   * sync.
   *
   * @param VersioncontrolEvent $event
   *   The incoming data, encapsulated within a VersioncontrolEvent-descended
   *   object. The specific form of this data varies extensively from backend to
   *   backend, but VersioncontrolEvent abstracts across these differences.
   *
   * @param array $options
   *   An array with options for the synchronization. Possible keys:
   *   - 'operation_labels_mapping': Bitmask describing how to map operation
   *     labels. Valid flags are:
   *     #- VersioncontrolRepositoryHistorySynchronizerInterface::MAP_COMMIT_BRANCH_RELATIONS
   *     #- VersioncontrolRepositoryHistorySynchronizerInterface::MAP_COMMIT_TAG_RELATIONS.
   *
   * @return
   *   TRUE on success, FALSE on failure.
   *
   * @throws VersioncontrolLockedRepositoryException
   *   The repository was locked. Probably another syncronization execution is
   *   in porgress.
   * @throws VersioncontrolNeedsFullSynchronizationException
   *   The repository can not be synced only with the event information, and
   *   therefore a full syncronization is needed.
   * @throws VersioncontrolSynchronizationException
   *   There was an unrecoverable problem during the syncronization execution.
   */
  public function syncEvent(VersioncontrolEvent $event, $options);

  /**
   * Verify that the changeset represented by a VersioncontrolEvent object is
   * reconcilable with the repository and the database.
   *
   * @param VersioncontrolEvent $event
   *   The event against which the verification check should be performed.
   *
   * @return bool
   *   TRUE if the database and repository are consistent, FALSE if there are
   *   any irregularities.
   */
  public function verifyEvent(VersioncontrolEvent $event);

  /**
   * Verify that the data represented in the database is an accurate
   * representation of the current state of repository data.
   *
   * @return bool
   *   TRUE if the database is consistent with the repository, FALSE if there
   *   are any irregularities whatsoever.
   */
  public function verifyData();
}
