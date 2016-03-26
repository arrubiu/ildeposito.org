<?php
/**
 * @file
 * Class WdMessageWrapperQuery
 */

class WdMessageWrapperQuery extends WdWrapperQuery {

  /**
   * Construct a WdMessageWrapperQuery
   */
  public function __construct() {
    parent::__construct('message');
  }

  /**
   * Construct a WdMessageWrapperQuery
   *
   * @return WdMessageWrapperQuery
   */
  public static function find() {
    return new self();
  }

  /**
   * Query by the Message MID.
   *
   * @param int $mid
   * @param string $operator
   *
   * @return $this
   */
  public function byMid($mid, $operator = NULL) {
    return parent::byId($mid);
  }

  /**
   * Query by the Message owner.
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
   * Query by the Message timestamp.
   *
   * @param int $time
   * @param string $operator
   *
   * @return $this
   */
  public function byTimestamp($time, $operator = NULL) {
    return $this->byPropertyConditions(array('timestamp' => array($time, $operator)));
  }

  /**
   * @return WdMessageWrapperQueryResults
   */
  public function execute() {
    return new WdMessageWrapperQueryResults($this->entityType, $this->query->execute());
  }

  /**
   * Order by message ID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByMid($direction = 'ASC') {
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
   * Order by timestamp
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByTimestamp($direction = 'ASC') {
    return $this->orderByProperty('timestamp', $direction);
  }

}

class WdMessageWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdMessageWrapper
   */
  public function current() {
    return parent::current();
  }
}