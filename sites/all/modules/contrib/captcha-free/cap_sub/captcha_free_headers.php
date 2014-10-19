<?php
/**
 * @file
 * Generate a cookie for anonymous user with the
 * needed http headers. This is done outside the normal Drupal
 * flow to avoid issues with the option to cache pages for Anonymous
 * users.
 */

// Making allowance for GoDaddy and other special server setups.
if (!empty($_SERVER['SUBDOMAIN_DOCUMENT_ROOT'])) {
  $server_root = $_SERVER['SUBDOMAIN_DOCUMENT_ROOT'];
}
elseif (!empty($_SERVER['REAL_DOCUMENT_ROOT'])) {
  $server_root = $_SERVER['REAL_DOCUMENT_ROOT'];
}
else {
  $server_root = $_SERVER['DOCUMENT_ROOT'];
}
 // We bootstrap Drupal to have access to variables.
define('DRUPAL_ROOT', $server_root);
include_once DRUPAL_ROOT . '/' . 'includes/bootstrap.inc';
chdir(DRUPAL_ROOT);
ob_start();
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
ob_end_clean();

$secret_salt = variable_get('captcha_free_secret_salt', 'secret salt');

$ct = time();
// Set your own Secret salt in the admin.
setcookie('capfree', md5($secret_salt . $ct), 0, '/');

// Add headers
// Always modified
drupal_add_http_header('Last-Modified', gmdate("D, d M Y H:i:s") . ' GMT');
// Expires in the past
drupal_add_http_header('Expires', 'Sun, 19 Nov 1978 05:00:00 GMT');
// HTTP/1.1
drupal_add_http_header('Cache-Control', 'no-store, no-cache, must-revalidate, post-check=0, pre-check=0');
// HTTP/1.0
drupal_add_http_header('Pragma', 'no-cache');

echo $ct;
