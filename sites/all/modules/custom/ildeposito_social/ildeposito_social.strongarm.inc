<?php
/**
 * @file
 * ildeposito_social.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ildeposito_social_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_customize_widget_per_form';
  $strongarm->value = 1;
  $export['hybridauth_bonus_customize_widget_per_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_registration_roles';
  $strongarm->value = array(
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $export['hybridauth_bonus_registration_roles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_registration_role_choice';
  $strongarm->value = 0;
  $export['hybridauth_bonus_registration_role_choice'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_icon_pack_comment_form';
  $strongarm->value = 'ildeposito_24x24';
  $export['hybridauth_bonus_widget_icon_pack_comment_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_icon_pack_user_login';
  $strongarm->value = 'hybridauth_24';
  $export['hybridauth_bonus_widget_icon_pack_user_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_icon_pack_user_login_block';
  $strongarm->value = 'hybridauth_24';
  $export['hybridauth_bonus_widget_icon_pack_user_login_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_icon_pack_user_register_form';
  $strongarm->value = 'hybridauth_48';
  $export['hybridauth_bonus_widget_icon_pack_user_register_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_link_text_comment_form';
  $strongarm->value = 'Social network account';
  $export['hybridauth_bonus_widget_link_text_comment_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_link_text_user_login';
  $strongarm->value = 'Social network account';
  $export['hybridauth_bonus_widget_link_text_user_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_link_text_user_login_block';
  $strongarm->value = 'Social network account';
  $export['hybridauth_bonus_widget_link_text_user_login_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_link_text_user_register_form';
  $strongarm->value = 'Social network account';
  $export['hybridauth_bonus_widget_link_text_user_register_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_link_title_comment_form';
  $strongarm->value = 'Social network account';
  $export['hybridauth_bonus_widget_link_title_comment_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_link_title_user_login';
  $strongarm->value = 'Social network account';
  $export['hybridauth_bonus_widget_link_title_user_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_link_title_user_login_block';
  $strongarm->value = 'Social network account';
  $export['hybridauth_bonus_widget_link_title_user_login_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_link_title_user_register_form';
  $strongarm->value = 'Social network account';
  $export['hybridauth_bonus_widget_link_title_user_register_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_title_comment_form';
  $strongarm->value = 'Accedi tramite social network';
  $export['hybridauth_bonus_widget_title_comment_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_title_user_login';
  $strongarm->value = 'Registrati e accedi tramite il tuo accoun social';
  $export['hybridauth_bonus_widget_title_user_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_title_user_login_block';
  $strongarm->value = 'Account social';
  $export['hybridauth_bonus_widget_title_user_login_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_title_user_register_form';
  $strongarm->value = 'Registrati e accedi tramite il tuo account social';
  $export['hybridauth_bonus_widget_title_user_register_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_type_comment_form';
  $strongarm->value = 'list';
  $export['hybridauth_bonus_widget_type_comment_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_type_user_login';
  $strongarm->value = 'list';
  $export['hybridauth_bonus_widget_type_user_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_type_user_login_block';
  $strongarm->value = 'list';
  $export['hybridauth_bonus_widget_type_user_login_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_type_user_register_form';
  $strongarm->value = 'list';
  $export['hybridauth_bonus_widget_type_user_register_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_use_overlay_comment_form';
  $strongarm->value = 1;
  $export['hybridauth_bonus_widget_use_overlay_comment_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_use_overlay_user_login';
  $strongarm->value = 1;
  $export['hybridauth_bonus_widget_use_overlay_user_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_use_overlay_user_login_block';
  $strongarm->value = 1;
  $export['hybridauth_bonus_widget_use_overlay_user_login_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_use_overlay_user_register_form';
  $strongarm->value = 1;
  $export['hybridauth_bonus_widget_use_overlay_user_register_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_weight_comment_form';
  $strongarm->value = '100';
  $export['hybridauth_bonus_widget_weight_comment_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_weight_user_login';
  $strongarm->value = '100';
  $export['hybridauth_bonus_widget_weight_user_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_weight_user_login_block';
  $strongarm->value = '100';
  $export['hybridauth_bonus_widget_weight_user_login_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_bonus_widget_weight_user_register_form';
  $strongarm->value = '100';
  $export['hybridauth_bonus_widget_weight_user_register_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_destination';
  $strongarm->value = 'user';
  $export['hybridauth_destination'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_disable_username_change';
  $strongarm->value = 0;
  $export['hybridauth_disable_username_change'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_display_name';
  $strongarm->value = '[user:hybridauth:firstName] [user:hybridauth:lastName]';
  $export['hybridauth_display_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_duplicate_emails';
  $strongarm->value = '1';
  $export['hybridauth_duplicate_emails'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_email_verification';
  $strongarm->value = '2';
  $export['hybridauth_email_verification'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_forms';
  $strongarm->value = array(
    'user_login_block' => 'user_login_block',
    'user_login' => 0,
    'user_register_form' => 0,
    'comment_form' => 0,
  );
  $export['hybridauth_forms'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_override_realname';
  $strongarm->value = 0;
  $export['hybridauth_override_realname'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_pictures';
  $strongarm->value = 0;
  $export['hybridauth_pictures'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_register';
  $strongarm->value = '1';
  $export['hybridauth_register'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_registration_username_change';
  $strongarm->value = 0;
  $export['hybridauth_registration_username_change'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_remove_password_fields';
  $strongarm->value = 1;
  $export['hybridauth_remove_password_fields'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_required_fields';
  $strongarm->value = array(
    'email' => 0,
    'firstName' => 0,
    'lastName' => 0,
    'gender' => 0,
  );
  $export['hybridauth_required_fields'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_username';
  $strongarm->value = '[user:hybridauth:displayName]';
  $export['hybridauth_username'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_widget_icon_pack';
  $strongarm->value = 'hybridauth_48';
  $export['hybridauth_widget_icon_pack'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_widget_link_text';
  $strongarm->value = 'Social network account';
  $export['hybridauth_widget_link_text'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_widget_link_title';
  $strongarm->value = 'Social network account';
  $export['hybridauth_widget_link_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_widget_title';
  $strongarm->value = 'Accedi tramite social network';
  $export['hybridauth_widget_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_widget_type';
  $strongarm->value = 'list';
  $export['hybridauth_widget_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_widget_use_overlay';
  $strongarm->value = 1;
  $export['hybridauth_widget_use_overlay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_widget_weight';
  $strongarm->value = '100';
  $export['hybridauth_widget_weight'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hybridauth_window_type';
  $strongarm->value = 'current';
  $export['hybridauth_window_type'] = $strongarm;

  return $export;
}
