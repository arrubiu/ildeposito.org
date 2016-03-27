<?php
/**
 * @file
 * ildeposito_layout.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function ildeposito_layout_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-ildeposito-amministrazione.
  $menus['menu-ildeposito-amministrazione'] = array(
    'menu_name' => 'menu-ildeposito-amministrazione',
    'title' => 'ilDeposito Amministrazione',
    'description' => 'Il menu per lo staff de ilDeposito.org',
  );
  // Exported menu: menu-ildeposito-footer.
  $menus['menu-ildeposito-footer'] = array(
    'menu_name' => 'menu-ildeposito-footer',
    'title' => 'ilDeposito Footer',
    'description' => 'Le voci di menu del footer de ilDeposito.org',
  );
  // Exported menu: menu-ildeposito-menu.
  $menus['menu-ildeposito-menu'] = array(
    'menu_name' => 'menu-ildeposito-menu',
    'title' => 'ilDeposito Menu',
    'description' => 'Il menu principale del sito, l\'alberatura completa.',
  );
  // Exported menu: menu-ildeposito-top-menu.
  $menus['menu-ildeposito-top-menu'] = array(
    'menu_name' => 'menu-ildeposito-top-menu',
    'title' => 'ilDeposito Top Menu',
    'description' => 'La top-bar de ilDeposito.org.',
  );
  // Exported menu: menu-ildeposito-top-right.
  $menus['menu-ildeposito-top-right'] = array(
    'menu_name' => 'menu-ildeposito-top-right',
    'title' => 'ilDeposito Top Right',
    'description' => 'Il menu in alto a destra del sito. Solo link di accesso/registrazione.',
  );
  // Exported menu: menu-ildeposito-utente.
  $menus['menu-ildeposito-utente'] = array(
    'menu_name' => 'menu-ildeposito-utente',
    'title' => 'ilDeposito Utente',
    'description' => 'Il menu per gli utenti autenticati de ilDeposito.org.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Il menu in alto a destra del sito. Solo link di accesso/registrazione.');
  t('Il menu per gli utenti autenticati de ilDeposito.org.');
  t('Il menu per lo staff de ilDeposito.org');
  t('Il menu principale del sito, l\'alberatura completa.');
  t('La top-bar de ilDeposito.org.');
  t('Le voci di menu del footer de ilDeposito.org');
  t('ilDeposito Amministrazione');
  t('ilDeposito Footer');
  t('ilDeposito Menu');
  t('ilDeposito Top Menu');
  t('ilDeposito Top Right');
  t('ilDeposito Utente');

  return $menus;
}
