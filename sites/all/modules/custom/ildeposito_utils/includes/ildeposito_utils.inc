<?php

/**
 * @file
 */

/**
 * @param $entity_type
 * @param null $bundle
 * @param null $column
 * @param null $value
 * @param null $field_name
 * @param null $status
 * @param null $property_order_by
 * @return array
 */
function ildeposito_utils_get_entity($entity_type, $bundle = NULL, $field_name = NULL,  $column = NULL, $value = NULL, $status = NULL, $property_order_by = NULL) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', $entity_type);

  if ($field_name && $value && $column) {
    $query->fieldCondition($field_name, $column, $value, '=');
  }

  if ($bundle) {
    $query->entityCondition('bundle', $bundle);
  }

  if ($status) {
    $query->propertyCondition('status', $status);
  }

  if (is_array($property_order_by)) {
    list($column_ord, $direction_ord) = $property_order_by;
    $query->propertyOrderBy($column_ord, $direction_ord);
  }

  $result = $query->execute();
  $entity_ids = array();

  if (isset($result[$entity_type])) {
    foreach (array_keys($result[$entity_type]) as $entity_id) {
      $entity_ids[] = $entity_id;
    }
  }

  return $entity_ids;
}
