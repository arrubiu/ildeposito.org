<?php
/**
 * @file
 * Class WdEntityqueueSubqueueWrapper
 */

class WdEntityqueueSubqueueWrapper extends WdEntityWrapper {

  protected $entity_type = 'entityqueue_subqueue';

  /**
   * Wrap a entityqueue_subqueue entity.
   *
   * @param stdClass|int|string $entityqueue_subqueue
   */
  public function __construct($entityqueue_subqueue) {
    if (is_numeric($entityqueue_subqueue) || is_string($entityqueue_subqueue)) {
      $entityqueue_subqueue = entityqueue_subqueue_load($entityqueue_subqueue);
    }
    parent::__construct($entityqueue_subqueue);
  }

  /**
   * Create a entityqueue_subqueue entity
   *
   * @param array $values
   *
   * @return WdEntityqueueSubqueueWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $values += array(
      'entity_type' => 'entityqueue_subqueue',
      'queue' => !empty($values['bundle']) ? $values['bundle'] : NULL,
      'bundle' => !empty($values['queue']) ? $values['queue'] : NULL,
    );
    $entityqueue_subqueue = parent::create($values, $language);
    return new WdEntityqueueSubqueueWrapper($entityqueue_subqueue->value());
  }

  /**
   * Create an entityqueue queue. The entityqueue queue is not and entity
   * but it is the bundle type for entityqueue_subqueue.
   *
   * @param array $values
   * @param string $language
   *
   * @return object
   */
  public static function createQueue($values = array(), $save_queue = FALSE) {
    module_load_include('inc', 'ctools', 'includes/export');
    $queue = entityqueue_queue_create($values);
    if ($save_queue) {
      entityqueue_queue_save($queue);
    }
    return $queue;
  }

  /**
   * Retrieves the Subqueue ID.
   *
   * @return int
   */
  public function getSubqueueId() {
    return $this->get('subqueue_id');
  }

  /**
   * @return string
   */
  public function getQueue() {
    return $this->getBundle();
  }

  /**
   * @return string
   */
  public function getName() {
    return $this->get('name');
  }

  /**
   * @param string $name
   *
   * @return $this
   */
  public function setName($name) {
    $this->set('name', $name);
    return $this;
  }

  /**
   * @return string
   */
  public function getLabel() {
    return $this->get('label');
  }

  /**
   * @param string $label
   *
   * @return $this
   */
  public function setLabel($label) {
    $this->set('label', $label);
    return $this;
  }

  /**
   * @return string
   */
  public function getModule() {
    return $this->get('module');
  }

  /**
   * @return array
   */
  public function getData() {
    return $this->get('data');
  }

  /**
   * @param array $data
   *
   * @return $this
   */
  public function setData($data) {
    $this->set('data', $data);
    return $this;
  }

  /**
   * Retrieves the Subqueue owner.
   *
   * @return WdUserWrapper
   */
  public function getOwner() {
    return new WdUserWrapper($this->get('uid'));
  }

  /**
   * Sets the Subqueue owner.
   *
   * @param stdClass|WdUserWrapper $account
   *
   * @return $this
   */
  public function setOwner($account) {
    if ($account instanceof WdUserWrapper) {
      $account = $account->value();
    }
    $this->set('uid', $account);
    return $this;
  }

  /**
   * Retrieves the Subqueue owner UID.
   *
   * @return int
   */
  public function getOwnerId() {
    return $this->get('uid')->uid;
  }

}