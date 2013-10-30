<?php

/**
 * @file
 * Admin files for Push Notifications module.
 */

/**
 * Overview form for Push Notification Settings.
 */
function push_notifications_admin_overview_form($form_state) {
  // Load all tokens stored in the database.
  $query = db_select('push_notifications_tokens', 'pnt');
  $query->fields('pnt', array('uid', 'type', 'language'));
  $result = $query->execute();
  $counts = array(
    'total' => 0,
    'ios' => 0,
    'android' => 0,
    'anonymous' => 0,
    'registered' => 0,
  );

  foreach ($result as $data) {
    $counts['total']++;
    switch ($data->type) {
      case PUSH_NOTIFICATIONS_TYPE_ID_IOS: $counts['ios']++; break;
      case PUSH_NOTIFICATIONS_TYPE_ID_ANDROID: $counts['android']++; break;
    }
    if ($data->uid == 0) {
      $counts['anonymous']++;
    }
    else {
      $counts['registered']++;
    }
  }

  $form = array();

  $statistics_description = (!$counts['total']) ? t('No tokens stored yet.') : null;
  $form['statistics'] = array(
    '#type' => 'fieldset',
    '#title' => 'Push Notification Statistics',
    '#description' => $statistics_description,
  );

  $form['statistics']['total'] = array(
    '#type' => 'item',
    '#title' => t('Total Tokens Stored'),
    '#markup' => $counts['total'],
  );

  $form['statistics']['ios'] = array(
    '#type' => 'item',
    '#title' => t('iOS Tokens Stored'),
    '#markup' => $counts['ios'],
  );

  $form['statistics']['android'] = array(
    '#type' => 'item',
    '#title' => t('Android Tokens Stored'),
    '#markup' => $counts['android'],
  );

  $form['statistics']['anonymous'] = array(
    '#type' => 'item',
    '#title' => t('Anonymous Tokens Stored'),
    '#markup' => $counts['anonymous'],
  );

  $form['statistics']['registered'] = array(
    '#type' => 'item',
    '#title' => t('Registered Tokens Stored'),
    '#markup' => $counts['registered'],
  );

  $form['languages'] = array(
    '#type' => 'fieldset',
    '#title' => 'Push Notification Languages',
    '#description' => t('Languages used across all push notification recipients'),
  );

  // Determine which languages are used.
  $languages_used = push_notifications_used_languages();
  if (!empty($languages_used)) {
    unset($languages_used[0]);
    $languages_markup = theme('item_list', array('items' => $languages_used));
  }
  else {
    $languages_markup = t('No tokens stored or no tokens with a language association stored');
  }

  $form['languages']['used'] = array(
    '#type' => 'item',
    '#markup' => $languages_markup,
  );

  return $form;
}

/**
 * Form callback for Push Notifications Settings.
 */
function push_notifications_admin_form($form_state) {
  $form = array();

  // Add JavaScript for Google push notification selector.
  drupal_add_js(drupal_get_path('module', 'push_notifications') . '/scripts/push_notifications_admin.js');

  $form['configuration_general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Push Notifications Settings'),
  );

  $form['configuration_general']['push_notifications_require_enabled_language'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only allow enabled languages'),
    '#description' => t('When setting a device token, only allow languages that are enabled on this site (instead of all valid langauges)'),
    '#default_value' => variable_get('push_notifications_require_enabled_language', 0),
  );

  $replacements_privatemsg = array(
    '!privatemsg' => l('PrivateMSG', 'http://drupal.org/project/privatemsg/', array('html' => true, 'attributes' => array('target' => '_blank'))),
    '!privatemsg_status' => (module_exists('privatemsg')) ? 'successfully installed' : 'not installed',
  );
  $form['configuration_general']['push_notifications_privatemsg_integration'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable integration with PrivateMSG module'),
    '#description' => t('Check this to deliver messages sent through the !privatemsg module to all recipients with at least one valid device token. Requires !privatemsg module 7.x-1.x (status: !privatemsg_status)', $replacements_privatemsg),
    '#default_value' => variable_get('push_notifications_privatemsg_integration', 0),
  );

  $configuration_apns_replacements = array(
    '!link' => l(t('this tutorial'), 'http://blog.boxedice.com/2009/07/10/how-to-build-an-apple-push-notification-provider-server-tutorial/', array('attributes' => array('target' => '_blank'))),
  );
  $form['configuration_apns'] = array(
    '#type' => 'fieldset',
    '#title' => t('Apple Push Notifications'),
    '#description' => t('Configure Push Notifications for Apple\'s Push Notification Server. Select your environment. Both environments require the proper certificates in the \'certificates\' folder of this module. The filename for the development certificate should be \'apns-development.pem\', the production certificate should be \'apns-production.pem\'. See !link for instructions on creating certificates.', $configuration_apns_replacements),
  );

  $form['configuration_apns']['push_notifications_apns_environment'] = array(
    '#type' => 'select',
    '#title' => t('APNS Environment'),
    '#description' => t('Select the active APNS Environment. Please note that development certificates do not work with apps released in the Apple app store; production certificates only work with apps released in the app store.'),
    '#options' => array(
      0 => 'Development',
      1 => 'Production',
    ),
    '#default_value' => variable_get('push_notifications_apns_environment', 0),
  );

  $form['configuration_apns']['stream_context_limit'] = array(
    '#type' => 'select',
    '#title' => t('Stream Context Limit'),
    '#description' => t('Defines the amount of messages sent per stream limit, i.e. how many notifications are sent per connection created with Apple\'s servers. The higher the limit, the faster the message delivery. If the limit is too high, messages might not get delivered at all. Unclear (to me) what Apple\'s <em>actual</em> limit is.'),
    '#options' => drupal_map_assoc(array(1, 5, 10, 25, 50)),
    '#default_value' => variable_get('push_notifications_apns_stream_context_limit', 1),
  );

  $form['configuration_apns']['passphrase'] = array(
    '#type' => 'textfield',
    '#title' => t('Passphrase'),
    '#description' => t('If your APNS certificate has a passphrase, enter it here. Otherwise, leave this field blank.'),
    '#default_value' => variable_get('push_notifications_apns_passphrase', ''),
  );

  $form['configuration_apns']['push_notifications_apns_certificate_folder'] = array(
    '#type' => 'textfield',
    '#title' => t('APNS Certificate Folder Path'),
    '#description' => t('If you want to store your certificates in a different directory than the modules default (the \'certificates\' folder inside this module\'s folder), specify the path here. If you use your own path, use the full path, e.g. \'/users/danny/drupal_install/certificates/\', not the relative path. Otherwise, leave this field blank.'),
    '#default_value' => variable_get('push_notifications_apns_certificate_folder', ''),
  );

  $form['configuration_c2dm'] = array(
    '#type' => 'fieldset',
    '#title' => t('Google Push Notifications'),
    '#description' => t('Requires a valid Google Cloud Messaging or C2DM account. !signup for Google Cloud Messaging. Google does not accept new signups for C2DM.', array('!signup' => l(t('Signup here'), 'http://developer.android.com/guide/google/gcm/gs.html', array('attributes' => array('target' => '_blank'))))),
  );

  $form['configuration_c2dm']['push_notifications_google_type'] = array(
    '#type' => 'radios',
    '#title' => t('Google Push Notifications Type'),
    '#description' => t('Google\'s C2DM service (Cloud 2 Device Messaging) was replaced by the Google Cloud Messaging Service. Each services requires a different authentication method. '),
    '#default_value' => PUSH_NOTIFICATIONS_GOOGLE_TYPE,
    '#options' => array(
      PUSH_NOTIFICATIONS_GOOGLE_TYPE_C2DM => 'Cloud 2 Device Messaging',
      PUSH_NOTIFICATIONS_GOOGLE_TYPE_GCM => 'Google Cloud Messaging',
    ),
  );

  $c2dm_credentials_visible = (PUSH_NOTIFICATIONS_GOOGLE_TYPE == PUSH_NOTIFICATIONS_GOOGLE_TYPE_C2DM);
  $form['configuration_c2dm']['c2dm_credentials'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cloud 2 Device Messaging Settings'),
    '#description' => t('Enter your C2DM credentials.'),
      '#attributes' => array(
        'style' => (PUSH_NOTIFICATIONS_GOOGLE_TYPE != PUSH_NOTIFICATIONS_GOOGLE_TYPE_C2DM) ? 'display:none' : '',
      ),
  );

  $form['configuration_c2dm']['c2dm_credentials']['push_notifications_c2dm_username'] = array(
    '#type' => 'textfield',
    '#title' => t('C2DM Username'),
    '#description' => t('Enter the username for your C2DM Google Account'),
    '#default_value' => variable_get('push_notifications_c2dm_username', ''),
  );

  $form['configuration_c2dm']['c2dm_credentials']['push_notifications_c2dm_password'] = array(
    '#type' => 'textfield',
    '#title' => t('C2DM Password'),
    '#description' => t('Enter the password for your C2DM Google Account'),
    '#default_value' => variable_get('push_notifications_c2dm_password', ''),
  );

  $form['configuration_c2dm']['gcm_credentials'] = array(
    '#type' => 'fieldset',
    '#title' => t('Google Cloud Messaging'),
    '#description' => t('Enter your Google Cloud Messaging details'),
      '#attributes' => array(
        'style' => (PUSH_NOTIFICATIONS_GOOGLE_TYPE != PUSH_NOTIFICATIONS_GOOGLE_TYPE_GCM) ? 'display:none' : '',
      ),

  );

  $form['configuration_c2dm']['gcm_credentials']['push_notifications_gcm_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Cloud Messaging API Key'),
    '#description' => t('Enter the API key for your Google Cloud project'),
    '#default_value' => variable_get('push_notifications_gcm_api_key', ''),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save Configuration',
  );

  return $form;
}



/**
 * Submit callback for push notification configuration page.
 */
function push_notifications_admin_form_submit($form, &$form_state) {
  // Module settings.
  variable_set('push_notifications_require_enabled_language', $form_state['values']['push_notifications_require_enabled_language']);
  variable_set('push_notifications_privatemsg_integration', $form_state['values']['push_notifications_privatemsg_integration']);

  $apns_environment = $form_state['values']['push_notifications_apns_environment'];
  switch ($apns_environment) {
    // Development Environment.
    case 0:
      // Set the variables for the apns development environment.
      variable_set('push_notifications_apns_environment', $apns_environment);
      // Set the individual variables.
      variable_set('push_notifications_apns_host', 'gateway.sandbox.push.apple.com');
      variable_set('push_notifications_apns_certificate', 'apns-development.pem');
      break;
    case 1:
      // Set the variables for the apns production environment.
      variable_set('push_notifications_apns_environment', $apns_environment);
      // Set the individual variables.
      variable_set('push_notifications_apns_host', 'gateway.push.apple.com');
      variable_set('push_notifications_apns_certificate', 'apns-production.pem');
      break;
  }

  // Set C2DM credentials.
  variable_set('push_notifications_c2dm_username', $form_state['values']['push_notifications_c2dm_username']);
  variable_set('push_notifications_c2dm_password', $form_state['values']['push_notifications_c2dm_password']);

  // Set GCM API key.
  variable_set('push_notifications_gcm_api_key', $form_state['values']['push_notifications_gcm_api_key']);

  // Set the APNS certificate location.
  $apns_cert_folder = $form_state['values']['push_notifications_apns_certificate_folder'];
  if (!empty($apns_cert_folder)) {

    // Add a trailing slash if not present.
    if ($apns_cert_folder[strlen($apns_cert_folder) - 1] != DIRECTORY_SEPARATOR) {
      $apns_cert_folder .= DIRECTORY_SEPARATOR;
    }

    variable_set('push_notifications_apns_certificate_folder', $apns_cert_folder);
    $apns_cert = _push_notifications_get_apns_certificate();
    if (!file_exists($apns_cert)) {
      drupal_set_message(t('Could not find any APNS certificates at @path. Please ensure your certificates are located in the correct folder to send push notifications.', array('@path' => $apns_cert)), 'warning');
    }
  }
  // Remove the variable if the location field is blank
  // but a variable had been set previously.
  else if (variable_get('push_notifications_apns_certificate_folder', NULL)) {
    variable_del('push_notifications_apns_certificate_folder');
  }

  // Set the APNS pem file passphrase.
  variable_set('push_notifications_apns_passphrase', $form_state['values']['passphrase']);

  // Set the APNS stream limit.
  variable_set('push_notifications_apns_stream_context_limit', $form_state['values']['stream_context_limit']);

  $replacements = array(
    '@environment' => ($apns_environment) ? "Production" : "Development",
  );
  drupal_set_message(t('The APNS environment was successfully set to "@environment".', $replacements));
}



/**
 * Form callback for sending a mass-push notification.
 */
function push_notifications_mass_push_form($form_state) {
  $form = array();

  $form['message'] = array(
    '#type' => 'fieldset',
    '#title' => t('Push Notification Message'),
    '#description' => t('Compose the elements of your push notification message.'),
    '#tree' => TRUE,
  );

  $form['message']['alert'] = array(
    '#type' => 'textfield',
    '#title' => t('Push Message'),
    '#description' => t('Compose the message to send out (256 characters max.)'),
    '#default_value' => (isset($form_state['values']['message']['alert'])) ? $form_state['values']['message']['alert'] : '',
    '#required' => TRUE,
    '#size' => 128,
    '#maxlength' => 256,
    '#weight' => 10,
  );

  if (module_exists('locale')) {
    $form['language'] = array(
      '#type' => 'select',
      '#title' => t('Language'),
      '#options' => push_notifications_used_languages(),
      '#description' => t('Optionally, only select the push notifications to recipients with this language.'),
      '#default_value' => (isset($form_state['values']['language'])) ? $form_state['values']['language'] : '',
      '#weight' => 12,
    );
  }

  // Only show Android option if C2DM credentials are available.
  $recipients_options = array('ios' => t('iOS (iPhone/iPad)'));
  if ((PUSH_NOTIFICATIONS_C2DM_USERNAME && PUSH_NOTIFICATIONS_C2DM_PASSWORD) || PUSH_NOTIFICATIONS_GCM_API_KEY) {
    $recipients_options['android'] = t('Android');
  }
  $form['recipients'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Recipients'),
    '#description' => t('Select the recipients for this push message'),
    '#options' => $recipients_options,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Send Push Notification',
    '#weight' => 50,
  );

  return $form;
}



/**
 * Submit handler for sending out a mass-push notification.
 */
function push_notifications_mass_push_form_validate($form, &$form_state) {
  $recipients = $form_state['values']['recipients'];

  // Define an empty array for the payload.
  $payload = array();

  // Add all "message" elements to the payload.
  // Other modules can alter the contents of the payload
  // array by adding additional elements to 'message'
  // when it implements hook_form_alter.
  $message_elements = $form_state['values']['message'];
  foreach ($message_elements as $key => $value) {
    $payload[$key] = $value;
  }

  // Store payload in the form_state.
  $form_state['values']['payload'] = $payload;

  // Make sure at least one recipient (group) is selected.
  if (empty($recipients['ios']) && empty($recipients['android'])) {
    form_set_error('recipients', t('No message was sent. Please select at least one recipient group.'));
  }

  // Validate that the message size is ok.
  if (!push_notifications_check_payload_size($form_state['values']['payload'])) {
    form_set_error('message', t('Your message exceeds the allowed size of 256 bytes. Please shorten your message.'));
  }
}



/**
 * Submit handler for sending out a mass-push notification.
 */
function push_notifications_mass_push_form_submit($form, &$form_state) {
  $recipients = $form_state['values']['recipients'];
  $payload = $form_state['values']['payload'];
  $language = (isset($form_state['values']['language'])) ? $form_state['values']['language'] : false;

  // Send message to all iOS recipients.
  if (!empty($recipients['ios'])) {
    // Get all iOS recipients.
    $tokens_ios = push_notifications_get_tokens(PUSH_NOTIFICATIONS_TYPE_ID_IOS, $language);
    if (!empty($tokens_ios)) {
      // Convert the payload into the correct format for APNS.
      $payload_apns = array('aps' => $payload);
      $result = push_notifications_apns_send_message($tokens_ios, $payload_apns);
      $dsm_type = ($result['success']) ? 'status' : 'error';
      drupal_set_message($result['message'], $dsm_type);
    }
    else {
      drupal_set_message(t('No iOS recipients found, potentially for this language.'));
    }
  }

  // Send message to all Android recipients.
  if (!empty($recipients['android'])) {
    // Get all Android recipients.
    $tokens_android = push_notifications_get_tokens(PUSH_NOTIFICATIONS_TYPE_ID_ANDROID, $language);
    if (!empty($tokens_android)) {
      // Determine which method to use for Google push notifications.
      switch (PUSH_NOTIFICATIONS_GOOGLE_TYPE) {
        case PUSH_NOTIFICATIONS_GOOGLE_TYPE_C2DM:
        $result = push_notifications_c2dm_send_message($tokens_android, $payload);
        break;

        case PUSH_NOTIFICATIONS_GOOGLE_TYPE_GCM:
        $result = push_notifications_gcm_send_message($tokens_android, $payload);
        break;
      }
      $dsm_type = ($result['success']) ? 'status' : 'error';
      drupal_set_message($result['message'], $dsm_type);
    }
    else {
      drupal_set_message(t('No Android recipients found, potentially for this language.'));
    }
  }
}
