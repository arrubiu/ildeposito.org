<?php
/**
 * @file
 * HybridAuth Google specific settings.
 */

/**
 * Plugin declaration.
 */
$plugin = array(
  'configuration_form_callback' => 'hybridauth_provider_google_configuration_form_callback',
);

function hybridauth_provider_google_configuration_form_callback(&$form, $provider_id) {
  unset($form['vtabs']['application']['hybridauth_provider_' . $provider_id . '_keys_key']);

  $language_default = language_default();
  $language_default->prefix = '';
  $origin_uri_parts = parse_url(url('<front>', array('absolute' => TRUE)));
  $form['vtabs']['application']['#description'] = t('<p>Enter your application ID and private key. You can get these by creating a new application at <a href="!apps_uri">!apps_uri</a>.</p>'
    . '<p>You must set <strong>Authorized Redirect URIs</strong> to <strong>%redirect_uri</strong>.</p>'
    . '<p>You must set <strong>Authorized JavaScript Origins</strong> to <strong>%origin_uri</strong>.</p>',
    array(
      '!apps_uri' => 'https://code.google.com/apis/console#access',
      '%redirect_uri' => url('hybridauth/endpoint', array('absolute' => TRUE, 'query' => array('hauth.done' => 'Google'), 'language' => $language_default)),
      '%origin_uri' => $origin_uri_parts['scheme'] . '://' . $origin_uri_parts['host'],
    )
  );

  $form['vtabs']['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => 'Advanced settings',
  );
  $form['vtabs']['advanced']['hybridauth_provider_' . $provider_id . '_scope'] = array(
    '#type' => 'textfield',
    '#title' => t('Scope'),
    '#default_value' => variable_get('hybridauth_provider_' . $provider_id . '_scope', 'https://www.googleapis.com/auth/userinfo.profile https://www.googleapis.com/auth/userinfo.email'),
    '#size' => 150,
  );
}
