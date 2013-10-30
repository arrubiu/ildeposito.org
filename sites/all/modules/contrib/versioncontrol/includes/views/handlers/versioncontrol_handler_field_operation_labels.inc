<?php
/**
 * @file
 *   Views Field handler to show the list of label names this operation is in.
 */
class versioncontrol_handler_field_operation_labels extends views_handler_field {
  public $backends = array();
  public $repositories = array();

  /**
   * An array to store operation objects we want its labels to show.
   */
  public $operations = array();

  function construct() {
    parent::construct();
    $this->backends = versioncontrol_get_backends();
  }

  /**
   * Get a repository of the @param $vcs type.
   */
  function getRepository($vcs, $repo_id) {
    if (!isset($this->repositories[$repo_id])) {
      $this->repositories[$repo_id] = $this->backends[$vcs]->loadEntity('repo', array($repo_id));
    }
    return $this->repositories[$repo_id];
  }

  function pre_render(&$values) {
    parent::pre_render($values);

    // Get all vc_op_ids.
    $vc_op_ids = array();
    $repository_data = array();
    foreach ($values as $result) {
      $vc_op_ids[$result->{$this->aliases['repo_id']}][$result->{$this->field_alias}] = TRUE;
      $repository_data[$result->{$this->aliases['repo_id']}] = $result->{$this->aliases['vcs']};
    }
    $repository_ids = array_keys($repository_data);

    foreach ($repository_ids as $repo_id) {
      $vcs = $repository_data[$repo_id];
      $repository = $this->getRepository($vcs, $repo_id);
      $commit_ids = array_keys($vc_op_ids[$repo_id]);
      if (!empty($commit_ids)) {
        $commits = $repository->loadCommits($commit_ids);
      }
      $this->operations += $commits;
    }
  }

  function render($values) {
    if (!isset($this->operations[$values->{$this->field_alias}])) {
      return '';
    }
    $operation = $this->operations[$values->{$this->field_alias}];
    $label_names = array();
    foreach ($operation->labels as $label) {
      $label_names[] = check_plain($label->name);
    }
    return implode(', ', $label_names);
  }

}
