<?php

/**
 * Implements hook_views_data()
 */
function voipblast_scheduler_views_data() {
  $data['voipblast_scheduler']['table']['group']  = t('Queue');

  $data['voipblast_scheduler']['queue_name'] = array(
    'title' => t('Queue name'),
    'help' => t('The queue name of the item'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'advancedqueue',
      'field' => 'name',
      'label' => t('Queue name'),
    ),
  );

  $data['voipblast_scheduler']['tag'] = array(
    'title' => t('Tag'),
    'help' => t('A tag associated with the queued item.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'advancedqueue_tags',
      'field' => 'tag',
      'label' => t('Queue tag'),
    ),
  );

  $data['voipblast_scheduler']['date_start'] = array(
    'title' => t('Start date'),
    'help' => t('The date the items are scheduled to start.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['voipblast_scheduler']['date_end'] = array(
    'title' => t('End date'),
    'help' => t('The date the blast is scheduled to stop.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  return $data;
}
