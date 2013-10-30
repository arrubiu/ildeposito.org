<?php
/**
 * @file
 *
 * An exception to be thrown when an error occurs during event-driven
 * repository synchronization that can or should be resolved by a full sync
 * attempt.
 *
 */
class VersioncontrolNeedsFullSynchronizationException extends VersioncontrolSynchronizationException { }
