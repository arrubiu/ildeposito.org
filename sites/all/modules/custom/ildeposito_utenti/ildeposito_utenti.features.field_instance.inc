<?php
/**
 * @file
 * ildeposito_utenti.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function ildeposito_utenti_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_messggio_personale'.
  $field_instances['user-user-field_messggio_personale'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Lascia un tuo messaggio personale che sarà visualizzato quando un utente visualizza il tuo profilo.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'user',
    'field_label_plurals_singular' => '',
    'field_name' => 'field_messggio_personale',
    'label' => 'Messaggio personale',
    'required' => 0,
    'settings' => array(
      'linkit' => array(
        'enable' => 0,
        'insert_plugin' => '',
      ),
      'text_processing' => 1,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => 200,
        'maxlength_js_enforce' => 1,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'maxlength_js_truncate_html' => 0,
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'user-user-field_nickname'.
  $field_instances['user-user-field_nickname'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Imposta il nome con cui sarai visualizzato nel sito.',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_label_plurals_singular' => '',
    'field_name' => 'field_nickname',
    'label' => 'Nickname',
    'required' => 0,
    'settings' => array(
      'linkit' => array(
        'enable' => 0,
        'insert_plugin' => '',
      ),
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => 0,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Imposta il nome con cui sarai visualizzato nel sito.');
  t('Lascia un tuo messaggio personale che sarà visualizzato quando un utente visualizza il tuo profilo.');
  t('Messaggio personale');
  t('Nickname');

  return $field_instances;
}
