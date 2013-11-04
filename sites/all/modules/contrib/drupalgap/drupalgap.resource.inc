<?php

/**
 * @file
 * This file implements the DrupalGap service resource call back functions.
 */

/*function _drupalgap_field_info_instances($entity_type = NULL, $bundle_name = NULL) {
  return field_info_instances($entity_type, $bundle_name);
}

function _drupalgap_field_info_fields() {
  return field_info_fields();
}*/

/**
 * Determines whether the current user can access a drupalgap resource.
 *
 * @param string $op
 *   String indicating which operation to check access for.
 * @param array $args
 *   Array arguments passed through from the original request.
 *
 * @return boolean
 *   Boolean indicating whether or not the user has access to the resource.
 *
 * @see node_access()
 */
function _drupalgap_resource_access($op = 'view', $args = array()) {
  return user_access($op);
}

/**
 * Returns a collection of content types from the {node_type} table.
 *
 * It also bundles other available information about each content type
 * with the return results.
 *
 * @param array $options
 *   An array of options.
 *
 * @return object
 *   MySQL object results from the {node_type} table
 */
function _drupalgap_resource_content_types_list($options = array()) {
  // Grab content types.
  $sql = "SELECT * FROM {node_type} ORDER BY name ASC";
  $content_types_result = db_query($sql);

  if ($content_types_result) {
    $content_types = $content_types_result->fetchAll();
    foreach ($content_types as $i => $content_type) {
      // Grab comment settings for content type.
      $names = array(
        'comment_anonymous_' . $content_type->type,
        'comment_' . $content_type->type,
        'comment_default_mode_' . $content_type->type,
        'comment_default_per_page_' . $content_type->type,
        'comment_form_location_' . $content_type->type,
        'comment_preview_' . $content_type->type,
        'comment_subject_field_' . $content_type->type,
      );
      $sql = "SELECT * FROM {variable} WHERE name IN (:names)";
      $variable_results = db_query($sql, array(':names' => $names));

      if ($variable_results) {
        // Extract comment settings variables and attach to content type result.
        $variables = $variable_results->fetchAll();
        foreach ($variables as $variable) {
          // Strip the '_type' from the end.
          $end = drupal_strlen($variable->name) - (drupal_strlen($content_type->type) + 1);
          $variable_name = drupal_substr($variable->name, 0, $end);
          $content_types[$i]->$variable_name = unserialize($variable->value);
        }
      }
    }
    return $content_types;
  }
}

/**
 * Returns a collection of permissions from content types for the current user.
 *
 * @return array
 *   Array of content types with permissions for each.
 */
function _drupalgap_resource_content_types_user_permissions() {
  $content_types = _drupalgap_resource_content_types_list();
  $content_type_permissions = array();
  foreach ($content_types as $content_type) {
    $content_type_permissions[$content_type->type] = array(
      'create' => user_access("create $content_type->type content"),
      'delete any' => user_access("delete any $content_type->type content"),
      'delete own' => user_access("delete own $content_type->type content"),
      'edit any' => user_access("edit any $content_type->type content"),
      'edit own' => user_access("edit own $content_type->type content"),
    );
  }
  return $content_type_permissions;
}

/**
 * Checks to see if the user has access to a permission.
 *
 * @return boolean
 *   Bool indicating whether or not the user has access to the permission.
 *
 * @see user_access()
 */
function _drupalgap_resource_user_access($data) {
  if (!isset($data['permission'])) {
    return services_error(t('Missing argument permission.'), 406);
  }
  return user_access($data['permission']);
}

/**
 * Performs a user login service resource call and bundles up the drupalgap 
 * system connect resource results as well.
 *
 * @param $username
 *   String The Drupal user name.
 * @param $password
 *   String The Drupal user password.
 *
 * @return array
 *   Array with the user login result and drupalgap system connect result.
 */
function _drupalgap_resource_user_login($username, $password) {
  $results = array();
  
  // Make a call to the user login resource.
  module_load_include('inc', 'services', 'resources/user_resource');
  $results['_user_resource_login'] = _user_resource_login($username, $password);
  
  // If the user login was successful, make a call to the drupalgap system
  // connect resource.
  if ($results['_user_resource_login']) {
    $results['drupalgap_system_connect'] = _drupalgap_resource_system_connect();
  }
  
  return $results;
}

/**
 * Performs a user logout service resource call and bundles up the drupalgap 
 * system connect resource results as well.
 *
 * @return array
 *   Array with the user logout result and drupalgap system connect result.
 */
function _drupalgap_resource_user_logout() {
  $results = array();
  
  // Make a call to the user login resource.
  module_load_include('inc', 'services', 'resources/user_resource');
  $results['_user_resource_logout'] = _user_resource_logout();
  
  // If the user logout was successful, make a call to the drupalgap system
  // connect resource.
  if ($results['_user_resource_logout']) {
    $results['drupalgap_system_connect'] = _drupalgap_resource_system_connect();
  }
  
  return $results;
}

/**
 * Performs a user registration service resource call and bundles up the 
 * drupalgap system connect resource results as well.
 *
 * @param $name
 *   String The Drupal user name.
 * @param $mail
 *   String The Drupal user e-mail address.
 * @param $pass
 *   String The Drupal user password.
 *
 * @return array
 *   Array with the user registration result and drupalgap system connect result.
 */
function _drupalgap_resource_user_register ($name, $mail, $pass) {
  $results = array();
  
  // Make a call to the user login resource.
  module_load_include('inc', 'services', 'resources/user_resource');
  $data = array(
    'name' => $name,
    'mail' => $mail,
    'pass' => $pass,
  );
  $results['_user_resource_create'] = _user_resource_create($data);
  
  // If the user registeration was successful, make a call to the drupalgap system
  // connect resource.
  if ($results['_user_resource_create']) {
    $results['drupalgap_system_connect'] = _drupalgap_resource_system_connect();
  }
  
  return $results;
}

/**
 * Returns a user's roles and permissions.
 *
 * @return array
 *   Array of user roles and their corresponding permissions.
 */
function _drupalgap_resource_user_roles_and_permissions() {
  global $user;
  $uid = $user->uid;
  if ($uid == 0) {
    // Grab permissions for 'anonymous user' role.
    $query = db_select('role_permission', 'rp');
    $query
      ->condition('rp.rid', '1')
      ->fields('rp', array('permission', 'module'));
    $result = $query->execute();
    return $result->fetchAll();
  }
  else {
    // Grab roles for authenticated user.
    $query = db_select('users_roles', 'ur');
    $query
      ->condition('ur.uid', $uid)
      ->fields('ur', array('rid'));
    $result = $query->execute();
    $results = $result->fetchAll();
    if (empty($results)) {
      // The user only has the 'authenticated user' role.
      // Grab permissions for 'anonymous user' role.
      $query = db_select('role_permission', 'rp');
      $query
        ->condition('rp.rid', '2')
        ->fields('rp', array('permission', 'module'));
      $result = $query->execute();
      return $result->fetchAll();
    }
    else {
      // The user has roles other than the 'authenticated user' role.
      $query = db_select('users_roles', 'ur');
      $query
        ->condition('ur.uid', $uid)
        ->fields('ur', array('uid', 'rid'))
        ->fields('r', array('name'))
        ->innerJoin('role', 'r', 'ur.rid = r.rid');
      $query
        ->fields('rp', array('permission', 'module'))
        ->innerJoin('role_permission', 'rp', 'rp.rid = r.rid');
      $result = $query->execute();
      return $result->fetchAll();
    }
  }
}

/**
 * Returns the current user's permissions.
 *
 * @return array
 *   Array of user roles and their corresponding permissions.
 */
function _drupalgap_resource_user_permissions() {
  global $user;
  $uid = $user->uid;
  if ($uid == 0) {
    // Grab permissions for 'anonymous user' role.
    $query = db_select('role_permission', 'rp');
    $query
      ->condition('rp.rid', '1')
      ->fields('rp', array('permission', 'module'));
    $result = $query->execute();
    return $result->fetchAll();
  }
  else {
    // Grab roles for authenticated user.
    $query = db_select('users_roles', 'ur');
    $query
      ->condition('ur.uid', $uid)
      ->fields('ur', array('rid'));
    $result = $query->execute();
    $results = $result->fetchAll();
    if (empty($results)) {
      // The user only has the 'authenticated user' role.
      // Grab permissions for 'anonymous user' role.
      $query = db_select('role_permission', 'rp');
      $query
        ->condition('rp.rid', '2')
        ->fields('rp', array('permission', 'module'));
      $result = $query->execute();
      return $result->fetchAll();
    }
    else {
      // The user has roles other than the 'authenticated user' role.
      $query = db_select('users_roles', 'ur');
      $query
        ->condition('ur.uid', $uid)
        ->fields('ur', array('rid'))
        ->fields('r', array('name'))
        ->innerJoin('role', 'r', 'ur.rid = r.rid');
      $query
        ->fields('rp', array('permission', 'module'))
        ->innerJoin('role_permission', 'rp', 'rp.rid = r.rid');
      $result = $query->execute();
      return $result->fetchAll();
    }
  }
}

/**
 * Returns a collection of variables from the current Drupal site.
 *
 * @return array
 *   Array of variables from the variable table.
 */
function _drupalgap_resource_system_site_settings() {
  // Grab column names from the variable table.
  $names = array(
    'admin_theme',
    'clean_url',
    'date_default_timezone',
    'site_name',
    'theme_default',
    'user_register',
  );
  $sql = "SELECT * FROM {variable} WHERE name IN (:names)";
  $result = db_query($sql, array(':names' => $names));

  $settings = new stdClass();
  if ($result) {
    $settings->variable = new stdClass();
    $variables = $result->fetchAll();
    foreach ($variables as $variable) {
      $name = $variable->name;
      $value = unserialize($variable->value);
      $settings->variable->$name = $value;
    }
  }

  // Add Drupal core verion into settings.
  $settings->variable->drupal_core = "7";

  return $settings;
}

/**
 * Performs service calls to various resources and bundles them all up so the 
 * mobile device gets results, settings and permissions in one request.
 *
 * @param $created
 *   Integer The time at which the last system connect call took place. This is
 *   used to determine what, if any, content/comments/etc have been updated
 *   since the last call took place from the mobile app.
 *
 * @return array
 *   Array of service resources, settings and permissions.
 */
function _drupalgap_resource_system_connect($created = null) {
  global $user;
  $results = array();
  
  // Make a call to the system connect resource.
  module_load_include('inc', 'services', 'resources/system_resource');
  $results['system_connect'] = _system_resource_connect();
  
  // Make calls to various DrupalGap resources.
  $results['site_settings'] = _drupalgap_resource_system_site_settings();
  // TODO - Leave user_roles_and_permissions in for backwards compatability
  // until 7.x-1.4 of the module is released, then remove it.
  $results['user_roles_and_permissions'] = _drupalgap_resource_user_roles_and_permissions();
  $results['user_permissions'] = _drupalgap_resource_user_permissions(array('uid' => $user->uid));
  $results['content_types_list'] = _drupalgap_resource_content_types_list();
  $results['content_types_user_permissions'] = _drupalgap_resource_content_types_user_permissions();
  $results['entity_info'] = entity_get_info();
  $results['field_info_instances']['node'] = field_info_instances('node');
  $results['field_info_instances']['comment'] = field_info_instances('comment');
  $results['field_info_instances']['taxonomy_vocabulary'] = field_info_instances('taxonomy_vocabulary');
  $results['field_info_instances']['taxonomy_term'] = field_info_instances('taxonomy_term');
  $results['field_info_instances']['user'] = field_info_instances('user');
  $results['field_info_fields'] = field_info_fields();
  
  // Add the time at which this call occurred to the result.
  $results['created'] = "" . time();
  
  // Add the last time at which this call occurred, if ever, to the result.
  if ($created != null) {
    //$results['last_created'] = date("Y-m-d h:i:s", $created);
    $results['last_created'] = $created;
  }
  
  return $results;
}

/**
 * Retrieves basic data for  vocabularies.
 *
 * @return array containing associative array(s) of vocabulary data.
 */
function _drupalgap_taxonomy_get_vocabularies() {
  $query = db_select('taxonomy_vocabulary', 'v');
  $query->fields(
    'v',
    array('vid', 'name', 'machine_name', 'description', 'weight')
  )->orderBy('weight', 'ASC');
  $result = $query->execute();
  return $result->fetchAll();
}

/**
 * DrupalGap interface to taxonomy_get_tree().
 *
 * @see taxonomy_get_tree()
 */
function _drupalgap_taxonomy_get_terms($vid, $parent = 0, $max_depth = NULL) {
  $terms = taxonomy_get_tree($vid, $parent, $max_depth);
  return $terms;
}

