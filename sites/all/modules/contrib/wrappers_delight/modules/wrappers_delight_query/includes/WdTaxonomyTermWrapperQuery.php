<?php
/**
 * @file
 * class WdTaxonomyTermWrapperQuery
 */

class WdTaxonomyTermWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdTaxonomyTermWrapper
   */
  public function current() {
    return parent::current();
  }
}

class WdTaxonomyTermWrapperQuery extends WdWrapperQuery {

  /**
   * Construct a WdTaxonomyTermWrapperQuery
   */
  public function __construct() {
    parent::__construct('taxonomy_term');
  }

  /**
   * Construct a WdTaxonomyTermWrapperQuery
   *
   * @return WdTaxonomyTermWrapperQuery
   */
  public static function find() {
    return new self();
  }

  /**
   * @return WdTaxonomyTermWrapperQueryResults
   */
  public function execute() {
    return new WdTaxonomyTermWrapperQueryResults($this->entityType, $this->query->execute());
  }

  /**
   * Query by tid
   *
   * @param int $tid
   * @param string $operator
   *
   * @return $this
   */
  public function byTid($tid, $operator = NULL) {
    return parent::byId($tid, $operator);
  }

  /**
   * Order by tid
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByTid($direction = 'ASC') {
    return $this->orderByProperty('tid.value', $direction);
  }

  /**
   * Query by name
   *
   * @param string $name
   * @param string $operator
   *
   * @return $this
   */
  public function byName($name, $operator = NULL) {
    return $this->byPropertyConditions(array('name' => array($name, $operator)));
  }

  /**
   * Order by name
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByName($direction = 'ASC') {
    return $this->orderByProperty('name', $direction);
  }

  /**
   * Query by description
   *
   * @param string $description
   * @param string $operator
   *
   * @return $this
   */
  public function byDescription($description, $operator = NULL) {
    return $this->byPropertyConditions(array('description' => array($description, $operator)));
  }

  /**
   * Order by description
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByDescription($direction = 'ASC') {
    return $this->orderByProperty('description', $direction);
  }

  /**
   * Query by weight
   *
   * @param int $weight
   * @param string $operator
   *
   * @return $this
   */
  public function byWeight($weight, $operator = NULL) {
    return $this->byPropertyConditions(array('weight' => array($weight, $operator)));
  }

  /**
   * Order by weight
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByWeight($direction = 'ASC') {
    return $this->orderByProperty('weight', $direction);
  }

  /**
   * Query by vid
   *
   * @param int|object|WdTaxonomyVocabularyWrapper $vid
   * @param string $operator
   *
   * @return $this
   */
  public function byVocabulary($vid, $operator = NULL) {
    if ($vid instanceof WdEntityWrapper) {
      $id = $vid->getId();
    }
    elseif (is_object($vid)) {
      $wrapper = new WdTaxonomyVocabularyWrapper($vid);
      $id = $wrapper->getId();
    }
    else {
      $id = $vid;
    }
    return $this->byPropertyConditions(array('vid' => array($id, $operator)));
  }

  /**
   * Order by vid
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByVocabulary($direction = 'ASC') {
    return $this->orderByProperty('vid', $direction);
  }

}
