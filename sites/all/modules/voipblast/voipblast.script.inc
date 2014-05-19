<?php

/**
 * @file
 * VoIP scripts for VoIP Call Blast.
 */

/**
 * Outgoing call that plays a file.
 */
function _voipblast_outgoing_file_script($fid) {
  $file_url = file_create_url(file_load($fid)->uri);

  $script = new VoipScript('voipblast_outgoing_file_script');
  $script->addSay($file_url);

  return $script;
}
