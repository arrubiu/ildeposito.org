<?php
/**
 * @file
 * Class WdCommerceOrderWrapper
 */

class WdCommerceOrderWrapper extends WdEntityWrapper {
  protected $entity_type = 'commerce_order';

  /**
   * Retrieve the commerce line items.
   *
   * @return array
   */
  public function getLineItems() {
    return $this->get('commerce_line_items');
  }

}
