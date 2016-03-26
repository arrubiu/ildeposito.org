<?php
/**
 * @file
 * ildeposito_gruppi.custom_formatters.inc
 */

/**
 * Implements hook_custom_formatters_defaults().
 */
function ildeposito_gruppi_custom_formatters_defaults() {
  $export = array();

  $formatter = new stdClass();
  $formatter->disabled = FALSE; /* Edit this to true to make a default formatter disabled initially */
  $formatter->api_version = 2;
  $formatter->name = 'indirizzo_gruppi';
  $formatter->label = 'Indirizzo gruppi';
  $formatter->description = 'Formattazione indirizzo per i gruppi.';
  $formatter->mode = 'token';
  $formatter->field_types = 'addressfield';
  $formatter->code = '<div>[node:field_indirizzo:name-line]</div>
[node:field_indirizzo:thoroughfare], [node:field_indirizzo:locality] ([node:field_indirizzo:administrative-area-raw])';
  $formatter->fapi = '';
  $export['indirizzo_gruppi'] = $formatter;

  return $export;
}
