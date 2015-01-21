<?php

class VoipEvent {

  /**
   * Constants
   */

  /**
   * 'event status' values
   */
  const INBOUND_CALL = 1;
  const OUTBOUND_CALL = 2;
  const HANGUP_BY_USER = 3;
  const NO_ANSWER = 4;
  const BUSY = 5;
  const INVALID = 6;
  const INBOUND_SMS_RECEIVED = 7;
  const OUTBOUND_SMS = 8;
  const CANCELED = 9;
  const SESSION_EXPIRED = 10;

  public static function event(&$call, $event_type) {
    module_invoke_all('voip_event', $call, $event_type);
  }
}