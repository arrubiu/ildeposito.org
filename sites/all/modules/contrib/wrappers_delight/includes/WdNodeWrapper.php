<?php
/**
 * @file
 * Node wrapper class
 */


/**
 * Class WdNodeWrapper
 */
class WdNodeWrapper extends WdEntityWrapper {
  protected $entity_type = 'node';

  /**
   * Create a new node.
   *
   * @param array $values
   * @param string $language
   * @return WdNodeWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $values += array('entity_type' => 'node', 'type' => $values['bundle']);
    $entity_wrapper = parent::create($values, $language);
    return new WdNodeWrapper($entity_wrapper->value());
  }

  /**
   * Retrieve the NID.
   *
   * @return int
   */
  public function getNid() {
    return $this->get('nid');
  }

  /**
   * Retrieve the title.
   *
   * @return string
   */
  public function getTitle($format = WdEntityWrapper::FORMAT_PLAIN) {
    return $this->getText('title', $format);
  }

  /**
   * Set the title.
   *
   * @param string $title
   * @return $this
   */
  public function setTitle($title) {
    $this->set('title', $title);
    return $this;
  }

  /**
   * Retrieve the node type.
   *
   * @return string
   */
  public function getType() {
    return $this->getBundle();
  }

  /**
   * Retrieve the created time.
   *
   * @return int|string
   */
  public function getCreatedTime($format = WdEntityWrapper::DATE_UNIX, $custom_format = '') {
    return $this->getDate('created', $format, $custom_format);
  }

  /**
   * Set the created time.
   *
   * @param int $timestamp
   * @return $this
   */
  public function setCreatedTime($timestamp) {
    $this->set('created', $timestamp);
    return $this;
  }

  /**
   * Retrieve the updated time.
   *
   * @return int|string
   */
  public function getChangedTime($format = WdEntityWrapper::DATE_UNIX, $custom_format = '') {
    return $this->getDate('changed', $format, $custom_format);
  }

  /**
   * Retrieve the node promoted to front page state.
   *
   * @return bool
   */
  public function isPromoted() {
    return (bool) $this->get('promote');
  }

  /**
   * Set the node promoted to front page status.
   *
   * @param bool $promoted
   * @return $this
   */
  public function setPromoted($promoted) {
    $promoted = $promoted ? NODE_PROMOTED : NODE_NOT_PROMOTED;
    $this->set('promote', $promoted);
    return $this;
  }

  /**
   * Retrieve the node sticky state.
   *
   * @return bool
   */
  public function isSticky() {
    return (bool) $this->get('sticky');
  }

  /**
   * Set the node promoted to front page state.
   *
   * @param bool $sticky
   *
   * @return $this
   */
  public function setSticky($sticky) {
    $sticky = $sticky ? NODE_STICKY : NODE_NOT_STICKY;
    $this->set('sticky', $sticky);
    return $this;
  }

  /**
   * Retrieve the node published status.
   *
   * @return bool
   */
  public function isPublished() {
    return (bool) $this->get('status');
  }

  /**
   * Set the node published status.
   *
   * @param bool $published
   * @return $this
   */
  public function setPublished($published) {
    $published = $published ? NODE_PUBLISHED : NODE_NOT_PUBLISHED;
    $this->set('status', $published);
    return $this;
  }

  /**
   * Retrieve the node author.
   *
   * @return WdUserWrapper
   */
  public function getAuthor() {
    return new WdUserWrapper($this->get('author'));
  }

  /**
   * Retrieve the node author UID.
   *
   * @return int
   */
  public function getAuthorId() {
    return $this->get('author')->uid;
  }

  /**
   * Set the node author UID.
   *
   * @param int $uid
   *
   * @return $this
   */
  public function setAuthorId($uid) {
    $this->set('author', $uid);
    return $this;
  }

  /**
   * Set the node author.
   *
   * @param object $account
   * @return $this
   */
  public function setAuthor($account) {
    if ($account instanceof WdUserWrapper) {
      $account = $account->value();
    }
    $this->set('author', $account);
    return $this;
  }

  /**
   * Retrieve the revision ID.
   *
   * @return int
   */
  public function getRevision() {
    return $this->get('revision');
  }

}
