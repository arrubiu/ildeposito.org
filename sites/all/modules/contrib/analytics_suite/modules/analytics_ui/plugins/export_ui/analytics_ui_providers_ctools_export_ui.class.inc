<?php

/**
 * @file
 */

class analytics_ui_providers_ctools_export_ui extends ctools_export_ui {

  function list_sort_options() {
    return array(
      'disabled' => t('Enabled'),
      'machine_name' => t('Machine name'),
      'description' => t('Description'),
      'storage' => t('Storage'),
    );
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
      case 'storage':
        $this->sorts[$object->machine_name] = strtolower($object->type . $object->machine_name);
        break;
    }

    $ops = theme('links__ctools_dropbutton', array('links' => $operations, 'attributes' => array('class' => array('links', 'inline'))));

    $this->rows[$object->machine_name] = array(
      'data' => array(
        array('data' => $object->machine_name, 'class' => array('providers-ui-name')),
        array('data' => check_plain($object->description), 'class' => array('providers-ui-description')),
        array('data' => $object->type, 'class' => array('providers-ui-storage')),
        array('data' => $ops, 'class' => array('providers-ui-operations')),
      ),
      'title' => t('Machine name: ') . check_plain($object->machine_name),
      'class' => array(!empty($object->disabled) ? 'ctools-export-ui-disabled' : 'ctools-export-ui-enabled'),
    );
  }

  function list_render(&$form_state) {
    $this->active = $form_state['values']['order'];
    $this->order = $form_state['values']['sort'];

    $header = array(
      array('data' => t('Machine name'), 'class' => array('providers-ui-name')),
      array('data' => t('Description'), 'class' => array('providers-ui-description')),
      array('data' => t('Storage'), 'class' => array('providers-ui-storage')),
      array('data' => t('Operations'), 'class' => array('providers-ui-operations')),
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