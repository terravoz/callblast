<?php
// $Id$
/**
 * @file
 * Audio Blog VoIP Scripts and helper functions
 */

/**
 * Implementation of hook_voipscript_get_script_names()
 */
function pbb_voipscript_get_script_names() {
  $script_names[] = 'pbb_welcome_script';
  $script_names[] = 'pbb_sms_handler_script';
  return $script_names;
}

/**
 * Implementation of hook_voipscript_load_script()
 */
function pbb_voipscript_load_script($script_name, $options = NULL) {

  $script = NULL;
  switch ($script_name) {
    default:
      break;
    case 'pbb_welcome_script':
      $script = new VoipScript('pbb_welcome_script');
      $options['voice'] = 'pbb';
      $voice = $options['voice'];
      voipvoice_set_current_voice($voice);

      $script->addLabel('options_menu');

      $p_options_menu = v("Hi, thank you for calling Youth Lead the Change!
      If you would like to hear more about Youth Lead the Change and Participatory Budgeting, press 1,
      if you would like to enroll in our contact list for text message updates, press 2,
      if you would like to contribute your project idea to improve the city of Boston, press 3,
      or if you would like to be redirected to our Boston Youth Lead the Change headquarters, press STAR.");

      $input_options = array(
        //'1' => 'audio_announcements',
        '3' => 'propose_idea',
        '2' => 'sms_subscription',
        '1' => 'get_information',
        '4' => 'redirect',
        '*' => 'repeat',
        '#' => 'invalid_option',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('Oops! That option is invalid. ');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      /*$script->addLabel('audio_announcements');
      $script->addGosub('audio_announcements_play_blogs_script', $options);
      $script->addGoto('options_menu');
*/

      $script->addLabel('propose_idea');
      $script->addGosub('propose_idea_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('sms_subscription');
      $options['signup_number'] = '%caller_number';
      $script->addGosub('pbb_sms_subscription_menu', $options);
      $script->addGoto('options_menu');

      $script->addLabel('get_information');
      $script->addGetInput(v('Welcome to Youth Lead the Change recording'), 1);
      $script->addGotoIf('sms_subscription', "^%input_digits == '2'");
      $script->addGoto('options_menu');

      $script->addLabel('redirect');
      $script->addSay(v('Your call will now be redirected to Boston HQ. '));
      //$script->addDial('+16466993989');
      $script->addGoto('options_menu');

      $script->addLabel('repeat');
      $script->addGoto('options_menu');

      $script->addLabel('invalid_option');
      $script->addGoto('hang_up');

      $script->addLabel('hang_up');
      $script->addHangup();
      break;

    case 'pbb_sms_subscription_menu':
      $script = new VoipScript('pbb_sms_subscription_menu');
      $voice = $options['voice'];
      voipvoice_set_current_voice($voice);

      $signup_number = VoipCall::NormalizeNumber($options['signup_number']);
      $phone_number = callblast_alters_get_phone_number($signup_number);

      if ($phone_number) {
        //Number already exists
      }
      else {
        $node->type = 'phone_number';
        $node->title = $signup_number;
        $node->language = 'und';
        $node->status = 1;
        $node->field_opt_in['und'][0]['value'] = 1; //verify
        $node->field_phone_number['und'][0]['vnid'] = $signup_number;
        //$language = callblast_alters_number_to_lang($dest_number);
        $language = 'en';
        $node->field_language['und'][0]['value'] = $language;
        // create the node
        node_save($node);
      }
      /*$text = variable_get('claro_sms_help',
        'Welcome to The PBB App! To JOIN and receive weekly text messages, text the letter "J". To STOP receiving text messages, text "S". For HELP, text "H". Msg & data rates may apply.');

      $script->addSendText($text, $signup_number);*/

      $script->addLabel('options_menu');
      $p_options_menu = v("Great! Your number has been successfully added to our text message reminders.
      You will now receive reminders to contribute ideas and join Youth Lead the Change events!
To repeat this message, press the star key.
To go back to the main menu, press the pound key. ");

      $input_options = array(
        '*' => 'repeat',
        '#' => 'go_back',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('Oops! That option is invalid. ');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('repeat');
      $script->addGoto('options_menu');

      $script->addLabel('go_back');
      $script->addReturn();
      break;

    case 'propose_idea_script':
      $script = new VoipScript('propose_idea_script');

      $voice =  $options['voice'];
      voipvoice_set_current_voice($voice);

      $script->addLabel('start');
      $script->addSay(v('Intro message for idea collection. '));
      $script->addLabel('options_menu');
      $p_options_menu = v("Great! Remember, ideas have to be for physical projects to improve the city of Boston.
  Ideas shouldn’t be for programs and services.
  If your idea is for Schools & Education projects, press 1,
  if it is for Streets & Transportation & Community Safety projects, press 2,
  if it is for Arts & Culture projects, press 3, if it is Parks & Environment projects press 4,
  if it is for Community Centers projects press 5, if it is for Libraries projects press 6.
  To hear these options again, press 8.
");

      $input_options = array(
        '1' => 'category1',
        '2' => 'category2',
        '3' => 'category3',
        '4' => 'category4',
        '5' => 'category5',
        '6' => 'category6',
        '8' => 'repeat',
        '#' => 'invalid_option',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('Oops! That option is invalid. ');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('setcategory');

      $script->addLabel('setcategory');
      $script->addSet('idea_category', '%ivr_option_selected');
      //$script->addGoto('options_menu');

      //Record location
      $script->addLabel('start_recording_location');
      // prepare the call to finish processing the recording even in case of hang up
      //$script->addSet('voipscript_hangup_callback', '_pbb_record_on_hang_up');
      //$script->addLog('About to start recording (%voipscript_hangup_callback)');

      $prompt = t("Now please name the neighborhood and the streets or intersection for which your idea applies. When you are finished, press #. ");
      $timeout = 5;
      $end_key = '#';
      $max_length = 200;
      $format = 'mp3';

      $script->addRecord($prompt, $timeout, $end_key, $max_length, $format);

      //$script->addLog('Back from recording (%voipscript_hangup_callback)');
      // reset the hang up handler
      //$script->addSet('voipscript_hangup_callback', '');
      $script->addSet('idea_location', '%recording_public_url');

      //Record idea
      $script->addLabel('start_recording_idea');
      // prepare the call to finish processing the recording even in case of hang up
      //$script->addSet('voipscript_hangup_callback', '_pbb_record_on_hang_up');
      $script->addLog('About to start recording (%voipscript_hangup_callback)');

      $prompt = t("Now please say describe your idea in up to 45 seconds. When you are finished, press #. ");
      $timeout = 5;
      $end_key = '#';
      $max_length = 45;
      $format = 'mp3';

      $script->addRecord($prompt, $timeout, $end_key, $max_length, $format);

      //$script->addLog('Back from recording (%voipscript_hangup_callback)');
      // reset the hang up handler
      //$script->addSet('voipscript_hangup_callback', '');
      $script->addSet('idea_recording', '%recording_public_url');


      $script->addSet('callback_result',
        '^_pbb_save_idea(%idea_category, %idea_location, %idea_recording, %caller_number, %source)');

      $script->addLabel('end call');
      $script->addSay(v('Bye bye.'));
      $script->addHangup();

      break;
  }

  return $script;
}
