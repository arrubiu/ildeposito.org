<?php

$plugin = array(
  'title' => t('Default Git history synchronizer'),
  'worker' => array(
    'class' => 'VersioncontrolGitRepositoryHistorySynchronizerDefault',
  ),
);
