<?php

/**
 * @file
 * Provides tokens, for use with page_title module.
 */

/**
 * Implements hook_token_info().
 */
function taxonomy_title_token_info() {
  $info['tokens']['term']['title'] = array(
    'name' => t('Term title'),
    'description' => t("The term's title, defaults to term name (same as [term:name]) if no title provided."),
    'needs-data' => 'term',
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function taxonomy_title_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);

  if ($type == 'term' && !empty($data['term'])) {
    $term = $data['term'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'title':
          $title = _taxonomy_title_get_title($term->tid);
          if ($title) {
            $replacements[$original] = ($sanitize) ? check_plain($title) : $title;
          }
          else {
            $replacements[$original] = $term->name;
          }
          break;
      }
    }
  }

  return $replacements;
}