<?php

/**
 * @file
 * Template for related items
 *
 * @TODO: Add documentation about this file and the available variables
 */
?>

<div class="islandora-related-objects islandora">
  <div class="islandora-related-content-wrapper clearfix">

    <?php if($related): ?>
      <div>
        <h2><?php print t('Related Objects'); ?></h2>
        <ul>
          <?php foreach ($related as $obj): ?>
            <?php if(isset($obj['thumbnail_url'])): ?>
              <div class="thumb"><?php print $obj['thumbnail_url']; ?> </div>
            <?php endif; ?>
            <div class="label"><?php print $obj['relationship'] . ' : ' .  $obj['object_link']; ?></div>
          <?php endforeach; ?>
        </ul>
      </div>
    <?php endif; ?>
  </div>
</div>

