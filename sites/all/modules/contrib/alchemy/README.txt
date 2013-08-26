; $Id $

DESCRIPTION
--------------------------
Alchemy is a API service that provides various different analysis on content. The Drupal Alchemy module provides an interface to that API primarily focused on keyword, entity and concept extraction from content.

The Alchemy module provides interfaces into three other modules:
* Content Analysis - drupal.org/project/contentanalysis
* Auto Tagging - drupal.org/project/autotagging
* Tagging - drupal.org/project/tagging

You will want to use the Alchemy module with at least one of these other modules.

INSTALLATION
---------------
- Upload the Alchemy archive files from drupal.org/project/alchemy to a modules directory on your server such as sites/all/modules/alchemy or sites/default/modules/alchemy.
- Download the Alchemy PHP SDK archive from http://www.alchemyapi.com/tools/ and install the files in the archive inside the module subdirectory alchemy/AlchemyAPI
- Enable the module via the Admin > Site building > Modules
- You will need an API Key from http://www.alchemyapi.com/api/register.html to use the Alchemy service. A FREE key is available that will give you up to 30,000 call per day. That should be more than enough for virtually any website.
- Enter your API Key at Admin > Site configuration > Alchemy and click the Save Configuration button.
- The last step is to configure the Alchemy module for any of the three interface modules:
  - For Content Analysis integration set configuration at Admin > Site configuration > Alchemy > Content Analysis
  - For Auto Tagging integration set configuration on the auto tagging settings page at Admin > Site configuration > Auto Tagging
  - For Tagging suggestions set configuration at Admin > Site configuration > Alchemy > Tagging


DEPENDENCIES
---------------
- None but you will need to integrate with Content Analysis, Auto Tagging or Tagging (or program your own custom module) for a user interface 

CREDITS
----------------------------
Sponsored by LevelTen Interactive
Authored and maintained by Tom McCracken <tom AT leveltendesign DOT com> twitter: @levelten_tom (http://www.leveltendesign.com)
