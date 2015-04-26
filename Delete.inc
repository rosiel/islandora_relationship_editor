<?php

function islandora_relationship_editor_delete_relationships(array $form, array &$form_state, $objectPid, $namespace, $relationship, $targetPid) {
  $object = islandora_object_load($objectPid);
  if (!$object) {
    drupal_set_message("Fedora object " . $objectPid . " not found.");
    drupal_not_found();
    exit;
  }
  $namespace = urldecode($namespace);
  $relationship = urldecode($relationship);
  $form_state['storage']['object'] = $object;
  $form_state['storage']['namespace'] = $namespace;
  $form_state['storage']['relationship'] = $relationship;
  $form_state['storage']['targetPid'] = $targetPid;

  $form['confirmed'] = array(
    '#type' => 'value',
    '#value' => $objectPid,
  );
  return confirm_form(
    $form,
    t("Are you sure you want to delete this relationship?"),
    'example',
    "This will delete &lt;$objectPid&gt;&lt;$namespace" . "$relationship&gt;&lt;$targetPid&gt;.",
    t('Delete'),
    t('Cancel')
  );
  return $form;

}

function islandora_relationship_editor_delete_relationships_validate(array $form, array &$form_state) {
  if (!isset($form_state['storage']['namespace']) || !$form_state['storage']['namespace']) {
    form_set_error('value', t("Can't delete a relationship without a namespace."));
  }
  if (!isset($form_state['storage']['relationship']) || !$form_state['storage']['relationship']) {
    form_set_error('value', t("Can't delete a relationship without a target relationship."));
  }
  if (!isset($form_state['storage']['targetPid']) || !$form_state['storage']['targetPid']) {
    form_set_error('value', t("Can't delete a relationship without a target object."));
  }
}

function islandora_relationship_editor_delete_relationships_submit(array $form, array &$form_state) {
  if (isset($form_state['values']['confirmed'])) {
    // Delete the relationship.
    $object = $form_state['storage']['object'];
    $namespace = $form_state['storage']['namespace'];
    $relationship = $form_state['storage']['relationship'];
    $targetPid = $form_state['storage']['targetPid'];
    $object->relationships->remove($namespace, $relationship, $targetPid);
    $form_state['redirect'] = 'islandora/object/' . $object->id . '/manage/relationships';
  }
}


