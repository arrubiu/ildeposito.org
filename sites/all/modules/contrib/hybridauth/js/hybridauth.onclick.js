(function ($) {

  Drupal.behaviors.hybridauth_onclick = {};
  Drupal.behaviors.hybridauth_onclick.attach = function(context, settings) {
    $('.hybridauth-onclick-current', context).bind('click', function() {
      $(this).parents('.hybridauth-widget').after('<div>' + Drupal.t('Contacting') + ' ' + this.title + '...</div>');
    });
    $('.hybridauth-onclick-popup', context).bind('click', function() {
      var width = $(this).attr('data-hybridauth-width'), height = $(this).attr('data-hybridauth-height');
      var popup_window = window.open(
        this.href,
        'hybridauth',
        'location=no,menubar=no,resizable=yes,scrollbars=yes,status=no,titlebar=yes,toolbar=no,channelmode=yes,fullscreen=yes,width=' + width + ',height=' + height
      );
      popup_window.focus();
      return false;
    });

    // Last used provider feature.
    var last_provider = $.cookie('hybridauth_last_provider');
    if (last_provider != null) {
      $('[data-hybridauth-provider="' + last_provider + '"]').addClass('hybridauth-last-provider');
    }
    $('.hybridauth-widget-provider', context).bind('click', function() {
      $.cookie('hybridauth_last_provider', $(this).attr('data-hybridauth-provider'), {expires: 30, path: '/'});
    });
  };

})(jQuery);
