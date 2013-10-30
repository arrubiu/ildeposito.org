<?php
/**
 * @file
 * Git backend for Version Control API - Provides Git commit information and
 * account management as a pluggable backend.
 *
 * Copyright 2008 by Jimmy Berry ("boombatower", http://drupal.org/user/214218)
 * Copyright 2009 by Cornelius Riemenschneider ("CorniI", http://drupal.org/user/136353)
 */

 /**
  * Theme function for VersioncontrolGitEvent.
  *
  * @param VersioncontrolGitEvent $event
  *   The VersioncontrolGitEvent object to generate a text string from.
  *
  * @return string
  */
function theme_versioncontrol_git_event($variables) {
  $refs = array();
  $event = $variables['event'];

  foreach ($event as $event_ref) {
    // @todo Recover the commit listing per ref, but not from here, we are at
    //       theme layer, so we are not suppossed to load from database.
    switch ($event_ref->reftype) {
      case VERSIONCONTROL_GIT_REFTYPE_BRANCH:
        if ($event_ref->eventDeletedMe()) {
          $refs[] = t('Branch !branch was deleted.', array('!branch' => $event_ref->refname));
        }
        else {
          $ref = array();

          if ($event_ref->eventCreatedMe()) {
            $ref['data'] = t('Branch !branch was created.', array('!branch' => $event_ref->refname));
          }
          else {
            $ref['data'] = t('Branch !branch was updated.', array('!branch' => $event_ref->refname));
          }

          $refs[] = $ref;
        }
        break;
      case VERSIONCONTROL_GIT_REFTYPE_TAG:
        if ($event_ref->eventCreatedMe()) {
          $refs[] = t('Tag !tag was created and points to !commit.', array('!tag' => $event_ref->refname, '!commit' => theme('versioncontrol_git_operation', array('operation' => $event_ref->getNewCommit()))));
        }
        elseif ($event_ref->eventDeletedMe()) {
          $refs[] = t('Tag !tag was deleted.', array('!tag' => $event_ref->refname));
        }
        break;
    }
  }

  return theme('item_list', array('items' => $refs));
}

/**
 * Theme function for VersioncontrolGitOperation.
 *
 * @param VersioncontrolGitOperation $operation
 *   The VersioncontrolGitOperation object to generate a text string from.
 *
 * @return string
 */
function theme_versioncontrol_git_operation($variables) {
  $operation = $variables['operation'];
  $revision = $operation->getBackend()->formatRevisionIdentifier($operation->revision, 'short');
  $revision_link = $operation->getRepository()->getUrlHandler()->getCommitViewUrl($revision);
  $revision = (!empty($revision_link) ? $revision_link : $revision);

  return t('!revision: !message', array('!revision' => $revision, '!message' => check_plain(truncate_utf8($operation->message, 100, FALSE, TRUE))));
}
