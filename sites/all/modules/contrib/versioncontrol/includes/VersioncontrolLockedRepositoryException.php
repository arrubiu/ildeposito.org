<?php
/**
 * @file
 *
 * An exception to be thrown when an attempt is made to synchronize a locked
 * repository, but it has already been locked by another sync process.
 *
 */
class VersioncontrolLockedRepositoryException extends VersioncontrolSynchronizationException { }
