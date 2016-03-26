<?php
/**
 * @file
 * API documentation for Wrappers Delight Query
 */


/**
 * Declare base classes for entity queries.
 * Make sure you include the class files in your .info file.
 * Wrappers Delight Query (for D7) does not do any autoloading.
 *
 * @return array
 */
function hook_wrappers_delight_query_base_classes() {
  return array(
    'entity_type' => 'WdEntityTypeWrapperQuery',
    'example_entity' => 'WdExampleEntityWrapperQuery',
  );
}

/**
 * Alter base classes for entity queries.
 *
 * @return array
 */
function hook_wrappers_delight_query_base_classes_alter(&$base_classes) {
  $base_classes['example_entity'] = 'WdExampleEntityCustomWrapper';
}


class WdExampleEntityWrapperQuery extends WdWrapperQuery {

  /**
   * Construct a WdExampleEntityWrapperQuery
   */
  public function __construct() {
    parent::__construct('example_entity');
  }

  /**
   * Construct a WdExampleEntityWrapperQuery
   *
   * @return WdExampleEntityWrapperQuery
   */
  public static function find() {
    return new self();
  }

  /**
   * @return WdExampleEntityWrapperQueryResults
   */
  public function execute() {
    return new WdExampleEntityWrapperQueryResults($this->entityType, $this->query->execute());
  }

  // You should include byXXXX() and orderByXXXX() query methods for your
  // entity's base properties. Example below:

  public function byOwner($uid, $operator = NULL) {
    return $this->byPropertyConditions(array('uid' => array($uid, $operator)));
  }

  public function orderByOwner($direction = 'ASC') {
    return $this->orderByProperty('uid', $direction);
  }

}

class WdExampleEntityWrapperQueryResults extends WdWrapperQueryResults {

  /**
   * @return WdExampleEntityWrapper
   */
  public function current() {
    return parent::current();
  }
}