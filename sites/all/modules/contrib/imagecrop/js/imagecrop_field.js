/**
 * @file
 * Hook on the bind events from media field buttons.
 *
 */

(function ($) {

	Drupal.Imagecrop = {}
	
/**
 * Loads media browsers and callbacks, specifically for media as a field.
 * This is overridden, because there is no js event available to hook in.
 */
Drupal.behaviors.imagecropMediaElement = {
    
  attach: function (context, settings) {  
  	$('.imagecrop-media', context).find('.fid').bind('change', Drupal.Imagecrop.mediaChangeListener);
  }
  
}

/**
 * Listener on a media field.
 */	
Drupal.Imagecrop.mediaChangeListener = function(e) {
	
	var $this = $(this);
	var $mediaWrapper = $this.parent();
	var $imagecropButton = $('.imagecrop-button', $mediaWrapper);
	
	if ($this.val() != 0) {
	  
	  var $imagecropUrl = $('.imagecrop-url', $mediaWrapper);
		$imagecropButton.css({display : 'inline-block'});

		// Set the new url
    $imagecropButton.attr('href', $imagecropUrl.val().replace('/fid/', '/' + $this.val() + '/'));
    
	}
	else {
		$imagecropButton.hide();
	}
		
}

/**
 * Open the imagecrop popup to the given link
 */
Drupal.Imagecrop.openPopup = function(url) {
  window.open(url, 'imagecrop', 'menubar=0,scrollbars=1,resizable=1,width=' + Drupal.settings.imagecrop.popupWidth + ',height=' + Drupal.settings.imagecrop.popupWidth + "'");  
}

})(jQuery);