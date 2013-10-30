<?php
/**
 * @file
 *   Default view export.
 */

$view = new view();
$view->name = 'commitlog_global_commits';
$view->description = 'Commitlog Global Commit Log';
$view->tag = 'VersionControl Core';
$view->base_table = 'versioncontrol_operations';
$view->human_name = '';
$view->core = 0;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = 'All commits';
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'list';
$handler->display->display_options['style_options']['grouping'] = '';
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
$handler->display->display_options['fields']['vc_op_id']['exclude'] = TRUE;
/* Field: VersionControl Operations: Author date */
$handler->display->display_options['fields']['author_date']['id'] = 'author_date';
$handler->display->display_options['fields']['author_date']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['author_date']['field'] = 'author_date';
$handler->display->display_options['fields']['author_date']['exclude'] = TRUE;
$handler->display->display_options['fields']['author_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['author_date']['custom_date_format'] = 'F j, Y G:i';
$handler->display->display_options['fields']['author_date']['link'] = 1;
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
$handler->display->display_options['fields']['revision']['exclude'] = TRUE;
$handler->display->display_options['fields']['revision']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['revision']['alter']['ellipsis'] = FALSE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="commit-global">
  <h3>[author_date]</h3>
  <div class="commit-info">Commit <strong>[revision]</strong> on <strong>[labels]</strong></div>
  <div class="attribtution">[attribution]</div>
</div>';
$handler->display->display_options['fields']['nothing']['alter']['path'] = '#';
$handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'global-author';
/* Field: Global: View */
$handler->display->display_options['fields']['view']['id'] = 'view';
$handler->display->display_options['fields']['view']['table'] = 'views';
$handler->display->display_options['fields']['view']['field'] = 'view';
$handler->display->display_options['fields']['view']['label'] = '';
$handler->display->display_options['fields']['view']['view'] = 'commitlog_commit_items';
$handler->display->display_options['fields']['view']['display'] = 'block_2';
$handler->display->display_options['fields']['view']['arguments'] = '[vc_op_id]';
$handler->display->display_options['fields']['view']['query_aggregation'] = 1;
/* Field: VersionControl Operations: Message */
$handler->display->display_options['fields']['message']['id'] = 'message';
$handler->display->display_options['fields']['message']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['message']['field'] = 'message';
$handler->display->display_options['fields']['message']['label'] = '';
$handler->display->display_options['fields']['message']['exclude'] = TRUE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_1']['label'] = '';
$handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<pre>[message]</pre>';
/* Sort criterion: VersionControl Operations: Author date */
$handler->display->display_options['sorts']['author_date']['id'] = 'author_date';
$handler->display->display_options['sorts']['author_date']['table'] = 'versioncontrol_operations';
$handler->display->display_options['sorts']['author_date']['field'] = 'author_date';
$handler->display->display_options['sorts']['author_date']['order'] = 'DESC';

/* Display: Feed */
$handler = $view->new_display('feed', 'Feed', 'feed');
$handler->display->display_options['style_plugin'] = 'rss';
$handler->display->display_options['row_plugin'] = 'rss_fields';
$handler->display->display_options['row_options']['title_field'] = 'nothing';
$handler->display->display_options['row_options']['link_field'] = 'nothing_2';
$handler->display->display_options['row_options']['description_field'] = 'nothing_1';
$handler->display->display_options['row_options']['creator_field'] = 'author';
$handler->display->display_options['row_options']['date_field'] = 'committer_date';
$handler->display->display_options['row_options']['guid_field_options'] = array(
  'guid_field' => 'nothing_2',
  'guid_field_is_permalink' => 0,
);
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: VersionControl Operations: Attribution */
$handler->display->display_options['fields']['attribution']['id'] = 'attribution';
$handler->display->display_options['fields']['attribution']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['attribution']['field'] = 'attribution';
$handler->display->display_options['fields']['attribution']['label'] = '';
$handler->display->display_options['fields']['attribution']['exclude'] = TRUE;
$handler->display->display_options['fields']['attribution']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['attribution']['plain_text_output'] = 1;
/* Field: VersionControl Operations: List of label this operation is in */
$handler->display->display_options['fields']['labels']['id'] = 'labels';
$handler->display->display_options['fields']['labels']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['labels']['field'] = 'labels';
$handler->display->display_options['fields']['labels']['label'] = '';
$handler->display->display_options['fields']['labels']['exclude'] = TRUE;
$handler->display->display_options['fields']['labels']['element_label_colon'] = FALSE;
/* Field: VersionControl Operations: Revision - short */
$handler->display->display_options['fields']['revision']['id'] = 'revision';
$handler->display->display_options['fields']['revision']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['revision']['field'] = 'revision';
$handler->display->display_options['fields']['revision']['ui_name'] = 'VersionControl Operations: Revision - short';
$handler->display->display_options['fields']['revision']['exclude'] = TRUE;
$handler->display->display_options['fields']['revision']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['revision']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['revision']['plain_text_output'] = 1;
/* Field: Feed item title */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['ui_name'] = 'Feed item title';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'Commit [revision] on [labels] [attribution]';
$handler->display->display_options['fields']['nothing']['alter']['path'] = '#';
$handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'global-author';
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
/* Field: VersionControl Repository: Repository ID */
$handler->display->display_options['fields']['repo_id']['id'] = 'repo_id';
$handler->display->display_options['fields']['repo_id']['table'] = 'versioncontrol_repositories';
$handler->display->display_options['fields']['repo_id']['field'] = 'repo_id';
$handler->display->display_options['fields']['repo_id']['exclude'] = TRUE;
/* Field: VersionControl Operations: Revision - full */
$handler->display->display_options['fields']['revision_1']['id'] = 'revision_1';
$handler->display->display_options['fields']['revision_1']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['revision_1']['field'] = 'revision';
$handler->display->display_options['fields']['revision_1']['ui_name'] = 'VersionControl Operations: Revision - full';
$handler->display->display_options['fields']['revision_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['revision_1']['plain_text_output'] = 1;
$handler->display->display_options['fields']['revision_1']['operation_format'] = 'full';
/* Field: Feed item link */
$handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
$handler->display->display_options['fields']['nothing_2']['table'] = 'views';
$handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_2']['ui_name'] = 'Feed item link';
$handler->display->display_options['fields']['nothing_2']['label'] = '';
$handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'commitlog/commit/[repo_id]/[revision_1]';
$handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
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
$handler->display->display_options['fields']['author_date']['exclude'] = TRUE;
$handler->display->display_options['fields']['author_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['author_date']['custom_date_format'] = 'F j, Y G:i';
$handler->display->display_options['fields']['author_date']['link'] = 1;
/* Field: Commit items list */
$handler->display->display_options['fields']['view']['id'] = 'view';
$handler->display->display_options['fields']['view']['table'] = 'views';
$handler->display->display_options['fields']['view']['field'] = 'view';
$handler->display->display_options['fields']['view']['ui_name'] = 'Commit items list';
$handler->display->display_options['fields']['view']['label'] = '';
$handler->display->display_options['fields']['view']['exclude'] = TRUE;
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
$handler->display->display_options['fields']['message']['exclude'] = TRUE;
$handler->display->display_options['fields']['message']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['message']['alter']['text'] = '<pre>[message]</pre>';
$handler->display->display_options['fields']['message']['element_label_colon'] = FALSE;
/* Field: Feed item description */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Feed item description';
$handler->display->display_options['fields']['nothing_1']['label'] = '';
$handler->display->display_options['fields']['nothing_1']['alter']['text'] = '[view]
[message]';
$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
/* Field: VersionControl Operations: Author */
$handler->display->display_options['fields']['author']['id'] = 'author';
$handler->display->display_options['fields']['author']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['author']['field'] = 'author';
$handler->display->display_options['fields']['author']['label'] = '';
$handler->display->display_options['fields']['author']['exclude'] = TRUE;
$handler->display->display_options['fields']['author']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['author']['plain_text_output'] = 1;
/* Field: VersionControl Operations: Committer date */
$handler->display->display_options['fields']['committer_date']['id'] = 'committer_date';
$handler->display->display_options['fields']['committer_date']['table'] = 'versioncontrol_operations';
$handler->display->display_options['fields']['committer_date']['field'] = 'committer_date';
$handler->display->display_options['fields']['committer_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['committer_date']['custom_date_format'] = 'r';
$handler->display->display_options['fields']['committer_date']['link'] = 0;
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Sort criterion: VersionControl Operations: Committer date */
$handler->display->display_options['sorts']['committer_date']['id'] = 'committer_date';
$handler->display->display_options['sorts']['committer_date']['table'] = 'versioncontrol_operations';
$handler->display->display_options['sorts']['committer_date']['field'] = 'committer_date';
$handler->display->display_options['sorts']['committer_date']['order'] = 'DESC';
$handler->display->display_options['path'] = 'versioncontrol/garbage/path';
