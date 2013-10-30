<?php
/**
 * @file
 *   An example of the classes a backend would need.
 *
 *   Please notice this is just a subset implementation.
 *   It is recommended to use one file per class, but for this example, since
 *   it is not really implementing so much functionallity on any subclass and
 *   it's easier to review one file, it is all here.
 */

class VersioncontrolFakeBackend extends VersioncontrolBackend {
  public $classes = array(
    'repo'      => 'VersioncontrolFakeRepository',
    'operation' => 'VersioncontrolFakeOperation',
    'item'      => 'VersioncontrolFakeItem',
    'event'     => 'VersioncontrolFakeEvent',
  );
  public $classesControllers = array(
    'event'     => 'VersioncontrolFakeEventController',
  );

  public function __construct() {
    // The user-visible name of the VCS.
    $this->name = 'FakeVCS';
    // A short description of the VCS, if possible not longer than one or
    // two sentences.
    $this->description = t('FakeVCS is a version control system that is specifically capable in doing everything that any other version control system might ever do.');
    // Our example VCS supports all possible capabilities, but they are
    // optional.
    $this->capabilities = array(
        // Able to retrieve a file or its revision number based on a global
        // revision identifier.
        VERSIONCONTROL_CAPABILITY_ATOMIC_COMMITS,

        // The version control system assigns revisions not only to files
        // but also to directories.
        VERSIONCONTROL_CAPABILITY_DIRECTORY_REVISIONS,
    );
  }

  function isUsernameValid(&$username) {
    // Continuing the email-style username example from above.
    return valid_email_address($username);
  }
}

class VersioncontrolFakeRepository extends VersioncontrolRepository {
  public function formatRevisionIdentifier($revision, $format = 'full') {
    switch ($format) {
      case 'full':
      case 'short':
      default:
        // Suppose we're a distributed VCS backend and have an SHA-1 hash:
        // $revision == '30581e4ec3347d1294ec05a91eec1a8588e5993c'
        // Let's return only the first 12 characters of the revision identifier,
        // like Mercurial (including hgweb) does by default.
        return drupal_substr($revision, 0, 12);

        // SVN also wants to format revisions in a slightly custom way:
        return 'r' . $revision;
    }
  }

  public function generateCodeArrivalEvent($data) {
    // First, let's see the event is known.
    if (!empty($data['elid'])) {
      return $this->loadEvent($data['elid']);
    }
    // Assuming FakeVCS passes only one commit at a time, and provides the
    // following output format:
    //     rev: 30581e4ec3347d1294ec05a91eec1a8588e5993c
    //     foo: bar
    $payload = explode("\n", $data['data']);
    list($push_revision_line, $foo_line) = explode("\n", $payload);
    list(, $push_revision) = explode(': ', $push_revision_line);
    list(, $foo) = explode(': ', $foo_line);

    // Prepare for constructor.
    $obj = new stdClass();
    $obj->uid = empty($data['uid']) ? 0 : $data['uid'];
    $obj->timestamp = empty($data['timestamp']) ? time() : $data['timestamp'];
    $obj->repository = $data['repository'];
    $obj->foo = $foo;
    $obj->pushRevision = $push_revision;

    return $this->getBackend()->buildEntity('event', $obj);
  }

  public function generateRawData($event) {
    $output = sprintf("rev: %s\nfoo: %s", $event->revision, $event->foo);
  }

  public function finalizeEvent(VersioncontrolEvent $event) {
  }
}

class VersioncontrolFakeOperation extends VersioncontrolOperation {
  public $parent_commit = '';

  // Asumming for fakevcs is better retrieving information if we have the
  // parent commit revision, we interact to have CRUD around that in out own
  // table.

  protected function backendInsert($options) {
    db_insert('versioncontrol_fakevcs_operations')
      ->fields(array(
        'vc_op_id' => $this->vc_op_id,
        'parent_commit' => $this->parent_commit,
      ))
      ->execute();
  }

  protected function backendUpdate($options) {
    db_update('versioncontrol_fakevcs_operations')
      ->fields(array(
        'vc_op_id' => $this->vc_op_id,
        'parent_commit' => $this->parent_commit,
      ))
      ->condition('vc_op_id', $this->vc_op_id)
      ->execute();
  }

  protected function backendDelete($options) {
    db_delete('versioncontrol_fakevcs_operations')
      ->condition('vc_op_id', $this->vc_op_id)
      ->execute();
  }
}

class VersioncontrolFakeOperationController extends VersioncontrolOperationController {
  /**
   * Extend the base query with the fakevcs backend's additional data in
   * {versioncontrol_fakevcs_operations}.
   *
   * @return SelectQuery
   */
  protected function buildQueryBase($ids, $conditions) {
    $query = parent::buildQueryBase($ids, $conditions);
    $alias = $this->addTable($query, 'versioncontrol_fakevcs_operations', 'vcfo', 'base.vc_op_id = vcfo.vc_op_id');
    $query->fields($alias, drupal_schema_fields_sql('versioncontrol_fakevcs_operations'));
    return $query;
  }
}

class VersioncontrolFakeItem extends VersioncontrolItem {}

class VersioncontrolGitEvent extends VersioncontrolEvent {
  public $pushRevision = NULL;
  public $foo = NULL;

  public function build($args = array()) {
    parent::build($args);
    // Map db field to data member.
    if (isset($this->push_revision)) {
      $this->pushRevision= $this->push_revision;
    }
    unset($this->push_revision);
  }

  protected function backendInsert($options = array()) {
    db_insert('versioncontrol_fakevcs_event')
      ->fields(array(
        'elid' => $this->vc_op_id,
        'push_revision' => $this->pushRevision,
        'foo' => $this->foo,
      ))
      ->execute();
  }

  protected function backendUpdate($options = array()) {
    db_update('versioncontrol_fakevcs_event')
      ->fields(array(
        'elid' => $this->vc_op_id,
        'push_revision' => $this->pushRevision,
        'foo' => $this->foo,
      ))
      ->condition('vc_op_id', $this->vc_op_id)
      ->execute();
  }

  protected function backendDelete($options = array()) {
    db_delete('versioncontrol_fake_event')
      ->condition('elid', $this->elid)
      ->execute();
  }
}

class VersioncontrolFakeEventController extends VersioncontrolEventController {
  /**
   * Extend the base query with the fake backend's additional data in
   * {versioncontrol_git_event}.
   */
  protected function attachExtendedEventData($elids, &$queried_entities) {
    $result = db_select('versioncontrol_fake_event', 'vfe')
      ->fields('vfe')
      ->condition('vfe.elid', $elids)
      ->execute();
    foreach ($result as $row) {
      $row = (array) $row;
      $queried_entities[$row['elid']]->revision = $row['revision'];
      $queried_entities[$row['elid']]->foo = $row['foo'];
    }
  }
}
