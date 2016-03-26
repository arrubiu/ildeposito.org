<?php
/**
 * @file
 * ildeposito_media.ds.inc
 */

/**
 * Implements hook_ds_view_modes_info().
 */
function ildeposito_media_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'header';
  $ds_view_mode->label = 'Header';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['header'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'only_image';
  $ds_view_mode->label = 'Only image';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['only_image'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'video_grande';
  $ds_view_mode->label = 'Video grande';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['video_grande'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'video_piccolo';
  $ds_view_mode->label = 'Video piccolo';
  $ds_view_mode->entities = array(
    'file' => 'file',
  );
  $export['video_piccolo'] = $ds_view_mode;

  return $export;
}
