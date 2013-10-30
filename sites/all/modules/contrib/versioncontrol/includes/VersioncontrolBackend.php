<?php
/**
 * @file
 * Backend class
 */

/**
 * Backend base class
 *
 * @abstract
 */
abstract class VersioncontrolBackend {
  /**
   * The user-visible name of the VCS.
   *
   * @var string
   */
  public $name;

  /**
   * The machine name of the backend. This value is used in
   * {versioncontrol_repositories}.vcs, and ubiquitously elsewhere in the code
   * to refer to the backend.
   *
   * @var string
   */
  public $type = '';

  /**
   * A short description of the backend, if possible not longer than
   * one or two sentences.
   *
   * @var string
   */
  public $description;

  /**
   * An array listing optional capabilities, in addition
   * to the required functionality like retrieval of detailed
   * commit information. Array values can be an arbitrary combination
   * of VERSIONCONTROL_CAPABILITY_* values. If no additional capabilities
   * are supported by the backend, this array will be empty.
   *
   * @var array
   */
  public $capabilities;

  /**
   * Classes which this backend will instantiate when acting as a factory.
   */
  public $classesEntities = array();

  public $classesControllers = array();

  /**
   * An array of the default views for use in the Versioncontorl API interfaces.
   */
  public $defaultViews = array();

  /**
   * An array of instantiated VersioncontrolEntityController objects through
   * which all requests to load objects pass.
   *
   * @var array
   */
  protected $controllers = array();

  /**
   * Restore controller caching defaults to their state prior to forcing them
   * all to no caching mode.
   *
   * Convenience.
   *
   * @var array
   *
   * @see VersioncontrolBackend::disableControllerCaching()
   */
  protected $controllerCachingDefaults = array();

  /**
   * Internal state var indicating that controller caching defaults have been
   * toggled off. Allows us to preserve idempotence.
   * @var bool
   */
  protected $ccToggled = FALSE;

  /**
   * To prevent massive numbers of reflection object instanciations, we cache
   * the reflection objects we've created. Memory cost is minimal.
   *
   * @var array
   */
  protected $reflections;

  /**
   * An array of interfaces that plugins must comply with.
   *
   * @var array
   */
  protected $pluginInterfaces = array(
    'repo' => array(
      'repomgr' => 'VersioncontrolRepositoryManagerWorkerInterface',
      'reposync' => 'VersioncontrolRepositoryHistorySynchronizerInterface',
      'webviewer_url_handler' => 'VersioncontrolWebviewerUrlHandlerInterface',
      'committer_mapper' => 'VersioncontrolUserMapperInterface',
      'author_mapper' => 'VersioncontrolUserMapperInterface',
      'auth_handler' => 'VersioncontrolAuthHandlerInterface',
    ),
  );

  /**
   * Configure the entities and controllers.
   */
  public function __construct() {
    // Add defaults to $this->classes
    $this->classesControllers += array(
      'repo'      => 'VersioncontrolRepositoryController',
      'operation' => 'VersioncontrolOperationController',
      'item'      => 'VersioncontrolItemController',
      'branch'    => 'VersioncontrolBranchController',
      'tag'       => 'VersioncontrolTagController',
      'event'     => 'VersioncontrolEventController',
    );
    // FIXME currently all these classes are abstract, so this won't work. Decide
    // if this should be removed, or if they should be made concrete classes
    $this->classesEntities += array(
      'repo'      => 'VersioncontrolRepository',
      'operation' => 'VersioncontrolOperation',
      'item'      => 'VersioncontrolItem',
      'branch'    => 'VersioncontrolBranch',
      'tag'       => 'VersioncontrolTag',
      'event'     => 'VersioncontrolEvent',
    );
  }

  /**
   * Instantiate and build a VersioncontrolEntity object using provided data.
   *
   * This is the central factory method that should ultimately be used to
   * produce any VersioncontrolEntity-descended object for any backend. It does
   * two important things:
   *   - Provides a central point of control over what classes are used to
   *     instanciate what string 'type', as dictated by $this->classesEntities.
   *   - Ensure the backend can handle the type requested, and that the class
   *     it wants to instantiate descends from VersioncontrolEntity.
   *
   * @throws Exception
   *
   * @param string $type
   *   A string indicating the type of entity to be created. Should match with a
   *   key in $this->classesEntities.
   * @param mixed $data
   *   Either a stdClass object or an associative array of data to build the
   *   object with.
   * @return VersioncontrolEntity
   *   The instantiated and built object.
   */
  public function buildEntity($type, $data) {
    // Ensure this backend knows how to handle the entity type requested
    if (empty($this->classesEntities[$type])) {
      throw new Exception("Invalid entity type '$type' requested; not supported by " . __CLASS__, E_ERROR);
    }

    $class = $this->classesEntities[$type];

    // Ensure the class actually exists; throw an error if it does not.
    if (!class_exists($class)) {
      throw new Exception("Nonexistent class '$class' specified by " . __CLASS__ . " backend for requested type '$type' when attempting to build a Versioncontrol entity.", E_ERROR);
    }

    // Ensure the class to create comes from VersioncontrolEntityInterface.
    else {
      if (empty($this->reflections[$class])) {
        $this->reflections[$class] = new ReflectionClass($class);
      }
      if (!$this->reflections[$class]->implementsInterface('VersioncontrolEntityInterface')) {
        throw new Exception("Invalid class '$class' specified by " . __CLASS__ . " backend for requested type '$type' when attempting to build a Versioncontrol entity; class does not implement VersioncontrolEntityInterface.", E_ERROR);
      }
    }

    // If we're not building a repository object, snag the repo object and pass
    // it to the object builder.
    if ($type !== 'repo' && empty($data->repository) && !empty($data->repo_id)) {
      $data->repository = $this->loadEntity('repo', $data->repo_id);
    }

    $obj = new $this->classesEntities[$type]($this);
    $obj->build($data);
    return $obj;
  }

  /**
   * Loads entities via the specified controller type, instantiates
   * VersioncontrolEntity-descended objects from them, and returns them.
   *
   * This is the main entry point for all entity loaders, and its behavior is
   * largely consistent across entity types and backends. Client code will
   * never need to call this directly, but all load*() calls on other objects
   * will pass through here eventually.
   *
   * @param string $controller
   *   The type of object being loaded (e.g., 'repo', 'branch', 'tag'.).
   * @param array $ids
   *   An array of numeric primary key ids for the entity being loaded. The name
   *   of the primary key varies by entity, but if given, only entities matching
   *   whose primary keys match these numeric ids be returned.
   *
   * @param $conditions
   *   An associative array of additional conditions. These will be passed to
   *   the entity controller and composed into the query. The array should be
   *   key/value pairs with the field name as key, and desired field value as
   *   value. The value may also be an array, in which case the IN operator is
   *   used. For example, passing array('name' => array('foo', 'bar') will
   *   add a WHERE clause using the 'name' field on the base table and limiting
   *   results to values matching 'foo' or 'bar'.
   *
   * @param array $options
   *   Options that govern certain ways in which the controller will behave
   *   during load. The most important ones available in all controllers are:
   *     #- 'may cache': whether or not the results of this query can be fetched
   *        from and/or stored in memory by the controller.
   *     #- 'callback' => allows the client to specify an optional callback
   *
   * @return array
   *   Returns an array of VersioncontrolEntity-descended objects, typically
   *   keyed by the objects' primary keys.
   */
  public function loadEntities($controller, $ids = array(), $conditions = array(), $options = array()) {
    return $this->getController($controller)->load($ids, $conditions, $options);
  }

  /**
   * Returns the controller of the type named by the argument, instantiating it
   * if necessary.
   *
   * @throws Exception
   *
   * @param string $type
   *   The type of controller to return. The class to use is determined by the
   *   hashtable in VersioncontrolBackend::$classesControllers.
   *
   * @return VersioncontrolEntityController
   */
  public function getController($type) {
    if (!isset($this->controllers[$type])) {
      if (!isset($this->classesControllers[$type])) {
        $msg = t("Invalid controller type %type requested against @class.", array('%type' => $type, '@class' => __CLASS__));
        throw new Exception($msg, E_ERROR);
      }
      $class = $this->classesControllers[$type];
      $this->controllers[$type] = new $class();
      $this->controllers[$type]->setBackend($this);
    }
    return $this->controllers[$type];
  }

  /**
   * Disable object caching in the controller for all subsequent load calls
   * during this request.
   *
   * This is a considerable convenience method, as it makes for very awkward
   * calls to disable the caching manually on a per-load basis, and when
   * disabling caching is necessary, it's often necessary for a string of
   * queries.
   */
  public function disableControllerCaching() {
    if (FALSE === $this->ccToggled) {
      foreach ($this->classesControllers as $type => $class) {
        $controller = $this->getController($type);
        $this->controllerCachingDefaults[$type] = $controller->defaultOptions['may cache'];
        $controller->defaultOptions['may cache'] = FALSE;
      }
      $this->ccToggled = TRUE;
    }
  }

  /**
   * Restore controller caching settings to their defaults prior to a call to
   * VersioncontrolBackend::disableControllerCaching().
   */
  public function restoreControllerCachingDefaults() {
    if (TRUE === $this->ccToggled) {
      foreach ($this->classesControllers as $type => $class) {
        if (!empty($this->controllerCachingDefaults[$type])) {
          $controller = $this->getController($type);
          $controller->defaultOptions['may cache'] = $this->controllerCachingDefaults[$type];
        }
      }
      $this->ccToggled = FALSE;
    }
  }

  /**
   * Perform a load operation that is expected to produce a single
   * VersioncontrolEntity object.
   *
   * Convenience function that helps simplify other code which is only
   * interested in loading a single object. All parameters pass straight through
   * to VersioncontrolBackend::loadEntities(), with the exception of the
   * $ids parameter, which is normalized to an array as an additional
   * convenience for callers.
   *
   * @return VersioncontrolEntity
   *
   * @see VersioncontrolBackend::loadEntities()
   */
  public function loadEntity($controller, $ids = array(), $conditions = array(), $options = array()) {
    // Normalize the $ids parameter to an array, further convenience for callers
    if (!is_array($ids)) {
      $ids = array($ids);
    }

    $results = $this->loadEntities($controller, $ids, $conditions, $options);

    // Pop the first item off the result set and return it.
    return reset($results);
  }

  /**
   * Augment a select query with options specific to this backend.
   *
   * This method is fired by entity controllers whenever the backend type is
   * known prior to the issuing of the query.
   *
   * @param SelectQuery $query
   *   The query object being built.
   * @param string $entity_type
   *   The type of entity being loaded.
   */
  public function augmentEntitySelectQuery($query, $entity_type) {}

  /**
   * Get the user-visible version of a commit identifier a.k.a.
   * 'revision', as plaintext. By default, this function returns the
   * operation's revision if that property exists, or its vc_op_id
   * identifier as fallback.
   *
   * Version control backends can, however, choose to implement their
   * own version of this function, which for example makes it possible
   * to cut the SHA-1 hash in distributed version control systems down
   * to a readable length.
   *
   * @param $revision
   *   The unformatted revision, as given in $operation->revision
   *   or $item->revision (or the respective table columns for those values).
   *
   * @param $format
   *   Either 'full' for the original version, or 'short' for a more compact form.
   *   If the commit identifier doesn't need to be shortened, the results can
   *   be the same for both versions.
   */
  public function formatRevisionIdentifier($revision, $format = 'full') {
    return $revision;
  }

  /**
   * Verify that a plugin object conforms to the required interface.
   *
   * @param mixed $entity
   *   A VersioncontrolEntity object, or string name of a VersioncontrolEntity
   *   class, for which we are verifying a plugin.
   * @param string $slot
   *   The plugin slot which the plugin is being used for; determines which
   *   interface will be checked against.
   * @param object $plugin_object
   *   An instanciated plugin object.
   */
  public function verifyPluginInterface($entity, $slot, $plugin_object) {
    $entity_class = $entity instanceof VersioncontrolEntity ? get_class($entity) : $entity;
    $type = array_search($entity_class, $this->classesEntities);
    if (!empty($this->pluginInterfaces[$type][$slot]) && !($plugin_object instanceof $this->pluginInterfaces[$plugin_slot])) {
      $vars = array(
        '%plugin_class' => get_class($plugin_object),
        '%entity_class' => $entity_class,
        '%slot' => $slot,
        '%interface' => $this->pluginInterfaces[$type][$plugin_slot],
      );
      $errstring = "Plugin class '%class' used in slot '%slot' by entity class '%entity_class' does not implement required interface '%interface'.";
      watchdog('versioncontrol', $errstring, $vars, WATCHDOG_ERROR);
      throw new Exception(strtr($errstring, $vars), E_ERROR);
    }
  }

  /**
   * Return the most accurate guess on what the VCS username for a Drupal user
   * might look like in the repository's account.
   *
   * @param $user
   *  The Drupal user who wants to register an account.
   */
  public function usernameSuggestion($user) {
    return strtr(drupal_strtolower($user->name),
      array(' ' => '', '@' => '', '.' => '', '-' => '', '_' => '', '.' => '')
    );
  }

  /**
   * Determine if the vcs_username is valid for this backend.
   *
   * @param $vcs_username
   *  The vcs_username to check. It is passed by reference so if the
   *  vcs_username is valid but needs minor adaptions (such as cutting
   *  away unneeded parts) then it the backend can modify it before
   *  returning the result.
   *
   * @return
   *   TRUE if the username is valid, FALSE if not.
   */
  public function isUsernameValid(&$username) {
    if (!preg_match('/^[a-zA-Z0-9]+$/', $username)) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Retrieves the default plugin for the backend.
   *
   * @param $plugin_type
   *   The ctools plugin type of the plugin name to be retrieved.
   *
   * @return string
   *   The name of the default plugin to be used.
   */
  public function getDefaultPluginName($plugin_type) {
    // Do not provide default plugin names on the base backend.
    return FALSE;
  }

}
