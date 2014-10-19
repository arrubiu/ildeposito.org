README.txt
==========

Captcha-free is based on a tutorial by Jack Born published on jQuery.com.
This module gives form spam protection for those that don't want to use the aggravating
captchas or a third party external service.

It basically won't allow the submit of a protected form if the user has
disabled cookies, JavaScript, or exceeds a preset time limit on the page.
In each case error warnings are given in case the user is a real person and not a bot.

No database tables are created. The settings for the module are stored in the variable table.
Only 3 settings are required and they are configured via an Admin UI.

INSTALATION NOTE
================

This module was intended to be installed at /sites/all/modules/captcha_free but will work in
a sub-directory such as /sites/all/modules/custom/captcha_free.

UPDATE
=======

After updating the module go to /admin/config/content/captcha-free. Double check your settings 
and then Save them even if you changed nothing. That's to update the array in the variables table
that contains the forms you wish to protect.
