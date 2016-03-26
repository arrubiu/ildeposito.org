/**
 * @file
 *   Main JavaScript file for Dismiss module
 */

(function ($) {

  Drupal.behaviors.dismiss = {
    attach: function (context, settings) {

      // Prepend the Dismiss button to each message box.
      $('.messages').each(function () {
        var flag = $(this).children().hasClass('dismiss');

        if (!flag) {
          $(this).prepend('<button class="dismiss"><span class="element-invisible">' + Drupal.t('Close this message.') + '</span></button>');
        }
      });

      // When the Dismiss button is clicked hide this set of messages.
      $('.dismiss').click(function (event) {
        $(this).parent().hide('fast');
        // In case this message is inside a form, prevent form submission.
        event.preventDefault();
      });

      // Fadeout out status messages when positive value defined.
      if (Drupal.settings.dismiss.fadeout > 0) {
        setTimeout(function () { $('.messages.status').fadeOut(); }, Drupal.settings.dismiss.fadeout);
      }

    }
  }

})(jQuery);
