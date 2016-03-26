<?php
/**
 * @file
 * Class WdEntityWrapper
 */

class WdEntityWrapper {

  const FORMAT_DEFAULT = 'default';
  const FORMAT_PLAIN = 'plain';
  const FORMAT_MARKUP = 'markup';
  const FORMAT_RAW = 'raw';

  const DATE_UNIX = 'unix_timestamp';
  const DATE_CUSTOM = 'custom';

  /**
   * Wrapped entity
   *
   * @var EntityMetadataWrapper
   */
  protected $entity;

  /**
   * Wrapped entity type
   *
   * @var string
   */
  protected $entity_type;

  /**
   * Wrap an entity.
   *
   * @param stdClass|int $entity
   *   Entity to wrap. Will load entity if ID is passed.
   *
   * @param string|null $entity_type
   *   Entity type
   *
   */
  public function __construct($entity, $entity_type = NULL) {

    // Provide a workaround for code written in the pre Issue #2464623 style.
    // This constructor used to have arguments ($entity_type, $entity)
    if (!is_null($entity_type) && is_string($entity) && (is_object($entity_type) || is_numeric($entity_type))) {
      $actual_entity = $entity_type;
      $entity_type = $entity;
      $entity = $actual_entity;
    }

    if (!is_null($entity_type)) {
      $this->entity_type = $entity_type;
    }

    $this->entity = entity_metadata_wrapper($this->entity_type, $entity);
  }

  /**
   * Create a new entity. Does not save entity before returning.
   *
   * @param $entity_type
   * @param $bundle
   * @param array $values
   * @param string $language
   *
   * @return WdEntityWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $values += array('bundle' => $values['bundle'], 'language' => $language);
    $entity = entity_create($values['entity_type'], $values);
    return new WdEntityWrapper($entity, $values['entity_type']);
  }

  /**
   * @return string
   */
  public function getEntityType() {
    return $this->entity_type;
  }

  /**
   * Retrieve wrapped entity bundle
   *
   * @return string
   */
  public function getBundle() {
    return $this->entity->getBundle();
  }

  /**
   * Retrieve an entity value by name.
   *
   * @param $name
   *
   * @return mixed
   */
  public function get($name) {
    return $this->entity->{$name}->value();
  }

  /**
   * Retrieve an entity value by name.
   *
   * @param $name
   * @param $format
   *
   *
   * @return mixed
   */
  public function getText($name, $format = WdEntityWrapper::FORMAT_DEFAULT, $markup_format = NULL) {
    $raw_value = $this->entity->{$name}->value();
    $value = NULL;

    if (is_array($raw_value)) {
      if (is_null($markup_format)) {
        $markup_format = $raw_value['format'];
      }
      $value = $raw_value['value'];
    }
    else {
      $value = $raw_value;
    }

    // First check if the field allows a text format, and we have one assigned
    if ($format == WdEntityWrapper::FORMAT_DEFAULT && is_array($raw_value)) {
      $instance = field_info_instance($this->entity_type, $name, $this->getBundle());

      // If text format is allowed, use check_markup and the existing or requested format.
      if (!empty($instance['settings']['text_processing'])) {
        $format = WdEntityWrapper::FORMAT_MARKUP;
      }
      else {
        // else plain text is enforced.
        $format = WdEntityWrapper::FORMAT_PLAIN;
      }
    }

    // Now apply the formatting if default, plain or markup are requested.
    if ($format == WdEntityWrapper::FORMAT_DEFAULT || $format == WdEntityWrapper::FORMAT_PLAIN) {
      $value = check_plain($value);
    }
    elseif ($format == WdEntityWrapper::FORMAT_MARKUP) {
      $value = check_markup($value, $markup_format);
    }

    return $value;
  }

  /**
   * Retrieve an entity value and format as a date.
   *
   * @param $name
   *
   * @return mixed
   */
  public function getDate($name, $format = WdEntityWrapper::DATE_UNIX, $custom_format = '') {
    $value = $this->entity->{$name}->value();
    if (!is_null($value) && $format != WdEntityWrapper::DATE_UNIX) {
      $value = format_date($value, $format, $custom_format);
    }
    return $value;
  }

  /**
   * Set an entity value by name.
   *
   * @param $name
   * @param $value
   *
   * @return $this
   */
  public function set($name, $value) {
    $this->entity->{$name} = $value;
    return $this;
  }

  /**
   * Save the wrapped entity.
   *
   * @return $this
   */
  public function save() {
    $this->entity->save();
    return $this;
  }

  /**
   * Delete this entity
   *
   * @return $this
   */
  public function delete() {
    entity_delete($this->entity_type, $this->getId());
    return $this;
  }

  /**
   * Retrieve the EntityMetadataWrapper object.
   *
   * @return EntityMetadataWrapper
   */
  public function getEntityMetadataWrapper() {
    return $this->entity;
  }

  /**
   * Gets the info about the given property from the EntityMetadataWRapper object
   *
   * @param $name
   *   The name of the property. If not given, info about all properties will
   *   be returned.
   * @throws EntityMetadataWrapperException
   *   If there is no such property.
   * @return
   *   An array of info about the property.
   */
  public function getPropertyInfo($name = NULL) {
    return $this->entity->getPropertyInfo($name);
  }

  /**
   * Retrieve the wrapped entity.
   *
   * @return mixed
   */
  public function value() {
    return $this->entity->value();
  }

  /**
   * Retrieve the language.
   *
   * @return string
   */
  public function getLanguage() {
    return $this->entity->language->value();
  }

  /**
   * Retrieve the entity ID
   *
   * @return int
   */
  public function getId() {
    return $this->getIdentifier();
  }

  /**
   * Retrieve the entity ID
   *
   * @return int
   */
  public function getIdentifier() {
    return $this->entity->getIdentifier();
  }

  /**
   * Retrieve the entity label
   *
   * @return string
   */
  public function getLabel() {
    return $this->entity->label();
  }

  /**
   * Utility function to save filtered text fields and clear safe_value from them.
   *
   * @param $field_name
   * @param $value
   * @return $this
   */
  protected function setText($field_name, $value, $format = NULL) {
    $instance = field_info_instance($this->entity_type, $field_name, $this->getBundle());

    if (!empty($instance['settings']['text_processing'])) {
      // Filtered textfield, requires format.
      // We need to clear safe_value in order to have it regenerated
      // within the same page load.
      $field_value = $this->entity->{$field_name}->value();
      $field_value['value'] = $value;
      $field_value['format'] = is_null($format) ? filter_default_format() : $format;
      unset($field_value['safe_value']);
    }
    else {
      // For plain text fields, no format.
      $field_value = $value;
    }

    $this->entity->{$field_name} = $field_value;
    return $this;
  }

  /**
   * @param $entity_type
   * @return string
   */
  protected function getBaseClassName($entity_type) {
    $camelized_type = str_replace(' ', '', ucwords(str_replace('_', ' ', $entity_type)));
    $class = 'Wd' . $camelized_type . 'Wrapper';
    if (!class_exists($class)) {
      $class = 'WdEntityWrapper';
    }
    return $class;
  }

  /**
   * Check if entity marked as new.
   *
   * @return boolean
   */
  public function isNew() {
    return !empty($this->entity->value()->is_new);
  }

  /**
   * Check if entity has an original value
   *
   * @return bool
   */
  public function hasOriginal() {
    return property_exists($this->value(), 'original');
  }

  /**
   * Original entity if exists or current entity if not.
   * Can be handy on hook_presave.
   *
   * @return $this
   */
  public function getOriginal() {
    if (!$this->hasOriginal()) {
      return $this;
    }
    $class = wrappers_delight_get_wrapper_class($this->entity_type, $this->getBundle());
    return new $class($this->value()->original);
  }

  /**
   * Sets a new language to use for retrieving properties.
   *
   * @param $langcode
   * @return $this
   */
  public function language($langcode = LANGUAGE_NONE) {
    $this->entity->language($langcode);
    return $this;
  }

}
