<?php

/**
 * @file Preprocess page
 */

/**
 * Implements hook_preprocess_page.
 */
function ildepositoboot_preprocess_page(&$vars) {

  $ubuntu_font = array(
      '#tag' => 'link',
      '#attributes' => array(
        'rel' => 'stylesheet',
        'href' => 'https://fonts.googleapis.com/css?family=Ubuntu',
        'type' => 'text/css',
      ),
  );
  drupal_add_html_head($ubuntu_font, 'link');

  $theme_path = drupal_get_path('theme', 'ildepositoboot');

  /** HEADER COMPONENTS */
  //Common variables for header
  $img = array(
    'path' => $theme_path . '/images/logo.svg',
    'alt' => 'logo',
  );
  $vars['logo'] = l(theme('image', $img), $GLOBALS['base_path'], array('html'=>TRUE, 'attributes'=>array('id'=>'logo')));

  $img = array(
    'path' => $theme_path . '/images/title.svg',
    'alt' => 'ilDeposito.org',
  );
  $vars['site_title'] = l(theme('image', $img), $GLOBALS['base_path'], array('html'=>TRUE, 'attributes'=>array('id'=>'title')));

  $img = array(
    'path' => $theme_path . '/images/subtitle.svg',
    'alt' => 'canti di protesta politica e sociale',
  );
  $vars['site_subtitle'] = l(theme('image', $img), $GLOBALS['base_path'], array('html'=>TRUE, 'attributes'=>array('id'=>'subtitle')));


  $block = block_load('system','user-menu');
  $block_array = _block_get_renderable_array(_block_render_blocks(array($block)));
  $vars['top_right_menu'] = render($block_array);

  $block = block_load('menu','menu-top-menu');
  $block_array = _block_get_renderable_array(_block_render_blocks(array($block)));
  $vars['top_menu'] = render($block_array);

  $block = block_load('menu','menu-sub-menu');
  $block_array = _block_get_renderable_array(_block_render_blocks(array($block)));
  $vars['sub_menu'] = render($block_array);

  /*$block = block_load('menu','menu-sub-menu');
  $block_array = _block_get_renderable_array(_block_render_blocks(array($block)));
  $vars['search_form'] = render($block_array);*/

  /** END HEADER COMPONENTS **/





  /** FOOTER COMPONENTS **/
  $block = block_load('menu','menu-footer');
  $block_array = _block_get_renderable_array(_block_render_blocks(array($block)));
  $vars['footer_menu'] = render($block_array);

  /** END FOOTER COMPONENTS */

}