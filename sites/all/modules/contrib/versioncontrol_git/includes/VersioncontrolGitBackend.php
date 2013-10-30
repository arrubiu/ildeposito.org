<?php

class VersioncontrolGitBackend extends VersioncontrolBackend {

  public $type = 'git';

  public $classesEntities = array(
      'repo' => 'VersioncontrolGitRepository',
      'account' => 'VersioncontrolGitAccount',
      'operation' => 'VersioncontrolGitOperation',
      'item' => 'VersioncontrolGitItem',
      'event' => 'VersioncontrolGitEvent',
    );

  public $classesControllers = array(
    'repo' => 'VersioncontrolGitRepositoryController',
    'operation' => 'VersioncontrolGitOperationController',
    'item' => 'VersioncontrolGitItemController',
    'event' => 'VersioncontrolGitEventController',
  );

  public $defaultViews = array(
    'project_global_commit_view' => 'vc_git_project_global_commits',
    'project_user_commit_view' => 'vc_git_project_user_commits',
    'project_commit_view' => 'vc_git_project_commit_view',
    'individual_commit_view' => 'vc_git_individual_commit',
  );

  public function __construct() {
    parent::__construct();
    $this->name = 'Git';
    $this->description = t('Git is a fast, scalable, distributed revision control system with an unusually rich command set that provides both high-level operations and full access to internals.');
    $this->capabilities = array(
        // Use the commit hash for to identify the commit instead of an individual
        // revision for each file.
        VERSIONCONTROL_CAPABILITY_ATOMIC_COMMITS
    );
  }

  /**
   * Overwrite to get short sha-1's
   */
  public function formatRevisionIdentifier($revision, $format = 'full') {
    switch ($format) {
      case 'short':
        // Let's return only the first 7 characters of the revision identifier,
        // like git log --abbrev-commit does by default.
        return substr($revision, 0, 7);
      case 'full':
      default:
        return $revision;
    }
  }

  /**
   * Provide default plugins.
   */
  public function getDefaultPluginName($plugin_type) {
    // Use our reposync and repomgr provided plugin as default.
    if ($plugin_type == 'reposync' || $plugin_type == 'repomgr') {
      return 'git_default';
    }
  }
}
