<?php


function edit_relationships(array $form, array &$form_state, $object_pid) {
  $object = islandora_object_load($object_pid);
  if (!$object) {
    drupal_set_message("Fedora object doesn't exist.");
  }
  $rels = $object->relationships->get();
  $create_table_rows = function($o) {
    $o['delete'] = '';
    if ($o['predicate']['namespace'] == 'info:fedora/fedora-system:def/model#') {
      $o['delete'] = t('Can\'t delete fedora model.');
    }
    if ($o['predicate']['namespace'] == 'info:fedora/fedora-system:def/relations-external#' and $o['predicate']['value'] == 'isMemberOfCollection') {
      $o['delete'] = t('Manage from collection object');
    }
    $o['predicate'] = $o['predicate']['namespace'] . $o['predicate']['value'];
    $o['object'] = $o['object']['value'] ? $o['object']['value'] : $o['object']['literal'];
        
    return $o;
  };
  $form = array(
    'list' => array(
      '#type' => 'fieldset',
      '#title' => t('List relationships'),
      '#value' => theme('relationship_editor_table', array(
                       'relationships' => array_map($create_table_rows, $rels)
		       )),
    ),
  );

  return $form;

}

