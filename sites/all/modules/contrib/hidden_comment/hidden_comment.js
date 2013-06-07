(function ($) {
Drupal.behaviors.hidden_comment = {
  attach: function (context, settings) {
    $('#edit-default-reasons').change(function() {
      $('#edit-reason').val($('#edit-default-reasons :selected').text());
    });
  }
}
})(jQuery);
