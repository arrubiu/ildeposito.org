<?php

/**
 * @file
 * DrupalGap's implementation of Hooks provided by Services
 * for the definition of new service resources.
 */

 /**
  * Defines function signatures for resources available to services.
  */
function drupalgap_services_resources() {
  $drupalgap_resource = array(
    'drupalgap_content' => array(
      'actions' => array(
        'content_types_list' => array(
          'help' => t('Gets a list of Drupal content types.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_resource_content_types_list',
          'args' => array(),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
        ),
        'content_types_user_permissions' => array(
          'help' => t('Returns a list of permissions the current user has for
           all content types.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_resource_content_types_user_permissions',
          'args' => array(),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
        ),
      ),
    ),
    /*'drupalgap_field' => array(
      'actions' => array(
        'field_info_instances' => array(
          'help' => t('Retrieves information about field instances.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_field_info_instances',
          'args' => array(
            array(
              'name' => 'entity_type',
              'optional' => TRUE,
              'source' => 'data',
              'description' => 'The entity type for which to return instances.',
              'type' => 'string',
            ),
            array(
              'name' => 'bundle_name',
              'optional' => TRUE,
              'source' => 'data',
              'description' => 'The bundle name for which to return instances.',
              'type' => 'string',
            ),
          ),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
        ),
      ),
    ),*/
    'drupalgap_system' => array(
      'actions' => array(
        'site_settings' => array(
          'help' => t('Gets a list of various drupal settings and variables.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_resource_system_site_settings',
          'args' => array(),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
        ),
        'connect' => array(
          'help' => t('The DrupalGap system connect with bundled result data.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_resource_system_connect',
          'args' => array(),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'created',
              'type' => 'int',
              'description' => t('The last time the system connect was called.'),
              'source' => array('data' => 'created'),
              'optional' => TRUE,
            ),
          ),
        ),
      ),
    ),
    'drupalgap_taxonomy' => array(
      'actions' => array(
        'get_vocabularies' => array(
          'help' => t('Returns a list of vocabularies.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_taxonomy_get_vocabularies',
          'args' => array(),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('drupalgap get vocabularies'),
          'access arguments append' => TRUE,
        ),
        'get_terms' => array(
          'help' => t('Returns a list of terms for a vocabulary.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_taxonomy_get_terms',
          'args'     => array(
            array(
              'name'         => 'vid',
              'type'         => 'int',
              'description'  => t('The vocabulary id to retrieve.'),
              'source'       => array('data' => 'vid'),
              'optional'     => FALSE,
            ),
            array(
              'name'         => 'parent',
              'type'         => 'int',
              'description'  => t('The term ID under which to generate the tree. If 0, generate the tree for the entire vocabulary.'),
              'source'       => array('data' => 'parent'),
              'default value' => 0,
              'optional'     => TRUE,
            ),
            array(
              'name'         => 'maxdepth',
              'type'         => 'int',
              'description'  => t('The number of levels of the tree to return. Leave NULL to return all levels.'),
              'source'       => array('data' => 'maxdepth'),
              'default value' => NULL,
              'optional'     => TRUE,
            ),
          ),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('drupalgap get terms'),
          'access arguments append' => TRUE,
        ),
      ),
    ),
    'drupalgap_user' => array(
      'actions' => array(
        'access' => array(
          'help' => t('A service that performs a user_access function call for
           the current user.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_resource_user_access',
          'args' => array(
            array(
              'name' => 'permission',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'The permission, such as "administer nodes",' .
              ' being checked for.',
              'type' => 'string',
            ),
          ),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
        ),
        'login' => array(
          'help' => t('The DrupalGap user login bundle resource.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_resource_user_login',
          'args' => array(),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'username',
              'type' => 'string',
              'description' => t('The Drupal username.'),
              'source' => array('data' => 'username'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'password',
              'type' => 'string',
              'description' => t("The Drupal user's password."),
              'source' => array('data' => 'password'),
              'optional' => FALSE,
            ),
          ),
        ),
        'logout' => array(
          'help' => t('The DrupalGap user logout bundle resource.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_resource_user_logout',
          'args' => array(),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
          'args' => array(),
        ),
        'register' => array(
          'help' => t('The DrupalGap user register bundle resource.'),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_resource_user_register',
          'args' => array(),
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'name',
              'type' => 'string',
              'description' => t('The desired Drupal user name.'),
              'source' => array('data' => 'name'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'mail',
              'type' => 'string',
              'description' => t("The desired Drupal user's e-mail address."),
              'source' => array('data' => 'mail'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'pass',
              'type' => 'string',
              'description' => t("The desired Drupal user's password."),
              'source' => array('data' => 'pass'),
              'optional' => FALSE,
            ),
          ),
        ),
        'roles_and_permissions' => array(
          'help' => t("Retrieves a user's roles and permissions."),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_resource_user_roles_and_permissions',
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
        ),
        'permissions' => array(
          'help' => t("Retrieves the current user's permissions."),
          'file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'callback' => '_drupalgap_resource_user_permissions',
          'access callback' => '_drupalgap_resource_access',
          'access callback file' => array(
            'type' => 'inc',
            'module' => 'drupalgap',
            'name' => 'drupalgap.resource',
          ),
          'access arguments' => array('access content'),
          'access arguments append' => TRUE,
        ),
      ),
    ),
  );
  return $drupalgap_resource;
}

