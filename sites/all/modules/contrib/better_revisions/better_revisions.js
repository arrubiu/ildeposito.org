(function ($) {

Drupal.behaviors.betterRevisionsFieldset = {
  attach: function (context) {
    $('fieldset.node-form-revision-information', context).drupalSetSummary(function (context) {
      var revisionCheckbox = $('.form-item-revision input', context);

      // Return 'New revision' if the 'Create new revision' checkbox is checked,
      // or if the checkbox doesn't exist, but the revision select list does. For users
      // without the "Administer content" permission the checkbox won't appear,
      // but the revision log will if the content type is set to auto-revision.
      // Thank you node module for the answer to this.
      if (revisionCheckbox.is(':checked') || (!revisionCheckbox.length && $('.form-item-log #edit-log', context).length)) {
        return Drupal.t('New revision');
      }

      return Drupal.t('No revision');
    });
  }};
})(jQuery);
