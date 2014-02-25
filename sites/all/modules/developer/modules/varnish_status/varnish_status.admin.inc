<?php

/**
 * @file
 * Varnish dashboard admin pages.
 */

/**
 * Callback for administer page for Varnish Status.
 */
function varnish_status_admin($form, &$form_state) {
	
	$form['varnish_status_path'] = array(
			'#type' => 'textfield',
			'#title' => t('Varnish Agent 2 path'),
			'#description' => t('Add absolute path to Varnish Agent (starts with http or your protocol).'),
			'#default_value' => variable_get('varnish_status_path'),
	);

	$form['varnish_status_port'] = array(
			'#type' => 'textfield',
			'#title' => t('Varnish Agent 2 port'),
			'#description' => t('Add port for the Varnish Agent (maybe 6085).'),
			'#default_value' => variable_get('varnish_status_port'),
	);

	$form['varnish_status_username'] = array(
			'#type' => 'textfield',
			'#title' => t('Username'),
			'#description' => t('Add username for the Varnish Agent.'),
			'#default_value' => variable_get('varnish_status_username'),
	);
	$form['varnish_status_password'] = array(
			'#type' => 'textfield',
			'#title' => t('Password'),
			'#description' => t('Add username for the Varnish Agent.)'),
			'#default_value' => variable_get('varnish_status_password'),
	);

	return system_settings_form($form);
}
