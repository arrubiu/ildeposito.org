; $Id $

DESCRIPTION
--------------------------
This module integrates as suite of SEO tools into a single dashboard.

For more inforamtion and a list of module dependancies see:
drupal.org/project/seotools 

INSTALLATION
---------------
* Upload the seotools archive to a modules directory on your server such as sites/all/modules or sites/default/modules.
* Enable the module via the admin > site building > modules
* Depending on the modules you already have installed in your site, you may get a message to ???
* Go to Admin > Presents > SEO Tools (admin/presets/seotools). This page will walk you through the installation and configuration of modules needed to complete the suite.
* The top of the page contains a list of modules. Any modules highlighed in red need to be uploaded and installed.
  - Use the "Download" link to download the modules from drupal.org (or use Drush or CVS checkout if you prefer). Places these modules in the same directory on your server you placed the seotools directory.
* When done refresh the page. Now no modules should have a red X. Click the "Enable" links next to any modules. You will be taken to the Admin > Site building > Modules page where a message box will appear allowing you to automatically enable all the modules you just uploaded.
  - Click the "Enable Recommended Modules" button
  - Enable any dependent modules if necissary
* Return to Admin > Presents > SEO Tools. It may take a while for the page to load.
* Scroll down to "Auto configuration all" and click the "Reset All" link. This will configure all modules to any presets that can be auto-configured. 
* Scroll down to "Custom configurations". Not all module settings can be auto-configured. In this section you will need to input various different settings. Follow the instructions for each input to complete installation.


CREDITS
----------------------------
Authored and maintained by Tom McCracken <tom AT leveltendesign DOT com> twitter: @levelten_tom
Sponsored by LevelTen Interactive - http://www.leveltendesign.com