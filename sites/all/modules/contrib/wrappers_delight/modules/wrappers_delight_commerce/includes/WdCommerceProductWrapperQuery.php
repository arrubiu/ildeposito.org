<?php
/**
 * @file
 * WdCommerceProductWrapperQuery
 */

class WdCommerceProductWrapperQuery extends WdWrapperQuery {

  /**
   * Construct a WdCommerceProductWrapperQuery
   */
  public function __construct() {
    parent::__construct('commerce_product');
  }

  /**
   * Construct a WdCommerceProductWrapperQuery
   *
   * @return WdCommerceProductWrapperQuery
   */
  public static function find() {
    return new self();
  }

  /**
   * Query by the commerce product ID.
   *
   * @param int $product_id
   * @param string $operator
   *
   * @return $this
   */
  public function byProductId($product_id, $operator = NULL) {
    return parent::byId($product_id, $operator);
  }

  /**
   * Query by the commerce product revision ID.
   *
   * @param int $revision_id
   * @param string $operator
   *
   * @return $this
   */
  public function getRevisionId($revision_id, $operator = NULL) {
    return $this->byEntityConditions(array('revision_id' => array($revision_id, $operator)));
  }

  /**
   * Query by the commerce product sku.
   *
   * @param string $sku
   * @param string $operator
   *
   * @return $this
   */
  public function bySku($sku, $operator = NULL) {
    return $this->byPropertyConditions(array('sku' => array($sku, $operator)));
  }

  /**
   * Query by the commerce product title.
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
   * Query by the commerce product creator.
   *
   * @param int $uid
   * @param string $operator
   *
   * @return $this
   */
  public function byCreator($uid, $operator = NULL) {
    return $this->byPropertyConditions(array('uid' => array($uid, $operator)));
  }

  /**
   * Query by the commerce product status.
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
   * Query by the commerce product created time.
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
   * Query by the commerce product updated time.
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
   * Query by the commerce product price.
   *
   * @param int $amount
   * @param string $currency_code
   * @param string $amount_operator
   * @param string $currency_code_operator
   *
   * @return $this
   */
  public function byPrice($amount, $currency_code, $amount_operator = NULL, $currency_code_operator = NULL) {
    return $this->byFieldConditions(
      array(
        'commerce_price.amount' => array($amount, $amount_operator),
        'commerce_price.currency_code' => array($currency_code, $currency_code_operator),
      )
    );
  }

  /**
   * @return WdCommerceProductWrapperQueryResults
   */
  public function execute() {
    return new WdCommerceProductWrapperQueryResults($this->entityType, $this->query->execute());
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
   * Order by creator UID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByCreator($direction = 'ASC') {
    return $this->orderByProperty('uid', $direction);
  }

  /**
   * Order by price amount
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByPriceAmount($direction = 'ASC') {
    return $this->orderByField('commerce_price.amount', $direction);
  }

  /**
   * Order by price currency code
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByPriceCurrency($direction = 'ASC') {
    return $this->orderByField('commerce_price.currency_code', $direction);
  }

  /**
   * Order by product ID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByProductId($direction = 'ASC') {
    return parent::orderById($direction);
  }

  /**
   * Order by SKU
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderBySku($direction = 'ASC') {
    return $this->orderByProperty('sku', $direction);
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

class WdCommerceProductWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdCommerceProductWrapper
   */
  public function current() {
    return parent::current();
  }
}