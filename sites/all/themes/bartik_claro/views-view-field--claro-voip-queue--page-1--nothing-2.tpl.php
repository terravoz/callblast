<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php 
$nid = $row->advancedqueue_tags_tag;
$node = node_load($nid);
//dpm($node);
$blast_type = $node->field_blast_type['und'][0]['value'];

switch($blast_type) {
  case 'sms':
    //SMS announcement
    //fix: for some reason body changed to eng
    $message = $node->body[$node->language][0]['value'];
    print "SMS announcement: '$message'";
    break;
  case 'voice_text':
  case 'voice_script':
    if($blast_type == 'voice') {
      $voice_say = $node->field_voice_announcement['und'][0]['value'];
      print "Voice announcement: '$voice_say'";
    }
    else {
      $voip_script = $node->field_voip_script['und'][0]['value'];
      print "Voice announcement using: '$voip_script'";
    }
    break;
}
?>