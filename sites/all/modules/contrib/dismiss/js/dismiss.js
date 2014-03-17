/**
 * @file
 *   Main JavaScript file for Dismiss module
 */

(function ($) {

  Drupal.behaviors.dismiss = {
    attach: function (context) {

      // Prepend the Dismiss button to each message box.
      $('.messages').each(function () {
        var flag = $(this).children().hasClass('dismiss');

        if (!flag) {
          $(this).prepend('<button class="dismiss"><span class="element-invisible">' + Drupal.t('Close this message.') + '</span></button>');
        }
      });

      // When the Dismiss button is clicked hide this set of messages.
      $('.dismiss').click(function () {
        $(this).parent().hide('fast');
      });

    }
  }

})(jQuery);
