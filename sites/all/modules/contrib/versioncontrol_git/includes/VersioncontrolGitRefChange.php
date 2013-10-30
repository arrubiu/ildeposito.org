<?php

/**
 * Represents a change to an individual ref made as part of a `git push`.
 *
 * The entire push event is represented using VersioncontrolGitEvent; classes in
 * this family represent the individual ref updates within that push.
 */
abstract class VersioncontrolGitRefChange {
  /**
   * The repository on which this event occurred.
   *
   * @var VersioncontrolGitRepository
   */
  protected $repository;

  /**
   * The event id of the associated VersioncontrolGitEvent.
   *
   * @var int
   */
  public $elid;

  /**
  * The name of the ref (branch or tag) that was updated.
  *
  * @var string
  */
  public $refname;

  /**
   * The identifier of the label, if one exists.
   *
   * Note that deleted branches and tags do not persist in our database records
   * but events do, so it is possible (and indeed likely) that events will
   * exist that have no corresponding ref. This should be indicated, so far as
   * it is possible, by storing -1 in this field.
   *
   * The field may also contain a 0, which is the default value, and indicates
   * that no attempt has been made to link the event to a branch or tag. This
   * should only be very temporary, as
   *
   * @var int
   */
  public $label_id;

  /**
   * The type of the reference:
   *    2 == branch
   *    3 == tag
   *
   * @var int
   */
  public $reftype;

  /**
   * The object to which this reference pointed before the push.
   *
   * @var string
   */
  public $old_sha1;

  /**
   * The object to which this reference pointed after the push.
   *
   * @var string
   */
  public $new_sha1;

 /**
  * Only valid for branches. Indicates whether or not the branch update
  * was a fast-forward.
  *
  * @var bool
  */
  public $ff = NULL;

  public function __construct($data) {
    foreach ($data as $key => $val) {
      $this->$key = $val;
    }
  }

  /**
   * Load (from the database) the VersioncontrolGitOperation object representing
   * the commit this ref pointed to after the push event.
   *
   * If the push event deleted the ref, this method returns null.
   *
   * @return VersioncontrolGitOperation|null
   */
  public function getNewCommit() {
    if (!$this->eventDeletedMe()) {
      return $this->repository->loadCommit($this->new_sha1);
    }
  }

  /**
  * Load (from the database) the VersioncontrolGitOperation object representing
  * the commit this ref pointed to before the push event.
  *
  * If the push event created the ref, this method returns null.
  *
  * @return VersioncontrolGitOperation|null
  */
  public function getOldCommit() {
    if (!$this->eventCreatedMe()) {
      return $this->repository->loadCommit($this->old_sha1);
    }
  }

  /**
   * Return the VersioncontrolGit label (branch or tag) object that the change
   * event represented by this object applies to.
   *
   * @return VersioncontrolGitBranch|VersioncontrolGitTag|null
   * 	 Returns a branch or tag object, or null if no object exists. The latter
   *   will occur if this object represents an old event attached to a branch
   *   or tag that has been subsequently deleted.
   */
  abstract public function getLabel();

  /**
   * Indicates whether the push event deleted this ref.
   *
   * @return boolean
   */
  public function eventDeletedMe() {
    return GIT_NULL_REV === $this->new_sha1;
  }

  /**
   * Indicates whether the push event created this ref.
   *
   * @return boolean
   */
  public function eventCreatedMe() {
    return GIT_NULL_REV === $this->old_sha1;
  }

  /**
   * Attempt to determine the label_id associated with this ref.
   *
   * The associated is recorded in $this->label_id, but is not automatically
   * written to the database.
   */
  abstract public function syncLabel();

  /**
   * Return an associative array containing data about the ref update.
   *
   * Really this is just a way to dump all the relevant information out for
   * easy use in insert/update queries.
   *
   * @return array
   */
  public function dumpProps() {
    $refl = new ReflectionObject($this);
    // Get all properties
    $props = $refl->getProperties(ReflectionProperty::IS_PRIVATE | ReflectionProperty::IS_PROTECTED | ReflectionProperty::IS_PUBLIC);

    $return = array();
    foreach ($props as $prop) {
      if (in_array($prop->name, array('repository'))) {
        continue;
      }
      $return[$prop->name] = (is_array($this->{$prop->name}) || is_object($this->{$prop->name}) ? serialize($this->{$prop->name}) : $this->{$prop->name});
    }
    return $return;
  }

  /**
   *
   * @return VersioncontrolRepository
   */
  public function getRepository() {
    if (empty($this->repository) || !($this->repository instanceof VersioncontrolRepository)) {
      return NULL;
    }
    return $this->repository;
  }
}
