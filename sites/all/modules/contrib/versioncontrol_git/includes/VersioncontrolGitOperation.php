<?php

class VersioncontrolGitOperation extends VersioncontrolOperation {

  public $author_name = '';

  public $committer_name = '';

  public $parent_commit = '';

  public $merge = FALSE;

  protected function backendInsert($options) {
    db_insert('versioncontrol_git_operations')
      ->fields(array(
        'vc_op_id' => $this->vc_op_id,
        'author_name' => check_plain($this->author_name),
        'committer_name' => check_plain($this->committer_name),
        'parent_commit' => $this->parent_commit,
        'merge' => (int) $this->merge,
      ))
      ->execute();
  }

  protected function backendUpdate($options) {
    db_update('versioncontrol_git_operations')
      ->fields(array(
        'author_name' => $this->author_name,
        'committer_name' => check_plain($this->committer_name),
        'parent_commit' => check_plain($this->parent_commit),
        'merge' => (int) $this->merge,
      ))
      ->condition('vc_op_id', $this->vc_op_id)
      ->execute();
  }

  protected function backendDelete($options) {
    db_delete('versioncontrol_git_operations')
      ->condition('vc_op_id', $this->vc_op_id)
      ->execute();
  }
}
