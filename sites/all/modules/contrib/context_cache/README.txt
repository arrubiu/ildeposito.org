CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirement
 * Installation
 * Credits


INTRODUCTION
------------

Context Cache is module which lets you control caching and expiration through
Context. For example, for one content type you can set its cache for two hours
while for another content type you can set it for 30 minutes. In case you use an
external cache this module lets you set an expiration of five minutes for the
homepage and 30 minutes for any page under news/*, etc. The cache reaction works
with any condition that applies to anonymous users.


REQUIREMENT
-----------

Context module, version 3.x, http://drupal.org/project/context

Chaos tools which is required by Context, http://drupal.org/project/ctools


INSTALLATION
------------

If using Drush, "drush dl context_cache" and then "drush en context_cache"
otherwise unpack, place and enable just like any other module.

Navigate to Administration » Configuration » Development » Performance
(admin/config/development/performance) and make sure page cache is enabled if
you're looking to control your Drupal cache with this module. If you are using
an external cache you don't need to enable page caching.

Navigate to Administration » Structure » Context (admin/structure/context) and
click on a context or create a new one. Under Reactions the Add Reaction pull-
down menu will give you a new option, Cache.

Add the Cache reaction to a context. The "Internal" option controls Drupal's
page cache and the "External" option sets the proper headers for an external
cache, while "Disabled" disables page caching and sends strict headers to
prevent caching (no-cache/must-revalidate). The Cache Lifetime field lets you
select the duration of the cache, internal and external.


CREDIT
------

Gerald Melendez / geraldmelendez on Drupal.org
