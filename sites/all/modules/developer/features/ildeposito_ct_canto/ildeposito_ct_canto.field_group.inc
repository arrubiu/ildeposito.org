<?php
/**
 * @file
 * ildeposito_ct_canto.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ildeposito_ct_canto_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_categorie|node|canto|form';
  $field_group->group_name = 'group_categorie';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'canto';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Categorie',
    'weight' => '4',
    'children' => array(
      0 => 'field_lingua',
      1 => 'field_sezione',
      2 => 'field_tags',
      3 => 'metatags',
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
  $export['group_categorie|node|canto|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_principale|node|canto|form';
  $field_group->group_name = 'group_principale';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'canto';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Principale',
    'weight' => '0',
    'children' => array(
      0 => 'field_anno',
      1 => 'field_autore_musica',
      2 => 'field_autore_testo',
      3 => 'field_capoverso',
      4 => 'field_titolo_alt',
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
  $export['group_principale|node|canto|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_risorse|node|canto|form';
  $field_group->group_name = 'group_risorse';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'canto';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Risorse',
    'weight' => '5',
    'children' => array(
      0 => 'field_fonte',
      1 => 'field_fonte_biblio',
      2 => 'field_informazioni',
      3 => 'field_link_audio',
      4 => 'field_links',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-risorse field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_risorse|node|canto|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_staff|node|canto|form';
  $field_group->group_name = 'group_staff';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'canto';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Staff only',
    'weight' => '6',
    'children' => array(
      0 => 'field_old_id',
      1 => 'field_presenza_accordi',
      2 => 'field_tematica',
      3 => 'field_evento',
      4 => 'field_traduzione',
      5 => 'field_radioactiviy',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-staff field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_staff|node|canto|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_testo|node|canto|form';
  $field_group->group_name = 'group_testo';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'canto';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Testo/Accordi',
    'weight' => '3',
    'children' => array(
      0 => 'field_accordi',
      1 => 'field_testo',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-testo field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_testo|node|canto|form'] = $field_group;

  return $export;
}
