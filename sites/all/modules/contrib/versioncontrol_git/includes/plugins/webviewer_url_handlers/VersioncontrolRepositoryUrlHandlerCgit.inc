<?php
/**
 * @file
 * Repository Url handler class for cgit.
 */

/**
 * cgit webviewer url handler class.
 */
class VersioncontrolRepositoryUrlHandlerCgit extends VersioncontrolRepositoryUrlHandler {

  /**
   * cgit do not need to have a hash base parameter to show an item log history.
   */
  public function getItemLogViewUrl($item, $current_label = NULL) {
    $placeholders = array(
      '%repo_name' => $this->repository->name,
      '%path'     => substr($item->path, 1),
      '%revision' => $item->revision,
    );

    if (isset($current_label->type) && $current_label->type == VERSIONCONTROL_LABEL_BRANCH) {
      $label_name = $current_label->name;
    }
    if (isset($label_name)) {
      $placeholders['%branch'] = '?h=' . $label_name;
    }
    else {
      $placeholders['%branch'] = '';
    }

    $view_url = $item->isFile()
      ? $this->getTemplateUrl('file_view')
      : $this->getTemplateUrl('directory_view');

    return strtr($view_url, $placeholders);
  }

  /**
   * cgit do not need to have a hash base parameter to show an item content.
   */
  public function getItemViewUrl($item, $current_label = NULL) {
    // Removed items has not blob hash
    if (is_null($item->blob_hash)) {
      return '';
    }
    $placeholders = array(
      '%repo_name' => $this->repository->name,
      '%path'     => substr($item->path, 1),
      '%revision' => $item->blob_hash,
    );

    if (isset($current_label->type) && $current_label->type == VERSIONCONTROL_LABEL_BRANCH) {
      $label_name = $current_label->name;
    }
    if (isset($label_name)) {
      $placeholders['%branch'] = '&h=' . $label_name;
    }
    else {
      $placeholders['%branch'] = '';
    }

    $view_url = $item->isFile()
      ? $this->getTemplateUrl('file_view')
      : $this->getTemplateUrl('directory_view');

    return strtr($view_url, $placeholders);
  }
}
