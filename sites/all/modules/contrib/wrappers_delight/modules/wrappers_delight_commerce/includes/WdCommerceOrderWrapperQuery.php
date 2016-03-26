<?php
/**
 * @file
 * Class WdCommerceOrderWrapperQuery
 */

class WdCommerceOrderWrapperQuery extends WdWrapperQuery {

  /**
   * Construct a WdCommerceOrderWrapperQuery
   */
  public function __construct() {
    parent::__construct('commerce_order');
  }

  /**
   * Construct a WdCommerceOrderWrapperQuery
   *
   * @return WdCommerceOrderWrapperQuery
   */
  public static function find() {
    return new self();
  }

  /**
   * Query by the commerce order ID.
   *
   * @param int $order_id
   * @param string $operator
   *
   * @return $this
   */
  public function byOrderId($order_id, $operator = NULL) {
    parent::byId($order_id, $operator);
  }

  /**
   * Query by the commerce order owner.
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
   * Query by the commerce order owner email address.
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
   * Query by the commerce order status.
   *
   * @param string $status
   * @param string $operator
   *
   * @return $this
   */
  public function byStatus($status, $operator = NULL) {
    return $this->byPropertyConditions(array('status' => array($status, $operator)));
  }

  /**
   * Query by the commerce order created time.
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
   * Query by the commerce order updated time.
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
   * Query by the commerce order hostname.
   *
   * @param string $hostname
   * @param string $operator
   *
   * @return $this
   */
  public function byHostname($hostname, $operator = NULL) {
    return $this->byPropertyConditions(array('hostname' => array($hostname, $operator)));
  }

  /**
   * @return WdCommerceOrderWrapperQueryResults
   */
  public function execute() {
    return new WdCommerceOrderWrapperQueryResults($this->entityType, $this->query->execute());
  }

  /**
   * Order by changed time
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByChangedTime($direction = 'ASC') {
    return $this->orderByProperty('changed', $direction);
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
   * Order by hostname
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByHostname($direction = 'ASC') {
    return $this->orderByProperty('hostname', $direction);
  }

  /**
   * Order by order email
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByMail($direction = 'ASC') {
    return $this->orderByProperty('mail', $direction);
  }

  /**
   * Order by order id
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByOrderId($direction = 'ASC') {
    return parent::orderById($direction);
  }

  /**
   * Order by owner UID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByOwner($direction = 'ASC') {
    return $this->orderByProperty('uid', $direction);
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

}

class WdCommerceOrderWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdCommerceOrderWrapper
   */
  public function current() {
    return parent::current();
  }
}
