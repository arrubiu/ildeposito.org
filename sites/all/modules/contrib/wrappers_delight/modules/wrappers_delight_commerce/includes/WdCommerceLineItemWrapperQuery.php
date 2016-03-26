<?php
/**
 * @file
 * Class WdCommerceLineItemQuery
 */

class WdCommerceLineItemWrapperQuery extends WdWrapperQuery {

  /**
   * Construct a WdCommerceLineItemWrapperQuery
   */
  public function __construct() {
    parent::__construct('commerce_line_item');
  }

  /**
   * Construct a WdCommerceLineItemWrapperQuery
   *
   * @return WdCommerceLineItemWrapperQuery
   */
  public static function find() {
    return new self();
  }

  /**
   * Query by the commerce line item ID.
   *
   * @param int $line_item_id
   * @param string $operator
   *
   * @return $this
   */
  public function byLineItemId($line_item_id, $operator = NULL) {
    return parent::byId($line_item_id, $operator);
  }

  /**
   * Query by the commerce order id.
   *
   * @param int $order_id
   * @param string $operator
   *
   * @return $this
   */
  public function byOrderId($order_id, $operator = NULL) {
    return $this->byPropertyConditions(array('order_id' => array($order_id, $operator)));
  }

  /**
   * Query by the commerce line item type.
   *
   * @param string $type
   * @param string $operator
   *
   * @return $this
   */
  public function byType($type, $operator = NULL) {
    return $this->byPropertyConditions(array('type' => array($type, $operator)));
  }

  /**
   * Query by the commerce line item label.
   *
   * @param string $label
   * @param string $operator
   *
   * @return $this
   */
  public function byLineItemLabel($label, $operator = NULL) {
    return $this->byPropertyConditions(array('line_item_label' => array($label, $operator)));
  }

  /**
   * Query by the commerce line item quantity.
   *
   * @param int $quantity
   * @param string $operator
   *
   * @return $this
   */
  public function byQuantity($quantity, $operator = NULL) {
    return $this->byPropertyConditions(array('quantity' => array($quantity, $operator)));
  }

  /**
   * Query by the commerce line item created time.
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
   * Query by the commerce line item updated time.
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
   * Query by the commerce product ID.
   *
   * @param int $product_id
   * @param string $operator
   *
   * @return $this
   */
  public function byProductId($product_id, $operator = NULL) {
    return $this->byFieldConditions(array('commerce_product' => array($product_id, $operator)));
  }

  /**
   * Query by the commerce line item unit price.
   *
   * @param int $amount
   * @param string $currency_code
   * @param string $amount_operator
   * @param string $currency_code_operator
   *
   * @return $this
   */
  public function byUnitPrice($amount, $currency_code, $amount_operator = NULL, $currency_code_operator = NULL) {
    return $this->byFieldConditions(
      array(
        'commerce_unit_price.amount' => array($amount, $amount_operator),
        'commerce_unit_price.currency_code' => array($currency_code, $currency_code_operator),
      )
    );
  }

  /**
   * Query by the commerce line item total.
   *
   * @param int $amount
   * @param string $currency_code
   * @param string $amount_operator
   * @param string $currency_code_operator
   *
   * @return $this
   */
  public function byTotal($amount, $currency_code, $amount_operator = NULL, $currency_code_operator = NULL) {
    return $this->byFieldConditions(
      array(
        'commerce_total.amount' => array($amount, $amount_operator),
        'commerce_total.currency_code' => array($currency_code, $currency_code_operator),
      )
    );
  }

  /**
   * @return WdCommerceLineItemWrapperQueryResults
   */
  public function execute() {
    return new WdCommerceLineItemWrapperQueryResults($this->entityType, $this->query->execute());
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
   * Order by line item id
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByLineItemId($direction = 'ASC') {
    return parent::orderById($direction);
  }

  /**
   * Order by label
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByLineItemLabel($direction = 'ASC') {
    return $this->orderByProperty('line_item_label', $direction);
  }

  /**
   * Order by order ID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByOrderId($direction = 'ASC') {
    return $this->orderByProperty('order_id', $direction);
  }

  /**
   * Order by product ID
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByProductId($direction = 'ASC') {
    return $this->orderByField('commerce_product.product_id', $direction);
  }

  /**
   * Order by quantity
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByQuantity($direction = 'ASC') {
    return $this->orderByProperty('quantity', $direction);
  }

  /**
   * Order by total amount
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByTotalAmount($direction = 'ASC') {
    return $this->orderByField('commerce_total.amount', $direction);
  }

  /**
   * Order by total currency
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByTotalCurrency($direction = 'ASC') {
    return $this->orderByField('commerce_total.currency', $direction);
  }

  /**
   * Order by type
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByType($direction = 'ASC') {
    return parent::orderByBundle($direction);
  }

  /**
   * Order by unit price amount
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByUnitPriceAmount($direction = 'ASC') {
    return $this->orderByField('commerce_unit_price.amount', $direction);
  }

  /**
   * Order by unit price currency
   *
   * @param string $direction
   *
   * @return $this
   */
  public function orderByUnitPriceCurrency($direction = 'ASC') {
    return $this->orderByField('commerce_unit_price.currency_code', $direction);
  }

}

class WdCommerceLineItemWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdCommerceLineItemWrapper
   */
  public function current() {
    return parent::current();
  }
}
