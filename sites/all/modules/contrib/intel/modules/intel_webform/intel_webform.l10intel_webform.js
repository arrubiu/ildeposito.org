var _l10iq = _l10iq || [];

function l10iWebformTracker() {  
  this.init = function init() {
    _l10iq.push(['_log', "l10iWebformTracker.init()"]);
    _l10iq.registerCallback('saveFormSubmitAlter', this.saveFormSubmitAlterCallback, this);
  }
  
  this.saveFormSubmitAlterCallback = function saveFormSubmitCallback(json_params, json_data, $obj, event) {
    // check if a webform
    var id = $obj.attr('id');
    
    var e = id.split("-");
    if ((e[0] == 'webform') && (e[1] == 'client') && (e[2] == 'form')) {
      json_data['value']['type'] = 'webform';
      json_data['value']['fid'] = e[3];
      json_data['value']['label'] = 'node/' + e[3];      
    }    
  }
}

var l10iWebform = new l10iWebformTracker();
jQuery(document).ready(function() {
  _l10iq.push(['_onReady', l10iWebform.init, l10iWebform]);
});


