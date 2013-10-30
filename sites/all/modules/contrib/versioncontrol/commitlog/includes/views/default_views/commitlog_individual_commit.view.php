<?php
/**
 * @file
 *   Default view export.
 */

$view = new view();
$view->name = 'commitlog_individual_commit';
$view->description = 'Commitlog Global Commit Log';
$view->tag = 'VersionControl Core';
$view->base_table = 'versioncontrol_operations';
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
$handler->display->display_options['row_plugin'] = 'fields';
/* Field: VersionControl Operations: Attribution */
$handler->display->display_options['fields']['attribution']['id'] = 'attribution';
$handler->display->display_options['fields']['attribution']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['attribution']['field'] = 'attribution';
$handler->display->display_options['fields']['attribution']['label'] = '';
$handler->display->display_options['fields']['attribution']['exclude'] = TRUE;
/* Field: VersionControl Operations: Operation ID */
$handler->display->display_options['fields']['vc_op_id']['id'] = 'vc_op_id';
$handler->display->display_options['fields']['vc_op_id']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['vc_op_id']['field'] = 'vc_op_id';
$handler->display->display_options['fields']['vc_op_id']['label'] = '';
$handler->display->display_options['fields']['vc_op_id']['exclude'] = TRUE;
$handler->display->display_options['fields']['vc_op_id']['element_label_colon'] = FALSE;
/* Field: VersionControl Operations: Author date */
$handler->display->display_options['fields']['author_date']['id'] = 'author_date';
$handler->display->display_options['fields']['author_date']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['author_date']['field'] = 'author_date';
$handler->display->display_options['fields']['author_date']['label'] = '';
$handler->display->display_options['fields']['author_date']['exclude'] = TRUE;
$handler->display->display_options['fields']['author_date']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['author_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['author_date']['custom_date_format'] = 'F j, Y G:i';
$handler->display->display_options['fields']['author_date']['link'] = 0;
/* Field: VersionControl Operations: List of label this operation is in */
$handler->display->display_options['fields']['labels']['id'] = 'labels';
$handler->display->display_options['fields']['labels']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['labels']['field'] = 'labels';
$handler->display->display_options['fields']['labels']['label'] = '';
$handler->display->display_options['fields']['labels']['exclude'] = TRUE;
/* Field: VersionControl Operations: Revision */
$handler->display->display_options['fields']['revision']['id'] = 'revision';
$handler->display->display_options['fields']['revision']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['revision']['field'] = 'revision';
$handler->display->display_options['fields']['revision']['label'] = '';
$handler->display->display_options['fields']['revision']['exclude'] = TRUE;
$handler->display->display_options['fields']['revision']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['revision']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['revision']['element_label_colon'] = FALSE;
/* Field: Operation text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['ui_name'] = 'Operation text';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="commit-global">
  <h3>[author_date]</h3>
  <div class="commit-info">Commit <strong>[revision]</strong> on <strong>[labels]</strong></div>
  <div class="attribtution">[attribution]</div>
</div>';
$handler->display->display_options['fields']['nothing']['alter']['path'] = '#';
$handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'global-author';
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
/* Field: Operation items */
$handler->display->display_options['fields']['view']['id'] = 'view';
$handler->display->display_options['fields']['view']['table'] = 'views';
$handler->display->display_options['fields']['view']['field'] = 'view';
$handler->display->display_options['fields']['view']['ui_name'] = 'Operation items';
$handler->display->display_options['fields']['view']['label'] = '';
$handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['view']['view'] = 'commitlog_commit_items';
$handler->display->display_options['fields']['view']['display'] = 'block_2';
$handler->display->display_options['fields']['view']['arguments'] = '[vc_op_id]';
$handler->display->display_options['fields']['view']['query_aggregation'] = 1;
/* Field: VersionControl Operations: Message */
$handler->display->display_options['fields']['message']['id'] = 'message';
$handler->display->display_options['fields']['message']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['message']['field'] = 'message';
$handler->display->display_options['fields']['message']['label'] = '';
$handler->display->display_options['fields']['message']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['message']['alter']['text'] = '<pre>[message]</pre>';
$handler->display->display_options['fields']['message']['element_label_colon'] = FALSE;
/* Sort criterion: VersionControl Operations: Author date */
$handler->display->display_options['sorts']['author_date']['id'] = 'author_date';
$handler->display->display_options['sorts']['author_date']['table'] = 'versioncontrol_operations';
$handler->display->display_options['sorts']['author_date']['field'] = 'author_date';
$handler->display->display_options['sorts']['author_date']['order'] = 'DESC';
/* Contextual filter: VersionControl Repository: Repository ID */
$handler->display->display_options['arguments']['repo_id']['id'] = 'repo_id';
$handler->display->display_options['arguments']['repo_id']['table'] = 'versioncontrol_repositories';
$handler->display->display_options['arguments']['repo_id']['field'] = 'repo_id';
$handler->display->display_options['arguments']['repo_id']['default_action'] = 'not found';
$handler->display->display_options['arguments']['repo_id']['exception']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['repo_id']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['repo_id']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['repo_id']['specify_validation'] = TRUE;
/* Contextual filter: VersionControl Operations: Revision */
$handler->display->display_options['arguments']['revision']['id'] = 'revision';
$handler->display->display_options['arguments']['revision']['table'] = 'versioncontrol_operations';
$handler->display->display_options['arguments']['revision']['field'] = 'revision';
$handler->display->display_options['arguments']['revision']['default_action'] = 'not found';
$handler->display->display_options['arguments']['revision']['exception']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['revision']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['revision']['title'] = 'Revision %2';
$handler->display->display_options['arguments']['revision']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['revision']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['revision']['specify_validation'] = TRUE;
$handler->display->display_options['arguments']['revision']['limit'] = '0';
