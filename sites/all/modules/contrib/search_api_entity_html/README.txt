Search API Entity HTML
======================

This simple module lets Views to display Entity HTML Output without stripping html tags.

The problem
===========
Search API gives the possibility to index the html of an entity.
But if you try to retrive this field from Views, called "Entity HTML Output",
the system strip html tags, and so the HTML output is useless.

The solution
============
With this modules every field from Search API that contains HTML output
of an entity is rendered without stripping html tags.

Dependencies
============
- Search API
- Search API Solr

Suggested
=========
- Entity View Modes
- Search API Solr Multiple View Modes

Developers
==========
This module has been developed by Sergio Durzu and Mauro Sardu.