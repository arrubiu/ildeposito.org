; $Id $

DESCRIPTION
--------------------------
The Content Analysis module acts as a standard interface (API) for other modules to analyze page content. This module does nothing by itself. You only need it if you are using another module that requires it or you want to build your own module for analyzing content.

Below is a list of analyzers that provide content analysis:
�	Content Optimizer - drupal.org/project/contentoptimizer � Analyses content for search engine optimization.
�	Scribe SEO 
�	Readability
�	W3C Analyzer


INSTALLATION
---------------
1.	Download it from drupal.org/project/contentanalysis. 
2.	Upload to a valid module directory in your Drupal installation. E.g. sites/all/modules
3.	Once upload go to the Modules admin, admin/build/modules, and enable the module. Also enable any analyzer modules you want to use to analyze content. See the list below for available analyzers.
4.	Go to the Content Analysis admin configuration, admin/settings/contentanalysis and set your configuration and defaults.

USAGE
----------------
Content Analysis provides two interfaces for analyzing content:
1.	Page Analyzer via Admin > Content management > Content Analysis 
2.	Node Analyzer via node edit forms

The node analyzer UI adds a fieldset to the node edit forms with an �Analyze Content� button. When clicked the, the module sends the node edit form�s body, title and other content to the sever via AJAX and returns recommendations on how to better optimize each of your content areas based on the Content Analyzers you have enabled.

API Integration
----------------
The Content Analysis module essentially consists of two parts. The first takes user input to designate a content source and analyzer option, then parses the content to create a consistant context. The module then calls any enabled analyzers which add status messages and content based on their analysis. Then the Content Analysis module themes the output and returns it to the user.

In order to create an analyzer you must understand the data structures, hooks and helper functions.

Data Structures:
The Content Analysis provides two main datastructures: 
Context - the content readied for analysis
Analysis - The output from the analyzers.

Note: both datastructures were loosely based on the Form API structure

Context:
�	aid - the analysis id (created by the Content Analysis module)
�	nid - node id if a node is being analyzed
�	path - the Drupal path of the page being analyzed
�	url - the url of the page being analyzed
�	page - if analyzing a full web page, this contains the full content of the xHTML document
�	title - the node title if a node is being analyzed
�	node_body - the node body if a node is being analyzed
�	body - the main content, e.g. what is between the <body></body> tags if a page is anazlysed or the node body if a node is being analyzed
�	body_notags - the body content striped of all xHTML tags 
page_title - the page title, e.g. what is between the <title></title> tags
�	meta_keywords - the content in the <meta keywords=""> tag
�	meta_description - the content in the <meta description=""> tag
�	inputs - data inputed by the submission form/action
  �	analyzers - analyzers enabed by the user input
  �	analyzer_options - custom input defined by an analyzer
  
Analysis
Each analyzer addes a hash to the Analysis array keyed by the machinecode of the analyzer.
For example if you had the reability and Scribe SEO enabled you would have: 

Analysis (Array 2 elements)
  �	readability
  �	scribeseo

There are two main types of output analyzers can add to the analysis array:
messages: similar to drupal_set_message these have text (the message) and a status (status|complete|warning|error)
content: general text to add to the output, similar to the markup type in the form API

All messages have the form

Each analyzer element includes a set of general attributes including:
#title - The title of the analyzer
#status - set to one of four values to indicate the status (status|compete|warning|error)
content - contains any content
  


 

CREDITS
----------------------------
Authored and maintained by Tom McCracken <tom AT leveltendesign DOT com> twitter: @levelten_tom
Sponsored by LevelTen Interactive - http://www.leveltendesign.com