<?php
/**
 * @file
 * WdWrapperQuery class
 */

class WdWrapperQuery {

  /**
   * @var EntityFieldQuery
   */
  protected $query;

  /**
   * @var string
   */
  protected $entityType;

  /**
   * Create a new WdWrapperQuery
   *
   * @param $entity_type
   */
  public function __construct($entity_type) {
    $this->query = new EntityFieldQuery();
    $this->query->entityCondition('entity_type', $entity_type);
    $this->entityType = $entity_type;
  }

  /**
   * Create a new WdWrapperQuery.
   *
   * @param $entity_type
   *
   * @return WdWrapperQuery
   */
  public static function findEntity($entity_type) {
    return new self($entity_type);
  }

  /**
   * Add a mix of entity, property and field conditions.
   *
   * @param $conditions
   *
   * @return $this
   */
  public function by($conditions) {
    if (!empty($conditions['entity'])) {
      $this->byEntityConditions($conditions['entity']);
    }
    if (!empty($conditions['property'])) {
      $this->byPropertyConditions($conditions['property']);
    }
    if (!empty($conditions['field'])) {
      $this->byFieldConditions($conditions['field']);
    }
    return $this;
  }

  /**
   * Add entity conditions
   *
   * @param $conditions
   *
   * @return $this
   */
  public function byEntityConditions($conditions) {
    foreach ($conditions as $name => $condition) {
      if (is_array($condition)) {
        $this->query->entityCondition($name, $condition[0], $condition[1]);
      }
      else {
        $this->query->entityCondition($name, $condition);
      }
    }
    return $this;
  }

  /**
   * Add property conditions
   *
   * @param $conditions
   *
   * @return $this
   */
  public function byPropertyConditions($conditions) {
    foreach ($conditions as $name => $condition) {
      if (is_array($condition)) {
        $this->query->propertyCondition($name, $condition[0], $condition[1]);
      }
      else {
        $this->query->propertyCondition($name, $condition);
      }
    }
    return $this;
  }

  /**
   * Add field conditions
   *
   * @param $conditions
   *
   * @return $this
   */
  public function byFieldConditions($conditions) {
    foreach ($conditions as $name => $condition) {
      list($name, $column) = explode('.', $name);
      if (is_array($condition)) {
        $this->query->fieldCondition($name, $column, $condition[0], $condition[1]);
      }
      else {
        $this->query->propertyCondition($name, $column, $condition);
      }
    }
    return $this;
  }

  /**
   * Query by entity ID
   *
   * @param int $id
   * @param string $operator
   *
   * @return $this
   */
  public function byId($id, $operator = NULL) {
    return $this->byEntityConditions(array('entity_id' => array($id, $operator)));
  }

  /**
   * Query by the revision ID.
   *
   * @param int $revision_id
   * @param string $operator
   *
   * @return $this
   */
  public function byRevision($revision_id, $operator = NULL) {
    return $this->byEntityConditions(array('revision_id' => array($revision_id, $operator)));
  }

  /**
   * Query by the language.
   *
   * @param string $language
   * @param string $operator
   *
   * @return $this
   */
  public function byLanguage($language, $operator = NULL) {
    return $this->byPropertyConditions(array('language' => array($language, $operator)));
  }

  /**
   * Query by bundle type.
   *
   * @param string $type
   * @param string $operator
   *
   * @return $this
   */
  public function byBundle($type, $operator = NULL) {
    return $this->byEntityConditions(array('bundle' => array($type, $operator)));
  }

  /**
   * @return WdWrapperQueryResults
   */
  public function execute() {
    return new WdWrapperQueryResults($this->entityType, $this->query->execute());
  }

  /**
   * Returns the count query result.
   *
   * @return int
   */
  public function executeCount() {
    $count_query = $this->query->count();
    return $count_query->execute();
  }

  /**
   * Set range for query
   *
   * @param int $start
   * @param int $length
   *
   * @return $this
   */
  public function range($start = NULL, $length = NULL) {
    $this->query->range($start, $length);
    return $this;
  }

  /**
   * Order by entity key field
   *
   * @param $name
   * @param string $direction
   *
   * @return $this
   */
  public function orderByEntity($name, $direction = 'ASC') {
    $this->query->entityOrderBy($name, $direction);
    return $this;
  }

  /**
   * Order by entity property
   *
   * @param $name
   * @param string $direction
   *
   * @return $this
   */
  public function orderByProperty($name, $direction = 'ASC') {
    $this->query->propertyOrderBy($name, $direction);
    return $this;
  }

  /**
   * Order by entity field
   *
   * @param $name
   * @param string $direction
   *
   * @return $this
   */
  public function orderByField($name, $direction = 'ASC') {
    list($name, $column) = explode('.', $name);
    $this->query->fieldOrderBy($name, $column, $direction);
    return $this;
  }

  /**
   * Order by entity ID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderById($direction = 'ASC') {
    return $this->orderByEntity('entity_id', $direction);
  }

  /**
   * Order by the revision ID.
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByRevision($direction = 'ASC') {
    return $this->orderByEntity('revision_id', $direction);
  }

  /**
   * Order by the language.
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByLanguage($direction = 'ASC') {
    return $this->orderByProperty('language', $direction);
  }

  /**
   * Order by bundle type.
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByBundle($direction = 'ASC') {
    return $this->orderByEntity('bundle', $direction);
  }

}