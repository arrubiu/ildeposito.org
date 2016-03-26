<?php
/**
 * @file
 * Class WdUserWrapper
 */

class WdUserWrapper extends WdEntityWrapper {

  protected $entity_type = 'user';

  /**
   * Create a user.
   *
   * @param array $values
   * @param string $language
   *
   * @return WdUserWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $values += array('entity_type' => 'user', 'bundle' => 'user');
    $entity_wrapper = parent::create($values, $language);
    return new WdUserWrapper($entity_wrapper->value());
  }

  /**
   * Retrieve the user UID.
   *
   * @return int
   */
  public function getUid() {
    return $this->get('uid');
  }

  /**
   * Retrieve the user name.
   *
   * @return string
   */
  public function getName($format = WdEntityWrapper::FORMAT_PLAIN) {
    return $this->getText('name', $format);
  }

  /**
   * Set user name.
   *
   * @param string $name
   *
   * @return $this
   */
  public function setName($name) {
    $this->set('name', $name);
    return $this;
  }

  /**
   * Retrieve the user email address.
   *
   * @return string
   */
  public function getMail($format = WdEntityWrapper::FORMAT_PLAIN) {
    return $this->getText('mail', $format);
  }

  /**
   * Set user email address.
   *
   * @param string $address
   *
   * @return $this
   */
  public function setMail($address) {
    $this->set('mail', $address);
    return $this;
  }

  /**
   * Retrieve the user created time.
   *
   * @return int|string
   */
  public function getCreatedTime($format = WdEntityWrapper::DATE_UNIX, $custom_format = '') {
    return $this->getDate('created', $format, $custom_format);
  }

  /**
   * Retrieve the user last login time.
   *
   * @return int|string
   */
  public function getLastLogin($format = WdEntityWrapper::DATE_UNIX, $custom_format = '') {
    return $this->getDate('last_login', $format, $custom_format);
  }

  /**
   * Retrieve the user last access time.
   *
   * @return int|string
   */
  public function getLastAccess($format = WdEntityWrapper::DATE_UNIX, $custom_format = '') {
    return $this->getDate('last_access', $format, $custom_format);
  }

  /**
   * Retrieve the user status
   *
   * @return int
   */
  public function getStatus() {
    return $this->get('status');
  }

  /**
   * Set user status.
   *
   * @param int $status
   *
   * @return $this
   */
  public function setStatus($status) {
    $this->set('status', $status);
    return $this;
  }

  /**
   * Retrieve the user picture.
   *
   * @return stdClass
   */
  public function getPicture() {
    $picture = $this->entity->value()->picture;
    if (!is_object($picture)) {
      $picture = file_load($picture);
    }
    return $picture;
  }

  // @todo: This doesn't work.
  /*public function setPicture($image) {
    $image = (array) $image;
    $this->entity->value()->picture = $image['fid'];
    return $this;
  }*/

  /**
   * Retrieve the user signature.
   *
   * @return array
   */
  public function getSignature($format = WdEntityWrapper::FORMAT_DEFAULT, $markup_format = NULL) {
    $account = $this->entity->value();
    $value = $account->signature;

    if ($format == WdEntityWrapper::FORMAT_DEFAULT) {
      $value = check_markup($account->signature, $account->signature_format);
    }
    elseif ($format == WdEntityWrapper::FORMAT_MARKUP) {
      $value = check_markup($account->signature, $markup_format);
    }
    elseif ($format == WdEntityWrapper::FORMAT_PLAIN) {
      $value = check_plain($account->signature);
    }

    return $value;
  }

  /**
   * Set user signature.
   *
   * @param array $signature
   * @return $this
   */
  public function setSignature($signature) {
    $this->entity->value()->signature = $signature;
    return $this;
  }

  /**
   * Retrieve the user theme.
   *
   * @return string
   */
  public function getTheme() {
    return $this->get('theme');
  }

  /**
   * Set user theme.
   *
   * @param string $theme
   *
   * @return $this
   */
  public function setTheme($theme) {
    $this->set('theme', $theme);
    return $this;
  }

  /**
   * Retrieve the user initial email address.
   *
   * @return string
   */
  public function getInitialEmail($format = WdEntityWrapper::FORMAT_PLAIN) {
    $value = $this->entity->value()->init;
    if ($format == WdEntityWrapper::FORMAT_PLAIN) {
      $value = check_plain($value);
    }
    return $value;
  }

  /**
   * Set user initial email address.
   *
   * @param string $value
   *
   * @return $this
   */
  public function setInitialEmail($value) {
    $this->entity->value()->init = $value;
    return $this;
  }

}
