<?php
/**
 * @file
 * ildeposito_gruppi.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ildeposito_gruppi_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_geo|node|gruppi|form';
  $field_group->group_name = 'group_geo';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gruppi';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Geolocalizzazione',
    'weight' => '2',
    'children' => array(
      0 => 'field_geofield',
      1 => 'field_indirizzo',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-geo field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_geo|node|gruppi|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_main|node|gruppi|form';
  $field_group->group_name = 'group_main';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gruppi';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Dati principali',
    'weight' => '0',
    'children' => array(
      0 => 'body',
      1 => 'field_tipo_gruppo',
      2 => 'field_anno',
      3 => 'field_links',
      4 => 'field_email',
      5 => 'field_citta',
      6 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-main field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_main|node|gruppi|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_multimedia|node|gruppi|form';
  $field_group->group_name = 'group_multimedia';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gruppi';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Multimedia',
    'weight' => '1',
    'children' => array(
      0 => 'field_images',
      1 => 'field_media',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-multimedia field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_multimedia|node|gruppi|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Dati principali');
  t('Geolocalizzazione');
  t('Multimedia');

  return $field_groups;
}
