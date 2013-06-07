Description
-----------
This module allows the users to select taxonomy terms/tags by just clicking on
them rather than typing them (auto-complete) or selecting them from a select
box/checkbox/radio etc. It shows them a list of tags, sorted by popularity
(defined as how many nodes are tagged with it), up to a configurable maximum
number. Also, when you hover over a listed tag, it shows how many times it has
been used.

This helps the user see what the most commonly used tags, rather than having
to guess. It also avoids creation of numerous closely related and similar tags
because the user can see such a tag if it already exists. The fact that the tag
is only a click away, encourages users to coalesce around a tighter vocabulary
than one would have in the absence of this module.

Requirements
------------
Drupal 7.x and "taxonomy" module (part of core).

Installation & Usage
------------
See the screenshots for usage examples. To use popular_tags, do the following.

1. Copy the entire popular_tags directory the Drupal sites/all/modules
directory (or sites/<yoursite>/modules).

2. Login as an administrator. Enable the module in the "Administer" -> "Modules"

3. Visit the term-reference fields in your content types (at
admin/structure/types/manage/<mytype>/fields/<myfield> under
Structure>Content Types>MyType>Manage Fields>MyField) and under the "Popular
Tags" fieldset, check the "Use Clickable Popular Tags?" checkbox.

4. Now create or edit a node of MyType and right under the tag field you'll
see a list of clickable popular tags (provided that some tags do exist).

That's it. Now whenever you edit a node of that content type, you will have
clickable/popular tags listed for you.
