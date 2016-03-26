<?php
/**
 * @file
 * Class WdEntityQueueSubqueueWrapperQuery
 */

class WdEntityQueueSubqueueWrapperQuery extends WdWrapperQuery {

  /**
   * Construct a WdEntityQueueSubqueueWrapperQuery
   */
  public function __construct() {
    parent::__construct('entityqueue_subqueue');
  }

  /**
   * Construct a WdEntityQueueSubqueueWrapperQuery
   *
   * @return WdEntityQueueSubqueueWrapperQuery
   */
  public static function find() {
    return new self();
  }

  /**
   * Query by the Subqueue ID.
   *
   * @param int $subqueue_id
   * @param string $operator
   *
   * @return $this
   */
  public function bySubqueueId($subqueue_id, $operator = NULL) {
    return parent::byId($subqueue_id);
  }

  /**
   * Query by the Subqueue owner.
   *
   * @param int $uid
   * @param string $operator
   *
   * @return $this
   */
  public function byOwner($uid, $operator = NULL) {
    return $this->byPropertyConditions(array('uid' => array($uid, $operator)));
  }

  /**
   * Query by the Subqueue queue.
   *
   * @param string $queue_name
   * @param string $operator
   *
   * @return $this
   */
  public function byQueue($queue_name, $operator = NULL) {
    return $this->byBundle($queue_name, $operator);
  }

  /**
   * Query by the Subqueue name.
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
   * Query by the Subqueue label.
   *
   * @param string $label
   * @param string $operator
   *
   * @return $this
   */
  public function byLabel($label, $operator = NULL) {
    return $this->byPropertyConditions(array('label' => array($label, $operator)));
  }


  /**
   * @return WdEntityQueueSubqueueWrapperQueryResults
   */
  public function execute() {
    return new WdEntityQueueSubqueueWrapperQueryResults($this->entityType, $this->query->execute());
  }

  /**
   * Order by Subqueue ID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderBySubuqueId($direction = 'ASC') {
    return parent::orderById($direction);
  }

  /**
   * Order by owner
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByOwner($direction = 'ASC') {
    return $this->orderByProperty('uid', $direction);
  }

  /**
   * Order by queue
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByQueue($direction = 'ASC') {
    return $this->orderByBundle($direction);
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
   * Order by label
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByLabel($direction = 'ASC') {
    return $this->orderByProperty('label', $direction);
  }

}

class WdEntityQueueSubqueueWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdEntityQueueSubqueueWrapper
   */
  public function current() {
    return parent::current();
  }
}