<?php

class VersioncontrolGitBranchChange extends VersioncontrolGitRefChange {

  public function __construct($data) {
    parent::__construct($data);
  }

  public function getLabel() {
    if (!empty($this->label_id)) {
      return $this->repository->loadBranch(NULL, $this->label_id);
    }
  }

  public function syncLabel() {
    if (!empty($this->refname)) {
      $branch = $this->repository->loadBranch($this->refname);
      if (!empty($branch)) {
        $this->label_id = $branch->label_id;
      }
    }
  }
}
