<?php
/**
 * @file
 * ildeposito_traduzione.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ildeposito_traduzione_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_categorie|node|traduzione|form';
  $field_group->group_name = 'group_categorie';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'traduzione';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Categorie',
    'weight' => '1',
    'children' => array(
      0 => 'field_lingua',
      1 => 'field_lingua_originale',
      2 => 'field_sezione',
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
  $field_groups['group_categorie|node|traduzione|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_dati|node|traduzione|form';
  $field_group->group_name = 'group_dati';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'traduzione';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Principale',
    'weight' => '0',
    'children' => array(
      0 => 'field_canto_riferimento',
      1 => 'field_informazioni',
      2 => 'field_testo',
      3 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-dati field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_dati|node|traduzione|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_staff|node|traduzione|form';
  $field_group->group_name = 'group_staff';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'traduzione';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Staff',
    'weight' => '2',
    'children' => array(
      0 => 'field_old_id',
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
  $field_groups['group_staff|node|traduzione|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Categorie');
  t('Principale');
  t('Staff');

  return $field_groups;
}
