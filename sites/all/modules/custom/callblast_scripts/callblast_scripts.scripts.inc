<?php
// $Id$
/**
 * @file
 * Audio Blog VoIP Scripts and helper functions
 */

/**
 * Implementation of hook_voipscript_get_script_names()
 */
function callblast_scripts_voipscript_get_script_names() {
  $script_names[] = 'callblast_scripts_sms_handler_script';
  return $script_names;
}

/**
 * Implementation of hook_voipscript_load_script()
 */
function callblast_scripts_voipscript_load_script($script_name, $options = NULL) {

  $script = NULL;
  switch ($script_name) {
    default:
      break;
    case 'callblast_scripts_sms_handler_script':
      //callblast_scripts VoIP script for Text channel
      $script = new VoipScript('callblast_scripts_sms_handler_script');
      // log the sms
      $log_msg = t("SMS from %caller_number on @date (id: %call_id)",
        array('@date' => format_date(time(), 'custom', 'D, m/d/Y - H:i:s')));
      $script->addLog($log_msg, 'MDT');

      // below was the only way to avoid problems with special characters in the text message
      $options['text'] = '%inbound_text_contents';
      $options['caller_number'] = '%caller_number';
      $options['dest_number'] = '%dest_number';
      $options['call_id'] = '%cid';
      $options['source'] = '%source';
      $script->addGosub('callblast_scripts_sms_process_request_script', $options);
      break;
    case 'callblast_scripts_sms_process_request_script':
      //Helper script to process SMS request
      $script = new VoipScript('callblast_scripts_sms_process_request_script');
      $text = _callblast_scripts_sms_process_request($options['text'], $options['caller_number'], $options['dest_number'], $options['call_id']);

      if ($text) {
        //$footnote = variable_get('callblast_scripts_sms_footnote', '');
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
function _callblast_scripts_sms_process_request($msg, $caller_number, $dest_number, $call_id) {
  watchdog('callblast_scripts', "In _callblast_scripts_sms_process_request with $msg, $caller_number, $dest_number");
  $caller_number = VoipCall::NormalizeNumber($caller_number);
  $help_msg = variable_get('callblast_scripts_sms_help',
    'Welcome to Callblast! To JOIN text any letter. To STOP receiving text messages, text "S". For HELP, text "H". Msg & data rates may apply.');
  $msg = trim($msg);
  $phone_number = callblast_alters_get_phone_number($caller_number);

  if (!$phone_number) {
    //Number doesn't exists
    $cmd = 'J';
  }
  else {
    if ($msg) {
      $request = explode(" ", $msg);
      $cmd = strtoupper($request[0]);

      if(!$cmd == 'Y' && !$phone_number->field_opt_in['und'][0]['value']) {
        watchdog('debug', "received $cmd for unopted contact. Returning optin message");
        $ret = variable_get('callblast_scripts_opt_message',
          'Callblast App would like to send you SMS reminders @ this number. X/week. H for help. S to end. Msg&data rates may apply. Reply J to confirm today.');
        return $ret;
      }
    }
  }

  if ($cmd == 'Y') {
    //@todo: if number is not published then resend sms
    //watchdog('debug', print_r($phone_number,true));
    if ($phone_number) {
      $phone_number->field_opt_in['und'][0]['value'] = 1; //verify
      node_save($phone_number);
      $ret = variable_get('callblast_scripts_sms_welcome', 'Welcome to Callblast App.');
    }
    else {
      $ret = t('Phone number not recognised.');
    }
  }
  else {
    if ($cmd == 'S') {
      //Stop getting messages
      $nids = VoipNumber::getEidsByNumber($caller_number, 'node');
      //$nids = VoipNumber::getNidsByNumber($caller_number);
      if ($nid = reset($nids)) {
        node_delete($nid);
        $ret = variable_get('callblast_scripts_sms_unsubscribe', 'You\'ve unsubscribed from the Callblast App and should not receive further messages. Should you choose to subscribe again, text any letter to this number.');
      }
      else {
        $ret = variable_get('callblast_scripts_sms_not_in_list', 'Number not in the list.');
      }
    }
    else {
      if ($cmd == 'J') {
        if ($phone_number) {
          //Number already exists
          $ret = variable_get('callblast_scripts_sms_unknown', 'Number already registered.');
        }
        else {
          $node->type = 'phone_number';
          $node->title = $caller_number;
          $node->language = 'und';
          $node->status = 1;
          $node->field_opt_in['und'][0]['value'] = 1; //verify
          $node->field_phone_number['und'][0]['vnid'] = $caller_number;
          $language = callblast_alters_number_to_lang($dest_number);
          $node->field_language['und'][0]['value'] = $language;
          // create the node
          node_save($node);
          //@todo: verify number
          if ($node->nid) {
            $ret = variable_get('callblast_scripts_sms_welcome', 'Welcome to Callblast App.');
          }
          else {
            watchdog('callblast_scripts', 'Error saving phone number: ' . print_r($node, TRUE), array(), WATCHDOG_ERROR);
            $ret = t('System error. Please try again later.');
          }
        }
      }
      else {
        if ($cmd == 'H') {
          $ret = $help_msg;
        }
        else {
          $ret = variable_get('callblast_scripts_sms_unknown', 'Unknown command.') . ' ' . $help_msg;
        }
      }
    }
  }

  return $ret;
}

function callblast_scripts_log($message) {
  watchdog('callblast_scripts', $message);
}

