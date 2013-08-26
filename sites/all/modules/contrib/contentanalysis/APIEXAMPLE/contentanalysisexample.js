// $Id: contentanalysisexample.js,v 1.5 2010/05/08 16:12:13 tomdude48 Exp $
(function ($) {
/*
 * Implementation of hook_contentanalysis_data()
 * Gets the data from the custom fields to attach to the AJAX post data.
 */ 
var contentanalysisexample_contentanalysis_data = function() {		
  data = new Array();	
  data['name'] = document.getElementById('edit-contentanalysisexample-name').value;	
  return data;
}
})(jQuery);
