<?php

class VersioncontrolTestRepositoryHistorySynchronizerDefault implements VersioncontrolRepositoryHistorySynchronizerInterface {

  protected $repository;


  /**
   * The exception to throw, if any, whenever syncFull() is called.
   *
   * @var Exception
   */
  public $syncFullException;

  /**
   * The exception to throw, if any, whenever syncInitial() is called.
   *
   * @var Exception
   */
  public $syncInitialException;

  /**
  * The exception to throw, if any, whenever syncEvent() is called.
  *
  * @var Exception
  */
  public $syncEventException;

  /**
  * The exception to throw, if any, whenever verifyData() is called.
  *
  * @var Exception
  */
  public $verifyDataException;

  /**
  * The exception to throw, if any, whenever verifyEvent() is called.
  *
  * @var Exception
  */
  public $verifyEventException;

  public function setRepository(VersioncontrolRepository $repository) {
    $this->repository = $repository;
  }

  public function syncFull($options) {
    return $this->doThing('syncFullException');
  }

  public function syncInitial($options) {
    return $this->doThing('syncInitialException');
  }

  public function syncEvent(VersioncontrolEvent $event, $options) {
    return $this->doThing('syncEventException');
  }

  public function verifyEvent(VersioncontrolEvent $event) {
    return $this->doThing('verifyEventException');
  }

  public function verifyData() {
    return $this->doThing('verifyDataException');
  }

  protected function doThing($prop) {
    if ($this->$prop instanceof Exception) {
      throw $this->$prop;
    }
    return TRUE;
  }
}
