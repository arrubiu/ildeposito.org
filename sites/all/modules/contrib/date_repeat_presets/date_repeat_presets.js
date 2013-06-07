// $Id$
(function ($) {
  Drupal.behaviors.date_repeat_presets = {
    attach: function(context) {
      $('.date-repeat-presets-custom').each(function() {
        var fieldsetId = $(this).attr('id');

        $('#'+fieldsetId+' .drp-presets:not(drp-processed)')
        .addClass('drp-processed')
        // alter legend text of fieldset
        .filter(':has(option[value=custom],[value=custom])')
        .parents('fieldset:first').find('.fieldset-legend:first').text(Drupal.t('Custom repeat options'))
        .end().end().end()
        // initial custom form hide if custom is not set
        .filter(':has(option[value!=custom]:selected,[value!=custom]:checked)')
        .parents('fieldset:first').hide().addClass('collapsed').find('.fieldset-legend:first').text(Drupal.t('Custom repeat options')).end().end().end()
        // move preset selection outside the custom form
        .parents('.rrule-presets:first').remove().prependTo('#'+fieldsetId)

        // add change event handler to show/hide custom form
        .find(':input')
        .change(function() {
          if(this.value == 'custom') {
            // fieldset show
            $('#'+fieldsetId+' > fieldset').show();
            // trigger un-collapse
            $('#'+fieldsetId+' > fieldset.collapsed').find('.fieldset-legend:first > a').click();
          } else {
            // trigger collapse - queue the fieldset hide so the collapse animation isn't interrupted
            $('#'+fieldsetId+' > fieldset:not(.collapsed)').find('.fieldset-legend:first > a').click().end()
            .find('> div:not(.action)').animate({opacity: 1}, 1, function() {
              $('#'+fieldsetId+' > fieldset').hide();
            });
          }
        });
      });
    }
  }
})(jQuery);

