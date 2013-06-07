<?php

/**
 * @file
 * Contains the cache reaction class.
 */

/**
 * Main functions to set and run the cache reaction.
 */
class ContextReactionCache extends context_reaction {

  /**
   * Implements Context hook, options_form.
   */
  public function options_form($context) {
    $values = $this->fetch_from_context($context);

    // Create a type default value by checking if page cache is enabled.
    $type_default = variable_get('cache', 0) ? 'internal' : 'external';

    // If no values are set use the default type.
    $type = !empty($values['type']) ? $values['type'] : $type_default;

    // Grab the cache_lifetime variable from the performance page.
    $lifetime_default = variable_get('cache_lifetime', 7200);

    // Use cache_lifetime as default value for this context's lifetime.
    $lifetime = isset($values['lifetime']) ?
        $values['lifetime'] : $lifetime_default;

    // Make sure the acquired default is numeric.
    if (!is_numeric($lifetime) || $lifetime < 60) {
      $lifetime = 0;
    }

    // Description for the Caching field.
    $type_description = t('!starPage caching needs to be enabled in order to use "Internal", it is currently !status, edit this on the !link. "Internal" controls Drupal\'s page cache and "External" sets the proper headers for an external cache, while "Disabled" disables page caching and sends strict headers to prevent caching (no-cache/must-revalidate).', array(
        '!star' => variable_get('cache', 0) ? '' : '* ',
        '!status' => '<strong>' . (variable_get('cache', 0) ? t('enabled') : t('disabled')) . '</strong>',
        '!link' => l(t('performance page'), 'admin/config/development/performance'),
      ));

    // Radios to select which cache this context controls, internal or external.
    $items['type'] = array(
      '#type' => 'radios',
      '#title' => t('Caching'),
      '#default_value' => $type,
      '#options' => array(
        'disabled' => 'Disabled',
        'internal' => 'Internal' . (variable_get('cache', 0) ? '' : '*'),
        'external' => 'External',
      ),
      '#description' => $type_description,
    );

    // Options for the Cache Lifetime field.
    $options = array(
      0 => t('None'),
      60  => t('1 min'),
      120 => t('2 min'),
      180 => t('3 min'),
      300 => t('5 min'),
      600 => t('10 min'),
      900 => t('15 min'),
      1800 => t('30 min'),
      2700 => t('45 min'),
      3600 => t('1 hour'),
      7200 => t('2 hours'),
      10800 => t('3 hours'),
      21600 => t('6 hours'),
      32400 => t('9 hours'),
      43200 => t('12 hours'),
      86400 => t('1 day'),
      172800 => t('2 days'),
      604800 => t('7 days'),
      1209600 => t('14 days'),
      2592000 => t('1 month'),
      2592000 => t('2 months'),
      2592000 => t('3 months'),
      2592000 => t('6 months'),
      2592000 => t('1 year'),
    );

    // Drop-down to select the lifetime of the cache.
    $items['lifetime'] = array(
      '#type' => 'select',
      '#title' => t('Cache Lifetime'),
      '#default_value' => $lifetime,
      '#options' => $options,
      '#description' => t('How long to keep this page. When set to none, external caches will not keep a copy of the page.'),
    );

    return $items;
  }

  /**
   * Implements Context hook, execute.
   */
  public function execute() {

    // If user is logged in don't continue.
    if (user_is_logged_in()) {
      return TRUE;
    }

    // Get the contexts and the saved values.
    $contexts = $this->get_contexts();

    // Goes through each context applicable to the condition.
    foreach ($contexts as $context) {

      // Load settings into $settings variable.
      if (isset($context->reactions['cache'])) {
        $settings = $context->reactions['cache'];

        // If disabled, disable cache and set no cache headers.
        if ($settings['type'] == 'disabled') {
          drupal_page_is_cacheable(FALSE);
          context_cache_nocache_header();
        }

        // If internal, set page cache and set expire headers.
        if ($settings['type'] == 'internal') {
          drupal_page_is_cacheable(($settings['lifetime'] ? TRUE : FALSE));
          context_cache_expire_header($settings['lifetime']);
        }

        // If external, disable page cache and set expire headers.
        if ($settings['type'] == 'external') {
          drupal_page_is_cacheable(FALSE);
          context_cache_expire_header($settings['lifetime']);
        }
      }
    }
  }
}
