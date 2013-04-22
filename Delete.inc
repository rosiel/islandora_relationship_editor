<?php

function islandora_relationship_editor_delete_relationships(array $form, array &$form_state, $objectPid, $namespace, $relationship, $targetPid) {
  $object = islandora_object_load($objectPid);
  if (!$object) {
    drupal_set_message("Fedora object " . $objectPid . " not found.");
    drupal_not_found();
    exit;
  }
  return array(
    'object_pid' => array(
      '#type' => 'hidden',
      '#value' => $objectPid,
    ),
    'description' => array(
      '#type' => 'markup',
      '#prefix' => '<div>',
      '#markup' => t('This function is not yet implemented.'),
      '#suffix' => '</div>',
    ),
    'back' => array(
      '#type' => 'submit',
      '#value' => t('Go back'),
      '#name' => 'back',
    ),
  );
}

function islandora_relationship_editor_delete_relationships_submit(array $form, array &$form_state) {

    $form_state['redirect'] = 'islandora/object/' . $form_state['values']['object_pid'] . '/manage/relationships';
}


