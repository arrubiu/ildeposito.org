<?php
/**
 * @file
 * ildeposito_media.default_breakpoint_group.inc
 */

/**
 * Implements hook_default_breakpoint_group().
 */
function ildeposito_media_default_breakpoint_group() {
  $export = array();

  // Breakpoints.
  $breakpoints = array();
  $breakpoints[] = 'breakpoints.theme.ildeposito.mobile';
  $breakpoints[] = 'breakpoints.theme.ildeposito.narrow';
  $breakpoints[] = 'breakpoints.theme.ildeposito.normal';
  $breakpoints[] = 'breakpoints.theme.ildeposito.tv';

  // Breakpoint group.
  $breakpoint_group = new stdClass();
  $breakpoint_group->disabled = FALSE; /* Edit this to true to make a default breakpoint_group disabled initially */
  $breakpoint_group->api_version = 1;
  $breakpoint_group->machine_name = 'articolo';
  $breakpoint_group->name = 'articolo';
  $breakpoint_group->breakpoints = $breakpoints;
  $breakpoint_group->type = 'custom';
  $breakpoint_group->overridden = 0;
  $export['articolo'] = $breakpoint_group;

  // Breakpoints.
  $breakpoints = array();
  $breakpoints[] = 'breakpoints.theme.ildeposito.mobile';
  $breakpoints[] = 'breakpoints.theme.ildeposito.narrow';
  $breakpoints[] = 'breakpoints.theme.ildeposito.normal';
  $breakpoints[] = 'breakpoints.theme.ildeposito.tv';

  // Breakpoint group.
  $breakpoint_group = new stdClass();
  $breakpoint_group->disabled = FALSE; /* Edit this to true to make a default breakpoint_group disabled initially */
  $breakpoint_group->api_version = 1;
  $breakpoint_group->machine_name = 'ildeposito';
  $breakpoint_group->name = 'ilDeposito.org Theme';
  $breakpoint_group->breakpoints = $breakpoints;
  $breakpoint_group->type = 'theme';
  $breakpoint_group->overridden = 0;
  $export['ildeposito'] = $breakpoint_group;

  // Breakpoints.
  $breakpoints = array();
  $breakpoints[] = 'breakpoints.theme.ildeposito.mobile';
  $breakpoints[] = 'breakpoints.theme.ildeposito.narrow';
  $breakpoints[] = 'breakpoints.theme.ildeposito.normal';
  $breakpoints[] = 'breakpoints.theme.ildeposito.tv';

  // Breakpoint group.
  $breakpoint_group = new stdClass();
  $breakpoint_group->disabled = FALSE; /* Edit this to true to make a default breakpoint_group disabled initially */
  $breakpoint_group->api_version = 1;
  $breakpoint_group->machine_name = 'seizoni_home';
  $breakpoint_group->name = 'seizoni_home';
  $breakpoint_group->breakpoints = $breakpoints;
  $breakpoint_group->type = 'custom';
  $breakpoint_group->overridden = 0;
  $export['seizoni_home'] = $breakpoint_group;

  return $export;
}
