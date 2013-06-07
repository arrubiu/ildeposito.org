/**
 * Implementation of Drupal behavior.
 */
//Drupal.behaviors.openlayers_plus_behavior_themeregion = function(context) {
//  Drupal.OpenLayersPlusthemeregion.attach(context);
//};

(function($) {
/**
* Implementation of Drupal behavior.
*/
//Drupal.behaviors.openlayers_plus_behavior_themeregion = function(context) {
  Drupal.openlayers.addBehavior('openlayers_plus_behavior_themeregion', function (data, options) {
    Drupal.OpenLayersPlusthemeregion.attach(data, options);
  });

/**
* themeregion is **NOT** an OpenLayers control.
*/
Drupal.OpenLayersPlusthemeregion = {};
Drupal.OpenLayersPlusthemeregion.layerStates = [];

/**
* Initializes the themeregion and attaches to DOM elements.
*/
Drupal.OpenLayersPlusthemeregion.attach = function(data, options) {
/**
 * Initializes the themeregion and attaches to DOM elements.
 */

  if (data && data.map.behaviors.openlayers_plus_behavior_themeregion) {
	
	for (regionkey in options.regions) {
		if (regionkey != 0) {
			if (options.regions[regionkey]) {
		      region = options.regions[regionkey].replace('_', '-').toLowerCase();
              var cssid = options.prefix + region + options.suffix;
		      if ($(cssid).length > 0) {
		        $(data.openlayers.viewPortDiv).append($(cssid));
		        $(cssid).addClass('olControlNoSelect');
		        $(cssid).addClass('openlayers_plus-themeregion');
		        $(cssid).css('position', 'absolute'); // we need to do this because some themes override this with the id of the region
		      }
		    }
		}
	}


    // Don't propagate click events to the map
    // this doesn't catch events that are below the layer list
    $('div.block-openlayers_plus-themeregion *').mousedown(function(evt) {
      OpenLayers.Event.stop(evt);
    });

  }
};

})(jQuery);