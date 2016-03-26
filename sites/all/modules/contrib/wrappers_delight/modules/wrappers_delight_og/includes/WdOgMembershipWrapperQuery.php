<?php

/**
 * @file
 * WdOgMembershipWrapperQuery
 */
class WdOgMembershipWrapperQuery extends WdWrapperQuery {

  /**
   * Construct a WdOgMembershipWrapperQuery
   */
  public function __construct() {
    parent::__construct('og_membership');
  }

  /**
   * Construct a WdOgMembershipWrapperQuery
   *
   * @return WdOgMembershipWrapperQuery
   */
  public static function find() {
    return new self();
  }

  /**
   * Query by the membership ID.
   *
   * @param int $id
   * @param string $operator
   *
   * @return $this
   */
  public function byId($id, $operator = NULL) {
    return parent::byId($id, $operator);
  }

  /**
   * Query by the group.
   *
   * @param int $gid
   * @param string $operator
   *
   * @return $this
   */
  public function byGid($gid, $operator = NULL) {
    return $this->byPropertyConditions(array('gid' => array($gid, $operator)));
  }

  /**
   * Query by the group type.
   *
   * @param string $group_type
   * @param string $operator
   *
   * @return $this
   */
  public function byGroupType($group_type, $operator = NULL) {
    return $this->byPropertyConditions(array('group_type' => array($group_type, $operator)));
  }

  /**
   * Query by the entity type.
   *
   * @param string $entity_type
   * @param string $operator
   *
   * @return $this
   */
  public function byEntityType($entity_type, $operator = NULL) {
    return $this->byPropertyConditions(array('entity_type' => array($entity_type, $operator)));
  }

  /**
   * Query by the membership entity.
   *
   * @param int $etid
   * @param string $operator
   *
   * @return $this
   */
  public function byEntityId($etid, $operator = NULL) {
    return $this->byPropertyConditions(array('etid' => array($etid, $operator)));
  }

  /**
   * Query by the membership status.
   *
   * @param int $state
   * @param string $operator
   *
   * @return $this
   */
  public function byState($state, $operator = NULL) {
    return $this->byPropertyConditions(array('state' => array($state, $operator)));
  }

  /**
   * Query by the field name.
   *
   * @param string $field_name
   * @param string $operator
   *
   * @return $this
   */
  public function byFieldName($field_name, $operator = NULL) {
    return $this->byPropertyConditions(array('field_name' => array($field_name, $operator)));
  }

  /**
   * @return WdOgMembershipWrapperQueryResults
   */
  public function execute() {
    return new WdOgMembershipWrapperQueryResults($this->entityType, $this->query->execute());
  }

  /**
   * Order by entity id
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByEtid($direction = 'ASC') {
    return $this->orderByProperty('etid', $direction);
  }

  /**
   * Order by entity_type
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByEntityType($direction = 'ASC') {
    return $this->orderByProperty('entity_type', $direction);
  }

  /**
   * Order by field name
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByFieldName($direction = 'ASC') {
    return $this->orderByProperty('field_name', $direction);
  }

  /**
   * Order by GID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByGid($direction = 'ASC') {
    return $this->orderByProperty('gid', $direction);
  }

  /**
   * Order by group type
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByGroupType($direction = 'ASC') {
    return $this->orderByProperty('group_type', $direction);
  }

  /**
   * Order by state
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByState($direction = 'ASC') {
    return $this->orderByProperty('state', $direction);
  }

}

class WdOgMembershipWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdOgMembershipWrapper
   */
  public function current() {
    return parent::current();
  }
}