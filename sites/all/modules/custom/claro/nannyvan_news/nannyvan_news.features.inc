<?php
/**
 * @file
 * nannyvan_news.features.inc
 */

/**
 * Implements hook_node_info().
 */
function nannyvan_news_node_info() {
  $items = array(
    'nannyvan_audio_news' => array(
      'name' => t('NannyVan Audio News'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
