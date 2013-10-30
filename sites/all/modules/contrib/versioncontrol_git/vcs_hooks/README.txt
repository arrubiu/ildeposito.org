= Git hook scripts

This directory contains a set of example scripts that can be used via the hooks
provided by Git for several operations.

Naturally you will need to place them in the right $GIT_DIR/hooks directory  and
make them executable for them to work.

== Available hook scripts

For now the only available example hook script is post-receive.

=== post-receive

Enqueues a code arrival via drush, to schedule a log parsing.

Probably, if you only want to enqueue parse new code when it is added in the
repository, you wan to set its 'Update method' to 'Use external script to insert
data'.
