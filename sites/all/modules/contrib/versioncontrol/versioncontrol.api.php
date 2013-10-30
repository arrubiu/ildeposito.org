<?php
/**
 * @file
 * Version Control API - An interface to version control systems whose
 * functionality is provided by pluggable back-end modules.
 *
 * This file contains module hooks for users of Version Control API, with API
 * documentation and a bit of example code.
 * Poins of interactions for VCS backends are not to be found in this file as
 * they are already documented in the fakevcs backend classes of the example
 * module versioncontrol_fakevcs.
 *
 * Copyright 2007, 2008, 2009 by Jakob Petsovits ("jpetso", http://drupal.org/user/56020)
 */

/**
 * Act just after a versioncontrol operation has been inserted.
 *
 * @param VersioncontrolOperation $operation
 *   The operation object.
 *
 * @ingroup Operations
 */
function hook_versioncontrol_entity_commit_insert(VersioncontrolOperation $operation) {
}

/**
 * Act just after a versioncontrol operation has been updated.
 *
 * @param VersioncontrolOperation $operation
 *   The operation object.
 *
 * @ingroup Operations
 */
function hook_versioncontrol_entity_commit_update(VersioncontrolOperation $operation) {
}

/**
 * Act just after a versioncontrol operation has been deleted.
 *
 * @param VersioncontrolOperation $operation
 *   The operation object.
 *
 * @ingroup Operations
 */
function hook_versioncontrol_entity_commit_delete(VersioncontrolOperation $operation) {
}

/**
 * Declare versioncontrol backends.
 */
function hook_versioncontrol_backends() {
  return array(
    // The array key is up to 8 characters long, and used as unique identifier
    // for this VCS, in functions, URLs and in the database.
    'fakevcs' => new VersioncontrolFakeBackend(),
  );
}

/**
 * Take action before a resync is performed.
 *
 * @param VersioncontrolRepository $versioncontrol_repository
 *   The versioncontrol repository about to be synced.
 * @param Boolean $bypass
 *   Whether to bypass loading and then calling the delete method for each
 *   entity that needs to be deleted before resyncing.  Almost always true.
 */
function hook_versioncontrol_repository_pre_resync(VersioncontrolRepository $versioncontrol_repository, $bypass) {
}

/**
 * Take action after a resync is performed.
 *
 * @param VersioncontrolRepository $versioncontrol_repository
 *   The versioncontrol repository about to be synced.
 * @param Boolean $bypass
 *   Whether to bypass loading and then calling the delete method for each
 *   entity that needs to be deleted before resyncing.  Almost always true.
 */
function versioncontrol_repository_post_resync($versioncontrol_repository, $bypass) {
}

/**
 * Respond to a repository resync a proper purge has been bypassed.
 *
 * When a resync of a repository occurs the exisiting history is generally
 * purged without loading and calling delete() on each item. If this step is
 * skipped (as it usually is for expediency) this hook is called to allow
 * other modules to run cleanup operations that would normally run when delete()
 * is invoked.
 *
 * @param VersioncontrolRepository $versioncontrol_repository
 *   The versioncontrol repository about to be synced.
 */
function hook_versioncontrol_repository_bypassing_purge($versioncontrol_repository) {
}


/**
 * Act just after a versioncontrol branch has been inserted.
 *
 * @param VersioncontrolBranch $operation
 *   The branch object.
 *
 * @ingroup Branches
 */
function hook_versioncontrol_entity_branch_insert(VersioncontrolBranch $branch) {
}

/**
 * Act just after a versioncontrol branch has been updated.
 *
 * @param VersioncontrolBranch $branch
 *   The branch object.
 *
 * @ingroup Branches
 */
function hook_versioncontrol_entity_branch_update(VersioncontrolBranch $branch) {
}

/**
 * Act just after a versioncontrol branch has been deleted.
 *
 * @param VersioncontrolBranch $branch
 *   The branch object.
 *
 * @ingroup Branches
 */
function hook_versioncontrol_entity_branch_delete(VersioncontrolBranch $branch) {
}

/**
 * Act just after a versioncontrol event has been inserted.
 *
 * @param VersioncontrolEvent $event
 *   The event object.
 *
 * @ingroup Events
 */
function hook_versioncontrol_entity_event_insert(VersioncontrolEvent $event) {
}

/**
 * Act just after a versioncontrol event has been updated.
 *
 * @param VersioncontrolEvent $event
 *   The event object.
 *
 * @ingroup Events
 */
function hook_versioncontrol_entity_event_update(VersioncontrolEvent $event) {
}

/**
 * Act just after a versioncontrol event has been deleted.
 *
 * @param VersioncontrolEvent $event
 *   The event object.
 *
 * @ingroup Events
 */
function hook_versioncontrol_entity_event_delete(VersioncontrolEvent $event) {
}

/**
 * Act just after the repository have made the syncronization.
 *
 * @param VersioncontrolRepository $repository
 *   The repository object.
 * @param VersioncontrolEvent $event
 *   The event object.
 *
 * @ingroup Events
 */
function hook_versioncontrol_code_arrival(VersioncontrolRepository $repository, VersioncontrolEvent $event) {
}

/**
 * Act just after a versioncontrol item has been inserted.
 *
 * @param VersioncontrolItem $item
 *   The item object.
 *
 * @ingroup Items
 */
function hook_versioncontrol_entity_item_insert(VersioncontrolItem $item) {
}

/**
 * Act just after a versioncontrol item has been updated.
 *
 * @param VersioncontrolItem $item
 *   The item object.
 *
 * @ingroup Items
 */
function hook_versioncontrol_entity_item_update(VersioncontrolItem $item) {
}

/**
 * Act just after a versioncontrol item has been deleted.
 *
 * @param VersioncontrolItem $item
 *   The item object.
 *
 * @ingroup Items
 */
function hook_versioncontrol_entity_item_delete(VersioncontrolItem $item) {
}

/**
 * Act just after a versioncontrol tag has been inserted.
 *
 * @param VersioncontrolTag $tag
 *   The tag object.
 *
 * @ingroup Tags
 */
function hook_versioncontrol_entity_tag_insert(VersioncontrolTag $tag) {
}

/**
 * Act just after a versioncontrol tag has been updated.
 *
 * @param VersioncontrolTag $tag
 *   The tag object.
 *
 * @ingroup Tags
 */
function hook_versioncontrol_entity_tag_update(VersioncontrolTag $tag) {
}

/**
 * Act just after a versioncontrol tag has been deleted.
 *
 * @param VersioncontrolTag $tag
 *   The tag object.
 *
 * @ingroup Tags
 */
function hook_versioncontrol_entity_tag_delete(VersioncontrolTag $tag) {
}

/**
 * Act just after a versioncontrol repository has been inserted.
 *
 * @param VersioncontrolRepository $repository
 *   The repository object.
 *
 * @ingroup Repositories
 * @ingroup Database change notification
 * @ingroup Target audience: All modules with repository specific settings
 */
function hook_versioncontrol_entity_repository_insert(VersioncontrolRepository $repository) {
  $ponies = $repository->data['mymodule']['ponies'];
  $query = db_insert('mymodule_ponies')->fields(array('repo_id', 'pony'));
  foreach ($ponies as $pony) {
    $query->values($pony);
  }
  $query->execute();
}

/**
 * Act just after a versioncontrol repository has been updated.
 *
 * @param VersioncontrolRepository $repository
 *   The repository object.
 *
 * @ingroup Repositories
 * @ingroup Database change notification
 * @ingroup Target audience: All modules with repository specific settings
 */
function hook_versioncontrol_entity_repository_update(VersioncontrolRepository $repository) {
  $ponies = $repository->data['mymodule']['ponies'];
  db_delete('mymodule_ponies')
    ->condition('repo_id', $repository->repo_id)
    ->execute();

  $query = db_insert('mymodule_ponies')->fields(array('repo_id', 'pony'));
  foreach ($ponies as $pony) {
    $query->values($pony);
  }
  $query->execute();
}

/**
 * Act just after a versioncontrol repository has been deleted.
 *
 * @param VersioncontrolRepository $repository
 *   The repository object.
 *
 * @ingroup Repositories
 * @ingroup Database change notification
 * @ingroup Target audience: All modules with repository specific settings
 */
function hook_versioncontrol_entity_repository_delete(VersioncontrolRepository $repository) {
  db_query("DELETE FROM {mymodule_ponies} WHERE repo_id = %d", $repository->repo_id);
}
