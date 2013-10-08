var _l10iq = _l10iq || [];

function l10iHubSpotTracker() {  
  this.init = function init() {
    _l10iq.push(['_log', "l10iHubSpotTracker.init()"]);
    
    _l10iq.push(['_registerCallback', 'saveCTAClickAlter', this.saveCTAClickAlterCallback, this]);
    _l10iq.push(['_registerCallback', 'saveFormSubmitAlter', this.saveFormSubmitAlterCallback, this]);
    _l10iq.push(['_registerCallback', 'saveCommentSubmitAlter', this.saveCommentSubmitAlterCallback, this]);
    
    // add vtk to hidden field on HubSpot forms
    jQuery(".hs-form input[name='l10i_vtk']").val(_l10iq.vtk);
    
    var rf = _l10iq.push(['_getCookie', 'hsrecentfields']);
    if (rf) {
      rf = jQuery.parseJSON(rf);
      rf['hs_context'] = jQuery.parseJSON(rf['hs_context']);
      var count = 0;
      for (var i = 0; i < rf.length; i++) {
        if (i != 'hs_context') {
           _l10iq.push(['_setVar', 'visitor', 'hubspot', i, rf[i]]);
           count ++;
        }
      }
      if (count > 0) {
    	  _l10iq.push(['_saveVar', 'visitor', 'hubspot']);
      }
      
      _l10iq.push(['_setVar', 'ext', 'hubspot', 'hs_context', rf['hs_context']]);      
      _l10iq.push(['_saveVar', 'ext', 'hubspot']);
    }
  };
  
  this.saveCTAClickAlterCallback = function saveCTAClickAlterCallback(json_params, json_data, $obj, event) {
    json_data['value']['hubspotutk'] = _l10iq.getCookie('hubspotutk');
    var href = $obj.attr('cta_dest_link');  // used for HubSpot CTAs
    if (typeof href != 'undefined') {
      json_data['value']['href'] = href;
    }
  };
  
  this.saveFormSubmitAlterCallback = function saveFormSubmitCallback(json_params, json_data, $obj, event) {
	  json_data['value']['hubspotutk'] = _l10iq.getCookie('hubspotutk');
	  // check if a HubSpot form
	  if (!$obj.hasClass('hs-form')) {
		return;
	  }
	  // add vtk to hidden field on HubSpot forms
	  jQuery(".hs-form input[name='l10i_vtk']").val(_l10iq.vtk);
	    
	  json_data['value']['type'] = 'hubspot';
	  var id = $obj.attr('id');
	  json_data['value']['fid'] = id.replace('hsForm_', '');
  };
  
  this.saveCommentSubmitAlterCallback = function saveCommentSubmitCallback(json_params, json_data, $obj, event) {
	  json_data['value']['hubspotutk'] = _l10iq.getCookie('hubspotutk');
  };
}

var l10iHubSpot = new l10iHubSpotTracker();
jQuery(document).ready(function() {
	_l10iq.push(['_onReady', l10iHubSpot.init, l10iHubSpot]);
});


