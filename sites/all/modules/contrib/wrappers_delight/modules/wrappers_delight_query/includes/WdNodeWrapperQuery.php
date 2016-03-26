<?php
/**
 * @file
 * WdNodeWrapperQuery class
 */


/**
 * Class WdNodeWrapperQuery
 */
class WdNodeWrapperQuery extends WdWrapperQuery {

  /**
   * Construct a WdNodeWrapperQuery
   */
  public function __construct() {
    parent::__construct('node');
  }

  /**
   * Construct a WdNodeWrapperQuery
   *
   * @return $this
   */
  public static function find() {
    return new self();
  }

  /**
   * Query by NID
   *
   * @param int $nid
   * @param string $operator
   *
   * @return $this
   */
  public function byNid($nid, $operator = NULL) {
    return parent::byId($nid, $operator);
  }

  /**
   * Query by title.
   *
   * @param string $title
   * @param string $operator
   *
   * @return $this
   */
  public function byTitle($title, $operator = NULL) {
    return $this->byPropertyConditions(array('title' => array($title, $operator)));
  }

  /**
   * Query by node type.
   *
   * @param string $type
   * @param string $operator
   *
   * @return $this
   */
  public function byType($type, $operator = NULL) {
    return parent::byBundle($type, $operator);
  }

  /**
   * Query by created time.
   *
   * @param int $time
   * @param string $operator
   *
   * @return $this
   */
  public function byCreatedTime($time, $operator = NULL) {
    return $this->byPropertyConditions(array('created' => array($time, $operator)));
  }

  /**
   * Query by updated time.
   *
   * @param int $time
   * @param string $operator
   *
   * @return $this
   */
  public function byChangedTime($time, $operator = NULL) {
    return $this->byPropertyConditions(array('changed' => array($time, $operator)));
  }

  /**
   * Query by the node promoted to front page state.
   *
   * @param int $promoted
   * @param string $operator
   *
   * @return $this
   */
  public function byPromoted($promoted, $operator = NULL) {
    return $this->byPropertyConditions(array('promote' => array($promoted, $operator)));
  }

  /**
   * Query by the node sticky state.
   *
   * @param int $sticky
   * @param string $operator
   *
   * @return $this
   */
  public function bySticky($sticky, $operator = NULL) {
    return $this->byPropertyConditions(array('sticky' => array($sticky, $operator)));
  }

  /**
   * Query by the node published status.
   *
   * @param int $status
   * @param string $operator
   *
   * @return WdNodeWrapperQuery
   */
  public function byPublished($status, $operator = NULL) {
    return $this->byPropertyConditions(array('status' => array($status, $operator)));
  }

  /**
   * Query by the node author UID.
   *
   * @param int $uid
   * @param string $operator
   *
   * @return $this
   */
  public function byAuthor($uid, $operator = NULL) {
    return $this->byPropertyConditions(array('uid' => array($uid, $operator)));
  }

  /**
   * Query by the revision VID.
   *
   * @param int $vid
   * @param string $operator
   *
   * @return $this
   */
  public function byRevision($vid, $operator = NULL) {
    return parent::byRevision($vid, $operator);
  }

  /**
   * @return WdNodeWrapperQueryResults
   */
  public function execute() {
    return new WdNodeWrapperQueryResults($this->entityType, $this->query->execute());
  }

  /**
   * Order by node NID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByNid($direction = 'ASC') {
    return parent::orderById($direction);
  }

  /**
   * Order by node VID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByRevision($direction = 'ASC') {
    return parent::orderByRevision($direction);
  }

  /**
   * Order by node type
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByType($direction = 'ASC') {
    return parent::orderByBundle($direction);
  }

  /**
   * Order by author UID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByAuthor($direction = 'ASC') {
    return $this->orderByProperty('uid', $direction);
  }

  /**
   * Order by node changed time
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByChangedTime($direction = 'ASC') {
    return $this->orderByProperty('changed', $direction);
  }

  /**
   * Order by node created time
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByCreatedTime($direction = 'ASC') {
    return $this->orderByProperty('created', $direction);
  }

  /**
   * Order by promoted to front page flag
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByPromoted($direction = 'ASC') {
    return $this->orderByProperty('promote', $direction);
  }

  /**
   * Order by published status
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByPublished($direction = 'ASC') {
    return $this->orderByProperty('status', $direction);
  }

  /**
   * Order by sticky flag
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderBySticky($direction = 'ASC') {
    return $this->orderByProperty('sticky', $direction);
  }

  /**
   * Order by title
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByTitle($direction = 'ASC') {
    return $this->orderByProperty('title', $direction);
  }

}

class WdNodeWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdNodeWrapper
   */
  public function current() {
    return parent::current();
  }
}