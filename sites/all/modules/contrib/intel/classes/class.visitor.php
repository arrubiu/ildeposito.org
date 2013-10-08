<?php
/**
 * @file
 * Used to manage visitor entities.
 * 
 * @author Tom McCracken <tomm@getlevelten.com>
 */

intel_include_library_file('class.visitor.php');

class Visitor extends \LevelTen\Intel\ApiVisitor {

  protected $vid = null;
  protected $vtk = '';
  protected $vtkid = '';
  protected $vtkc = '';
  protected $uid = 0;
  protected $created = 0;
  protected $updated = 0;
  protected $contact_created = 0;
  protected $last_activity = 0;
  protected $name = '';
  protected $email = '';  
  protected $data_updated = 0;
  protected $data = array();
  protected $ext_updated = 0;
  protected $ext_data = array();
  protected $ga_attributes = array();

  /**
   * 
   * @param $id - null|'null'=blank visitor, ''|'user'=use current user, int = vid, any other string is vtk
   */
  public function __construct($id = 'user', $idType = '', $apiClientProperties = array()) {
    global $user;
    // if id null, create blank visitor
    if (!isset($id) || ($id == 'null')) {
      $vtk = null;
    }    
    // otherwise assume use the current visitor
    elseif (($id == 0) || ($id == '') || ($id == 'user')) {
      $vtk = parent::extractVtk();      
      $this->uid = $user->uid;
    }
    // if id is int, assume vid, otherwise vtk
    elseif (is_int($id)) {
      $this->vid = (int)$id;
      $this->load();
      $vtk = $this->vtk;
    }
    // if visitor stdClass object was passed
    elseif (is_object($id) && (!empty($id->vid))) {
      $this->dbRowToProps($id);
      $vtk = $this->vtk;
    }
    elseif (is_string($id) && (strlen($id) >= 10)) {
      $vtk = $id;      
    }
    if (!empty($vtk) && empty($this->vtk)) {
      $this->vtk = $vtk;
      $this->load();
    }
    parent::__construct($vtk, $apiClientProperties);
  }
  
  public function load($params = array()) {
    if (empty($this->vid)) {
      $alias = $this->aliasLoad();
      if (!empty($alias->vid)) {
        $this->vid = $alias->vid;
      }
    }
    
    $query = db_select('intel_visitor', 'v')
      ->fields('v');

    if (!empty($this->vid)) {
      $query->condition('vid', $this->vid);
    }
    elseif (!empty($this->vtk)) {
      $query->condition('vtkid', substr($this->vtk, 0, 20));
    }
    elseif (!empty($this->uid)) {
      $query->condition('uid', $this->uid);
    }
    elseif (!empty($this->email)) {
      $query->condition('email', $this->email);
    }
    else {
      return FALSE;
    }
    try {
      $row = $query->execute()->fetchAssoc();
    } 
    catch (intelException $e) {
      throw new intelException('Unable to load visitor: ' . $e);
    }
    if (!$this->vtk) {
      $this->vtk = $row->vtkid . $row->vtkc;
    }
    $this->dbRowToProps($row);
  }
  
  public function apiLoad($params = array()) {    
    try {
      parent::load($params);
    } 
    catch (Exception $e) {
      throw new Exception('Unable to load api visitor: ' . $e);
    }
  }
  
  private function dbRowToProps($row) {
    if (is_object($row)) {
      $row = (array) $row;
    }
    if (!empty($row['vid'])) {
      foreach ($row AS $k => $v) {
        $this->$k = $v;
      }
      $this->vtk = $this->vtkid . $this->vtkc;
    }    
  }
  
  public function save(){
    $key = array();
    $fields = array();
    if (empty($this->vtk)) {
      $vars = array(
        '!properties' => print_r($this->getProperties(), 1),
        '!get' => print_r($_GET, 1),
        '!cookie' => print_r($_COOKIE, 1),
      );
      watchdog('intel', "vtk missing on visitor save. <br>\n properites=!properties<br>\n<br>\nget=!get<br>\n<br>\ncookie=!cookie", $vars, WATCHDOG_DEBUG);  
    }
    if (!empty($this->vid)) {
      $key['vid'] = $this->vid;
      $fields['vtkid'] = substr($this->vtk, 0, 20);
      $fields['vtkc'] = substr($this->vtk, 20, 12);
    }
    elseif (!empty($this->vtk)) {
      $key['vtkid'] = substr($this->vtk, 0, 20);
      $key['vtkc'] = substr($this->vtk, 20, 12);
    }
    else {
      $fields['vtkid'] = '';
      $fields['vtkc'] = '';      
    }
    $fields['uid'] = $this->uid;
    $fields['name'] = trim($this->name);
    $fields['email'] = trim($this->email);
    $fields['created'] = !empty($this->created) ? $this->created : time();
    $fields['updated'] = time();
    $fields['contact_created'] = $this->contact_created;   
    $fields['last_activity'] = !empty($this->last_activity) ? $this->last_activity : time();   
    $fields['data_updated'] = $this->data_updated;
    $fields['data'] = $this->data;
    $fields['ext_updated'] = $this->ext_updated;
    $fields['ext_data'] = $this->ext_data;

    if (!is_string($fields['data'])) {
      $fields['data'] = serialize($fields['data']);
    }
    if (!is_string($fields['ext_data'])) {
      $fields['ext_data'] = serialize($fields['ext_data']);
    }

    if (empty($this->vid)) {
      $fields = array_merge($fields, $key);
      $query = db_insert('intel_visitor')
        ->fields($fields);
      $this->vid = $query->execute();
    }
    else {
      $query = db_merge('intel_visitor')
        ->key($key)
        ->fields($fields);
      $query->execute();
    }
  }
  
  /**
   * save with alias normalization
   * TODO create this function
   */
  public function merge() {
    $this->save();
  }
  
  public function aliasSave($alias) {
    $query = db_select('intel_visitor_alias', 'a')
      ->fields('a')
      ->condition('vid', $alias['vid'])
      ->condition('field', $alias['field'])
      ->condition('value', $alias['value'], 'LIKE');
    $db = $query->execute()->fetchAssoc();
    
    if (!empty($db['vid'])) {
      $query = db_update('intel_visitor_alias')
        ->fields(array(
          'value' => $alias['value'],
          'updated' => time(),
        ))
        ->condition('vid', $db['vid'])
        ->condition('field', $db['field'])
        ->condition('value', $db['value']); 
      $query->execute();     
    }
    else {
      $alias['updated'] = time();
      $query = db_insert('intel_visitor_alias')
        ->fields($alias);
      $query->execute();      
    }  
  }

  /**
   * checks if a visitor has alternative vtk or email address
   * 
   */
  public function aliasLoad($identifier = '', $type = 'vtk') {  
    $query = db_select('intel_visitor_alias', 'a')
      ->fields('a');
    
    if ($identifier) {
      if ($type == 'email') {
        $query->condition('a.email', $identifier);
      }
      else {
        $query->condition('a.vtkid', substr($identifier, 0, 20));
      }
    }
    elseif (!empty($this->vtk)) {
      $query->condition('a.vtkid', substr($this->vtk, 0, 20));
    }
    elseif (!empty($this->email)) {
      $query->condition('a.email', $this->email);
    }
    $v_alias = $query->innerJoin('intel_visitor', 'v', '%alias.vid = a.vid');
    $query->addField($v_alias, "vtkid", 'actual_vtkid');
    $query->addField($v_alias, "vtkc", 'actual_vtkc');
    $alias = $query->execute()->fetchObject();
    return $alias;
  }

  public function getProperties() {
    $props = (object) get_object_vars($this);
    if (is_string($props->data)) {
      $props->data = unserialize($props->data);
    }
    if (is_string($props->ext_data)) {
      $props->ext_data = unserialize($props->ext_data);
    }
    return $props;
  }
  
  public function getVisitor() {
    return (object) get_object_vars($this);
  }
  
  public function getApiVisitor() {
    return parent::getVisitor();
  }
  
  public function getVid() {
    return $this->vid;
  }
  
  public function getVtk() {
    return $this->vtk;
  }
  
  public function getLabel() {
    if ($this->name) {
      return $this->name;
    }
    else {
      return 'anon (' . substr($this->vtkid, 0, 10) . ')';
    }
  }
  
  public function getVar($scope, $namespace = 'default', $keys = '') {
    $a = explode('_', $scope);
    if ($a[0] == 'api') {
      return parent::getVar($a[1], $namespace, $keys);
    }
    if ($scope == 'ext') {
      $data = $this->ext_data;
    }
    else {
      $data = $this->data;
    }
    if (is_string($data)) {
      $data = unserialize($data);
    }
    if (empty($data[$namespace])) {
      return null;
    }
    $data = $data[$namespace];
    intel_include_library_file("libs/class.intel_data.php");
    return \LevelTen\Intel\IntelData::getVar($data, $keys);
  }
  
  public function updateData($namespace, $value, $keys = '') {
    $this->setVar('data', $namespace, $keys, $value);
    $this->data_updated = time();
  }
  
  public function updateExt($namespace, $value, $keys = '') {
    $this->setVar('ext', $namespace, $keys, $value);
    $this->ext_updated = time();
  }
  
  public function setVar($scope, $namespace, $keys, $value = null) {

    $a = explode('_', $scope);
    if ($a[0] == 'api') {
      return parent::setVar($a[1], $namespace, $keys, $value);
    }
    // check if three arg pattern
    $args = func_get_args();
    if (count($args) == 3) {
      $value = $keys;
      $keys = $namespace;
    }
    else {
      $keys = $namespace . '.' . $keys;
    }
    if ($scope == 'ext') {
      $data = $this->ext_data;
    }
    else {
      $data = $this->data;
    }
    if (is_string($data)) {
      $data = unserialize($data);
    }
    intel_include_library_file("libs/class.intel_data.php");
    $data = \LevelTen\Intel\IntelData::setVar($data, $keys, $value);
    if ($scope == 'ext') {
      $this->ext_data = $data;
      $this->ext_updated = time();
    }
    else {
      $this->data = $data;
      $this->data_updated = time();
    }
  }
  /**
   * TODO manage aliases
   * @param $email
   */
  public function setEmail($email) {
    $this->email = $email;
  }
  
  public function setName($name) {
    $this->name = $name;
  }
  
  public function setContactCreated($time) {
    $this->contact_created = $time;
  }
  
  public function setLastActivity($time) {
    $this->last_activity = $time;
  }
  
  public function __get($name) {
    // unserialize data if needed
    if (($name == 'data') && (is_string($this->data))) {
      $this->data = unserialize($this->data);
    }
    elseif (($name == 'ext_data') && (is_string($this->ext_data))) {
      $this->ext_data = unserialize($this->ext_data);
    }
    // return property if exists
    if (isset($this->$name)) {
      return $this->$name;
    }
    return null;
  }

  public function __isset($name) {
    $v = $this->__get($name);
    return isset($v);
  }
  
  public function __set($name, $value) {
    return $this->$name = $value;
  }
    
  public function __unset($name) {
    if (isset($this->$name)) {
      unset($this->$name);
    }
  }
  
  public function __toString() {
    return "visitor[$this->vtk]";
  }
}