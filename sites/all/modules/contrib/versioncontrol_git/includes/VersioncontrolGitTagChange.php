<?php

class VersioncontrolGitTagChange extends VersioncontrolGitRefChange {

  public function __construct($data) {
    parent::__construct($data);
    $this->ff = NULL;
  }

  public function getLabel() {
    if (!empty($this->label_id)) {
      $tags = $this->repository->loadTags(array($this->label_id));
      return reset($tags);
    }
  }

  public function syncLabel() {
    if (!empty($this->refname)) {
      $tags = $this->repository->loadTags(array(), array('name' => $this->refname));
      if (!empty($tags)) {
        $tag = reset($tags);
        $this->label_id = $tag->label_id;
      }
    }
  }
}
