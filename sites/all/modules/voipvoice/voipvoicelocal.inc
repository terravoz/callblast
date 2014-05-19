<?php 
/**
 * @file
 * Implementation of VoIP Voice class
 */

class VoipVoiceLocal extends VoipVoice {

 /**
 * Constructor
 */
 function __construct($voice_id, $gender, $language) {
    $is_local = TRUE;
    parent::__construct($voice_id, $gender, $language, $is_local);
 }
 
 /*
  * Public methods
  */

 /**
  * Extends VoipVoice::getPrompt() to return the audio files associated
  * with the local voices
  */
 function getPrompt($text, $args = NULL, $as = NULL) {
   //Use voipvoice function to get locally recorder voice
   $url_or_text = voipvoice_get_prompt($text, $args, $this->getVoiceId());
   //return new VoipPrompt($url_or_text, $this->getVoiceId(), $as);
   return new VoipPrompt($url_or_text, VoipVoice::getVoice($as)->getVoiceId(), $as);
 }
}
