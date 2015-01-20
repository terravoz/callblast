<?php

/**
 * @file
 * Views hooks.
 */

/**
 * Implements hook_views_data_alter().
 */
function voipqueue_views_data_alter(&$data) {
  $data['advancedqueue']['status']['field']['handler'] = 'voipqueue_handler_field_status';
}

/**
 * Implements hook_views_data().
 */
function voipqueue_views_data() {
  $data = array();

  $data['voipqueue_calls']['table']['group'] = t('VoIP Queue');
  // Available as a base table.
  $data['voipqueue_calls']['table']['base'] = array(
    'field' => 'item_id',
    'title' => t('VoIP Queue'),
    'help' => t('VoIP Queue.'),
  );

  // Fields.
  $data['voipqueue_calls']['cid'] = array(
    'title' => t('VoIP call ID'),
    'help' => t('Internal VoIP numeric ID'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'title',
      'zero is null' => TRUE,
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'voipcall',
      'base field' => 'cid',
      'label' => t('voipcall'),
    ),
  );

  $data['voipqueue_calls']['item_id'] = array(
    'title' => t('AdvancedQueue Item ID'),
    'help' => t('The unique AdvancedQueue id of this item.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'advancedqueue',
      'base field' => 'item_id',
      'label' => t('advancedqueue'),
    ),
  );

  $data['voipqueue_calls']['table']['join'] = array(
    'advancedqueue' => array(
      'left_field' => 'item_id',
      'field' => 'item_id',
    ),
  );

  $data['voipqueue_calls']['table']['join'] = array(
    'voipcall' => array(
      'left_field' => 'cid',
      'field' => 'cid',
    ),
  );

  return $data;
}
