var _l10iq = _l10iq || [];

function l10iLinkedInTracker() {  
  this.init = function init() {
	_l10iq.push(['_log', "l10iLinkedInTracker.init()"]);
    if (('linkedin' in _l10iq.settings) && ('apikey' in _l10iq.settings.linkedin)) {
        var script = document.createElement('script');
        script.src = 'http://platform.linkedin.com/in.js';
        script.text =  'api_key: ' +  _l10iq.settings['linkedin']['apikey'] + "\n";
        script.text += 'onLoad: l10iLinkedIn.onLinkedInLoad' + "\n";
        script.text += 'authorize: true' + "\n";
        //script.appendChild(document.createTextNode('api_key: ' +  _l10iq.settings['linkedin']['apikey']));
        document.getElementsByTagName('head')[0].appendChild(script);       
    }
  }
  
  this.onLinkedInLoad = function onLinkedInLoad() {
	IN.Event.on(IN, "auth", l10iLinkedIn.onLinkedInAuth);  
  }
  
  this.onLinkedInAuth = function() {
	var fields = [
	  'id',
	  'firstName',
	  'lastName',
	  'headline'
	];
	fields.push('pictureUrl');
	fields.push('industry');
	fields.push('numConnections');
	fields.push('specialties');
	fields.push('summary');
	fields.push('publicProfileUrl');
	fields.push('emailAddress');
	//fields.push('positions');
	IN.API.Profile("me").fields(fields).result(l10iLinkedIn.initProfile);
  }
  
  this.initProfile = function initProfile(profiles) {
	var members = profiles.values;
	var member = members[0];
	_l10iq.push(['_log', member]);
	var count = 0;
	for (var k in member) {
	  if (k.substring(0,1) == '_') {
	    continue;
	  }
      action = [
        '_setVar',
        'visitor',
        'linkedin',
        k,
        member[k]            
      ];
      _l10iq.push(action);
      count++;
    }
	var last_set = _l10iq.push(['_getFlag', 'session', 'linkedin']);
    //if ((count > 0) && ((last_set == undefined) || ((_l10iq.getTime() - last_set) > (60*60*24)))) { 
    _l10iq.push(['_saveVars', 'visitor', 'linkedin']);
    //_l10iq.push(['_setFlag', 'session', 'addthis', _l10iq.getTime(), true]);
  //}
    
  }
}

var l10iLinkedIn = new l10iLinkedInTracker();
jQuery(document).ready(function() {
	_l10iq.push(['_onReady', l10iLinkedIn.init, l10iLinkedIn]);
});

