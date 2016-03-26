<?php
/**
 * @file
 * Class WdUserWrapperQuery
 */

class WdUserWrapperQuery extends WdWrapperQuery {


  /**
   * Construct a WdUserWrapperQuery
   */
  public function __construct() {
    parent::__construct('user');
  }

  /**
   * Construct a WdUserWrapperQuery
   *
   * @return WdUserWrapperQuery
   */
  public static function find() {
    return new self();
  }

  /**
   * Query by the user UID.
   *
   * @param int $uid
   * @param string $operator
   *
   * @return $this
   */
  public function byUid($uid, $operator = NULL) {
    return parent::byId($uid, $operator);
  }

  /**
   * Query by the user name.
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
   * Query by the user email address.
   *
   * @param string $mail
   * @param string $operator
   *
   * @return $this
   */
  public function byMail($mail, $operator = NULL) {
    return $this->byPropertyConditions(array('mail' => array($mail, $operator)));
  }

  /**
   * Query by the user created time.
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
   * Query by the user last login time.
   *
   * @param int $time
   * @param string $operator
   *
   * @return $this
   */
  public function byLastLogin($time, $operator = NULL) {
    return $this->byPropertyConditions(array('login' => array($time, $operator)));
  }

  /**
   * Query by the user last access time.
   *
   * @param int $time
   * @param string $operator
   *
   * @return $this
   */
  public function byLastAccess($time, $operator = NULL) {
    return $this->byPropertyConditions(array('access' => array($time, $operator)));
  }

  /**
   * Query by the user status
   *
   * @param int $status
   * @param string $operator
   *
   * @return $this
   */
  public function byStatus($status, $operator = NULL) {
    return $this->byPropertyConditions(array('status' => array($status, $operator)));
  }

  /**
   * Query by the user picture.
   *
   * @param int $fid
   * @param string $operator
   *
   * @return $this
   */
  public function byPicture($fid, $operator = NULL) {
    return $this->byPropertyConditions(array('picture' => array($fid, $operator)));
  }

  /**
   * Query by the user signature.
   *
   * @param string $signature
   * @param string $operator
   *
   * @return $this
   */
  public function bySignature($signature, $operator = NULL) {
    return $this->byPropertyConditions(array('signature' => array($signature, $operator)));
  }

  /**
   * Query by the user theme.
   *
   * @param string $theme
   * @param string $operator
   *
   * @return $this
   */
  public function byTheme($theme, $operator = NULL) {
    return $this->byPropertyConditions(array('theme' => array($theme, $operator)));
  }


  /**
   * Query by the user initial email address.
   *
   * @param string $mail
   * @param string $operator
   *
   * @return $this
   */
  public function byInitialEmail($mail, $operator = NULL) {
    return $this->byPropertyConditions(array('init' => array($mail, $operator)));
  }

  /**
   * @return WdUserWrapperQueryResults
   */
  public function execute() {
    return new WdUserWrapperQueryResults($this->entityType, $this->query->execute());
  }

  /**
   * Order by UID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByUid($direction = 'ASC') {
    return parent::orderById($direction);
  }

  /**
   * Order by created time
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByCreatedTime($direction = 'ASC') {
    return $this->orderByProperty('created', $direction);
  }

  /**
   * Order by initial email
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByInitialEmail($direction = 'ASC') {
    return $this->orderByProperty('init', $direction);
  }

  /**
   * Order by last access
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByLastAccess($direction = 'ASC') {
    return $this->orderByProperty('access', $direction);
  }

  /**
   * Order by last login
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByLastLogin($direction = 'ASC') {
    return $this->orderByProperty('login', $direction);
  }

  /**
   * Order by email
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByMail($direction = 'ASC') {
    return $this->orderByProperty('mail', $direction);
  }

  /**
   * Order by username
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByName($direction = 'ASC') {
    return $this->orderByProperty('name', $direction);
  }

  /**
   * Order by picture
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByPicture($direction = 'ASC') {
    return $this->orderByProperty('picture', $direction);
  }

  /**
   * Order by signature
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderBySignature($direction = 'ASC') {
    return $this->orderByProperty('signature', $direction);
  }

  /**
   * Order by status
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByStatus($direction = 'ASC') {
    return $this->orderByProperty('status', $direction);
  }

  /**
   * Order by published theme
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByTheme($direction = 'ASC') {
    return $this->orderByProperty('theme', $direction);
  }

}

class WdUserWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdUserWrapper
   */
  public function current() {
    return parent::current();
  }
}