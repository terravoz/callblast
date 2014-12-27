<?php
/**
 * @file
 * nannyvan_news.features.inc
 */

/**
 * Implements hook_node_info().
 */
function audio_announcements_node_info() {
  $items = array(
    'audio_announcements' => array(
      'name' => t('Audio Announcements'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
