<?php
/**
 * @file
 * This plugin provides support for cgit.
 */

$plugin = array(
  'vcs' => 'git',
  'title' => t('cgit URL autogenerator'),
  'url_templates' => array(
    'repository_view' => '%base_url/%repo_name',
    'commit_view' => '%base_url/%repo_name/commit/?id=%revision',
    'file_log_view' => '%base_url/%repo_name/log/%path%branch',
    'directory_log_view' => '%base_url/%repo_name/log/%path%branch',
    'file_view' => '%base_url/%repo_name/tree/%path?id=%revision%branch',
    'directory_view' => '%base_url/%repo_name/tree/%path?id=%revision%branch',
    // @todo does cgit support diffing arbitrary files on different revisions?
    'diff' => '',
  ),
  'handler' => array(
    'class' => 'VersioncontrolRepositoryUrlHandlerCgit',
    'file' => 'VersioncontrolRepositoryUrlHandlerCgit.inc',
    'path' => drupal_get_path('module', 'versioncontrol_git') . '/includes/plugins/webviewer_url_handlers',
    'parent' => 'none',
  ),
);
