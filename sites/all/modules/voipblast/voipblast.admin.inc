<?php

/**
 * VoIP call blast administration pages.
 */

/**
 * Form callback. Default settings.
 */
function voipblast_admin_settings($form, &$form_state) {
  $defaults = voipblast_defaults();
  foreach ($defaults as $name => $value) {
    if (isset($form_state[$name])) {
      $defaults[$name] = $form_state[$name];
    }
  }

  $form['voipblast_recipient'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient field'),
    '#description' => t('The token for the recipient phone number field.'),
    '#default_value' => $defaults['voipblast_recipient'],
  );
  $form['voipblast_outgoing_script'] = array(
    '#type' => 'select',
    '#title' => t('VoIP script'),
    '#description' => t('The VoIP script to use for outgoing calls.'),
    '#options' => VoipScript::getScriptNames(),
    '#default_vaule' => $defaults['voipblast_outgoing_script'],
  );
  $form['voipblast_max_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum length'),
    '#description' => t('The maximum length of an individual outgoing call in seconds.'),
    '#default_value' => $defaults['voipblast_max_length'],
    '#element_validate' => array('element_validate_integer_positive'),
  );
  $form['voipblast_retries'] = array(
    '#type' => 'textfield',
    '#title' => t('Retries'),
    '#description' => t('The maximum number of retries for an individual call.'),
    '#default_value' => $defaults['voipblast_retries'],
    '#element_validate' => array('element_validate_integer_positive'),
  );
  $form['voipblast_retry_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Retry delay'),
    '#description' => t('The number of seconds between retries.'),
    '#default_value' => $defaults['voipblast_retry_delay'],
    '#element_validate' => array('element_validate_integer_positive'),
  );

  $form['voipqueue_limit_voipblast_voice'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of parallel calls'),
    '#description' => t('Maximum number of parallel calls.'),
    '#default_value' => $defaults['voipqueue_limit_voipblast_voice'],
    '#element_validate' => array('element_validate_integer_positive'),
  );

  return system_settings_form($form);
}
