var _l10iq = _l10iq || [];
var _l10iq = _l10iq || [];

function l10iAddthisTracker() {
  this.waits = 0;
  
  this.init = function init() {
	var waits, i;
	_l10iq.push(['_log', "l10iAddthisTracker.init()"]);
    if (typeof addthis == 'undefined') {
      if (this.waits < 5) {
    	this.waits++;
    	var delay = (this.waits >= 2) ? 2500 : 1000;
        with (this) { setTimeout( function() { init(); }, delay);}
      }
      return;
    }
    else {
      addthis.addEventListener('addthis.menu.share', this.eventHandler);
      addthis.addEventListener('addthis.user.clickback', this.eventHandler);
      addthis.user.ready(function (data){
        var services = addthis.user.services().toMap();
        var action = [];
        var count = 0;
        for (i in services) {  
          action = [
            '_setVar',
            'visitor',
            'addthis',
            "services." + services[i]['name'],
            Number(services[i]['score'])            
          ];
          _l10iq.push(action);
          count++;
        }
        var geo = addthis.user.location();
        if (geo['country'] !== 'undefined') {
          var e = ['country', 'dma', 'lat', 'lon', 'msa', 'region', 'zip'];  
          for(i = 0; i < e.length; i++) {
        	if (geo[e[i]] == undefined) {
        	  continue;
        	}
            action = [
              '_setVar',
              'visitor',
              'addthis',
              "geo." + e[i],
              geo[e[i]]                
            ];
            _l10iq.push(action);  
            count++;
          }
        }        
        var last_set = _l10iq.push(['_getFlag', 'session', 'addthis']);
        var timestamp = _l10iq.push(['_getTime']);
        if ((count > 0) && ((last_set == undefined) || ((timestamp - last_set) > (60*60*24)))) { 
          _l10iq.push(['_saveVar', 'visitor', 'addthis']);
          _l10iq.push(['_setFlag', 'session', 'addthis', timestamp, true]);
        }
      });
    }
  };
  
  this.eventHandler = function(evt) { 
    var share_event = {
      'category': "Social share!",
      'action': "[unknown]",
      'label': "!system_alias",
      'value': (typeof _l10iq.settings.scorings.social_share !== 'undefined') ? Number(_l10iq.settings.scorings.social_share) : 0,
      'noninteraction': false      
    };
    var clickback_event = {
      'category': "Social share clickback!",
      'action': "[unknown]",
      'label': "!system_alias",
      'value': (typeof _l10iq.settings.scorings.social_share_clickback !== 'undefined') ? Number(_l10iq.settings.scorings.social_share_clickback) : 0,
      'noninteraction': true      
    };
    var ignore = {
      'more': 1
    };
    if (evt.type == "addthis.menu.share") {
      if (ignore[evt.data.service]) {
        return;
      }
      share_event.action = (typeof addthis.util.getServiceName(evt.data.service) != 'undefined') ? addthis.util.getServiceName(evt.data.service) : evt.data.service;
      _l10iq.push(['_trackIntelEvent', jQuery(this), share_event, '']);
    }
    if (evt.type == "addthis.user.clickback") {
      clickback_event.action = (typeof addthis.util.getServiceName(evt.data.service) != 'undefined') ? addthis.util.getServiceName(evt.data.service) : evt.data.service;
      _l10iq.push(['_trackIntelEvent', jQuery(this), clickback_event, '']);
    }
  };
}

var l10iAddthis = new l10iAddthisTracker();
jQuery(document).ready(function() {
	_l10iq.push(['_onReady', l10iAddthis.init, l10iAddthis]);
});
