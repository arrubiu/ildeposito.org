
Description
-----------
This module makes a javascript toolbox action available for image styles.
It can currently 'hook' into several modules by adding a 'javascript crop' link on the edit forms of supported modules and/or fields. 
The popup window will display all available styles with
a javascript crop action. In your theming you can use the imagestyle theme function with
a preset. The style action will make a database call to choose the right crop area.

The main difference with projects like eyedrop or imagefield_crop is that it doesn't 
provide it's own widget to upload images, instead it just 'hooks' into image modules/fields.

Everyone is invited to submit patches for more module support. I might
even give some people cvs access.

Installation
------------
Core Image module should be enabled
If you use jquery update. Make sure you also have the latest version from jquery_ui.
(For example jquery update 1.3.2 needs jquery ui 1.7.3)

After you enable the module, you can go to admin/settings/imagecrop and set some extra settings.
  - Theme beïng used: The theme that is used for showing the popup. Admin theme is recommended.
  - Trigger imagecrop also for: Enable imagecrop for picture uploads that are not a field (ex profile pictures)
  - popup width and height
  - show cancel button: A button to cancel the popup is available in popup
  - skip image previews: Default imagecrop has a preview screen. If you want people to land on the cropping page, you can enable this checkbox
  - Advanced UI controls: Show a sidebar with live cropping info and the possibility to insert width / height
  - Step size for scale dropdown: The steps from the scaling selection. (ex: 50px = 500px width, 450px width, 400px width)
  - Autoscale the initial crop to fit the window: When a user uploads a big picture, the image will be scaled down, to fit in the popup
  - Allow rotation from image: Users can rotate an image 

After the settings are done. You can enable imagecrop for the styles you want.
Go to the image styles management, and edit the style you want. Choose 'Javascript crop' as an effect, and add it to your style.
You can also add 'Reuse a javascript crop selection'. This will automaticaly crop the image to the style you selected in this effect.

If you want to enable imagecrop for a field (ex image_field). Go to the field settings from your content type, and edit the image_field.
In the field settings, you see checkboxes from all available styles. (Available imagecrop styles).
Select the styles that you want to enable for this field.
After saving, a user will now see "Crop image" next to the uploaded image.

A cron task cleans up the imagecrop table clearing records from files and/or presets
which do not exist anymore, so make sure cron is running.

Extra Coolness
--------------
Imagecrop supports several modal modules to open your popup with.
Supported modules are:
  - colorbox (make sure you included node/*/edit in the module settings)
  - iframe
  
Features, support, bugs etc
---------------------------
File request,bugs,patches on http://drupal.org/project/imagecrop

Author
------
Nils Destoop - http://drupal.org/user/361625 - http://www.menhir.be