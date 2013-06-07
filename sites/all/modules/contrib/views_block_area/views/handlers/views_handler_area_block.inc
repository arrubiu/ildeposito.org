<?php

/**
 * @file
 * Block area handlers. Insert a block inside of an area.
 */
class views_handler_area_block extends views_handler_area {

  function option_definition() {

    $options = parent::option_definition();
    $options['block_to_insert'] = array('default' => '');
    $options['title'] = array('default' => '');

    return $options;

  }

  /**
   * Default options form that provides the label widget that all fields
   * should have.
   */
  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);

    $query = db_select('block', 'b');
    $result = $query
      ->fields('b')
      ->orderBy('b.module')
      ->condition('b.module', 'views', '!=')
      ->addTag('block_load')
      ->addTag('translatable')
      ->execute();

    $block_info = $result->fetchAllAssoc('bid');
    // Allow modules to modify the block list.
    drupal_alter('block_list', $block_info);

    $options = array();
    foreach ($block_info as $block) {
      $options["{$block->module}:{$block->delta}"] = "{$block->module}:{$block->delta}"; // @TODO: fetch the correct block title
    }

    $form['block_to_insert'] = array(
      '#type' => 'select',
      '#title' => t('Block to insert'),
      '#default_value' => $this->options['block_to_insert'],
      '#description' => t('The block to insert into this area.'),
      '#options' => $options,
    );

    $form['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Block title'),
      '#default_value' => $this->options['title'],
      '#description' => t('Override the title for the block. Use &lt;none&gt; to display no title, or leave blank to use the block title from block settings.'),
    );

  }

  /**
   * Render the area
   */
  function render($empty = FALSE) {

    if ((!$empty || !empty($this->options['empty'])) && !empty($this->options['block_to_insert'])) {

      list ($module, $delta) = explode(':', $this->options['block_to_insert'], 2);
      $block = block_load($module, $delta);
      if (empty($block)) {
        return;
      }

      if (!empty($this->options['title'])) {
        $block->title = $this->options['title'];
      }

      $block_content = _block_render_blocks(array($block));

      $build = _block_get_renderable_array($block_content);
      return drupal_render($build);

    }

    return '';

  }

}