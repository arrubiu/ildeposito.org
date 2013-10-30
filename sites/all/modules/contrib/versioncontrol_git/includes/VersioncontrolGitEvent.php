<?php
/**
 * Entity class representing a push event that occurred in a tracked
 * Git repository.
 *
 * Is Traversable - if you want to get at all the underlying ref changes
 * in this event, just foreach() the object.
 */
class VersioncontrolGitEvent extends VersioncontrolEvent implements IteratorAggregate {

  /**
   * An array of the refs that were updated by this event, each
   * represented as a VersioncontrolGitRefChange object.
   *
   * @var array
   */
  public $refs = array();

  /**
   * Populate the Git event object with all its data.
   *
   * @param $args
   *   An array of data provided from a post-receive hook.
   */
  public function build($args = array()) {
    // Don't build twice.
    if ($this->built === TRUE) {
      return;
    }

    foreach ($args as $prop => $value) {
      $this->$prop = $value;
    }

    $refs = array();
    foreach ($this->refs as $ref_data) {
      $ref_data['repository'] = $this->getRepository();

      if ($ref_data['reftype'] == VERSIONCONTROL_GIT_REFTYPE_BRANCH) {
        $refs[] = new VersioncontrolGitBranchChange($ref_data);
      }
      else {
        // TODO need to accommodate other ref namespaces, such as notes
        $refs[] = new VersioncontrolGitTagChange($ref_data);
      }
    }

    $this->refs = $refs;

    $this->built = TRUE;
  }

  public function getLabelChanges() {
    return $this->refs;
  }

  protected function backendInsert($options = array()) {
    $this->fillExtendedTable();
  }

  protected function backendUpdate($options = array()) {
    $this->cleanExtendedTable();
    $this->fillExtendedTable();
  }

  protected function backendDelete($options = array()) {
    $this->cleanExtendedTable();
  }

  protected function cleanExtendedTable() {
    db_delete('versioncontrol_git_event_data')
      ->condition('elid', $this->elid)
      ->execute();
  }

  protected function fillExtendedTable() {
    $fields = array('elid', 'refname', 'label_id', 'reftype', 'old_sha1', 'new_sha1', 'ff');
    $query = db_insert('versioncontrol_git_event_data')->fields($fields);

    foreach ($this->refs as $ref) {
      $ref->elid = $this->elid;
      $query->values($ref->dumpProps());
    }

    $query->execute();
  }

  public function getIterator() {
    // TODO ensure the array is passed by reference. Since the contents are
    // objects, they're automagically taken care of, but still.
    return new ArrayIterator($this->refs);
  }

}
