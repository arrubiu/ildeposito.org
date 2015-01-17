<?php
/**
 * @file
 * Basic event processor class doing nothing.
 */

/**
 * An example event processor class.
 */
class VersioncontrolEventProcessorNone implements VersioncontrolSynchronizationEventProcessorInterface, VersioncontrolPluginConfigurationInterface {
  const BEHAVIOR_A = 1;
  const BEHAVIOR_B = 2;

  /**
   * Associated repository.
   *
   * @var VersioncontrolRepository
   */
  protected $repository;

  public $behavior;
  public $message;

  public function setConfiguration($data) {
    $this->behavior = $data['behavior'];
    $this->message = $data['message'];
  }

  /**
   * This plugin is an example that does nothing.
   */
  public function process(VersioncontrolEvent $event) {
  }

  public function setRepository(VersioncontrolRepository $repository) {
    $this->repository = $repository;
  }

  public function buildForm($default_data) {
    $form['event-processor-none-behavior'] = array(
      '#type' => 'select',
      '#title' => 'Behavior',
      '#default_value' => !empty($default_data['behavior']) ? $default_data['behavior'] : self::BEHAVIOR_A,
      '#options' => array(
        self::BEHAVIOR_A => t('Behavior A'),
        self:: BEHAVIOR_B => t('Behavior B'),
      ),
      '#description' => t('An option that will not change any behavior.'),
    );
    $form['event-processor-none-message'] = array(
      '#type' => 'textfield',
      '#title' => 'Message',
      '#description' => t('One message that will not be displayed.'),
      '#default_value' => !empty($default_data['message']) ? $default_data['message'] : '',
    );
    return $form;
  }

  public function getFormData($form_state_values_data) {
    return array(
      'behavior' => $form_state_values_data['event-processor-none-behavior'],
      'message' => $form_state_values_data['event-processor-none-message'],
    );
  }

  public function submitForm(&$form, &$form_state) {
    // Nothing special.
  }
}
