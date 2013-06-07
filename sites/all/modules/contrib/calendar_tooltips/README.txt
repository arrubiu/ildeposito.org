SUMMARY

The purpose of the Calendar Tooltips module is displaying
a tooltip / popup / balloon when you hover over a day on
a calendar block. This tooltip would contain a list of events occurring
on that day.

Normally you would need to override theme functions and write custom PHP code
to accomplish this task. I have written a guide for that on my site:

   http://linuxpc.info/node/83

This module however saves you the trouble.

It started its life in this thread:

   http://drupal.org/node/462736 ("Calendar popup for calendar block")

REQUIREMENTS

This module requires the Calendar, Date, CCK, and Views modules.
It also depends on the Beautytips module for actually drawing the tooltip.
You can find that module on:

   http://drupal.org/project/beautytips

The Calendar Tooltip module is merely an interface between the Calendar
and the Beautytips modules.

CONFIGURATION

The configuration steps below are optional.

You can change which event fields are displayed in the fields section
of the block view settings of the calendar view. Go to the calendar view,
choose the "Block view" display, and check out the "Fields" section.

On the configuration page of this module you can specify when
the tooltip closes. By default it closes when the mouse cursor
moves away from the date. However, you may also choose for a click-to-close
strategy, or use a timer.

The appearance of the tooltip may be changed on the configuration page
of Beautytips.

CONTACT

If you have any questions or remarks, or if you would like to report a bug,
please visit our project page at

   http://drupal.org/project/calendar_tooltips

There you will also find a list of known issues and workarounds.

I hope this module is useful for you.

Cheers,
Ronald Baljeu (rjb@xs4all.nl)
