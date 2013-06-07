Introduction
============

This module provides further integration between the Entity reference and
Feeds modules, allowing the user to map values to fields and properties
of referenced entities. The mapper will automatically create the target
entity if it does not exist.

Mapping depth is limited to one.

Usage
=====

Some important points:

When for all entity references mapped to, a mapping for the unique GUID
target MUST be supplied. Else it would be impossible for the mapper to
separate new from updated entity values and keep on creating new ones.

Right now GUID is the only unique target supported.

Another potential source of confusion is that in the feeds importer settings 
will be there are two targets supplied for the GUID. One belongs to the 
"original" Entity referendce feeds integration, and one (with the more verbose
description) belongs to this module. When using Entity reference feeds for
a certain target field, use the one provided by this module.

Entities might have required values, that should be set to static values and
not provided by the feeds source. This can be done in the module's setting
page.
