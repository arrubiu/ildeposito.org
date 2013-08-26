<?php
/**
 * @file
 * seotools.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function seotools_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'insight_contentanalysis_autorun_analyzers';
  $strongarm->value = array(
    'seo' => 'seo',
    'insight_content' => 0,
  );
  $export['insight_contentanalysis_autorun_analyzers'] = $strongarm;

  return $export;
}
