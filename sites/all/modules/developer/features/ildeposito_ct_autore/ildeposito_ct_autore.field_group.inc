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
      2 => 'field_nome',
      3 => 'field_sezione',
      4 => 'field_localizzazione',
      5 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-principale field-group-fieldset',
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
      2 => 'field_autori_correlati',
      3 => 'field_biografia',
      4 => 'field_links',
      5 => 'field_numero_canti',
      6 => 'field_immagini',
      7 => 'metatags',
      8 => 'path',
      9 => 'redirect',
      10 => 'xmlsitemap',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-staff field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_staff|node|autore|form'] = $field_group;

  return $export;
}
