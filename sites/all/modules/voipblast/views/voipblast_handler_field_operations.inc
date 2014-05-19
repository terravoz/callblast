<?php

/**
* @file
* Views field handler. Contains all relevant VBO options and related logic.
* Implements the Views Form API.
*/

class voipblast_handler_field_operations extends views_handler_field {

  function construct() {
    parent::construct();
    $this->additional_fields['name'] = array('table' => 'advancedqueue', 'field' => 'name');
    $this->additional_fields['tags'] = array('table' => 'advancedqueue_tags', 'field' => 'tag');
  }

  /**
   * If the view is using a table style, provide a
   * placeholder for a "select all" checkbox.
   */
  function label() {
    if (!empty($this->view->style_plugin) && $this->view->style_plugin instanceof views_plugin_style_table) {
      return '<!--views-bulk-operations-select-all-->';
    }
    else {
      return parent::label();
    }
  }

  function render($values) {
    return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * The form which replaces the placeholder from render().
   */
  function views_form(&$form, &$form_state) {
    // The view is empty, abort.
    if (empty($this->view->result)) {
      return;
    }

    $form[$this->options['id']] = array(
      '#tree' => TRUE,
    );
    // At this point, the query has already been run, so we can access the results
    // in order to get the base key value (for example, nid for nodes).
    foreach ($this->view->result as $row_index => $row) {
      // @todo: Need to check the posible table aliases here.
      // They are forced with additional_fields.
      $queue_name = $row->advancedqueue_name;
      $tag = $row->advancedqueue_tags_tag;
      $form[$this->options['id']][$row_index] = array(
        '#type' => 'checkbox',
        '#return_value' => check_plain($queue_name . ':' . $tag),
        '#default_value' => FALSE,
        '#attributes' => array('class' => array('vbo-select')),
      );
    }
  }

  public function get_selected_operations() {
    return array(
      'pause' => 'Pause',
      'start' => 'Start',
      'delete' => 'Delete',
    );
  }

  /**
   * Returns the options stored for the provided operation id.
   */
  public function get_operation_options($operation_id) {
    $options = (array) $this->options['vbo_operations'];
    return isset($options[$operation_id]) ? $options[$operation_id] : array();
  }
}
