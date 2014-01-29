<?php
/**
 * @file
 * ildeposito_media.file_default_displays.inc
 */

/**
 * Implements hook_file_default_displays().
 */
function ildeposito_media_file_default_displays() {
  $export = array();

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'audio__preview__file_field_media_large_icon';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $export['audio__preview__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'document__preview__file_field_media_large_icon';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $export['document__preview__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_colorbox';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'colorbox_node_style' => '',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $export['image__articolo__file_field_colorbox'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_file_audio';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'controls' => 1,
    'autoplay' => 0,
    'loop' => 0,
    'multiple_file_behavior' => 'tags',
  );
  $export['image__articolo__file_field_file_audio'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_file_default';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__articolo__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_file_download_link';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'text' => 'Download [file:name]',
  );
  $export['image__articolo__file_field_file_download_link'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_file_rendered';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
  );
  $export['image__articolo__file_field_file_rendered'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_file_table';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__articolo__file_field_file_table'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_file_url_plain';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__articolo__file_field_file_url_plain'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_file_video';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'controls' => 1,
    'autoplay' => 0,
    'loop' => 0,
    'width' => '',
    'height' => '',
    'multiple_file_behavior' => 'tags',
  );
  $export['image__articolo__file_field_file_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_image';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => '',
    'image_link' => '',
  );
  $export['image__articolo__file_field_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_media_colorbox';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'colorbox',
    'colorbox_view_mode' => 'preview',
    'fixed_width' => '',
    'fixed_height' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'none',
    'audio_playlist' => 0,
  );
  $export['image__articolo__file_field_media_colorbox'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_media_large_icon';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__articolo__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_openlayers';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'imageStyle' => '',
    'pointRadius' => '6',
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => '1',
    'fillOpacity' => '1',
    'strokeOpacity' => '1',
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'cursor' => '',
    'graphicWidth' => '',
    'graphicHeight' => '',
    'graphicOpacity' => '1',
    'graphicXOffset' => '',
    'graphicYOffset' => '',
    'graphicName' => '',
    'rotation' => '',
    'display' => '',
    'label' => '',
    'labelAlign' => 'cm',
    'labelXOffset' => '',
    'labelYOffset' => '',
    'fontColor' => '',
    'fontSize' => '',
    'fontFamily' => '',
    'fontWeight' => '',
  );
  $export['image__articolo__file_field_openlayers'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_field_picture';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'picture_group' => 'articolo',
    'fallback_image_style' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
    'image_link' => '',
  );
  $export['image__articolo__file_field_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_image';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => 'articolo',
    'alt' => '[file:field_file_image_alt_text]',
    'title' => '[file:field_file_image_title_text]',
  );
  $export['image__articolo__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo__file_picture';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'picture_group' => 'articolo',
    'fallback_image_style' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
    'alt' => '',
    'title' => '',
  );
  $export['image__articolo__file_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_colorbox';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'colorbox_node_style' => '',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $export['image__articolo_home__file_field_colorbox'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_file_audio';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'controls' => 1,
    'autoplay' => 0,
    'loop' => 0,
    'multiple_file_behavior' => 'tags',
  );
  $export['image__articolo_home__file_field_file_audio'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_file_default';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__articolo_home__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_file_download_link';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'text' => 'Download [file:name]',
  );
  $export['image__articolo_home__file_field_file_download_link'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_file_rendered';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
  );
  $export['image__articolo_home__file_field_file_rendered'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_file_table';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__articolo_home__file_field_file_table'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_file_url_plain';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__articolo_home__file_field_file_url_plain'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_file_video';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'controls' => 1,
    'autoplay' => 0,
    'loop' => 0,
    'width' => '',
    'height' => '',
    'multiple_file_behavior' => 'tags',
  );
  $export['image__articolo_home__file_field_file_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_image';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => '',
    'image_link' => '',
  );
  $export['image__articolo_home__file_field_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_media_colorbox';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
    'colorbox_view_mode' => 'default',
    'fixed_width' => '',
    'fixed_height' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'title',
    'audio_playlist' => 0,
  );
  $export['image__articolo_home__file_field_media_colorbox'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_media_large_icon';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__articolo_home__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_openlayers';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'imageStyle' => '',
    'pointRadius' => '6',
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => '1',
    'fillOpacity' => '1',
    'strokeOpacity' => '1',
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'cursor' => '',
    'graphicWidth' => '',
    'graphicHeight' => '',
    'graphicOpacity' => '1',
    'graphicXOffset' => '',
    'graphicYOffset' => '',
    'graphicName' => '',
    'rotation' => '',
    'display' => '',
    'label' => '',
    'labelAlign' => 'cm',
    'labelXOffset' => '',
    'labelYOffset' => '',
    'fontColor' => '',
    'fontSize' => '',
    'fontFamily' => '',
    'fontWeight' => '',
  );
  $export['image__articolo_home__file_field_openlayers'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_field_picture';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'picture_group' => 'articolo',
    'fallback_image_style' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
    'image_link' => '',
  );
  $export['image__articolo_home__file_field_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'articolo_home',
    'alt' => '[file:field_file_image_alt_text]',
    'title' => '[file:field_file_image_title_text]',
  );
  $export['image__articolo_home__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__articolo_home__file_picture';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'picture_group' => 'articolo',
    'fallback_image_style' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
    'alt' => '',
    'title' => '',
  );
  $export['image__articolo_home__file_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__colorbox__file_field_file_default';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__colorbox__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__colorbox__file_field_file_rendered';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
  );
  $export['image__colorbox__file_field_file_rendered'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__colorbox__file_field_file_table';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__colorbox__file_field_file_table'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__colorbox__file_field_file_url_plain';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__colorbox__file_field_file_url_plain'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__colorbox__file_field_media_colorbox';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
    'colorbox_view_mode' => 'default',
    'fixed_width' => '',
    'fixed_height' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'title',
    'audio_playlist' => 0,
  );
  $export['image__colorbox__file_field_media_colorbox'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__colorbox__file_field_media_large_icon';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__colorbox__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__colorbox__file_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'articolo',
    'alt' => '[file:field_file_image_alt_text]',
    'title' => '[file:field_file_image_title_text]',
  );
  $export['image__colorbox__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__colorbox__file_picture';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'picture_group' => 'ildeposito',
    'fallback_image_style' => '',
    'alt' => '',
    'title' => '',
  );
  $export['image__colorbox__file_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_field_file_default';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__default__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_field_file_rendered';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
  );
  $export['image__default__file_field_file_rendered'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_field_file_table';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__default__file_field_file_table'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_field_file_url_plain';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__default__file_field_file_url_plain'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_field_image';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => '',
    'image_link' => '',
  );
  $export['image__default__file_field_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_field_media_large_icon';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__default__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => '',
    'alt' => '[file:field_file_image_alt_text]',
    'title' => '[file:field_file_image_title_text]',
  );
  $export['image__default__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_field_colorbox';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'colorbox_node_style' => '',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $export['image__elenco_termini_contenuti__file_field_colorbox'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_field_file_default';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__elenco_termini_contenuti__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_field_file_download_link';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'text' => 'Download [file:name]',
  );
  $export['image__elenco_termini_contenuti__file_field_file_download_link'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_field_file_rendered';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
  );
  $export['image__elenco_termini_contenuti__file_field_file_rendered'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_field_file_table';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__elenco_termini_contenuti__file_field_file_table'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_field_file_url_plain';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__elenco_termini_contenuti__file_field_file_url_plain'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_field_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'elenco_termine',
    'image_link' => 'content',
  );
  $export['image__elenco_termini_contenuti__file_field_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_field_media_large_icon';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__elenco_termini_contenuti__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_field_openlayers';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'imageStyle' => '',
    'pointRadius' => '6',
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => '1',
    'fillOpacity' => '1',
    'strokeOpacity' => '1',
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'cursor' => '',
    'graphicWidth' => '',
    'graphicHeight' => '',
    'graphicOpacity' => '1',
    'graphicXOffset' => '',
    'graphicYOffset' => '',
    'graphicName' => '',
    'rotation' => '',
    'display' => '',
    'label' => '',
    'labelAlign' => 'cm',
    'labelXOffset' => '',
    'labelYOffset' => '',
    'fontColor' => '',
    'fontSize' => '',
    'fontFamily' => '',
    'fontWeight' => '',
  );
  $export['image__elenco_termini_contenuti__file_field_openlayers'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_field_picture';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'picture_group' => 'articolo',
    'fallback_image_style' => '',
    'image_link' => '',
    'colorbox' => 'articolo',
  );
  $export['image__elenco_termini_contenuti__file_field_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'elenco_termine',
    'alt' => '[file:field_file_image_alt_text]',
    'title' => '[file:field_file_image_title_text]',
  );
  $export['image__elenco_termini_contenuti__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__elenco_termini_contenuti__file_picture';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'picture_group' => 'articolo',
    'fallback_image_style' => '',
    'alt' => '',
    'title' => '',
  );
  $export['image__elenco_termini_contenuti__file_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__full__file_image';
  $file_display->weight = 5;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'large',
  );
  $export['image__full__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__header__file_field_file_default';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__header__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__header__file_field_file_rendered';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'header',
  );
  $export['image__header__file_field_file_rendered'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__header__file_field_file_table';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__header__file_field_file_table'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__header__file_field_file_url_plain';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__header__file_field_file_url_plain'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__header__file_field_media_colorbox';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
    'colorbox_view_mode' => 'default',
    'fixed_width' => '',
    'fixed_height' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'title',
    'audio_playlist' => 0,
  );
  $export['image__header__file_field_media_colorbox'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__header__file_field_media_large_icon';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__header__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__header__file_image';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => 'intestazione',
    'alt' => '[file:field_file_image_alt_text]',
    'title' => '[file:field_file_image_title_text]',
  );
  $export['image__header__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__header__file_picture';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'picture_group' => 'ildeposito',
    'fallback_image_style' => 'respbreakpoints_theme_ildeposito_normal_1x',
    'alt' => '',
    'title' => '',
  );
  $export['image__header__file_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__preview__file_field_image';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'media_thumbnail',
    'image_link' => '',
  );
  $export['image__preview__file_field_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__preview__file_image';
  $file_display->weight = 5;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'square_thumbnail',
  );
  $export['image__preview__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_colorbox';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'colorbox_node_style' => '',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $export['image__sezioni_home__file_field_colorbox'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_file_audio';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'controls' => 1,
    'autoplay' => 0,
    'loop' => 0,
    'multiple_file_behavior' => 'tags',
  );
  $export['image__sezioni_home__file_field_file_audio'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_file_default';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__sezioni_home__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_file_download_link';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'text' => 'Download [file:name]',
  );
  $export['image__sezioni_home__file_field_file_download_link'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_file_rendered';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
  );
  $export['image__sezioni_home__file_field_file_rendered'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_file_table';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__sezioni_home__file_field_file_table'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_file_url_plain';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__sezioni_home__file_field_file_url_plain'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_file_video';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'controls' => 1,
    'autoplay' => 0,
    'loop' => 0,
    'width' => '',
    'height' => '',
    'multiple_file_behavior' => 'tags',
  );
  $export['image__sezioni_home__file_field_file_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_image';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => 'sezioni_homebreakpoints_theme_ildeposito_tv_1x',
    'image_link' => '',
  );
  $export['image__sezioni_home__file_field_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_media_colorbox';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
    'colorbox_view_mode' => 'default',
    'fixed_width' => '',
    'fixed_height' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'title',
    'audio_playlist' => 0,
  );
  $export['image__sezioni_home__file_field_media_colorbox'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_media_large_icon';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__sezioni_home__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_openlayers';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'imageStyle' => '',
    'pointRadius' => '6',
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => '1',
    'fillOpacity' => '1',
    'strokeOpacity' => '1',
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'cursor' => '',
    'graphicWidth' => '',
    'graphicHeight' => '',
    'graphicOpacity' => '1',
    'graphicXOffset' => '',
    'graphicYOffset' => '',
    'graphicName' => '',
    'rotation' => '',
    'display' => '',
    'label' => '',
    'labelAlign' => 'cm',
    'labelXOffset' => '',
    'labelYOffset' => '',
    'fontColor' => '',
    'fontSize' => '',
    'fontFamily' => '',
    'fontWeight' => '',
  );
  $export['image__sezioni_home__file_field_openlayers'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_field_picture';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'picture_group' => 'seizoni_home',
    'fallback_image_style' => 'sezioni_homebreakpoints_theme_ildeposito_normal_1x',
    'image_link' => '',
  );
  $export['image__sezioni_home__file_field_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_image';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'image_style' => '',
    'alt' => '[file:field_file_image_alt_text]',
    'title' => '[file:field_file_image_title_text]',
  );
  $export['image__sezioni_home__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__sezioni_home__file_picture';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'picture_group' => 'seizoni_home',
    'fallback_image_style' => 'sezioni_homebreakpoints_theme_ildeposito_normal_1x',
    'alt' => '',
    'title' => '',
  );
  $export['image__sezioni_home__file_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__teaser__file_field_image';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  $export['image__teaser__file_field_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__teaser__file_image';
  $file_display->weight = 5;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'medium',
  );
  $export['image__teaser__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_field_colorbox';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'colorbox_node_style' => '',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $export['image__termine_singolo__file_field_colorbox'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_field_file_default';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__termine_singolo__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_field_file_download_link';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'text' => 'Download [file:name]',
  );
  $export['image__termine_singolo__file_field_file_download_link'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_field_file_rendered';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'file_view_mode' => 'default',
  );
  $export['image__termine_singolo__file_field_file_rendered'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_field_file_table';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__termine_singolo__file_field_file_table'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_field_file_url_plain';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__termine_singolo__file_field_file_url_plain'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_field_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'termine_singolo',
    'image_link' => 'content',
  );
  $export['image__termine_singolo__file_field_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_field_media_large_icon';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = '';
  $export['image__termine_singolo__file_field_media_large_icon'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_field_openlayers';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'imageStyle' => '',
    'pointRadius' => '6',
    'fillColor' => '#EE9900',
    'strokeColor' => '#EE9900',
    'strokeWidth' => '1',
    'fillOpacity' => '1',
    'strokeOpacity' => '1',
    'strokeLinecap' => 'round',
    'strokeDashstyle' => 'solid',
    'cursor' => '',
    'graphicWidth' => '',
    'graphicHeight' => '',
    'graphicOpacity' => '1',
    'graphicXOffset' => '',
    'graphicYOffset' => '',
    'graphicName' => '',
    'rotation' => '',
    'display' => '',
    'label' => '',
    'labelAlign' => 'cm',
    'labelXOffset' => '',
    'labelYOffset' => '',
    'fontColor' => '',
    'fontSize' => '',
    'fontFamily' => '',
    'fontWeight' => '',
  );
  $export['image__termine_singolo__file_field_openlayers'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_field_picture';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'picture_group' => 'articolo',
    'fallback_image_style' => '',
    'image_link' => '',
    'colorbox' => 'articolo',
  );
  $export['image__termine_singolo__file_field_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'termine_singolo',
    'alt' => '[file:field_file_image_alt_text]',
    'title' => '[file:field_file_image_title_text]',
  );
  $export['image__termine_singolo__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__termine_singolo__file_picture';
  $file_display->weight = 0;
  $file_display->status = FALSE;
  $file_display->settings = array(
    'picture_group' => 'articolo',
    'fallback_image_style' => '',
    'alt' => '',
    'title' => '',
  );
  $export['image__termine_singolo__file_picture'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__preview__file_field_media_large_icon';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $export['video__preview__file_field_media_large_icon'] = $file_display;

  return $export;
}
