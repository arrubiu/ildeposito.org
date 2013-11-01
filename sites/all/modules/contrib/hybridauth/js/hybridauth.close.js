(function ($) {

  Drupal.behaviors.hybridauth_close = {};
  Drupal.behaviors.hybridauth_close.attach = function(context, settings) {
    var win = window;
    if (window.opener && window.opener.location.hostname === window.location.hostname) {
      win = window.opener;
    }
    else if (window.parent) {
      win = window.parent;
    }
    if (Drupal.settings.hybridauth.redirect) {
      win.location.href = Drupal.settings.hybridauth.destination;
    }
    else {
      win.location.href = Drupal.settings.hybridauth.destination_error;
    }
    // Close the popup window.
    if (window.opener) {
      window.self.close();
    }
  };

})(jQuery);
