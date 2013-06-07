MODULE
------
PDF using mPDF


DESCRIPTION/FEATURES
--------------------
* This module is used Conversion of HTML page to PDF using mPDF PHP Library.
This module allows you to generate the following pdf documents of any node:

  * PDF creation (at www.example.com/node/nid/pdf)

  where nid is the node id of content to render.


REQUIREMENTS
------------
Drupal 7.0


INSTALLATION
------------

pdf_using_mpdf module is dependent on the Libraries module, you need to
have Libraries module enabled prior to using pdf_using_mpdf module.

Decompress the pdf_using_mpdf.tar.gz file into your Drupal modules
directory (usually sites/all/modules) and rename the directory to "mpdf".

Enable the PDF Using mPDF module: Administration > Modules (admin/modules)

Create a directory (if not exists) named 'libraries' in /sites/all/ or 
/sites/your-domain-name/ and download mPDF PHP library in this directory.

You can also download mPDF library in the module directory itself without 
creating any 'libraries' directory.


CONFIGURATION
-------------

- There are several settings that can be configured in the following places:

  Administration > Modules (admin/modules)
    Enable or disable the module. (default: disabled)

  Administration > People > Permissions (admin/people/permissions)
    Under PDF using mPDF module.
    
  Administration > Configuration > User interface > PDF using mPDF settings
  (admin/config/user-interface/mpdf)
    This is where all the module-specific configuration options can be set.

- To create your own template pages, simply edit the node.tpl.php or
the css/style.css files.

- It is possible to set per-content-type and/or theme-specific templates
  which are searched for in the following order: 
  1. node--[id].tpl.php in the active theme directory.
  2. node--[type].tpl.php in the active theme directory.
  3. node.tpl.php in the active theme directory.


API
---

pdf_using_mpdf_api()

This api function is available to content developers that prefer
to generate a pdf file of custom path. The function takes two 
parameters, first a rendered html content and an optional second 
parameter, name of the pdf file.

Calling the function like this:

  pdf_using_mpdf_api($html)

will return the PDF file for the current html passed to it.

It is also possible to specify the function like this:

  pdf_using_mpdf_api("<html><body>Hello</body></html>", "mypdf")

will return the PDF file with a "Hello" and file named "mypdf.pdf".


PDF TOOL
--------

The pdf_using_mpdf module requires the use of an external PDF generation tool.
The currently supported tools are mPDF. Please note that any errors/bugs in
those tools need to be reported and fixed by their maintainers. DO NOT report
bugs in those tools in the PDF Using mPDF module's issue queue at Drupal.org.

supported paths:
  * libraries directory (sites/all/libraries/)
  * module directory itself (sites/all/modules/pdf_using_mpdf/)


MPDF support:
-------------
  MPDF's support for CSS is considerably worse than the other tools.
  Unicode is supported (use of Unicode fonts result in HUGE files).  Page
  header and footer are supported. This module requires MPDF >= 5.4 .

  1. Download mPDF from http://www.mpdf1.com/mpdf/download.
  2. Extract the contents of the downloaded package into one of the supported
  paths. There is a need to rename mpdf directry to mpdf eg: 'MPDF54' to 'mpdf'
  3. Grant write access to the cache and images directories to your
  webserver user.
  4. Check http://www.mpdf1.com/ for further information.
