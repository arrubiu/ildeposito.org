<?php

/**
 * @file
 * WdCommerceProductWrapper
 */
class WdCommerceProductWrapper extends WdEntityWrapper {

  protected $entity_type = 'commerce_product';

  /**
   * Create a Commerce Product
   *
   * @param string $type
   * @param string|null $sku
   * @param string|null $title
   * @param int|null $uid
   * @param string|null $language
   *
   * @return WdCommerceProductWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $values += array('entity_type' => 'commerce_product', 'type' => 'product');
    $values['bundle'] = $values['type'];
    $product = parent::create($values, $language);
    return new WdCommerceProductWrapper($product->value());
  }

  /**
   * Retrieves the commerce product ID.
   *
   * @return int
   */
  public function getProductId() {
    return $this->get('product_id');
  }

  /**
   * Retrieves the commerce product revision ID.
   *
   * @return int
   */
  public function getRevisionId() {
    return $this->entity->value()->revision_id;
  }

  /**
   * Retrieves the commerce product sku.
   *
   * @return string
   */
  public function getSku($format = WdEntityWrapper::FORMAT_PLAIN) {
    return $this->getText('sku', $format);
  }

  /**
   * Set the commerce product sku.
   *
   * @param string $sku
   *
   * @return $this
   */
  public function setSku($sku) {
    $this->set('sku', $sku);
    return $this;
  }

  /**
   * Retrieves the commerce product title.
   *
   * @return string
   */
  public function getTitle($format = WdEntityWrapper::FORMAT_PLAIN) {
    return $this->getText('title', $format);
  }

  /**
   * Set the commerce product title.
   *
   * @param string $title
   *
   * @return $this
   */
  public function setTitle($title) {
    $this->set('title', $title);
    return $this;
  }

  /**
   * Retrieves the commerce product creator.
   *
   * @return WdUserWrapper
   */
  public function getCreator() {
    return new WdUserWrapper($this->get('creator'));
  }

  /**
   * Retrieves the commerce product creator UID.
   *
   * @return int
   */
  public function getCreatorId() {
    return $this->get('uid');
  }

  /**
   * Set the commerce product creator.
   *
   * @param stdClass|WdUserWrapper $account
   * @return $this
   */
  public function setCreator($account) {
    if ($account instanceof WdUserWrapper) {
      $account = $account->value();
    }
    $this->set('uid', $account->uid);
    return $this;
  }

  /**
   * Retrieves the commerce product status.
   *
   * @return int
   */
  public function getStatus() {
    return $this->get('status');
  }

  /**
   * Set the commerce product status.
   *
   * @param int $value
   * @return $this
   */
  public function setStatus($value) {
    $this->set('status', $value);
    return $this;
  }

  /**
   * Retrieves the commerce product created time.
   *
   * @return int|string
   */
  public function getCreatedTime($format = WdEntityWrapper::DATE_UNIX, $custom_format = '') {
    return $this->getDate('created', $format, $custom_format);
  }

  /**
   * Set the commerce product created time.
   *
   * @param int $timestamp
   *
   * @return $this
   */
  public function setCreatedTime($timestamp) {
    $this->set('created', $timestamp);
    return $this;
  }

  /**
   * Retrieves the commerce product updated time.
   *
   * @return int|string
   */
  public function getChangedTime($format = WdEntityWrapper::DATE_UNIX, $custom_format = '') {
    return $this->getDate('changed', $format, $custom_format);
  }

  /**
   * Retrieves the commerce product price.
   *
   * @return array
   */
  public function getCommercePrice() {
    return $this->get('commerce_price');
  }

  /**
   * Set the commerce product price.
   *
   * @param array $price
   *
   * @return $this
   */
  public function setCommercePrice($price) {
    $this->set('commerce_price', $price);
    return $this;
  }

  /**
   * Retrieves the commerce product price.
   *
   * @param string $format
   *
   * @return array
   */
  public function getPrice($format = 'currency') {
    $price = $this->getCommercePrice();
    if (!empty($price)) {
      switch ($format) {
        case 'decimal':
          return commerce_currency_amount_to_decimal($price['amount'], $price['currency_code']);

        case 'currency':
          return commerce_currency_format($price['amount'], $price['currency_code']);
      }
    }

    return $price;
  }

  /**
   * Set the commerce product price.
   *
   * @param float $price_decimal
   * @param string $currency_code
   *
   * @return $this
   */
  public function setPrice($price_decimal, $currency_code) {
    $price = array(
      'amount' => commerce_currency_decimal_to_amount($price_decimal, $currency_code),
      'currency_code' => $currency_code,
    );
    $this->setCommercePrice($price);
    return $this;
  }

}
