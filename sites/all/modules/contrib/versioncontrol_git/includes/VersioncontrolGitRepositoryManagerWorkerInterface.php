<?php

interface VersioncontrolGitRepositoryManagerWorkerInterface extends VersioncontrolRepositoryManagerWorkerInterface {

  /**
   * Init a repository a repository on disk.
   *
   * If called on an existing repository, this will add any additional files
   * from the template directory that aren't already present. It will not
   * overwrite any existing files. If you must ensure the latest version of
   * some file, it is better to use
   * VersioncontrolGitRepositoryManagerWorkerInterface::reInit().
   */
  public function init();

  /**
   * Re-init a repository using the appropriate template directory.
   *
   * This method calls rm -rf $GIT_DIR/{each,file,in,param}, then calls init().
   * Make sure that provided file paths are relative to the $GIT_DIR.
   */
  public function reInit(array $flush);

  /**
   * Set a config option on the repository using `git config`.
   *
   * @param string $name
   *   The name of the config option to set, e.g., receive.denyNonFastForward.
   *   This option is passed through escapeshellarg().
   * @param string $value
   *   The value to set. This option is passed through escapeshellarg().
   * @param string $type
   *   The config value type hint to pass to git. Valid values are 'int', 'bool'
   *   or 'path'. Optional; see man 1 git-config for details.
   */
  public function configSet($name, $value, $type = NULL);

  /**
   * Set the contents of the git repo description file ($GIT_DIR/description).
   */
  public function setDescription($description);

  /**
   * Switches the default (HEAD) branch to the given one.
   *
   * @param $branch_name
   *   The name of the branch as under refs/heads, i.e. master.
   */
  public function setDefaultBranch($branch_name);

  /**
   * Reads the default branch from the Git repository.
   *
   * @return
   *   The name of the branch as under refs/heads HEAD points to.
   */
  public function fetchDefaultBranch();

  /**
   * Relocate the repository on disk to the new target location, then optionally
   * update the repository record in the database.
   */
  public function move($target);

  /**
   * Allows an arbitrary command to be run against the repository.
   *
   * Use of this command should be a last resort; whenever possible use the
   * more goal-specific methods that are provided.
   *
   * Note that the local setting for the git binary path is prepended to the
   * command string, so your command should only include the git subcommand
   * and additional arguments. For example, if you wanted to run the following:
   *
   *  `git config receive.denyNonFastForwards true`
   *
   * you should pass the following string as an array element:
   *
   *  `config receive.denyNonFastForwards true`
   *
   * @param string $command
   *   The string command to be run against the repository. The command will be
   *   executed using exec() after calling escapeshellcmd() on the entire
   *   command string.
   * @param bool $exception
   *   Whether or not to throw an (E_ERROR) exception on a non-0 exit status.
   * @return int
   *   The exit code of the command.
   */
  public function passthru($command, $exception = FALSE);
}

