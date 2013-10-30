= Version Control API =

An interface to version control systems whose functionality is provided by
pluggable back-end modules.


== Short description ==

This is a pure API module, providing functions for interfacing with version
control systems (VCS). In order to work, Version Control API needs at least one
VCS backend module that provides the specific VCS's functionality.

For the API documentation, please run doxygen. If you are about to create a new
backend module please take a look to versioncontrol_fakevcs.
The provided hooks for API users are documented in versioncontrol.api.php.

In subdirectories, you can find three modules that extend the basic
administration functionality of Version Control API with additional
functionality:

- Commit Log displays a history of commits and sends out notification mails
  to the version control administrator.

Have a look at the link:OVERVIEW.html[OVERVIEW.txt] file for a basic
introduction into concepts, forms and API of this module.


== Authors ==

- Jakob Petsovits - http://drupal.org/user/56020
- Sam Boyer - http://drupal.org/user/146719
- Marco Villegas - http://drupal.org/user/132175

== Credits ==

=== 6.x-1.x ===

Some code in Version Control API was taken from the CVS integration module on
drupal.org, its authors deserve a lot of credits and may also hold copyright for
parts of this module.

This module was originally created as part of Google Summer of Code 2007, so
Google deserves some credits for making this possible. Thanks also to Derek
Wright (dww) and Andy Kirkham (AjK) for mentoring the Summer of Code project.

=== 6.x-2.x ===

On 2009, Marco Villegas did some major refactoring to convert the code to OOP as
part of Google Summer of Code 2009.

The second big change in the branch was to make internal entities drupal
entities, done mainly by Sam Boyer.

Another important change done in the branch was to embrace ctools plugins on
every possible aspect, so any other module can extend it. Done, mainly by Sam
and Marco.

A lot more people participated in the development of this branch, in preparation
to the Great Git Migration for drupalorg.

=== 7.x-1.x ===

The initial step of porting to D7 was provided by Eric J. Duran (ericduran).
Most of the work in this branch was a joined effort between Howard Tyson
(tizzo), Sam Boyer and Marco Villegas.
