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
      $options['caller_number'] = VoipCall::NormalizeNumber($options['caller_number']);
      $options['text'] = trim($options['text']);
      if ($options['text']) {
        $request = explode(" ", $options['text']);
        $cmd = strtoupper($request[0]);
        $sms_action = sms_actions_get_action($cmd);

        if (!$sms_action) {
          $text = variable_get('sms_actions_sms_unknown', 'Unknown command.');
          $script->addSendText($text);
        }
        else {
          //call_user_func($sms_action, $script, $options);
          $script->addGosub($sms_action, $options);
        }
      }

      $script->addHangup();
      break;
    case 'sms_actions_action_subscribe':
      $script = new VoipScript('sms_actions_action_subscribe');
      $phone_number = VoipNumber::getVoipNumbersByNumber($options['caller_number'], 'node', 'phone_number');
      if ($phone_number) {
        $nid = $phone_number[0]->getEid();
        $contact = node_load($nid);
        if($contact->field_opt_in['und'][0]['value']) {
          //Number already exists
          $text = variable_get('sms_actions_sms_duplicate', 'Number already registered.');
        }
        else {
          //Opt-in the contact
          $contact->field_opt_in['und'][0]['value'] = 1;
          node_save($contact);
          $text = variable_get('sms_actions_sms_welcome', 'Welcome to Callblast App.');
        }
      }
      else {
        $node->type = 'phone_number';
        $node->title = $options['caller_number'];
        $node->language = 'und';
        $node->status = 1;
        $node->field_opt_in['und'][0]['value'] = 1; //verify
        $node->field_phone_number['und'][0]['vnid'] = $options['caller_number'];
        $language = callblast_alters_number_to_lang($options['dest_number']);
        $node->field_language['und'][0]['value'] = $language;
        // create the node
        node_save($node);
        //@todo: verify number
        if ($node->nid) {
          $text = variable_get('sms_actions_sms_welcome', 'Welcome to Callblast App.');
        }
        else {
          watchdog('sms_actions', 'Error saving phone number: ' . print_r($node, TRUE), array(), WATCHDOG_ERROR);
          $text = t('System error. Please try again later.');
        }
      }

      $script->addSendText($text);
      break;
    case 'sms_actions_action_unsubscribe':
      $script = new VoipScript('sms_actions_action_unsubscribe');
      //Stop getting messages
      $phone_number = VoipNumber::getVoipNumbersByNumber($options['caller_number'], 'node', 'phone_number');
      if ($phone_number) {
        node_delete($phone_number[0]->getEid());
        $text = variable_get('sms_actions_sms_unsubscribe', 'You\'ve unsubscribed from the Callblast App and should not receive further messages. Should you choose to subscribe again, text any letter to this number.');
      }
      else {
        $text = variable_get('sms_actions_sms_not_in_list', 'Number not in the list.');
      }
      $script->addSendText($text);
      break;
    case 'sms_actions_action_help':
      $script = new VoipScript('sms_actions_action_help');
      $text = variable_get('sms_actions_sms_help',
        'Welcome to Callblast! To JOIN text any letter. To STOP receiving text messages, text "S". For HELP, text "H". Msg & data rates may apply.');
      $script->addSendText($text);
      break;
  }

  return $script;
}