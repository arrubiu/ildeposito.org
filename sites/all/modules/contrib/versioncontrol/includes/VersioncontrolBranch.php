<?php
/**
 * @file
 * Repository Branch class.
 */

/**
 * Represents a repository branch.
 */
class VersioncontrolBranch extends VersioncontrolEntity {
  protected $_id = 'label_id';

  /**
   * The tag identifier (a simple integer), used for unique identification of
   * this tag in the database.
   *
   * @var int
   */
  public $label_id;

  /**
   * The tag name.
   *
   * @var string
   */
  public $name;

  /**
   * Indicates this is a branch; for db interaction only.
   *
   * @var int
   */
  public $type = VERSIONCONTROL_LABEL_BRANCH;

  protected $defaultCrudOptions = array(
    'update' => array('nested' => TRUE),
    'insert' => array('nested' => TRUE),
    'delete' => array('nested' => TRUE),
  );

  /**
   * Load commits from the database that are associated with this branch.
   *
   * @param array $ids
   * @param array $conditions
   * @param array $options
   */
  public function loadCommits($ids = array(), $conditions = array(), $options = array()) {
    $conditions['branches'] = array($this->label_id);
    return $this->getBackend()->loadEntities('operation', $ids, $conditions, $options);
  }

  /**
   * Update the record in the database.
   */
  public function update($options = array()) {
    if (empty($this->label_id)) {
      // This is supposed to be an existing branch, but has no label_id.
      throw new Exception('Attempted to update a Versioncontrol branch which has not yet been inserted in the database.', E_ERROR);
    }

    // Append default options.
    $options += $this->defaultCrudOptions['update'];

    // Make sure repository id is set for drupal_write_record().
    if (empty($this->repo_id)) {
      $this->repo_id = $this->repository->repo_id;
    }
    drupal_write_record('versioncontrol_labels', $this, 'label_id');

    // Let the backend take action.
    $this->backendUpdate($options);

    // Everything's done, invoke the hook.
    module_invoke_all('versioncontrol_entity_branch_update', $this);
    return $this;
  }

  /**
   * Insert the record in the database.
   */
  public function insert($options = array()) {
    if (!empty($this->label_id)) {
      // This is supposed to be a new branch, but has a label_id already.
      throw new Exception('Attempted to insert a Versioncontrol branch which is already present in the database.', E_ERROR);
    }

    // Append default options.
    $options += $this->defaultCrudOptions['insert'];

    // Make sure repository id is set for drupal_write_record().
    if (empty($this->repo_id)) {
      $this->repo_id = $this->repository->repo_id;
    }
    drupal_write_record('versioncontrol_labels', $this);

    $this->backendInsert($options);

    // Everything's done, invoke the hook.
    module_invoke_all('versioncontrol_entity_branch_insert', $this);
    return $this;
  }

  /**
   * Delete this branch from the database, along with all related data.
   */
  public function delete($options = array()) {
    // Append default options.
    $options += $this->defaultCrudOptions['delete'];

    if (!empty($options['nested'])) {
      $this->deleteRelatedCommits($options);
    }

    db_delete('versioncontrol_operation_labels')
      ->condition('label_id', $this->label_id)
      ->execute();

    db_delete('versioncontrol_labels')
      ->condition('label_id', $this->label_id)
      ->execute();

    $this->backendDelete($options);

    module_invoke_all('versioncontrol_entity_branch_delete', $this);
  }

  /**
   * Delete the commits related to this branch from the database.
   */
  protected function deleteRelatedCommits($options) {
    $operation_controller = $this->getBackend()->getController('operation');
    // Retrieve related commits.
    $label_commits = $operation_controller->getOperationLabels(array('label_id' => $this->label_id), array('idKey' => 'vc_op_id'));
    $label_commit_ids = array_keys($label_commits);
    // Calculate the commits to delete: Only delete the commit if this branch
    // is the commit's only associated label.
    $commit_ids_to_delete = array();
    if (count($label_commit_ids) > 0) {
      $commits_to_delete = $operation_controller->getOperationLabels(array('vc_op_id' => $label_commit_ids, 'sole_operation' => TRUE), array('idKey' => 'vc_op_id'));
      $commit_ids_to_delete = array_keys($commits_to_delete);
    }
    if (empty($commit_ids_to_delete)) {
      // Nothing to delete.
      return;
    }
    // Load and delete selected commits.
    $commits = $this->loadCommits($commit_ids_to_delete);
    foreach ($commits as $commit) {
      $commit->delete();
    }
  }
}
