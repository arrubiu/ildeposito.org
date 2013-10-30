<?php
/**
 * @file
 *   Default view export.
 */

$view = new view();
$view->name = 'commitlog_commit_items';
$view->description = 'VersionControl Commit Items';
$view->tag = 'VersionControl Core';
$view->base_table = 'versioncontrol_item_revisions';
$view->human_name = '';
$view->core = 0;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'default';
$handler->display->display_options['style_options']['grouping'] = '';
$handler->display->display_options['row_plugin'] = 'fields';
/* Field: VersionControl Item Revisions: File path */
$handler->display->display_options['fields']['path']['id'] = 'path';
$handler->display->display_options['fields']['path']['table'] = 'versioncontrol_item_revisions';
$handler->display->display_options['fields']['path']['field'] = 'path';
$handler->display->display_options['fields']['path']['label'] = '';
$handler->display->display_options['fields']['path']['link_type'] = 'log';
/* Contextual filter: VersionControl Operations: Operation ID */
$handler->display->display_options['arguments']['vc_op_id']['id'] = 'vc_op_id';
$handler->display->display_options['arguments']['vc_op_id']['table'] = 'versioncontrol_operations';
$handler->display->display_options['arguments']['vc_op_id']['field'] = 'vc_op_id';
$handler->display->display_options['arguments']['vc_op_id']['exception']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['vc_op_id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['vc_op_id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['vc_op_id']['specify_validation'] = TRUE;

/* Display: With name */
$handler = $view->new_display('block', 'With name', 'block_2');
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: VersionControl Repository: Repository Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'versioncontrol_repositories';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['exclude'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['path'] = 'project/[name]';
/* Field: VersionControl Item Revisions: File path */
$handler->display->display_options['fields']['path']['id'] = 'path';
$handler->display->display_options['fields']['path']['table'] = 'versioncontrol_item_revisions';
$handler->display->display_options['fields']['path']['field'] = 'path';
$handler->display->display_options['fields']['path']['label'] = '';
$handler->display->display_options['fields']['path']['exclude'] = TRUE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '[name]: [path]';

/* Display: With diffstat */
$handler = $view->new_display('block', 'With diffstat', 'block_1');
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: VersionControl Item Revisions: File path */
$handler->display->display_options['fields']['path']['id'] = 'path';
$handler->display->display_options['fields']['path']['table'] = 'versioncontrol_item_revisions';
$handler->display->display_options['fields']['path']['field'] = 'path';
$handler->display->display_options['fields']['path']['label'] = '';
/* Field: VersionControl Item Revisions: Lines changed */
$handler->display->display_options['fields']['changed_lines']['id'] = 'changed_lines';
$handler->display->display_options['fields']['changed_lines']['table'] = 'versioncontrol_item_revisions';
$handler->display->display_options['fields']['changed_lines']['field'] = 'changed_lines';
$handler->display->display_options['fields']['changed_lines']['label'] = '';
/* Field: VersionControl Item Revisions: Visual diffstat */
$handler->display->display_options['fields']['visual_diffstat']['id'] = 'visual_diffstat';
$handler->display->display_options['fields']['visual_diffstat']['table'] = 'versioncontrol_item_revisions';
$handler->display->display_options['fields']['visual_diffstat']['field'] = 'visual_diffstat';
$handler->display->display_options['fields']['visual_diffstat']['label'] = '';

/* Display: With name & diffstat */
$handler = $view->new_display('block', 'With name & diffstat', 'block_3');
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: VersionControl Repository: Repository Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'versioncontrol_repositories';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['exclude'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['path'] = 'project/[name]';
/* Field: VersionControl Item Revisions: File path */
$handler->display->display_options['fields']['path']['id'] = 'path';
$handler->display->display_options['fields']['path']['table'] = 'versioncontrol_item_revisions';
$handler->display->display_options['fields']['path']['field'] = 'path';
$handler->display->display_options['fields']['path']['label'] = '';
$handler->display->display_options['fields']['path']['exclude'] = TRUE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '[name]: [path]';
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
/* Field: VersionControl Item Revisions: Visual diffstat */
$handler->display->display_options['fields']['visual_diffstat']['id'] = 'visual_diffstat';
$handler->display->display_options['fields']['visual_diffstat']['table'] = 'versioncontrol_item_revisions';
$handler->display->display_options['fields']['visual_diffstat']['field'] = 'visual_diffstat';
$handler->display->display_options['fields']['visual_diffstat']['label'] = '';
/* Field: VersionControl Item Revisions: Lines changed */
$handler->display->display_options['fields']['changed_lines']['id'] = 'changed_lines';
$handler->display->display_options['fields']['changed_lines']['table'] = 'versioncontrol_item_revisions';
$handler->display->display_options['fields']['changed_lines']['field'] = 'changed_lines';
$handler->display->display_options['fields']['changed_lines']['label'] = '';

/* Display: File only */
$handler = $view->new_display('block', 'File only', 'block_4');
