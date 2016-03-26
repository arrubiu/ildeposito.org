<?php
/**
 * Created by PhpStorm.
 * User: wayne
 * Date: 10/10/14
 * Time: 11:26 PM
 */

class WdWrapperQueryResults implements Iterator {

  private $results;
  private $rawResults;
  private $entityType;
  private $entityInfo;
  private $loaded;
  private $iterator;

  function __construct($entity_type, $results) {
    if (!empty($results[$entity_type])) {
      $this->rawResults = $results[$entity_type];
    }
    else {
      $this->rawResults = array();
    }
    $this->entityType = $entity_type;
    $this->entityInfo = entity_get_info($entity_type);
    $this->results = $this->rawResults;
    $this->iterator = new ArrayIterator($this->results);
    $this->loaded = FALSE;
  }

  /**
   * (PHP 5 &gt;= 5.0.0)<br/>
   * Return the current element
   * @link http://php.net/manual/en/iterator.current.php
   * @return WdEntityWrapper
   */
  public function current() {
    $current = $this->iterator->current();
    $entity_info = entity_extract_ids($this->entityType, $current);
    list($entity_id,,$bundle) = $entity_info;

    $class = wrappers_delight_get_wrapper_class($this->entityType, $bundle);

    // If the entity is a stub, we need to send in the entity id so it loads it
    $stub = entity_create_stub_entity($this->entityType, $entity_info);
    $parameter = ($stub == $current) ? $entity_id : $current;

    if ($class == 'WdEntityWrapper') {
      return new WdEntityWrapper($this->entityType, $parameter);
    }
    return new $class($parameter);
  }

  /**
   * (PHP 5 &gt;= 5.0.0)<br/>
   * Move forward to next element
   * @link http://php.net/manual/en/iterator.next.php
   * @return void Any returned value is ignored.
   */
  public function next() {
    $this->iterator->next();
  }

  /**
   * (PHP 5 &gt;= 5.0.0)<br/>
   * Return the key of the current element
   * @link http://php.net/manual/en/iterator.key.php
   * @return mixed scalar on success, or null on failure.
   */
  public function key() {
    return $this->iterator->key();
  }

  /**
   * (PHP 5 &gt;= 5.0.0)<br/>
   * Checks if current position is valid
   * @link http://php.net/manual/en/iterator.valid.php
   * @return boolean The return value will be casted to boolean and then evaluated.
   * Returns true on success or false on failure.
   */
  public function valid() {
    $this->warmCache();
    return $this->iterator->valid();
  }

  /**
   * (PHP 5 &gt;= 5.0.0)<br/>
   * Rewind the Iterator to the first element
   * @link http://php.net/manual/en/iterator.rewind.php
   * @return void Any returned value is ignored.
   */
  public function rewind() {
    $this->iterator->rewind();
  }

  /**
   * Disable the cache so that all entities aren't loaded all at once.
   * @return self
   */
  public function disableCache() {
    $this->loaded = TRUE;
    return $this;
  }

  /**
   * Warm the cache by loading the entities all at once.
   */
  private function warmCache() {
    if (!$this->loaded) {
      $this->results = entity_load($this->entityType, array_keys($this->rawResults));
      $this->loaded = TRUE;
    }
  }

  /**
   * Returns the Entities loaded
   */
  public function getValues() {
    $this->warmCache();
    return $this->results;
  }

  /**
   * Returns the raw results of the Query
   * @return array
   */
  public function getRawResults() {
    return $this->rawResults;
  }

  /**
   * Returns the Entity Type of the query
   * @return mixed
   */
  public function getEntityType() {
    return $this->entityType;
  }

}
