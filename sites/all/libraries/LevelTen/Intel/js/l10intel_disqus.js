var _l10iq = _l10iq || [];
var _l10iq = _l10iq || [];

function l10iDisqusTracker() {
  this.apiUrl = 'https://disqus.com/api/3.0/';
  
  this.init = function init() {
    _l10iq.push(['_log', "l10iDisqusTracker.init()"]);
  };
  
  this.trackComment = function trackComment(comment) {
    var action = "Disqus", ga_event, json_data, json_params, timestamp;
    if (comment.text.length > 40) {
      action = action + ": " + comment.text.substring(0, 35) + '...';
    }
    else {
      action = action + ": " + comment.text;
    }
    ga_event = {
	  'category': "Comment!",
	  'action': action,
      'label': window.location.pathname.substring(1) + "#comment-" + comment.id,
      'value': (typeof _l10iq.settings.scorings.comment !== 'undefined') ? Number(_l10iq.settings.scorings.comment) : 0,
  	  'noninteraction': false			
    };
    _l10iq.push(['_trackIntelEvent', jQuery(this), ga_event, '']);

    timestamp = _l10iq.push(['_getTime']);
    comment = {
      'id': comment.id,
      'text': comment.text,
      'type': 'disqus',
      'submitted': timestamp,
      'location': _l10iq.location,
      'system_path' : (_l10iq.settings.system_path != undefined) ? _l10iq.settings.system_path : ''      
    };
    
    json_data = {
      'value': comment,
      'valuemeta': {'_updated': timestamp},
      'return': {commentid: comment.id, keys: timestamp, type: 'disqus'}
    };
    json_params = {
      'keys': timestamp,
      'type': 'session',
      'namespace': 'comment_submit'
    }; 
    _l10iq.push(['_triggerCallbacks', 'saveCommentSubmitAlter', [json_params, json_data, {}, {}]]);
    _l10iq.push(['_getJSON', 'var_merge', json_params, json_data, 'l10iDisqus.submitComment']);
  };
  
  this.submitComment = function submitComment(data) {
    _l10iq.push(['_triggerCallbacks', 'saveCommentSubmitPostSubmit', [data['return']]]);
  };
}

var l10iDisqus = new l10iDisqusTracker();
jQuery(document).ready(function() {
	_l10iq.push(['_onReady', l10iDisqus.init, l10iDisqus]);
});
