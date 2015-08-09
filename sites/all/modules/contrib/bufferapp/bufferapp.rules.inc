<?php

/**
 * Implements hook_rules_action_info().
 */
function bufferapp_rules_action_info() {
  $actions = array(
      'bufferapp_rules_send' => array(
          'label' => t('Send Buffer update'),
          'group' => t('Bufferapp'),
          'parameter' => array(
              'text' => array(
                  'type' => 'text',
                  'required' => TRUE,
                  'label' => t('Text'),
              ),
              'link' => array(
                  'type' => 'text',
                  'label' => t('Link URL'),
              ),
              'link_title' => array(
                  'type' => 'text',
                  'label' => t('Link title'),
              ),
              'link_description' => array(
                  'type' => 'text',
                  'label' => t('Link description'),
              ),
              'share_now' => array(
                  'type' => 'boolean',
                  'label' => t('Share now'),
                  'description' => t('If enabled, updates will be published immediatelly to social profiles')
              ),
          ),
      ),
  );
  return $actions;
}

/**
 * Prepare data and then send them to Buffer
 */
function bufferapp_rules_send($text, $link_url, $link_title, $link_description, $share_now) {
  $text = strip_tags($text);
  $media = array();

  if ($link_url != '') {
    $media = array(
        'link' => $link_url,
        'title' => strip_tags($link_title),
        'description' => strip_tags($link_description),
    );
  }

  bufferapp_data(TRUE, NULL, $text, $media, $share_now);
}