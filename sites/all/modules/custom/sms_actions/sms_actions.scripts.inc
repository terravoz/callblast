<?php
// $Id$
/**
 * @file
 * SMS Actions VoIP Scripts and helper functions
 */

/**
 * Implementation of hook_voipscript_get_script_names()
 */
function sms_actions_voipscript_get_script_names() {
  $script_names[] = 'sms_actions_sms_handler_script';
  return $script_names;
}

/**
 * Implementation of hook_voipscript_load_script()
 */
function sms_actions_voipscript_load_script($script_name, $options = NULL) {
  $script = NULL;
  switch ($script_name) {
    default:
      break;
    case 'sms_actions_sms_handler_script':
      //sms_actions VoIP script for Text channel
      $script = new VoipScript('sms_actions_sms_handler_script');
      // log the sms
      $log_msg = t("SMS from %caller_number on @date (id: %call_id)",
        array('@date' => format_date(time(), 'custom', 'D, m/d/Y - H:i:s')));
      $script->addLog($log_msg, 'sms_actions');

      // below was the only way to avoid problems with special characters in the text message
      $options['text'] = '%inbound_text_contents';
      $options['caller_number'] = '%caller_number';
      $options['dest_number'] = '%dest_number';
      $options['call_id'] = '%cid';
      $options['source'] = '%source';
      $script->addGosub('sms_actions_sms_process_request_script', $options);
      break;
    case 'sms_actions_sms_process_request_script':
      //Helper script to process SMS request
      $script = new VoipScript('sms_actions_sms_process_request_script');
      $text = _sms_actions_sms_process_request($options['text'], $options['caller_number'], $options['dest_number'], $options['call_id']);

      if ($text) {
        $script->addSendText($text);
        $script->addLog("sending $text");
      }

      $script->addHangup();
      break;
  }

  return $script;
}

/**
 * Process incoming SMS messages
 */
function _sms_actions_sms_process_request($msg, $caller_number, $dest_number, $call_id) {
  watchdog('sms_actions', "In _sms_actions_sms_process_request with $msg, $caller_number, $dest_number");
  $caller_number = VoipCall::NormalizeNumber($caller_number);
  $msg = trim($msg);
  if ($msg) {
    $request = explode(" ", $msg);
    $cmd = strtoupper($request[0]);
    $sms_action = sms_actions_get_action($cmd);

    if (!$sms_action) {
      $ret = variable_get('sms_actions_sms_unknown', 'Unknown command.');
    }
    else {
      $ret = call_user_func($sms_action, $msg, $caller_number, $dest_number, $call_id);
    }
  }

  return $ret;
}
