<?php

/**
 * @file
 * WdOgMembershipWrapper
 */
class WdOgMembershipWrapper extends WdEntityWrapper {

  protected $entity_type = 'og_membership';

  /**
   * Create an OG Membership entity.
   *
   * @param array $values
   * @param string $language
   * @return WdOgMembershipWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $values += array('group_type' => 'node');
    $membership = og_group($values['group_type'], $values['gid'], $values, FALSE);
    return new WdOgMembershipWrapper($membership);
  }

  /**
   * Retrieves the membership ID.
   *
   * @return int
   */
  public function getId() {
    return $this->get('id');
  }

  /**
   * Retrieves the group.
   *
   * @return mixed
   */
  public function getGroup() {
    $base_class = $this->getBaseClassName($this->get('group_type'));
    if (class_exists($base_class)) {
      if ($base_class == 'WdEntityWrapper') {
        return new $base_class($this->get('group'), $this->get('group_type'));
      }
      return new $base_class($this->get('group'));
    }
    return $this->get('group');
  }

  /**
   * Retrieves the group type.
   *
   * @return string
   */
  public function getGroupType() {
    return $this->get('group_type');
  }

  /**
   * Retrieves the entity type.
   *
   * @return string.
   */
  public function getEntityType() {
    return $this->get('entity_type');
  }

  /**
   * Retrieves the membership entity.
   *
   * @return mixed
   */
  public function getEntity() {
    $base_class = $this->getBaseClassName($this->get('entity_type'));
    if (class_exists($base_class)) {
      if ($base_class == 'WdEntityWrapper') {
        return new $base_class($this->get('entity_type'), $this->get('entity'));
      }
      return new $base_class($this->get('entity'));
    }
    return $this->get('entity');
  }

  /**
   * Retrieves the membership status.
   *
   * @return int
   */
  public function getState() {
    return $this->get('state');
  }

  /**
   * Sets the membership state.
   *
   * @param int $state
   *
   * @return $this
   */
  public function setState($state) {
    $this->set('state', $state);
    return $this;
  }

  /**
   * Retrieves the field name.
   *
   * @return string
   */
  public function getFieldName() {
    return $this->get('field_name');
  }

}