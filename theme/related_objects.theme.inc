<?php
/**
 * @file
 * Theme functions for related items block.
 */

/**
 * Implements hook_preprocess().
 */
function islandora_relationship_editor_preprocess_islandora_relationship_editor_related_objects(&$variables) {
  $islandora_object = $variables['islandora_object'];
  $repository = $islandora_object->repository;
  $rels = $islandora_object->relationships->get();
  $related = array();
  foreach ($rels as $key => $rel) {
    if (($rel['predicate']['alias'] != 'fedora') and ($rel['predicate']['alias'] != 'fedora-model')) {
      try {
        $object = $islandora_object->repository->getObject($rel['object']['value']);
      }
      catch (Exception $e) {
        continue;
      }
      if ($object) {
        $values = array();
        $values['object_link'] = l($object->label, "islandora/object/{$object->id}");

        if (isset($object['TN']) && islandora_datastream_access(ISLANDORA_VIEW_OBJECTS, $object['TN'])) {
          $values['thumbnail_url'] = theme('image', array(
            'path' => url("islandora/object/{$object->id}/datastream/TN/view"),
            'attributes' => array(),
          ));
        }

        $related[] = $values;

      }
    }
  }
  $variables['related'] = $related;
}

/**
 * Implements hook_block_view_alter().
 */
function islandora_ethnography_block_view_alter(&$data, $block) {
  #print ('foo');
}
