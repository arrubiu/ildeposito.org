<?php
/**
 * @file
 * Repository Url handler class for GitPHP.
 */

/**
 * Repository Url handler class for GitPHP.
 */
class VersioncontrolRepositoryUrlHandlerGitphp extends VersioncontrolRepositoryUrlHandler {

  public function fixItemPath($item) {
    // GitPHP need the path without the initial '/'.
    $gitphp_item = clone $item;
    $gitphp_item->path = substr($item->path, 1);
    return $gitphp_item;
  }

  public function getItemLogViewUrl($item, $current_label = NULL) {
    if (!$item->isFile()) {
      // GitPHP do not support folder history
      return '';
    }
    $gitphp_item = $this->fixItemPath($item);
    return parent::getItemLogViewUrl($gitphp_item, $current_label);
  }

  public function getItemViewUrl($item, $current_label = NULL) {
    $gitphp_item = $this->fixItemPath($item);
    $placeholders = array(
      '%repo_name' => $this->repository->name,
      // GitPHP need the path without the initial '/'.
      '%path'     => substr($gitphp_item->path, 1),
      '%revision' => $gitphp_item->blob_hash,
    );

    if (isset($current_label->type) && $current_label->type == VERSIONCONTROL_LABEL_BRANCH) {
      $label_name = $current_label->name;
    }
    if (isset($label_name)) {
      $placeholders['%branch'] = '&hb=' . $label_name;
    }
    else {
      $placeholders['%branch'] = '';
    }

    $view_url = $gitphp_item->isFile()
      ? $this->getTemplateUrl('file_view')
      : $this->getTemplateUrl('directory_view');

    return strtr($view_url, $placeholders);
  }

  public function getDiffUrl($file_item_new, $file_item_old, $current_label = NULL) {
    $gitphp_old_item = $this->fixItemPath($file_item_old);
    $placeholders = array(
      '%repo_name' => $this->repository->name,
      '%path'         => $file_item_new->path,
      '%new_blob_hash' => $file_item_new->blob_hash,
      '%old_path'     => $file_item_old->path,
      '%old_blob_hash' => $gitphp_old_item->blob_hash,
      '%old_revision' => $file_item_old->revision,
    );

    return strtr($this->getTemplateUrl('diff'), $placeholders);
  }

}
