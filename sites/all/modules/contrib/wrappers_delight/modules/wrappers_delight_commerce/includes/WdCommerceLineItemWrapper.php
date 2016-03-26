<?php
/**
 * @file
 * Class WdCommerceLineItem
 */

class WdCommerceLineItemWrapper extends WdEntityWrapper {
  protected $entity_type = 'commerce_line_item';

  /**
   * Retrieves the commerce product on this line item.
   *
   * @return WdCommerceProductWrapper
   */
  public function getProduct() {
    return new WdCommerceProductWrapper($this->get('commerce_product'));
  }

  /**
   * Retrieves the commerce total.
   *
   * @return array
   */
  public function getTotal() {
    return $this->get('commerce_total');
  }

  /**
   * Retrieves the commerce unit price
   *
   * @return array
   */
  public function getUnitPrice() {
    return $this->get('commerce_unit_price');
  }

  /**
   * Retrieves the quantity.
   *
   * @return int
   */
  public function getQuantity() {
    return $this->get('quantity');
  }

}