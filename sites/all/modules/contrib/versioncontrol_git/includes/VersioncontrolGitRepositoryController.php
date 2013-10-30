<?php

/**
 * @file
 *
 * Extends VersioncontrolRepositoryController with Git specific features.
 */

class VersioncontrolGitRepositoryController extends VersioncontrolRepositoryController {

  /**
   * Extends the base query with the git backend's additional data in
   * {versioncontrol_git_repositories}.
   *
   * @return SelectQuery
   */
  protected function buildQueryBase($ids, $conditions) {
    $query = parent::buildQueryBase($ids, $conditions);
    $alias = $query->leftJoin('versioncontrol_git_repositories', 'vcgr', 'base.repo_id = vcgr.repo_id');
    $query->fields($alias, drupal_schema_fields_sql('versioncontrol_git_repositories'));
    return $query;
  }
}
