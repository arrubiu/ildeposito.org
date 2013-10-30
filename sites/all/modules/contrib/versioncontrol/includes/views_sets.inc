<?php

/**
 * @file
 *
 * Interfaces and base classes that define VCAPI's views set system.
 */

/**
 * Base class for views sets; reduce a little code duplication.
 *
 */
abstract class VersioncontrolViewsSetBase implements VersioncontrolViewsSetInterface {
  protected $setName = '';

  protected $baseView = '';

  protected $setData = array();

  protected $defaultViews = array();

  /**
   * Grab stored set data and attach it as a property.
   */
  public function __construct() {
    // $this->setData = versioncontrol_get_views_set($this->setName);
  }

  public function getViewNameByEntity(VersioncontrolEntityInterface $entity) {
    return $this->getViewNameByBackend($entity->getBackend());
  }

  public function getViewNameByBackend($backend) {
    if ($backend instanceof VersioncontrolBackend) {
      $backend = $backend->type;
    }
    return empty($this->setData[$backend]) ? $this->baseView : $this->setData[$backend];
  }

  public function getBaseView() {
    return $this->baseView;
  }

  public function getDefaultViews($vcs = '') {
    if (empty($vcs)) {
      return $this->defaultViews;
    }

    return empty($this->defaultViews[$vcs]) ? FALSE : $this->defaultViews[$vcs];
  }

  public function getSetName() {
    return $this->setName;
  }

  public function setSet($data) {
    $this->setData = $data;
  }
}

/**
 * Helper abstract parent for global views sets. For most of them, the logic
 * defined here will be perfectly adequate. If the logic doesn't work, others
 * can still just implement the interface directly.
 */
abstract class VersioncontrolViewsSetGlobalBase extends VersioncontrolViewsSetBase implements VersioncontrolViewsGlobalSetInterface {

  protected $view;

  public function getViewNameByEntity(VersioncontrolEntityInterface $entity) {
    return $this->view;
  }

  public function getViewName() {
    return $this->view;
  }

  public function setSet($data) {
    parent::setSet($data);

    if (variable_get('versioncontrol_single_backend_mode', FALSE)) {
      $backends = versioncontrol_get_backends();
      $this->view = $this->getViewNameByBackend(reset($backends));
    }
    else {
      $this->view = $this->baseView;
    }
  }
}
