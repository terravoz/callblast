<?php

/**
 * Implements hook_views_data_alter().
 */
function voipblast_views_data_alter(&$data) {
  if (isset($data['advancedqueue']['table'])) {
    $data['advancedqueue']['voipblast'] = array(
      'title' => $data['advancedqueue']['table']['group'],
      'group' => t('VoIP queue operations'),
      'help' => t('Provide a checkbox to select the aggregated rows for VoIP blast bulk operations.'),
//        'real field' => $info['entity keys']['id'],
      'field' => array(
        'handler' => 'voipblast_handler_field_operations',
        'click sortable' => FALSE,
      ),
    );
  }
}
