<?php

function islandora_relationship_editor_add_relationships(array $form, array &$form_state, $object_pid) {
  $form = array();
  $form['this'] = array(
    '#title' => t('This Object'),
    '#type' => 'textfield',
    '#value' => $object_pid,
    '#disabled' => TRUE,
  );
  $form['relationship'] = array(
    '#type' => 'select',
    '#title' => t('Relationship'),
    '#options' => get_possible_relationships($object_pid),
  );
  $form['target'] = array(
    '#type' => 'textfield',
    '#title' => t('Target object'),
  );
  $form['symmetric'] = array(
	  '#type' => 'fieldset',
	  '#title' => 'Symmetry',
  );
 $form['symmetric']['is-symmetric'] = array(
	  '#type' => 'checkbox',
	  '#title' => t('Add the corresponding relationship?'),
  );
  $form['symmetric']['sym-relationship'] = array(
	  '#type' => 'select',
	  '#title' => t('Choose the corresponding relationship'),
	  '#description' => t('This should be the "opposite" relationship, which will be applied to the target object, with a value of this object.'),
	  '#options' => get_possible_relationships($object_pid),
	  '#default_value' => '',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('submit'),
  );
  return $form;

}
function islandora_relationship_editor_add_relationships_validate($form, &$form_state) {
  $object = islandora_object_load($form_state['values']['this']);
  if (!$object) {
    form_set_error('object', t("This Fedora object doesn't exist."));
  }
  $target = islandora_object_load($form_state['values']['target']);
  if (!$target) {
    form_set_error('object', t("The target Fedora object doesn't exist. Please check the PID."));
  }
}

function islandora_relationship_editor_add_relationships_submit($form, &$form_state) {
  $object = islandora_object_load($form_state['values']['this']);
  $target = islandora_object_load($form_state['values']['target']);
  $chunks = explode('|', $form_state['values']['relationship']);
  $ns = $chunks[0];
  $relationship = $chunks[1];
  $object->relationships->add($ns, $relationship, $form_state['values']['target']);

  if ($form_state['values']['is-symmetric'] == 1) {
      $chunks = explode('|', $form_state['values']['sym-relationship']);
      $ns = $chunks[0];
      $relationship = $chunks[1];
	  $target->relationships->add($ns, $relationship, $form_state['values']['this']);
  }
  $form_state['redirect'] = "islandora/object/{$object->id}/manage/relationships";

}
