<?php
/**
 * @file
 * audio_announcements.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function audio_announcements_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-audio_announcements-body'
  $field_instances['node-audio_announcements-body'] = array(
    'bundle' => 'audio_announcements',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Body',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => TRUE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => -4,
    ),
  );

  // Exported field_instance: 'node-audio_announcements-field_audio_announcements_audio'
  $field_instances['node-audio_announcements-field_audio_announcements_audio'] = array(
    'bundle' => 'audio_announcements',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'audiofield',
        'settings' => array(),
        'type' => 'audiofield_embedded',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_audio_announcements_audio',
    'label' => 'Audio',
    'required' => 0,
    'settings' => array(
      'description_field' => 0,
      'file_directory' => '',
      'file_extensions' => 'wav mp3',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'audiorecorderfield',
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
      'type' => 'audiorecorderfield_widget',
      'weight' => -3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Audio');
  t('Body');

  return $field_instances;
}
