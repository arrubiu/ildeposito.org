
-- SUMMARY --

The Simplenews Scheduler module allows you to send a newsletter as a re-occurring item
based on a schedule. It does so by creating a new "edition" (rendered copy as HTML Format)
of a node at the time that it required to be sent again.

The editions have an extra tab (for those with permissions) for viewing all editions as well as
the original newsletter they are generated from. The original newsletter is never sent but all
editions are according to a pre-defined schedule which is triggered via cron and can be
defined when you create or edit a simplenews node.

Current options for sending are by day, week, and month.

For a full description of the module, visit the project page:
  http://drupal.org/project/simplenews_scheduler

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/simplenews_scheduler


-- REQUIREMENTS --

* Simplenews module - http://drupal.org/project/simplenews
* Date module - http://drupal.org/project/date


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.


-- RECOMMENDED --

* SuperCron module - http://drupal.org/project/supercron


-- CONFIGURATION --

Locate the module options under "Send newsletter" on the node edit page. When you select
"Send newsletter according to schedule" a new section titled "Schedule details" appear.

-- CONTACT --

Current maintainers:
* Leigh Morresi (dgtlmoon) - http://drupal.org/user/25027
* Gabor Seljan (sgabe) - http://drupal.org/user/232117

-- D7 RELEASE NOTES --

A field for interval frequency was integrated. At the moment it's not possible to create
a custom plaintext version of the newsletter for scheduled sending.
