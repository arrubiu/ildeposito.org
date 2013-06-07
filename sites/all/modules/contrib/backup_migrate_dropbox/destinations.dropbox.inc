<?php

/**
 * @file
 * Functions to handle the dropbox backup destination.
 */

/**
 * A destination for sending database backups to a Dropbox account.
 *
 * @ingroup backup_migrate_destinations
 */
class backup_migrate_destination_dropbox extends backup_migrate_destination_remote {
  var $supported_ops = array('scheduled backup', 'manual backup');
  var $dropbox = NULL;

  /**
   * Save to to the Dropbox destination.
   */
  function save_file($file, $settings) {
    $dropbox = $this->dropbox_object();
    $dest_filename = realpath(variable_get('file_temporary_path', '')) . '/' . $file->file_info['filename'] . '.' . implode('.', $file->ext);
    rename($file->filepath(), $dest_filename);

    try {
      $put = $dropbox->putFile($dest_filename, FALSE, $this->dest_url['path']);
    } catch (Exception $e) {
      watchdog(
        'backup_migrate',
        'There was a problem when we tried to save the file to Dropbox, the error message was: !error',
        array('!error' => $e->getMessage()),
        WATCHDOG_ERROR);
      return FALSE;
    }
    return $file;
  }

  /**
   * Get the form for the settings for this filter.
   */
  function edit_form() {
    $form = parent::edit_form();

    // TODO: add some help text here.
    $form['description'] = array(
      '#type' => 'markup',
      '#weight' => -999,
      '#markup' => t('In order to use your DropBox account as a Backup and Migrate destination,
        you must create a DropBox "App" and obtain your app credentials and enter them below.
        <ol><li>Create a DropBox App by logging into your DropBox account and going to
        <a href="https://www.dropbox.com/developers/apps">https://www.dropbox.com/developers/apps</a>
        and clicking the button to "Create an app". Be sure to give your app a descriptive name,
        as the name you give it will be part of the path within your DropBox folder. For example,
        if you create an app called "kittens", then DropBox will create an DropBox/Apps/kittens
        directory in your DropBox folder.</li>
        <li>Once the app is created, take note of your app\'s "App key" and "App secret" and enter
        both of them below.</li>
        <li>You may also enter a "path" that will be used inside your app\'s folder. For example,
        if you enter "fluffy/white" as your path, then backups will be placed in the
        DropBox/Apps/kittens/fluffy/white/ directory.</li>
        <li>Enter a 32-charater encryption key. We\'re not 100% sure if this is the best way to
        handle this, but for now, it works.</li></ol>
      '),
    );

    $form['name']['#description'] = t('Enter a "friendly" name for this destination. Only appears as a descriptor in the Backup and Migrate administration screens.');

    $form['scheme'] = array(
      '#type' => 'value',
      '#value' => 'https',
    );

    $form['host'] = array(
      '#type' => 'value',
      '#value' => 'www.dropbox.com',
    );

    $form['path'] = array(
      '#type' => 'textfield',
      '#title' => 'Path',
      '#required' => FALSE,
      '#description' => t('A relative folder inside your Dropbox App folder. For example, Dropbox/Apps/(your app name)/(whatever path you enter here).'),
    );

    $form['user'] = array(
      '#type' => 'textfield',
      '#title' => 'Dropbox App Key',
      '#required' => TRUE,
      '#description' => 'Enter the App key from Dropbox.com',
    );

    $form['pass'] = array(
      '#type' => 'password',
      '#title' => 'Dropbox App Secret',
      '#required' => TRUE,
      '#description' => 'Enter the App secret from Dropbox.com',
    );

    // TODO: figure out if this is the best way to do this.
    $form['settings']['encryption_key'] = array(
      '#type' => 'textfield',
      '#title' => '32-byte encryption key',
      '#required' => TRUE,
      '#description' => 'Enter a 32-byte (character) encryption key. TODO: figure out a better way to handle this.',
    );

    return $form;
  }

  /**
   * Submit the form for the settings for the files destination.
   */
  function edit_form_submit($form, &$form_state) {
    // Add the 32-byte encryption key to the settings for this destination.
    $form_state['values']['settings']['encryption_key'] = $form_state['values']['encryption_key'];
    parent::edit_form_submit($form, $form_state);
  }


  /**
   * Create the DropBox object from BenTheDesigner's PHP API.
   */
  function dropbox_object() {
    require_once 'sites/all/libraries/dropbox/Dropbox/API.php';
    if (!$this->dropbox) {
      $key    = $this->dest_url['user'];
      $secret = $this->dest_url['pass'];

      // Check whether to use HTTPS and set the callback URL
      $protocol = (!empty($_SERVER['HTTPS'])) ? 'https' : 'http';
      $callback = $protocol . '://' . $_SERVER['HTTP_HOST'] . request_uri();

      // Register a simple autoload function
      // TODO: figure out if this is the best way to do this.
      spl_autoload_register(function($class) {
        $class = str_replace('\\', '/', $class);
        require_once(libraries_get_path('dropbox') . '/' . $class . '.php');
      });

      // Instantiate the Encrypter and storage objects
      $encrypter = new \Dropbox\OAuth\Storage\Encrypter($this->settings('encryption_key'));

      // Create the storage object, passing it the Encrypter object
      $storage = new \Dropbox\OAuth\Storage\Session($encrypter);

      // Create the consumer and API objects
      $OAuth = new \Dropbox\OAuth\Consumer\Curl($key, $secret, $storage, $callback);
      $this->dropbox = new \Dropbox\API($OAuth);
    }
    return $this->dropbox;
  }
}


