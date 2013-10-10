ZURB Interchange
================

Interchange uses media queries to load the images that are appropriate for a user's browsers, making responsive images a snap.

Official documentation: http://foundation.zurb.com/docs/components/interchange.html
More info: http://zurb.com/article/1211/say-goodbye-to-painful-image-loads-on-sma

Configuration
=============

ZURB Interchange adds settings to Image field types in the Field UI display settings under Manage Display.

For images you want to enable this for, simply check off 'Enabled' next to each image style you want to use with Interchange, and set the order of the styles for this field.
The ordering is important, because the smallest sized image should be loaded first, in order of smallest to largest. Interchange will determine what image is referenced in
'src' based on the display resolution / device width being used, and swap accordingly for responsive design.

Development sponsored by Inclind, Inc.
Website: http://www.inclind.com