<?php
/**
 * @file
 * class WdTaxonomyVocabularyWrapperQuery
 */

class WdTaxonomyVocabularyWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdTaxonomyVocabularyWrapper
   */
  public function current() {
    return parent::current();
  }
}

class WdTaxonomyVocabularyWrapperQuery extends WdWrapperQuery {

  /**
   * Construct a WdTaxonomyVocabularyWrapperQuery
   */
  public function __construct() {
    parent::__construct('taxonomy_vocabulary');
  }

  /**
   * Construct a WdTaxonomyVocabularyWrapperQuery
   *
   * @return WdTaxonomyVocabularyWrapperQuery
   */
  public static function find() {
    return new self();
  }

  /**
   * @return WdTaxonomyVocabularyWrapperQueryResults
   */
  public function execute() {
    return new WdTaxonomyVocabularyWrapperQueryResults($this->entityType, $this->query->execute());
  }

  /**
   * Query by vid
   *
   * @param int $vid
   * @param string $operator
   *
   * @return $this
   */
  public function byVid($vid, $operator = NULL) {
    return parent::byId($vid, $operator);
  }

  /**
   * Order by vid
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByVid($direction = 'ASC') {
    return $this->orderByProperty('vid.value', $direction);
  }

  /**
   * Query by name
   *
   * @param mixed $name
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
   * Query by machine_name
   *
   * @param string $machine_name
   * @param string $operator
   *
   * @return $this
   */
  public function byMachineName($machine_name, $operator = NULL) {
    return $this->byPropertyConditions(array('machine_name' => array($machine_name, $operator)));
  }

  /**
   * Order by machine_name
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByMachineName($direction = 'ASC') {
    return $this->orderByProperty('machine_name', $direction);
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

}
