Projet homepage: http://drupal.org/project/hidden_comment

This module allows you to hide a certain comment (a posteriori moderation).
Hidden comments are displayed like normal comment, except that the content
is nullified.

You can give a reason when hidding a comment. In the setting page
(admin/settings/hidden_comment), you can define default reasons. The first
default reason is used to pre-fill the reason textbox (you can use empty
string for the first reason).

Permissions:
- hide comments
  Hide any comments
- hide personal comments
  Hide comments in the user's nodes
- administer hidden comments
  Unhide hidden comments
- administer personal comments
  Unhide hidden comments in the user's nodes
