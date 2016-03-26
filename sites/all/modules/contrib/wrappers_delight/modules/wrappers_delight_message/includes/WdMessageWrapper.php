<?php
/**
 * @file
 * Class WdMessageWrapper
 */

class WdMessageWrapper extends WdEntityWrapper {
  protected $entity_type = 'message';

  /**
   * Create a Message entity
   *
   * @param string $type
   * @param int|null $uid
   * @param array $values
   *
   * @return WdMessageWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $values += array(
      'entity_type' => 'message',
      'type' => $values['bundle'],
      'bundle' => $values['bundle'],
      'uid' => $GLOBALS['user']->uid
    );
    $message = parent::create($values, $language);
    return new WdMessageWrapper($message->value());
  }

  /**
   * Retrieves the Message MID.
   *
   * @return int
   */
  public function getMid() {
    return $this->get('mid');
  }

  /**
   * Retrieves the Message owner.
   *
   * @return WdUserWrapper
   */
  public function getOwner() {
    return new WdUserWrapper($this->get('user'));
  }

  /**
   * Sets the Message owner.
   *
   * @param stdClass|WdUserWrapper $account
   *
   * @return $this
   */
  public function setOwner($account) {
    if ($account instanceof WdUserWrapper) {
      $account = $account->value();
    }
    $this->set('user', $account);
    return $this;
  }

  /**
   * Retrieves the Message owner UID.
   *
   * @return int
   */
  public function getOwnerId() {
    return $this->get('user')->uid;
  }

  /**
   * Retrieves the Message timestamp.
   *
   * @return int|string
   */
  public function getTimestamp($format = WdEntityWrapper::DATE_UNIX, $custom_format = '') {
    return $this->getDate('timestamp', $format, $custom_format);
  }

  /**
   * Sets the Message timestamp.
   *
   * @param int $value
   *
   * @return $this
   */
  public function setTimestamp($value) {
    $this->set('timestamp', $value);
    return $this;
  }

}
