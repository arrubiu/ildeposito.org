(function ($) {

  Drupal.Imagecrop = Drupal.Imagecrop || {};
  Drupal.Imagecrop.dialogContainer = null;
  
  /**
   * Implement Drupal behavior for autoattach
   */
  Drupal.behaviors.imagecropDialog = {
    attach: function(context) {
      // Add dialog listener on imagecrop links.
      $(context).find('a.imagecrop-button').once('imagecrop').bind('click', Drupal.Imagecrop.openDialog);
    }
  }
  
  /**
   * Click listener: Open the dialog for clicked link.
   */
  Drupal.Imagecrop.openDialog = function(e) {
    
    e.preventDefault();
    var page = $(this).attr("href");
    var pagetitle = $(this).attr("title");
    if (Drupal.Imagecrop.dialogContainer == null) {
      Drupal.Imagecrop.dialogContainer = $('<div id="imagecrop-modal-container"></div>');      
    }
    
    var popup_height = $.isArray(Drupal.settings.imagecrop.popupHeight) ? Drupal.settings.imagecrop.popupHeight[0] : Drupal.settings.imagecrop.popupHeight;
    var popup_width = $.isArray(Drupal.settings.imagecrop.popupWidth) ? Drupal.settings.imagecrop.popupWidth[0] : Drupal.settings.imagecrop.popupWidth;
    
    Drupal.Imagecrop.dialogContainer
      .html('<iframe style="border: 0px; " src="' + page + '" width="100%" height="100%"></iframe>')
      .dialog({
        autoOpen: true,
        closeOnEscape : false,
        dialogClass : 'imagecrop-dialog',
        modal: true,
        height: popup_height,
        width: popup_width,
        title: pagetitle
      });
    
  }
  
})(jQuery);