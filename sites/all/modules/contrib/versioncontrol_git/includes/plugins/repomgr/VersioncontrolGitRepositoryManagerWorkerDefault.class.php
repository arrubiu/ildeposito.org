<?php

class VersioncontrolGitRepositoryManagerWorkerDefault implements VersioncontrolGitRepositoryManagerWorkerInterface {

  protected $repository;

  protected $templateDir;

  public function setRepository(VersioncontrolRepository $repository) {
    // Additional parameter check to the appropriate Git subclass of that
    // required by the interface itself.
    if (!$repository instanceof VersioncontrolGitRepository) {
      $msg = 'The repository "@name" with repo_id "@repo_id" passed to ' . __METHOD__ . ' was not a VersioncontrolGitRepository instance.' ;
      $vars = array(
        '@name' => $repository->name,
        '@repo_id' => empty($repository->repo_id) ? '[NEW]' : $repository->repo_id,
      );
      watchdog('versioncontrol', $msg, $vars, WATCHDOG_ERROR);
      throw new Exception(strtr($msg, $vars), E_ERROR);
    }
    $this->repository = $repository;
  }

  public function create() {
    $this->init();
    $this->save();
  }

  public function init() {
    // if mkdir fails for some reason, it'll error out
    $this->proc_open('mkdir -p ' . escapeshellarg($this->repository->root), TRUE);

    // Create the repository on disk. Init with a template dir if one exists
    if (!empty($this->templateDir) && file_exists($this->templateDir)) {
      $return = $this->passthru('init --template ' . $this->templateDir, TRUE);
    }
    else {
      $return = $this->passthru('init', FALSE);
    }

    if ($return) {
      // init failed for some reason, throw exception
      throw new Exception('Git repository initialization failed with code ' . $return, E_ERROR);
    }

    return TRUE;
  }

  public function reInit(array $flush) {
    if (!empty($flush)) {
      $flush = count($flush) > 1 ? '{' . implode(',', $flush) . '}' : array_shift($flush);
      $command = "rm -rf " . escapeshellarg($this->repository->root) . "/$flush";
      $this->proc_open($command, TRUE);
    }
    $this->init();
  }

  public function configSet($name, $value, $type = NULL) {
    $cmd = 'config --file ';
    if (!is_null($type) && in_array($type, array('int', 'bool', 'path'))) {
      $cmd .= "--$type ";
    }
    $cmd .= escapeshellarg($name) . ' ' . escapeshellarg($value);
    $return = $this->passthru($cmd);
    return empty($return);
  }

  public function delete() {
    $command = 'rm -rf ' . escapeshellarg($this->repository->root);
    // This'll error out if deletion fails.
    $this->proc_open($command, TRUE);

    $this->repository->delete();
    return TRUE;
  }

  public function move($target) {
    $command = 'mv ' . escapeshellarg($this->repository->root) . ' ' . escapeshellarg($target);
    $this->proc_open($command, TRUE);
    $this->repository->root = $target;
    return TRUE;
  }

  public function save() {
    $this->repository->save();
    return TRUE;
  }

  public function setDescription($description) {
    file_put_contents($this->repository->root . '/description', $description);
    return TRUE;
  }

  public function setDefaultBranch($branch_name) {
    $this->passthru('symbolic-ref --quiet HEAD ' . escapeshellarg('refs/heads/' . $branch_name), TRUE);
    $this->repository->defaultBranch = $branch_name;
  }

  public function fetchDefaultBranch() {
    // Prepare the git name-rev command to get the branch referenced by HEAD.
    $command = escapeshellcmd(_versioncontrol_git_get_binary_path() . ' symbolic-ref --quiet HEAD');

    // Execute it in the git repository using proc_open.
    $descriptor_spec = array(
      1 => array('pipe', 'w'),
      2 => array('pipe', 'w'),
    );
    $env = array(
      'GIT_DIR' => $this->repository->root,
    );
    $process = proc_open($command, $descriptor_spec, $pipes, $this->repository->root, $env);
    if (!is_resource($process)) {
      $vars = array('%root' => $this->repository->root);
      watchdog('versioncontrol', 'Failed to execute git symbolic-ref in %root.', $vars, WATCHDOG_ERROR);
      throw new Exception(t('Failed to execute git symbolic-ref in %root.', $vars));
    }

    // Read from the output streams and close them.
    $stdout = stream_get_contents($pipes[1]);
    $stderr = stream_get_contents($pipes[2]);
    fclose($pipes[1]);
    fclose($pipes[2]);

    // The exit code must be 0.
    if ($ret = proc_close($process)) {
      $vars = array(
        '%root' => $this->repository->root,
        '%ret' => $ret,
        '%stdout' => $stdout,
        '%stderr' => $stderr,
      );
      watchdog('versioncontrol', "git symbolic-ref exited with return code %ret in %root, emitting stdout:\n%stdout\n\nand stderr:\n%stderr", $vars, WATCHDOG_ERROR);
      throw new Exception(t('git-symbolic-ref exited with return code %ret in %root.', array_slice($vars, 0, 2)));
    }

    // Stdout should be refs/heads/<branchname>.
    if (!preg_match('/^refs\/heads\/(.*)$/', $stdout, $match)) {
      $vars = array(
        '%root' => $this->repository->root,
        '%stdout' => $stdout,
      );
      watchdog('versioncontrol', 'Output of git-symbolic ref HEAD in %root was %stdout, which is not under refs/heads/.', $vars, WATCHDOG_ERROR);
      throw new Exception(t('Output of git-symbolic ref HEAD in %root was %stdout, which is not under refs/heads/.', $vars));
    }

    // Set it on the repository object and return it.
    $this->repository->defaultBranch = $match[1];
    return $this->repository->defaultBranch;
  }

  public function passthru($command, $exception = FALSE) {
    $command = escapeshellcmd(_versioncontrol_git_get_binary_path() . ' ' . $command);

    $env = array(
      'GIT_DIR' => $this->repository->root,
    );
    return $this->proc_open($command, $exception, file_exists($this->repository->root) ? $this->repository->root : NULL, $env);
  }

  /**
   * Ensure we're properly set up before we try to do anything. If setup does
   * not pass verification, watchdog and optionally throw exceptions.
   */
  public function verify($exception = TRUE) {
    if (!is_null($this->verified)) {
      return $this->verified;
    }

    $this->verified = TRUE;

    if (empty($this->repository)) {
      $this->verified = FALSE;
      $msg = 'No repository object was attached for the repomgr to work on.';
      watchdog('versioncontrol', $msg, array(), WATCHDOG_ERROR);
      if ($exception) {
        throw new Exception($msg, E_ERROR);
      }
    }

    return $this->verified;
  }

  /**
   * Actually run the command, with full output control using the goodies of
   * proc_open().
   *
   * This is fully generic, so can also be used for git commands - we do all the
   * escaping and limiting to a particular dir in the public-facing passthru()
   * method, which then calls this.
   */
  protected function proc_open($command, $exception, $cwd = NULL, $env = array()) {
    $descriptor_spec = array(
      1 => array('pipe', 'w'),
      2 => array('pipe', 'w'),
    );

    $process = proc_open($command, $descriptor_spec, $pipes, $cwd, $env);
    if (is_resource($process)) {
      $stdout = stream_get_contents($pipes[1]);
      fclose($pipes[1]);
      $stderr = stream_get_contents($pipes[2]);
      fclose($pipes[2]);

      $return_code = proc_close($process);

      if ($return_code) {
        $vars = array(
          '%command' => $command,
          '%code' => $return_code,
          '%stdout' => $stdout,
          '%stderr' => $stderr,
        );
        $text = "Invocation of '%command' exited with return code %code";
        watchdog('versioncontrol', $text . ", emitting stdout:\n%stdout\n\nand stderr:\n%stderr", $vars, WATCHDOG_ERROR);
        if ($exception) {
          throw new Exception(strtr($text, array_slice($vars, 0, 2)), E_ERROR);
        }
      }

      return $return_code;
    }

    return FALSE;
  }
}

