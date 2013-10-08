var _l10iq = _l10iq || [];

function l10iMailChimpTracker() {  
  this.init = function init() {
	var e;
    _l10iq.push(['_log', "l10iMailChimpTracker.init()"]);
    var query = window.location.search;
    if (!query) {
      return;
    }
    // remove opening ?
    query = query.slice(1);
    var pairs = query.split('&');
    var params = {};
    for (var i = 0; i < pairs.length; i++) {
      e = pairs[i].split('=');
      params[e[0]] = e[1]; 
    }
    if ((params['utm_term'] == undefined) || (params['utm_medium'] == undefined) || (params['utm_medium'] != 'email')) {
      return;
    }
    e = params['utm_term'].split('-');
    if (!e.length == 3) {
      return;
    }
    action = [
      '_setVar',
      'ext',
      'mailchimp',
      "id",
      e[2]               
    ];
    _l10iq.push(action);   
    _l10iq.push(['_saveVar', 'ext', 'mailchimp']);    
  }
}

var l10iMailChimp = new l10iMailChimpTracker();
jQuery(document).ready(function() {
	//_l10iq.push(['_onReady', l10iMailChimp.init, l10iMailChimp]);
});

