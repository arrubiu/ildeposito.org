<?php
/**
 * @file
 * This plugin provides support for gitphp, the git repository browser
 * in php.
 */

$plugin = array(
  'vcs' => 'git',
  'title' => t('GitPHP URL autogenerator'),
  'url_templates' => array(
    'repository_view' => '%base_url/?p=%repo_name&a=summary',
    'commit_view' => '%base_url/?p=%repo_name&a=commit&h=%revision',
    'file_log_view' => '%base_url/?p=%repo_name&a=history&h=%revision&f=%path',
    'directory_log_view' => '%base_url/?p=%repo_name&a=history&f=%path&h=%revision%branch',
    'file_view' => '%base_url/?p=%repo_name&a=blob&f=%path&h=%revision%branch',
    'directory_view' => '%base_url/?p=%repo_name&a=tree&f=%path&h=%revision%branch',
    'diff' => '%base_url/?p=%repo_name&a=blobdiff&f=%path&h=%new_blob_hash&hp=%old_blob_hash&hb=%old_revision',
  ),
  'handler' => array(
    'class' => 'VersioncontrolRepositoryUrlHandlerGitphp',
    'file' => 'VersioncontrolRepositoryUrlHandlerGitphp.inc',
    'path' => drupal_get_path('module', 'versioncontrol_git') . '/includes/plugins/webviewer_url_handlers',
    'parent' => 'none',
  ),
);
