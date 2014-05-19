<?php

/**
 * @file
 * Default VoIP queue admin list view.
 */

function voipblast_scheduler_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'voipblast';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'advancedqueue';
  $view->human_name = 'VoIP Queue';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'VoIP Blast queue';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer voip drupal framework';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'voipblast' => 'voipblast',
    'tag' => 'tag',
    'status_1' => 'status_1',
    'status' => 'status',
    'name' => 'name',
    'date_start' => 'date_start',
    'date_end' => 'date_end',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'voipblast' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'tag' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'date_start' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'date_end' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Queue: VoIP Blast Schedule tag */
  $handler->display->display_options['relationships']['tag_blast']['id'] = 'tag_blast';
  $handler->display->display_options['relationships']['tag_blast']['table'] = 'advancedqueue_tags';
  $handler->display->display_options['relationships']['tag_blast']['field'] = 'tag_blast';
  /* Field: Queue: Item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  /* Field: Bulk operations: Queue */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::voipcallblast_add_dial_file_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::voipqueue_add_dial_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::voipqueue_add_text_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Queue: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Queue: Item status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Queue: Item title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Queue: Queue name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Field: Queue: Tag */
  $handler->display->display_options['fields']['tag']['id'] = 'tag';
  $handler->display->display_options['fields']['tag']['table'] = 'advancedqueue_tags';
  $handler->display->display_options['fields']['tag']['field'] = 'tag';
  $handler->display->display_options['fields']['tag']['exclude'] = TRUE;
  /* Field: Queue: Processed date */
  $handler->display->display_options['fields']['processed']['id'] = 'processed';
  $handler->display->display_options['fields']['processed']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['processed']['field'] = 'processed';
  $handler->display->display_options['fields']['processed']['date_format'] = 'time span';
  /* Field: Queue: Start date */
  $handler->display->display_options['fields']['date_start']['id'] = 'date_start';
  $handler->display->display_options['fields']['date_start']['table'] = 'voipblast_scheduler';
  $handler->display->display_options['fields']['date_start']['field'] = 'date_start';
  $handler->display->display_options['fields']['date_start']['relationship'] = 'tag_blast';
  $handler->display->display_options['fields']['date_start']['date_format'] = 'short';
  /* Field: Queue: End date */
  $handler->display->display_options['fields']['date_end']['id'] = 'date_end';
  $handler->display->display_options['fields']['date_end']['table'] = 'voipblast_scheduler';
  $handler->display->display_options['fields']['date_end']['field'] = 'date_end';
  $handler->display->display_options['fields']['date_end']['relationship'] = 'tag_blast';
  $handler->display->display_options['fields']['date_end']['date_format'] = 'short';
  /* Contextual filter: Queue: Tag */
  $handler->display->display_options['arguments']['tag']['id'] = 'tag';
  $handler->display->display_options['arguments']['tag']['table'] = 'advancedqueue_tags';
  $handler->display->display_options['arguments']['tag']['field'] = 'tag';
  $handler->display->display_options['arguments']['tag']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['tag']['title'] = '%1 blast';
  $handler->display->display_options['arguments']['tag']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tag']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tag']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tag']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['tag']['limit'] = '0';
  /* Filter criterion: Queue: Queue name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'advancedqueue';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'starts';
  $handler->display->display_options['filters']['name']['value'] = 'voipblast';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/voip/blast/%';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'VoIP Queue';
  $handler->display->display_options['menu']['description'] = 'Queued calls and SMS';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: VoIP queue operations: Queue */
  $handler->display->display_options['fields']['voipblast']['id'] = 'voipblast';
  $handler->display->display_options['fields']['voipblast']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['voipblast']['field'] = 'voipblast';
  $handler->display->display_options['fields']['voipblast']['label'] = '';
  $handler->display->display_options['fields']['voipblast']['element_label_colon'] = FALSE;
  /* Field: Queue: Tag */
  $handler->display->display_options['fields']['tag']['id'] = 'tag';
  $handler->display->display_options['fields']['tag']['table'] = 'advancedqueue_tags';
  $handler->display->display_options['fields']['tag']['field'] = 'tag';
  $handler->display->display_options['fields']['tag']['label'] = 'Name';
  $handler->display->display_options['fields']['tag']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['tag']['alter']['path'] = 'admin/voip/blast/[tag]';
  /* Field: Queue: Item status */
  $handler->display->display_options['fields']['status_1']['id'] = 'status_1';
  $handler->display->display_options['fields']['status_1']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['status_1']['field'] = 'status';
  $handler->display->display_options['fields']['status_1']['group_type'] = 'count';
  $handler->display->display_options['fields']['status_1']['label'] = 'Number in queue';
  /* Field: Queue: Item status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  /* Field: Queue: Queue name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'advancedqueue';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Field: Queue: Start date */
  $handler->display->display_options['fields']['date_start']['id'] = 'date_start';
  $handler->display->display_options['fields']['date_start']['table'] = 'voipblast_scheduler';
  $handler->display->display_options['fields']['date_start']['field'] = 'date_start';
  $handler->display->display_options['fields']['date_start']['relationship'] = 'tag_blast';
  $handler->display->display_options['fields']['date_start']['date_format'] = 'short';
  /* Field: Queue: End date */
  $handler->display->display_options['fields']['date_end']['id'] = 'date_end';
  $handler->display->display_options['fields']['date_end']['table'] = 'voipblast_scheduler';
  $handler->display->display_options['fields']['date_end']['field'] = 'date_end';
  $handler->display->display_options['fields']['date_end']['relationship'] = 'tag_blast';
  $handler->display->display_options['fields']['date_end']['date_format'] = 'short';
  $handler->display->display_options['path'] = 'admin/voip/blast/summary';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Summary';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $export['voipblast'] = $view;
  return $export;
}
