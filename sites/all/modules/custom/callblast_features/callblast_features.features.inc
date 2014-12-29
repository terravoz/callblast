<?php
/**
 * @file
 * callblast_features.features.inc
 */

/**
 * Implements hook_views_api().
 */
function callblast_features_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function callblast_features_node_info() {
  $items = array(
    'broadcast' => array(
      'name' => t('Announcement'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Blast Title'),
      'help' => '',
    ),
  );
  return $items;
}
