<?php
/**
 * Add body classes if certain regions have content.
 */
function bartik_claro_preprocess_html(&$variables) {
  if (!empty($variables['page']['featured'])) {
    $variables['classes_array'][] = 'featured';
  }

  if (!empty($variables['page']['triptych_first'])
    || !empty($variables['page']['triptych_middle'])
    || !empty($variables['page']['triptych_last'])) {
    $variables['classes_array'][] = 'triptych';
  }

  if (!empty($variables['page']['footer_firstcolumn'])
    || !empty($variables['page']['footer_secondcolumn'])
    || !empty($variables['page']['footer_thirdcolumn'])
    || !empty($variables['page']['footer_fourthcolumn'])) {
    $variables['classes_array'][] = 'footer-columns';
  }

  // Add conditional stylesheets for IE
  drupal_add_css(path_to_theme() . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css(path_to_theme() . '/css/ie6.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 6', '!IE' => FALSE), 'preprocess' => FALSE));
}

/**
 * Implements hook_preprocess_views_view().
 */
function bartik_claro_preprocess_views_view(&$vars) {
  // Wrap exposed filters in a fieldset.
  if ($vars['exposed']) {
    $fieldset['element'] = array(
      '#title' => t('Filter results'),
      '#id' => 'view_advanced_search',
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#attributes' => array('class' => array('collapsible', 'view_advanced_search')),
      '#children' => $vars['exposed'],
    );
    $vars['exposed'] = theme('fieldset', $fieldset);
  }
}
