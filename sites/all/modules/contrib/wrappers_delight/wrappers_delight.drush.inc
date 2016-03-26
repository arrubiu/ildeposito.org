<?php
/**
 * @file
 * Wrappers Delight Drush command
 */

/**
 * Implements hook_drush_command().
 */
function wrappers_delight_drush_command() {
  $items = array();

  $items['make-wrapper-class'] = array(
    'description' => "Makes a wrapper class for an entity.",
    'arguments' => array(
      'entity_type' => 'Entity type to wrap.',

    ),
    'options' => array(
      'bundles' => array(
        'description' => 'Entity bundles',
        'example-value' => 'page,article',
      ),
      'module' => array(
        'description' => 'Output module name',
        'example-value' => 'wrappers_custom',
      ),
      'destination' => array(
        'description' => 'Destination parent directory',
        'example-value' => 'profiles/yourapp/modules/custom'
      ),
      'skip-base-class' => array(
        'description' => 'Do not create an entity base class if one is missing',
      ),
    ),
    'examples' => array(
      'drush wrap node --bundles=page,article --module=wrappers_custom' => 'Generate wrapper classes for page and article node types and place them in the wrappers_custom module (generating module if not exists).',
    ),
    'aliases' => array('wrap'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function wrappers_delight_drush_help($section) {
  switch ($section) {
    case 'drush:make-wrapper-class':
      return dt("This command will generate or update a wrapper class for an entity.");
  }
}

/**
 * Implements drush_hook_COMMAND().
 *
 * Create wrapper classes for an entity type.
 *
 * @param $entity_type
 *   Entity type to create wrappers for
 *
 * @see drush_invoke()
 * @see drush.api.php
 */
function drush_wrappers_delight_make_wrapper_class($entity_type) {

  $entity_info = entity_get_info($entity_type);
  if (empty($entity_info)) {
    drush_set_error('ENTITY_TYPE_NOT_EXISTS', dt('Entity type @type does not exist.', array('@type' => $entity_type)));
    return;
  }

  $bundles = NULL;
  if ($bundle_string = drush_get_option('bundles')) {
    $bundles = explode(',', $bundle_string);
  }
  $module_name = drush_get_option('module');
  $destination = drush_get_option('destination');
  $skip_base_class = drush_get_option('skip-base-class');


  wrappers_delight_make_wrapper_classes($entity_type, $bundles, $module_name, $destination, $skip_base_class);

}



















