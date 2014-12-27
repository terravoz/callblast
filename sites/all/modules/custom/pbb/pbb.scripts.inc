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
    case 'claro_main_menu_script':
      $script = new VoipScript('claro_main_menu_script');
      $options['voice'] = 'pbb';
      $voice = $options['voice'];
      voipvoice_set_current_voice($voice);

      $script->addLabel('options_menu');

      $p_options_menu = v("Welcome to the Participatory Budgeting Boston hotline.
      To listen to recent announcements, dial 1.
      To propose a new idea for the city, dial 2.
      To join our SMS mailing list, dial 3.
      To learn more about PBB, dial 4.
      To be redirected to our Boston HQ, dial 5.
      To repeat this menu, press the star key. ");

      $input_options = array(
        '1' => 'audio_announcements',
        '2' => 'propose_idea',
        '3' => 'sms_subscription',
        '4' => 'get_information',
        '5' => 'redirect',
        '*' => 'repeat',
        '#' => 'invalid_option',
        'i' => 'invalid_option',
        't' => 'invalid_option'
      );
      $p_invalid_msg = v('Oops! That option is invalid. ');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('audio_announcements');
      $script->addGosub('audio_announcements_play_blogs_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('propose_idea');
      $script->addGosub('propose_idea_script', $options);
      $script->addGoto('options_menu');

      $script->addLabel('sms_subscription');
      $options['signup_number'] = '%caller_number';
      $script->addGosub('pbb_sms_subscription_menu', $options);
      $script->addGoto('options_menu');

      $script->addLabel('get_information');
      $script->addGetInput(v('Here is recording for "ABOUT THE PBB"'), 1);
      $script->addGotoIf('options_menu', "^%input_digits");
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

      $signup_number = $options['signup_number'];
      //$text = 'Welcome to Claro Que Sí! To subscribe, text the letter "J". To stop receiving text messages, text "S". For help, text "H". Msg & data rates may apply.';
      $text = variable_get('claro_sms_help',
        'Welcome to The PBB App! To JOIN and receive weekly text messages, text the letter "J". To STOP receiving text messages, text "S". For HELP, text "H". Msg & data rates may apply.');

      $script->addSendText($text, $signup_number);

      $script->addLabel('options_menu');
      $p_options_menu = v("You should have already received a text message with instructions to confirm your subscription. So check your cell phone, and thanks for signing up!”
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
  }

  return $script;
}

function _pbb_idea_collection_script($options) {
  $script = new VoipScript('audio_announcements_record_blog_script');

  $voice =  $options['voice'];
  voipvoice_set_current_voice($voice);

  $script->addLabel('start');
  $script->addSay(v('Intro message for idea collection. '));
  $script->addLabel('options_menu');
  $p_options_menu = v("Please select category. Options are
      For category 1 press 1.
      For category 2 press 2.
      For category 3 press 3.
      For category 4 press 4.
      For category 5 press 5.
      For category 6 press 6.
      To repeat this menu, press the star key. ");

  $input_options = array(
    '1' => 'category1',
    '2' => 'category2',
    '3' => 'category3',
    '4' => 'category4',
    '5' => 'category5',
    '6' => 'category6',
    '*' => 'repeat',
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

  $script->addLabel('start_recording');
  // prepare the call to finish processing the recording even in case of hang up
  $script->addSet('voipscript_hangup_callback', '_pbb_record_on_hang_up');
  $script->addLog('About to start recording (%voipscript_hangup_callback)');

  $prompt = t("Please record idea location after the beep.  When done press the pound key for additional options.");
  $timeout = 5;
  $end_key = '#';
  $max_length = 20;
  $format = 'mp3';

  $script->addRecord($prompt, $timeout, $end_key, $max_length, $format);

  $script->addLog('Back from recording (%voipscript_hangup_callback)');
  // reset the hang up handler
  $script->addSet('voipscript_hangup_callback', '');

  $script->addSet('idea_location', '%recording_public_url');

  // prepare the call to finish processing the recording even in case of hang up
  $script->addSet('voipscript_hangup_callback', '_audio_announcements_record_on_hang_up');
  $audio_announcements_name = variable_get('audio_announcements_name', 'Audio Announcement');
  $prompt = v("Please record your '.$audio_announcements_name.' after the beep.  When done, either hang up or press the pound key for additional options.");
  $timeout = 5;
  $end_key = '#';
  $max_length = 3600; //1 hour
  $script->addRecord($prompt, $timeout, $end_key, $max_length);

  // reset the hang up handler
  $script->addSet('voipscript_hangup_callback', '');

  $args = array('@message' => '%recording_public_url');
  $script->addSay(v('You said @message', $args));

  $script->addLabel('accept menu');
  $prompt = v("To accept this recording, press 1.  To record it once again, press 2. To hangup, press the pound key.");
  $timeout = 5;
  $end_key = '';
  $num_digits = 1;
  $script->addGetInput($prompt, $num_digits, $end_key, $timeout);

  $script->addGotoIf('accept recording', "^%input_digits == '1'");

  $script->addGotoIf('start', "^%input_digits == '2'");

  $script->addGotoIf('end call', "^%input_digits == '#'");

  $script->addSay(v('Invalid input received. '));
  $script->addSay(v('Please try again.'));
  $script->addGoto('accept menu');

  $script->addLabel('accept recording');
  $script->addSay(v('About to start processing your recording.'));
  $script->addSet('callback_result',
    '^_audio_announcements_record_callback(%recording_public_url, %source, %cid, %recording_duration)');

  $script->addSay('%callback_result');
  $script->addGoto('end call');

  $script->addLabel('no input received');
  $script->addSay(v("No input received. "));
  $script->addSay(v('Please try again.'));
  $script->addGoto('start');

  $script->addLabel('end call');
  $script->addSay(v('Bye bye.'));
  $script->addHangup();

  return $script;
}
