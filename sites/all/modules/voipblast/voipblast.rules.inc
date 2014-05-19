<?php

/**
 * @file
 * VoIP Blast rules actions.
 */

/**
 * Implements hook_rules_action_info().
 */
function voipblast_rules_action_info() {
  // @todo add the existing actions too.
  $defaults = array(
    'parameter' => array(
      'queue_name' => array(
        'type' => 'text',
        'label' => t('Queue'),
        'description' => t('The name of the queue.'),
      ),
      'tag' => array(
        'type' => 'text',
        'label' => t('Tag'),
        'description' => t('The tag given to the callblast.'),
      ),
    ),
    'group' => t('VoIP Callblast'),
  );
  $items['voipblast_operations_pause'] = $defaults + array(
    'label' => t('Pause blast by tag name'),
    'base' => 'voipblast_rules_operations_pause',
  );
  $items['voipblast_operations_start'] = $defaults + array(
    'label' => t('Start blast by tag name'),
    'base' => 'voipblast_rules_operations_start',
  );
  $items['voipblast_operations_delete'] = $defaults + array(
    'label' => t('Delete blast by tag name'),
    'base' => 'voipblast_rules_operations_delete',
  );
  return $items;
}

function voipblast_rules_operations_pause($queue_name, $tag) {
  voipblast_operations_operation('pause', array($queue_name . ':' . $tag), array());
}

function voipblast_rules_operations_start($queue_name, $tag) {
  voipblast_operations_operation('start', array($queue_name . ':' . $tag), array());
}

function voipblast_rules_operations_delete($queue_name, $tag) {
  voipblast_operations_operation('delete', array($queue_name . ':' . $tag), array());
}
