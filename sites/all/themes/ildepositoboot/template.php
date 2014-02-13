<?php

/**
 * @file
 * template.php
 */

/** 
 * Include di tutte le funzioni dentro preprocess 
 */
require 'preprocess/page.php.inc';
require 'preprocess/node.php.inc';
require 'preprocess/field.php.inc';
require 'preprocess/region.php.inc';
require 'inc/ildepositoboot.php.inc';


/**
 * Implements hook_facetapi_deactivate_widget
 * @param type $variables
 * @return string
 */
function ildepositoboot_facetapi_deactivate_widget($vars) {
	$sep = '<img src="' . $GLOBALS['base_path'] . '' . drupal_get_path('theme', 'ildepositoboot') . '/images/facet_uncheck.png" alt="-" title="Elimina filtro" class="icon" />';
	return $sep;
}

/**
 * Override of theme_tablesort_indicator().
 *
 * Use our own image versions, so they show up as black and not gray on gray.
 */
function ildepositoboot_tablesort_indicator($variables) {
	$style = $variables['style'];
	$theme_path = drupal_get_path('theme', 'ildepositoboot');
	if ($style == 'asc') {
		return theme('image', array('path' => $theme_path . '/images/facet_su.png', 'alt' => t('sort ascending'), 'title' => t('sort ascending')));
	} else {
		return theme('image', array('path' => $theme_path . '/images/facet_giu.png', 'alt' => t('sort descending'), 'title' => t('sort descending')));
	}
}
