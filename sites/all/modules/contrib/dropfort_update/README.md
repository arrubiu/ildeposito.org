Dropfort Update
===============

Reports on project update and system status information to Dropfort.com

Also allows site admins to apply update policies to their sites. See http://dropfort.com/features/update-policies for more information.

Installation/Drupal Configuration
----------------------------------

1. Enable the module
2. Go to admin/config/system/dropfort/update
3. Configure your settings
    - You will also find your site key and site token on this page.
4. Follow the "Guided Setup" steps to register your site against your Dropfort instance.

Drush Configuration
-------------------

Drupal will automatically respect the moderated update data.

How it works
------------

Dropfort Update implements ````hook_update_status_alter()```` which allows it to modify the available update information. It will contact the Dropfort instance and filter this information if it is configured to do so. These alterations are cached until a modification to your installed projects or a cache clear is run.

Usage
-----

This module is designed to be used in conjunction with an account on Dropfort.com or an equivalent instance of the Dropfort Drupal distribution.

It enables are the concept of "Update Policies". This allows you to restrict which updates to which modules your Drupal site will see. For example, if you're code depends on a specific version of Views (say you're running a patched version) then in your Update Policy you can set it so that Drupal's update system never sees a newer version of Views. Then, once that patch is incorporated into Views, you update the policy to allow that version to be seen. This is helpful if you aren't necessarily the only person managing a site and want to avoid destructive update notifications from appearing.

It is also useful in development environments to ensure your developers only use approved versions of modules or even and approved list of modules. Dropfort Update also affects the list of projects visible through ````drush```` commands.

You can always view the list of available updates for your sites on the connected Dropfort site. There you can manage the list of updates and choose which to allow through.

### Drush Make
To download authenticated projects from Dropfort using a Drush Make file, you'll have to follow a slightly modified format for downloading projects from Drupal.org. By following this format, it allows Dropfort Update to take care of adding in your authentication tokens when building the make file.

To trigger the dropfort make processor you need to provide the following in your project definition in your make file

- download type set to "dropfort"
- project type (i.e. module, theme) *
- (optional) download status url (default is https://app.dropfort.com/fserver/release-history)

This let's you avoid embedding your site tokens or auth tokens into your make files. Drush will use your user's auth token as defined in your ~/.drush/drushrc.php file.
See the **examples** folder in this module or https://git.dropfort.com/dropfort/dropfort_documentation/wikis/home#configure-dropfort-update-and-drush for more details.

For an example, see **examples/make.example** in this module.

Security
--------

Communication between your site and Dropfort is both encrypted and verified. You have the option of enforcing SSL/TLS connections between Dropfort and your Drupal site (enabled by default). As well, the identity of the connecting Dropfort site is verified using OpenSSL public key authentication. This guarantees that the data being sent and identity of the connecting Dropfort instance is secured from prying eyes.

Authentication between your site and the update feed on your Dropfort instance are done using the ````drupal_private_key```` variable value (which we call your "site key", this is normally included in all update requests made by Drupal) as well as by adding your secret Dropfort site token to the project info passed to the update server. See admin/config/system/dropfort/update for more details.

Known Issues
------------
### $base_url
Please be sure to set the <code>$base_url</code> value in your settings.php file to a fixed value. Drupal can improperly detect the <code>$base_url</code> value if it's running through drush vs through the web interface. The difference in values can cause issues with authenticating requests to Dropfort.com
Hopefully we can resolve this in a way where you won't have to fix that variable explicitly.

See [Issue 2412621](https://www.drupal.org/node/2412621) for more details.


Authors
-------

- Mathew Winstone (minorOffense)
- David Pascoe-Deslauriers (spotzero)
- Francois Xavier Lemieux (ClassicCut)
- Tiffany Tse (ttse)
