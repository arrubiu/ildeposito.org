Bufferapp is a module that communicates with BufferApp service (http://bufferapp.com).

Class connection is this: http://www.little-apps.org/blog/2012/09/automatically-post-updates-buffer-api-php/

Now you can automatically post Buffer updates when new nodes are created or using Rules.
Note that updates are sent only when a new published node is created,
not after publish an existing node (for now).
You can also add a scheduled date and time for each node.

## Installation & connection
- download and install
- go to bufferapp.com developer page and create an app (Callback URL field is not used, so fill it as you want)
- go to admin/config/services/buffer and set access token and enable some profiles

## Configuration
Go to admin/structure/types/content-type and set options from Buffer section.
You can add text, title and description for links, etc.
If you use Rules, you will be available a new action "Send Buffer update".

## Use by code
If you want to send to Buffer some content you can use this function:

bufferapp_data($send = TRUE, $node = NULL, $text, $media = array(), $now = FALSE, $scheduled_at = FALSE)

Arguments:
 $send: if TRUE send update, if FALSE return a formatted $data array
 $node: the object origins of data (useful when using HOOK_buffer_data_alter
 $text: text to publish (html tags will be automatically stripped)
 $now: if TRUE tells Buffer to publish immediatelly the update
 $scheduled_at: if set scheduled date time and time post (must be timestamp value)
 $media: an array that contains info about 'media'.
    For images, $media must have two options:
       $media = array(
         'picture' => 'url-to-image',
         'thumbnail' => 'url-to-thumb',
       );

    For links, $media must have "link" option and other options not mandatory:
       $media = array(
         'link' => 'link-url',
         'title' => 'title of link',
         'description' => 'description of link',
       );

## API
This module expose a hook to alter data before sending them to Buffer:
HOOK_bufferapp_data_alter.

## Info
Modules developed by Sergio Durzu - www.arrubiu.org
