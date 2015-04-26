<?php


function islandora_relationship_editor_display_relationships(array $form, array &$form_state, $object_pid) {
  $object = islandora_object_load($object_pid);
  if (!$object) {
    drupal_set_message("Fedora object doesn't exist.");
    drupal_not_found();
    exit;
  }
  $rels = $object->relationships->get();
  $create_table_rows = function($o) use ($object_pid) {
    #TODO: Can't create a delete path that uses the full namespace because it may contain forward slashes. is there another way to pass this argument than as a url?
    $delete_path = islandora_relationship_editor_get_delete_path($object_pid, $o['predicate']['namespace'], $o['predicate']['value'], $o['object']['value'] ? $o['object']['value'] : $o['object']['literal']);
    $o['relationship'] = $o['predicate']['namespace'] . $o['predicate']['value'];
    if (isset($o['object']['value'])) {
      $target = islandora_object_load($o['object']['value']);
      $o['object'] = $target ? $target->label . ' ('. $o['object']['value'] . ')' : t("WARNING: Target object no longer exists.") . ' (' . $o['object']['value'] . ')' ;
    }
    elseif (isset($o['object']['literal'])) {
      $o['object'] = $o['object']['literal'];
    }
    else {
      $o['object'] = '';
    }
    $o['delete'] = l(t('Delete'), $delete_path );
    if ($o['predicate']['namespace'] == 'info:fedora/fedora-system:def/model#') {
      $o['delete'] = t('Can\'t delete fedora model.');
    }
    if ($o['predicate']['namespace'] == 'info:fedora/fedora-system:def/relations-external#' and $o['predicate']['value'] == 'isMemberOfCollection') {
      $o['delete'] = t('Manage from collection object');
    }
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

