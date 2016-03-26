<?php
/**
 * @file
 * Documentation for extending Wrappers Delight
 */

/**
 * Declare base classes for entities.
 * Make sure you include the class files in your .info file.
 * Wrappers Delight (for D7) does not do any autoloading.
 *
 * @return array
 */
function hook_wrappers_delight_base_classes() {
  return array(
    'example_entity' => 'WdExampleEntityWrapper',
  );
}

/**
 * Alter base classes for entity wrappers.
 */
function hook_wrappers_delight_base_classes_alter(&$base_classes) {
  $base_classes['example_entity'] = 'WdExampleEntityCustomWrapper';
}

/**
 * Declare module dependencies for base classes.
 *
 * @return array
 */
function hook_wrappers_delight_base_class_dependencies($entity_type) {
  if ($entity_type == 'example_entity') {
    return array('example_entity_module');
  }
}


/**
 * Class WdExampleEntityWrapper
 */
class WdExampleEntityWrapper extends WdEntityWrapper {

  /**
   * Wrap an example entity
   *
   * @param stdClass|int $example
   */
  public function __construct($example) {
    if (is_numeric($example)) {
      $example = entity_load_single('example_entity', $example);
    }
    parent::__construct('example_entity', $example);
  }

  /**
   * Create a new example entity.
   *
   * @param array $values
   * @param string $language
   *
   * @return WdExampleEntityWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $values += array('entity_type' => 'example_entity', 'type' => $values['bundle']);
    $entity_wrapper = parent::create($values, $language);
    return new WdExampleEntityWrapper($entity_wrapper->value());
  }

  // You should include getters and setters for your entities base properties
  // in your custom class. (otherwise, you could use the WdEntityWrapper class
  // instead)

}
