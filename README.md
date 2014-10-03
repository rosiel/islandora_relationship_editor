islandora_relationship_editor
=============================

Islandora extension to add/view/delete RELS-EXT relationships

With this module, you can add rels-ext relationships to an object via the "Manage" tab. (Manage -> relationships). 
You can also add the reciprocal ('symmetric') relationship in one fell swoop.

- TODO: implement delete functionality. 
- TODO: create permissions to let Drupal users add/delete relationships - currently it's ISLANDORA_METADATA_EDIT. 
- TODO: source relationships from an actual ontology and use the appropriate namespace.
- TODO: programmatically determine the "reciprocal" relationship based on the chosen relationship
- Further TODO: autocomplete the target object pid from typing pid or label
- Further TODO: insert this form into the ingest steps (?)
