<?php
// $Id$

/**
 * @file
 * An example installation profile that uses a database callblast to recreate a
 * Drupal site rather than API function calls of a traditional installation
 * profile.
 */

/**
 * Name of profile; visible in profile selection form.
 */
define('PROFILE_NAME', 'Callblast');

/**
 * Description of profile; visible in profile selection form.
 */
define('PROFILE_DESCRIPTION', 'Callblast is open-source ready to use system built on Drupal, for delivering voice and SMS to a group of people.');

/**
 * Implementation of hook_form_alter().
 */
function callblast_form_install_configure_form_alter(&$form, $form_state) {
  // Add an additional submit handler.
  $form['#submit'] = array('callblast_form_submit');
}

/**
 * Custom form submit handler for configuration form.
 *
 * Drops all data from existing database, imports database callblast, and restores
 * values entered into configuration form.
 */
function callblast_form_submit($form, &$form_state) {
  global $user;
  // Import database callblast file.
  /*Database must be exported with this options:
  Add CREATE DATABASE / USE statement
  Add DROP TABLE / VIEW / PROCEDURE / FUNCTION / EVENT statement
  */
  $callblast_file = dirname(__FILE__) . '/callblast.sql';
  $success = import_callblast($callblast_file);

  if (!$success) {
    return;
  }

  // Now re-set the values they filled in during the previous step.
  variable_set('site_name', $form_state['values']['site_name']);
  variable_set('site_mail', $form_state['values']['site_mail']);
  variable_set('date_default_timezone', $form_state['values']['date_default_timezone']);
  variable_set('site_default_country', $form_state['values']['site_default_country']);

  // Perform additional clean-up tasks.
  variable_del('file_directory_temp');

  // Replace their username and password and log them in.
  $name = $form_state['values']['account']['name'];
  $pass = $form_state['values']['account']['pass'];
  $mail = $form_state['values']['account']['mail'];
  require_once DRUPAL_ROOT . '/includes/password.inc';
  $hashthepass = user_hash_password(trim($pass));

  db_update('users')
    ->fields(array(
      'name' => $name,
      'pass' => $hashthepass,
      'mail' => $mail,
    ))
    ->condition('uid', 1)
    ->execute();

  if (isset($form_state['values']['clean_url'])) {
    variable_set('clean_url', $form_state['values']['clean_url']);
  }

  // Record when this install ran.
  variable_set('install_time', $_SERVER['REQUEST_TIME']);

  // clear cache
  drupal_flush_all_caches();

// Load global $user and perform final login tasks.
  $user = user_load(1);
  user_login_finalize();
  // Finally, redirect them to the front page to show off what they've done.
  drupal_goto('installphp/postinstall');
}

/**
 * Imports a database callblast file.
 *
 * @see demo_reset().
 */
function import_callblast($filename) {
  // Open callblast file.
  if (!file_exists($filename) || !($fp = fopen($filename, 'r'))) {
    drupal_set_message(t('Unable to open callblast file %filename.', array('%filename' => $filename)), 'error');
    return FALSE;
  }

  // Load data from callblast file.
  $success = TRUE;
  $query = '';
  $new_line = TRUE;

  while (!feof($fp)) {
    // Better performance on PHP 5.2.x when leaving out buffer size to
    // fgets().
    $data = fgets($fp);

    if ($data === FALSE) {
      break;
    }
    // Skip empty lines (including lines that start with a comment).
    if ($new_line && ($data == "\n" || !strncmp($data, '--', 2) || !strncmp($data, '#', 1))) {
      continue;
    }
    // Skip SQL variables
    if (substr($data,0,3) === 'SET') {
      continue;
    }

    // Skip comments
    if (substr($data,0,2) === '/*') {
      continue;
    }

    // Skip creating database
    if (substr($data,0,15) === 'CREATE DATABASE') {
      continue;
    }

    //Skip USE commands
    if (substr($data,0,3) === 'USE') {
      continue;
    }

    $query .= trim($data);
    $len = strlen($data);
    if ($data[$len - 1] == "\n") {
      if ($data[$len - 2] == ';') {
        // Reached the end of a query, now execute it.
        if (!db_query($query)) {
          $success = FALSE;
        }
        $query = '';
      }
      $new_line = TRUE;
    }
    else {
      // Continue adding data from the same line.
      $new_line = FALSE;
    }
  }
  fclose($fp);

  if (!$success) {
    drupal_set_message(t('Failed importing database from %filename.', array('%filename' => $filename)), 'error');
  }

  return $success;
}