/*
 * Implementation of hook_contentanalysis_data()
 * Gets the data from the custom fields to attach to the AJAX post data.
 */ 
  var alchemy_contentanalysis_contentanalysis_data = function() {		
    var data = new Array();
    var types = new Array();
    var i = 0;
    jQuery('#alchemy_contentanalysis_types .form-checkbox:checked').each ( function () {  
      types[i] = jQuery(this).attr('value');    
      i++;
    });
    data['types'] = types.join(',');
    data['usecache'] = (jQuery('#edit-alchemy-alchemy-usecache').is(':checked')) ? data['usecache'] = 1 : data['usecache'] = 0;
    return data;
  }
