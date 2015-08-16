<?php
/**
 * @file
 * ildeposito_ct_evento.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ildeposito_ct_evento_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_categorie|node|evento|form';
  $field_group->group_name = 'group_categorie';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'evento';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Categorie',
    'weight' => '1',
    'children' => array(
      0 => 'field_percorso',
      1 => 'field_sezione',
      2 => 'field_tags',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-categorie field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_categorie|node|evento|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_impostazioni|node|evento|form';
  $field_group->group_name = 'group_impostazioni';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'evento';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Impostazioni',
    'weight' => '4',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-impostazioni field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_impostazioni|node|evento|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_localizzazioni|node|evento|form';
  $field_group->group_name = 'group_localizzazioni';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'evento';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Localizzazioni',
    'weight' => '2',
    'children' => array(
      0 => 'field_localizzazione',
      1 => 'field_geolocation',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-localizzazioni field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_localizzazioni|node|evento|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_principale|node|evento|form';
  $field_group->group_name = 'group_principale';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'evento';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Principale',
    'weight' => '0',
    'children' => array(
      0 => 'field_canti_evento',
      1 => 'field_data_evento',
      2 => 'field_informazioni',
      3 => 'field_links',
      4 => 'field_images',
      5 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-principale field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_principale|node|evento|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_staff|node|evento|form';
  $field_group->group_name = 'group_staff';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'evento';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Staff only',
    'weight' => '3',
    'children' => array(
      0 => 'field_tematica',
      1 => 'field_geofield',
      2 => 'field_evento_ordinamento',
      3 => 'field_descrizione_social',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-staff field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_staff|node|evento|form'] = $field_group;

  return $export;
}
