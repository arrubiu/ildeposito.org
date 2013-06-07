<?php

/**
 * implementation of hook_panels_layouts
 */
// Plugin definition
$plugin = array(
  'title' => t('Home Deposito'),
  'category' => t('Columns: 3'),
  'icon' => 'threecol_25_50_25.png',
  'theme' => 'home-3',
  'theme arguments' => array('id', 'content'),
  'css' => 'threecol_25_50_25.css',
  'regions' => array(
    'left' => t('Left side'),
    'middle' => t('Middle column'),
    'right' => t('Right side')
  ),
);

