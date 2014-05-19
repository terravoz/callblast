<?php

/**
 * Submit handler for the "add-one-more" button.
 *
 * Increments the max counter and causes a rebuild.
 */
function voipdrupal_multinumber_ahah_add_more_numbers($form, &$form_state) {
  $form_state['voipdrupal_multinumber_ahah_number_count']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Callback for both ajax-enabled buttons.
 *
 * Returns the anon page textfields
 */
function voipdrupal_multinumber_ahah_add_more_callback($form, $form_state) {
  return $form['number'];
}