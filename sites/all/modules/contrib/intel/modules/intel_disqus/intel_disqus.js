(function ($) {

/**
 * Provide the summary information for the block settings vertical tabs.
 */
Drupal.behaviors.l10insight_disqus = {
  attach: function (context) {
  _l10iq.push(['_registerCallback', 'saveCommentSubmitPostSubmit', this.saveCommentSubmitPostCallbackSubmit, this]);
  },

  saveCommentSubmitPostCallbackSubmit: function (data) {
    console.log('saveCommentSubmitPostCallbackSubmit');
    console.log(data);
    if (data.type != 'disqus') {
      return;
    }
    var data = {
    vtk: _l10iq.vtk,
    commentid: data.commentid
    };
      var url = Drupal.settings.intel.script_domain + "intel_disqus/comment_submit_js";
      jQuery.ajax({
      dataType: 'json',
      url: url, 
      data: data,
      type: 'GET'
      });
  }
};

})(jQuery);