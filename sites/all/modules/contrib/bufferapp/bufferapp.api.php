<?php

/**
 * @file
 * API documentation file for Buffer.
 */

/**
 * Allows modules to alter the default Buffer behaviour.
 *
 * @param $node
 *  Node
 * @param $data
 *  An array with data to pass to Buffer.
 *
 * @see buffed_send_update()
 */
function hook_bufferapp_data_alter(&$data, $node = NULL) {
  $data['text'] = 'My edited text';
}