(function($) {

Drupal.behaviors.rabbitHole = {
  attach: function (context, settings) {

    // Only show the redirect options if the user has selected redirect as the
    // behavior.
    var $redirectFieldset = $('fieldset.rabbit-hole-redirect-options');
    if ($('#edit-rabbit-hole input.rabbit-hole-action-setting:checked').val() != Drupal.settings.rabbitHole.redirectValue) {
      $redirectFieldset.hide();
    }
    $('#edit-rabbit-hole input.rabbit-hole-action-setting').change(function() {
      if ($(this).val() == Drupal.settings.rabbitHole.redirectValue) {
        $redirectFieldset.show();
      }
      else {
        $redirectFieldset.hide();
      }
    });
  
  }
}

})(jQuery);