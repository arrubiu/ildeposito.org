<?php

class VersioncontrolGitItemController extends VersioncontrolItemController {

  /**
   * Extend the base query with the git backend's additional data in
   * {versioncontrol_git_operations}.
   *
   * @return SelectQuery
   */
  protected function buildQueryBase($ids, $conditions) {
    $query = parent::buildQueryBase($ids, $conditions);
    $alias = $query->leftJoin('versioncontrol_git_item_revisions', 'vcgir', 'base.item_revision_id = vcgir.item_revision_id');
    $query->fields($alias, drupal_schema_fields_sql('versioncontrol_git_item_revisions'));
    return $query;
  }
}
