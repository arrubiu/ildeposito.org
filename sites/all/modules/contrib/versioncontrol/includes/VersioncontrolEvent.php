<?php
/**
 * @file
 * Event class
 */

/**
 * Stuff that happened in a repository at a specific time
 */
abstract class VersioncontrolEvent extends VersioncontrolEntity implements Serializable {
  protected $_id = 'elid';
  /**
   * db identifier
   *
   * The Drupal-specific operation identifier (a simple integer)
   * which is unique among all operations (commits, branch ops, tag ops)
   * in all repositories.
   *
   * @var int
   */
  public $elid;

  /**
   * The time when the event happened
   * Unix timestamp.
   *
   * @var timestamp
   */
  public $timestamp;

  /**
   * The Drupal user id of the event author, or 0 if no Drupal user
   * could be associated to the author.
   *
   * @var int
   */
  public $uid = 0;

  /**
   * The database id of the repository with which this event is associated.
   * @var int
   */
  public $repo_id;

  /**
   * Insert the record in the database.
   */
  public function insert($options = array()) {
    if (!empty($this->elid)) {
      throw new Exception('Attempted to insert a Versioncontrol event which is already present in the database.', E_ERROR);
    }

    // Append default options.
    $options += $this->defaultCrudOptions['insert'];

    if (empty($this->repo_id)) {
      $this->repo_id = $this->getRepository()->repo_id;
    }
    drupal_write_record('versioncontrol_event_log', $this);

    $this->backendInsert($options);

    // Everything's done, invoke the hook.
    module_invoke_all('versioncontrol_entity_event_insert', $this);
    return $this;
  }

  /**
   * Update the record in the database.
   */
  public function update($options = array()) {
    if (empty($this->elid)) {
      throw new Exception('Attempted to update a Versioncontrol event which has not yet been inserted in the database.', E_ERROR);
    }

    // Append default options.
    $options += $this->defaultCrudOptions['update'];

    if (empty($this->repo_id)) {
      $this->repo_id = $this->getRepository()->repo_id;
    }
    drupal_write_record('versioncontrol_event_log', $this, 'elid');

    $this->backendUpdate($options);

    // Everything's done, invoke the hook.
    module_invoke_all('versioncontrol_entity_event_update', $this);
    return $this;
  }

  /**
   * Delete the record in the database.
   */
  public function delete($options = array()) {
    // Append default options.
    $options += $this->defaultCrudOptions['delete'];

    db_delete('versioncontrol_event_log')
      ->condition('elid', $this->elid)
      ->execute();

    $this->backendDelete($options);

    module_invoke_all('versioncontrol_entity_event_delete', $this);
  }

  /**
   * @todo generalize for VersioncontrolEntity
   *
   * @see Serializable::serialize().
   */
  public function serialize() {
    $refl = new ReflectionObject($this);
    // Get all properties, except static ones.
    $props = $refl->getProperties(ReflectionProperty::IS_PRIVATE | ReflectionProperty::IS_PROTECTED | ReflectionProperty::IS_PUBLIC );

    $ser = array();
    foreach ($props as $prop) {
      // Avoid repository and backend.
      if (in_array($prop->name, array('backend', 'repository'))) {
        continue;
      }
      $ser[$prop->name] = $this->{$prop->name};
    }
    // Make sure ids are set.
    $ser['vcs'] = $this->getRepository()->vcs;
    $ser['repo_id'] = $this->getRepository()->repo_id;
    return serialize($ser);
  }

  /**
   * @see Serializable::unserialize().
   */
  public function unserialize($serialized) {
    foreach (unserialize($serialized) as $prop => $val) {
      $this->$prop = $val;
    }
    // And stripped out data members.
    $this->backend = versioncontrol_get_backends($this->vcs);
    unset($this->vcs);
    $this->repository = $this->backend->loadEntity('repo', $this->repo_id);
  }
}
