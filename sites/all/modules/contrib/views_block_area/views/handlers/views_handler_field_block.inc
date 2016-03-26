<?php
/**
 * @file
 * Block area handlers. Insert a block inside of an area.
 */
class views_handler_field_block extends views_handler_field {

  function query() {
    // do nothing -- to override the parent query.
  }

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
    $query->leftJoin('block_custom', 'c', 'b.delta = c.bid AND b.module = :module', array(':module' => 'block'));
    $result = $query
      ->fields('b')
      ->fields('c', array('info'))
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
      $options["{$block->module}:{$block->delta}"] = t('@module:@delta@title', array(
        '@module' => $block->module,
        '@delta' => $block->delta,
        '@title' => (!empty($block->info)) ? ' (' . $block->info .')' :
           (($block->title == '<none>' || $block->title == '') ? '' : ' (' . $block->title . ')'),
      ));
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
  function render($values) {

    if (!empty($this->options['block_to_insert'])) {

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
