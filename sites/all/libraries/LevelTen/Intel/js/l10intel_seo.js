var _l10iq = _l10iq || [];

function l10iSeoTracker() {  
  this.init = function init() {
	var e;
    _l10iq.push(['_log', "l10iSeoTracker.init()"]);
    if (document.referrer.match(/google\.com/gi) && document.referrer.match(/cd/gi)) {
	  var myString = document.referrer;
	  var r        = myString.match(/cd=(.*?)&/);
	  var rank     = parseInt(r[1]);
	  var kw       = myString.match(/q=(.*?)&/);
	  var keyword  = "(not provided)";
	  
	  if (kw[1].length > 0) {
	    keyword  = decodeURI(kw[1]);
	  }

      var search_event = {
	    'category': "Search keyword click",
	    'action': 'Google: ' + keyword,
	    'label': "!system_alias_or_location",
	    'value': rank,
	    'noninteraction': true      
	  };
      _l10iq.push(['_trackIntelEvent', jQuery(document), search_event, '']);
	}
  }
}

var l10iSeo = new l10iSeoTracker();
jQuery(document).ready(function() {
	_l10iq.push(['_onReady', l10iSeo.init, l10iSeo]);
});

