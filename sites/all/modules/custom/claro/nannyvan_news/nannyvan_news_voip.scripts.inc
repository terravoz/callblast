<?php
// $Id$
/**
* @file
* NannyVan News VoIP Scripts and helper functions
*/

/**
 * Implementation of hook_voipscript_get_script_names()
 */
function nannyvan_news_voipscript_get_script_names() {
  $script_names[] = 'nannyvan_news_main_menu_script';
  return $script_names;
}

/**
 * Implementation of hook_voipscript_load_script()
 */
function nannyvan_news_voipscript_load_script($script_name, $options=NULL) {

  $script = NULL;
  switch ($script_name) {
    default:
      break;
    case 'nannyvan_news_main_menu_script':
      //NannyVan News script for Voice channel
      $script = new VoipScript('nannyvan_news_main_menu_script');
      $script->addSetVoice('woman');
      $options['voice'] = 'claro';
      $voice =  $options['voice'];
      voipvoice_set_current_voice($voice);

      $script->addSay(v('Welcome to NannyVan News.'));
      $script->addLabel('main_menu');
      $p_options_menu = v('Main menu. To listen to the latest NannyVan News, press 1. To record a new NannyVan News press the star key. ');

      $input_options = array(
        '1' => 'play_audio_blogs',
        '*' => 'record_audio_blog',
      );
      $p_invalid_msg = v('Invalid option selected');
      $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
      $script->addGoto('%ivr_option_selected');

      $script->addLabel('play_audio_blogs');
      $script->addGosub('nannyvan_news_play_blogs_script', $options);
      $script->addGoto('main_menu');

      $script->addLabel('record_audio_blog');
      $script->addGosub('nannyvan_news_record_blog_script', $options);
      $script->addGoto('main_menu');

      $script->addLabel('end');
      $script->addSay(v('Thank you for calling. Bye bye.'));
      $script->addHangup();
      break;

    case 'nannyvan_news_play_blogs_script':
      //Helper script that provides play menu for NannyVan Newss.
      $script = new VoipScript('nannyvan_news_play_blogs_script');
      //$script->addSetVoice('woman');
      $voice =  $options['voice'];
      voipvoice_set_current_voice($voice);

      $blogs = _nannyvan_news_get_blogs();
      if (!$blogs) {
        $script->addSay(v('There are no NannyVan News at this time. '));
      }
      else {
        //$script->addSay(v('During playback, press any key to go to the NannyVan News menu. '));
        foreach ($blogs as $index => $blog) {
          $body = $blog['body'];
          //$args = array('@date' => VoipVoice::getDate($blog['changed']), '@time' => date("g:i a", $blog['changed']));
          //$info = v('This NannyVan News was created on @date at @time', $args);
          $current = "audio_blog_$index";
          //$current_info = "info_$index";
          $next = 'audio_blog_' . ($index+1);

          $script->addLabel($current);
          $script->addGetInput($body, 1, '#', 3);

          $script->addLabel('playback_menu');
          $p_options_menu = v('You have just heard the latest dispatch from the NannyVan.
           To replay this NannyVan dispatch, press 1.
           To hear the previous dispatch, press 2.
           To go back to the main menu, press the pound key.');
          $input_options = array(
            '1' => $current,
            '2' => $next,
            '#' => 'go_back',
          );
          $p_invalid_msg = v('Oops! That option is invalid. ');
          $script->addRunIvrMenu($p_options_menu, $input_options, $p_invalid_msg);
          $script->addGoto('%ivr_option_selected');

          /*$script->addLabel($current_info);
          $script->addSay($info);
          $script->addGoto('playback_menu');*/
        }
      }

      $no_more = count($blogs);
      $script->addLabel("audio_blog_$no_more");
      $script->addSay(v('No more NannyVan News to be played. '));
      $script->addGoto('go_back');

      $script->addLabel('invalid_option');
      $script->addGoto('go_back');

      $script->addLabel('go_back');
      $script->addReturn();
      break;

    case 'nannyvan_news_record_blog_script':
      //Helper script that prompts user to record a message
      $script = _nannyvan_news_get_record_script($options);
    break;
  }

  return $script;
}

/*
* Returns array of nannyvan_news nodes
*/
function _nannyvan_news_get_blogs() {
  $blogs = array();

  /*$result = db_select('node', 'n')
  ->fields('n', array('nid'))
  ->condition('type', 'nannyvan_audio_news')
  ->condition('status', 0, '<>')
  ->orderBy('changed', 'DESC')
  ->execute();*/

  $view = views_get_view('news_episode_management');
  $view->preview('page');
  foreach ($view->result as $res) {
    $n = node_load($res->nid);
    $blog = array();
    $blog['nid'] = $n->nid;
    $blog['changed'] = $n->changed;

    $field_audio = $n->field_nannyvan_news_audio;
    if ($field_audio['und'][0]) {
      $audio_url = file_create_url($field_audio['und'][0]['uri']);
      $blog['body'] = $audio_url;
    }

    if (!$blog['body']) {
      //If no audio then load text version
      $blog['body'] = $n->body['und'][0]['value'];
    }

    $blogs[] = $blog;
  }

  /*foreach ($result as $o) {
    $n = node_load($o->nid);
    $blog = array();
    $blog['nid'] = $n->nid;
    $blog['changed'] = $n->changed;

    $field_audio = $n->field_nannyvan_news_audio;
    if ($field_audio['und'][0]) {
      $audio_url = file_create_url($field_audio['und'][0]['uri']);
      $blog['body'] = $audio_url;
    }

    if (!$blog['body']) {
      //If no audio then load text version
      $blog['body'] = $n->body['und'][0]['value'];
    }

    $blogs[] = $blog;
  }*/

  return $blogs;
}

function _nannyvan_news_get_last_news() {
  $latest_news = '';
  $view = views_get_view('news_episode_management');
  $view->preview('page');
  foreach ($view->result as $res) {
    $n = node_load($res->nid);
    $field_audio = $n->field_nannyvan_news_audio;
    if ($field_audio['und'][0]) {
      $audio_url = file_create_url($field_audio['und'][0]['uri']);
      $latest_news = $audio_url;
    }
    else if (!$blog['body']) {
      //If no audio then load text version
      $latest_news = $n->body['und'][0]['value'];
    }
    break;
  }

  return $latest_news;
}

function _nannyvan_news_get_record_script($options) {
  $script = new VoipScript('nannyvan_news_record_blog_script');

  $voice =  $options['voice'];
  voipvoice_set_current_voice($voice);

  $script->addLabel('start');
  // prepare the call to finish processing the recording even in case of hang up
  $script->addSet('voipscript_hangup_callback', '_nannyvan_news_record_on_hang_up');
  $prompt = v("Please record your NannyVan News after the beep.  When done, either hang up or press the pound key for additional options.");
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
    '^_nannyvan_news_record_callback(%recording_public_url, %source, %cid, %recording_duration)');

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

/**
 * Function executed on hang up as part of nannyvan_news_record_blog_script script
 */
function _nannyvan_news_record_on_hang_up($original_call) {
  watchdog('debug', 'in _nannyvan_news_record_on_hang_up');
  $original_script = $original_call->getScript();
  $cid = $original_call->getCid();
  $source = $original_call->getSource();
  $recording_public_url = $original_script->getVar('recording_public_url');
  $recording_duration = $original_script->getVar('recording_duration');
  $result = _nannyvan_news_record_callback($recording_public_url, $source, $cid, $recording_duration);
}

/**
 * Callback function associated with the script nannyvan_news_record_blog_script.  It is called
 *  whenever that script records a new entry from the user and it creates a new nannyvan_news node.
 */
function _nannyvan_news_record_callback($recording_public_url, $source, $cid, $duration) {
  $server = Voipserver::getServer($source);
  $call = VoipCall::load($cid);
  $args = array(
    'call' => $call,
    'duration' => $duration,
  );
  $server->audioFileMover($recording_public_url, '_nannyvan_news_create_nannyvan_news', $args);
  $msg = t('Your NannyVan News has been saved. ');
  return $msg;
}

/**
 * Create blog node from audio message.
 *
 * @param object file.
 *   Drupal file object.
 *
 * @return
 *   Node object.
 */
function _nannyvan_news_create_nannyvan_news($file, $recording_public_url, $args) {
  $node->type = 'nannyvan_audio_news';
  $node->promote = TRUE;
  $node->language = 'und';

  $options = array('@datetime' => date('l, F j, Y \a\t g:i a', time()));
  $node->title = t('NannyVan News entry created on @datetime', $options);

  $file->display = 1;
  $node->field_nannyvan_news_audio['und'][0] = (array)$file;

  // create the node
  node_save($node);
  return $node;
}
