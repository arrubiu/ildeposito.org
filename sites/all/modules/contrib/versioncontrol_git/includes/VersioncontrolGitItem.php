<?php

class VersioncontrolGitItem extends VersioncontrolItem {

  public $blob_hash;

  protected function backendInsert($options) {
    if (empty($this->blob_hash)) {
      // blob hash is empty at deleting a file
      return;
    }
    db_insert('versioncontrol_git_item_revisions')
      ->fields(array(
        'item_revision_id' => $this->item_revision_id,
        'blob_hash' => $this->blob_hash,
      ))
      ->execute();
  }

  protected function backendUpdate($options) {
    if (empty($this->blob_hash)) {
      // blob hash is empty at deleting a file
      db_delete('versioncontrol_git_item_revisions')
        ->condition('item_revision_id', $this->item_revision_id)
        ->execute();
      return;
    }
    db_update('versioncontrol_git_item_revisions')
      ->fields(array(
        'blob_hash' => $this->blob_hash,
      ))
      ->condition('item_revision_id', $this->item_revision_id)
      ->execute();
  }

  protected function backendDelete($options) {
    db_delete('versioncontrol_git_item_revisions')
      ->condition('item_revision_id', $this->item_revision_id)
      ->execute();
  }

  public function determineSourceItemRevisionID() {
    if (!empty($this->sourceItem->item_revision_id)) {
      return;
    }
    if (!empty($this->source_item_revision_id)) {
      $this->sourceItem = $this->backend->loadEntity('item', $this->source_item_revision_id, array(), array('may cache' => FALSE));
      return;
    }
    if ($this->sourceItem instanceof VersioncontrolItem) {
      // do not insert a duplicate item revision
      $db_item = $this->backend->loadEntity('item', array(), array('revision' => $this->sourceItem->revision, 'path' => $this->sourceItem->path), array('may cache' => FALSE));
      if (is_subclass_of($db_item, 'VersioncontrolItem')) {
        $this->sourceItem = $db_item;
      }
      else {
        $this->sourceItem->insert();
      }
      $this->source_item_revision_id = $this->sourceItem->item_revision_id;
      return;
    }
  }

}
