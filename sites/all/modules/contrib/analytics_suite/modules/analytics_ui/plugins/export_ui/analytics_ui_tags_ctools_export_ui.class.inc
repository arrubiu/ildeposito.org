<?php

/**
 * @file
 */

class analytics_ui_tags_ctools_export_ui extends ctools_export_ui {
  function list_sort_options() {
    return array(
      'disabled' => t('Enabled'),
      'machine_name' => t('Machine name'),
      'description' => t('Description'),
      'provider' => t('Provider'),
      'storage' => t('Storage'),
    );
  }

  function list_form(&$form, &$form_state) {
    parent::list_form($form, $form_state);

    $providers = analytics_provider_load_all();
    $options = array('all' => t('- All -'));
    foreach($providers as $provider) {
      $options[$provider->machine_name] = $provider->description;
    }
    $form['top row']['provider'] = array(
      '#type' => 'select',
      '#title' => t('Provider'),
      '#options' => $options,
      '#weight' => -10
    );
  }

  function list_filter($form_state, $object) {
    if ($form_state['values']['provider'] != 'all') {
      return $object->provider != $form_state['values']['provider'];
    }

    return parent::list_filter($form_state, $object);
  }

  function list_build_row($object, &$form_state, $operations) {

    // Set up sorting
    switch ($form_state['values']['order']) {
      case 'disabled':
        $this->sorts[$object->machine_name] = strtolower(empty($object->disabled) . $object->machine_name);
        break;
      case 'machine_name':
        $this->sorts[$object->machine_name] = strtolower($object->machine_name);
        break;
      case 'description':
        $this->sorts[$object->machine_name] = strtolower($object->description);
        break;
      case 'provider':
        $this->sorts[$object->machine_name] = strtolower($object->provider);
        break;
      case 'storage':
        $this->sorts[$object->machine_name] = strtolower($object->type . $object->machine_name);
        break;
    }

    $ops = theme('links__ctools_dropbutton', array('links' => $operations, 'attributes' => array('class' => array('links', 'inline'))));

    $this->rows[$object->machine_name] = array(
      'data' => array(
        array('data' => $object->machine_name, 'class' => array('tags-ui-name')),
        array('data' => check_plain($object->description), 'class' => array('tags-ui-description')),
        array('data' => $object->provider, 'class' => array('tags-ui-provider')),
        array('data' => $object->type, 'class' => array('tags-ui-storage')),
        array('data' => $ops, 'class' => array('tags-ui-operations')),
      ),
      'title' => t('Machine name: ') . check_plain($object->machine_name),
      'class' => array(!empty($object->disabled) ? 'ctools-export-ui-disabled' : 'ctools-export-ui-enabled'),
    );
  }

  function list_render(&$form_state) {
    $this->active = $form_state['values']['order'];
    $this->order = $form_state['values']['sort'];

    $header = array(
      array('data' => t('Machine name'), 'class' => array('tags-ui-name')),
      array('data' => t('Description'), 'class' => array('tags-ui-description')),
      array('data' => t('Provider'), 'class' => array('tags-ui-provider')),
      array('data' => t('Storage'), 'class' => array('tags-ui-storage')),
      array('data' => t('Operations'), 'class' => array('tags-ui-operations')),
    );

    $table = array(
      'header' => $header,
      'rows' => $this->rows,
      'empty' => t('No providers match the search criteria.'),
      'attributes' => array('id' => 'ctools-export-ui-list-items'),
    );
    return theme('table', $table);
  }
}

?>
