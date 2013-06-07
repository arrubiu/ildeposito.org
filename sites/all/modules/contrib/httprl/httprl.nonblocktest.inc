<?php

/**
 * @file
 * Functions used to test loopback connections.
 */

/**
 * Menu Callback; Release a lock if the right conditions are met.
 */
function httprl_nonblockingtest_page() {
  // exit if
  //  The id is not set.
  //  The key is not set.
  //  The id does not start with httprl_.
  //  The key does not match the md5 of drupal_get_private_key().
  if (   empty($_GET['id'])
      || empty($_GET['key'])
      || strpos($_GET['id'], 'httprl_') !== 0
      || $_GET['key'] != md5(httprl_drupal_get_private_key())
        ) {
    httprl_fast403();
  }

  // Release the lock, echo out that the lock was cleared and exit.
  httprl_lock_release($_GET['id']);

  echo t('lock @id cleared', array('@id' => $_GET['id']));

  // Exit Script.
  httprl_call_exit();
}
