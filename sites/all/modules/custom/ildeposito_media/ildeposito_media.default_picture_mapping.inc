<?php
/**
 * @file
 * ildeposito_media.default_picture_mapping.inc
 */

/**
 * Implements hook_default_picture_mapping().
 */
function ildeposito_media_default_picture_mapping() {
  $export = array();

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'articolo';
  $picture_mapping->machine_name = 'articolo';
  $picture_mapping->breakpoint_group = 'articolo';
  $picture_mapping->mapping = array(
    'breakpoints.theme.ildeposito.mobile' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'resp_articolobreakpoints_theme_ildeposito_mobile_1x',
      ),
    ),
    'breakpoints.theme.ildeposito.narrow' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'resp_articolobreakpoints_theme_ildeposito_narrow_1x',
      ),
    ),
    'breakpoints.theme.ildeposito.normal' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
      ),
    ),
    'breakpoints.theme.ildeposito.tv' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'resp_articolobreakpoints_theme_ildeposito_tv_1x',
      ),
    ),
  );
  $export['articolo'] = $picture_mapping;

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'ildeposito';
  $picture_mapping->machine_name = 'ildeposito';
  $picture_mapping->breakpoint_group = 'ildeposito';
  $picture_mapping->mapping = array(
    'breakpoints.theme.ildeposito.mobile' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'respbreakpoints_theme_ildeposito_mobile_1x',
      ),
    ),
    'breakpoints.theme.ildeposito.narrow' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'respbreakpoints_theme_ildeposito_narrow_1x',
      ),
    ),
    'breakpoints.theme.ildeposito.normal' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'respbreakpoints_theme_ildeposito_normal_1x',
      ),
    ),
    'breakpoints.theme.ildeposito.tv' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'respbreakpoints_theme_ildeposito_tv_1x',
      ),
    ),
  );
  $export['ildeposito'] = $picture_mapping;

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'seizoni_home';
  $picture_mapping->machine_name = 'seizoni_home';
  $picture_mapping->breakpoint_group = 'seizoni_home';
  $picture_mapping->mapping = array(
    'breakpoints.theme.ildeposito.mobile' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'sezioni_homebreakpoints_theme_ildeposito_mobile_1x',
      ),
    ),
    'breakpoints.theme.ildeposito.narrow' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'sezioni_homebreakpoints_theme_ildeposito_narrow_1x',
      ),
    ),
    'breakpoints.theme.ildeposito.normal' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'sezioni_homebreakpoints_theme_ildeposito_normal_1x',
      ),
    ),
    'breakpoints.theme.ildeposito.tv' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'sezioni_homebreakpoints_theme_ildeposito_tv_1x',
      ),
    ),
  );
  $export['seizoni_home'] = $picture_mapping;

  return $export;
}
