<?php

/**
 * Service wrapper to count a flag on a entity.
 *
 * @param $data
 *   An associative array containing POSTed arguments.
 *   - flag_name: The flag name.
 *   - entity_id: The entity ID that should be flagged.
 *
 * @return
 *   A object contain the number which shows how many users flagged a entity.
 */
function alterator_users_flags($data) {
  $account = reset(entity_uuid_load('user', array($data)));

  if ($flags = flag_get_user_flags('node', NULL, $account->uid)) {
    unset($flags['da_rivedere']);
    foreach ($flags as $name => $value) {
      foreach ($value as $object) {
        $uuids[$name][] = array(
          'flag_name' => $name,
          'node_uuid' => reset(entity_get_uuid_by_id('node', array($object->entity_id))),
          'timestamp' => $object->timestamp,
          'weight' => $object->weight,
        );
      }
    }

    return $uuids;
  }
  else {
    return FALSE;
  }
}

function alterator_users_hybridauth($data) {

  $result = db_query('SELECT uid FROM {users} WHERE uuid = :uuid', array(':uuid' => $data));
  foreach ($result as $record) {
    $uid = $record->uid;
  }

  $result = db_query('SELECT * FROM {hybridauth_identity} WHERE uid = :uid', array(':uid' => $uid));
  foreach ($result as $record) {
    $results[] = $record;
  }
  return $results;
}


function alterator_media_uri($data) {

  $result = db_query('SELECT uri FROM {file_managed} WHERE uuid = :uuid', array(':uuid' => $data));
  foreach ($result as $record) {
    $uri = $record->uri;
  }
  return $uri;
}

function alterator_comment_pid($data) {

  $result = db_query('SELECT uuid FROM {comment} WHERE cid = :cid', array(':cid' => $data));
  foreach ($result as $record) {
    $uuid = $record->uuid;
  }
  return $uuid;
}