<?php
/**
 * @file
 * ildeposito_ct_autore.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ildeposito_ct_autore_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_principale|node|autore|form';
  $field_group->group_name = 'group_principale';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'autore';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Principale',
    'weight' => '0',
    'children' => array(
      0 => 'field_altri_nomi',
      1 => 'field_cognome',
      2 => 'field_links',
      3 => 'field_nome',
      4 => 'field_sezione',
      5 => 'field_localizzazione',
      6 => 'field_images',
      7 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_principale|node|autore|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_staff|node|autore|form';
  $field_group->group_name = 'group_staff';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'autore';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Staff only',
    'weight' => '1',
    'children' => array(
      0 => 'field_old_id',
      1 => 'field_tags',
      2 => 'field_biografia',
      3 => 'field_numero_canti',
      4 => 'field_autori_correlati',
      5 => 'metatags',
      6 => 'path',
      7 => 'redirect',
      8 => 'xmlsitemap',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_staff|node|autore|form'] = $field_group;

  return $export;
}
