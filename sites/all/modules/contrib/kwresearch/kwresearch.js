
var kwresearch = kwresearch || {};

(function ($, $$) {
	$.extend($$, {
		kwresearch_keyword_data: {},
		
		init: function() {
			$$.kwresearch_init();
		},
		
		kwresearch_init: function () {
		  var report_vocabs = Drupal.settings.kwresearch.tax_report_vocabs;
		  for(var vid in report_vocabs) {
			if (report_vocabs[vid] > 0 && ($('.kwresearch-refresh-link-' + vid).length == 0)) {
		      h = '<a href="#" class="kwresearch.kwresearch-refresh-link-' + vid + '" onclick="kwresearch.kwresearch_refresh_tax_report(\'' + vid + '\'); return false;" title="refresh report">';
		      h += '<img src="' + Drupal.settings.kwresearch.path_to_module + '/icons/refresh.png" alt="refresh report" />';
		      h += '</a>';
		      $('.kwresearch-tax-report-' + vid + ' label').append(h);
			}
		  } 
		  $$.kwresearch_process_keywords();
		},
		
		kwresearch_get_keyword_list: function(type) {
		  var value = '';
		  var keywords = new Array();
		  
		  if (type == 'vocab') {
		    if (Drupal.settings.kwresearch.keyword_tag_vocabulary) {    
		      if ($('#edit-taxonomy-tags-' + Drupal.settings.kwresearch.keyword_tag_vocabulary).val() != null) {
		        value = $('#edit-taxonomy-tags-' + Drupal.settings.kwresearch.keyword_tag_vocabulary).val();
		      } 
		    }    
		  }
		  else if (type == 'mlt') {
		    if ($('#edit-morelikethis-terms').val() != null) {
		      value = $('#edit-morelikethis-terms').val();  
		    }
		  }
		  else if (type == 'meta_keywords') {
		    if ($('#edit-nodewords-keywords-value').val() != null) {
		      value = $('#edit-nodewords-keywords-value').val();
		    }
		  }
		  
		  keywords = value.split(',');  
		  for(var i in keywords) {
		    keywords[i] = jQuery.trim(keywords[i].toLowerCase());
		  }
		  return keywords;
		},
		
		// Implementation of hook_contentanalysis_analysis_success
		kwresearch_contentanalysis_analysis_success: function(aid, data) {	
			$$.kwresearch_init();	
		},

		kwresearch_in_array: function(needle, haystack) {
			for(var i = 0; i < haystack.length; i++) {
				if (haystack[i] == needle) {
					return true;
				}
			}
			return false;
		},

		kwresearch_process_keywords: function() {
		//alert('hi');
		  $('.kwresearch_keyword:not(.processed)').each( function(index) {
		    keyword = $(this).text().toLowerCase();
		    str = $$.kwresearch_get_buttons(keyword);
		    
		    $(this).addClass('processed');
		    $(this).append(str);
		    $('.kwresearch_actions').hide();
		    $(this).mouseover( function() {
		      $(this).addClass('active');
		      var tools = $(this).find('.kwresearch_actions');
		      var pos = $(this).position(); 
		      var left = pos.left; 
		      var top = pos.top;
		      var topOffset = $(this).height();
		      var xTip = (left-0)+"px";  
		      //var yTip = (0-topOffset+top)+"px";  
		      var yTip = (0+top)+"px";  
		      tools.css({'top' : yTip, 'left' : xTip});  
		      tools.show();
		      
		    });
		    $(this).mouseout( function() {
		      var tools = $(this).find('.kwresearch_actions');
		      $(this).removeClass('active');
		      tools.hide();
		    });
		  });
		},

		kwresearch_get_buttons: function(keyword) {
		    str = '<div class="kwresearch_actions">';
		    title = Drupal.t('Keyword report');
		    str += '<a href="#" onclick="kwresearch.kwresearch_launch_report(\'' + keyword + '\'); return false;" title="' + title + '" class="kwresearch-tool-button">';
		    str += '<img src="' + Drupal.settings.kwresearch.module_path + '/icons/report.png" title="' + title + '" />';
		    str += '</a>';

		    str += $$.kwresearch_get_toggle_button(keyword, 'sitekw');
		    str += $$.kwresearch_get_toggle_button(keyword, 'siteops');
		    str += $$.kwresearch_get_toggle_button(keyword, 'pagekw');
		    str += $$.kwresearch_get_toggle_button(keyword, 'vocab');
		    str += $$.kwresearch_get_toggle_button(keyword, 'mlt');
		    str += $$.kwresearch_get_toggle_button(keyword, 'meta_keywords');

		    str += '</div>';
		    return str;
		},

		kwresearch_get_toggle_button: function(keyword, type) {
		  var str = '';
		  var keyword_list = $$.kwresearch_get_keyword_list(type);
		  if (type == 'sitekw') {  
		    if (Drupal.settings.kwresearch.enable_site_keyword_tool) { // TODO add admin permission logic
		      keywordns = keyword.replace(/ /g,'-');
		      add = 1;
		      img = 'add';
		      title = Drupal.t('Add keyword to targeted site keyword list');
		      var d = Drupal.settings.kwresearch.site_keywords_data;
		      var activei = -1;
		      if ((d[keyword] != null) && (d[keyword]['priority'] >= 0)) {
		        add = 0;
		        img = 'delete'
		        title = Drupal.t('Remove keyword from targeted site keyword list');
		        activei = d[keyword]['priority'];
		      }
		      str += '<div onmouseover="kwresearch.kwresearch_display_tool_site_keyword_menu(this, 1);" onmouseout="kwresearch.kwresearch_display_tool_site_keyword_menu(this, 0);" class="kwresearch-tool-group kwresearch-tool-button kwresearch-tool-button-site-keyword-' + keywordns + '">'
		      str += '<a href="#" onclick="kwresearch.kwresearch_toggle_sitekw_keyword(\'' + keyword + '\', ' + add + ', \'' + keywordns + '\'); return false;" title="' + title + '" >';
		      str += '<img src="' + Drupal.settings.kwresearch.module_path + '/icons/site_keyword_' + img + '.png" title="' + title + '" />';
		      str += '</a>';      

		      str += '<ul class="kwresearch-tool-menu kwresearch-tool-menu-site-priority-' + keyword + '" style="display: none; left: 0px; top: 18px;">';
		      op = Drupal.settings.kwresearch.site_priority_options;
		      for ( var i in op ) {
		        active = '';
		        if (activei == i) {
		          active = 'active';
		        }
		        str += '<li class="' + active + '"><a href="#" onclick="kwresearch.kwresearch_toggle_sitekw_keyword(\'' + keyword + '\', ' + add + ', \'' + keywordns + '\', ' + i + '); return false;">' + op[i] + '</a></li>';
		      }
		      str += '</ul>';  
		      str += '</div>';      
		    }
		  }
		  if (type == 'siteops') {
			var d = Drupal.settings.kwresearch.site_keywords_data;
			if ((Drupal.settings.kwresearch.form != null) && (Drupal.settings.kwresearch.form.substr(0, 5) == 'admin')) {
				var link = Drupal.settings.kwresearch.keyword_edit_path + d[keyword]['kid'];
				if (Drupal.settings.kwresearch.return_destination) {
			  		link += '?destination=' + Drupal.settings.kwresearch.return_destination;
			  	}
			  	var title = Drupal.t('Edit keyword');
			    str += '<a href="' + link + '" onclick="kwresearch.kwresearch_edit_keyword(' + d[keyword]['kid'] + '); return false;" title="' + title + '" class="kwresearch-tool-button">';
			    str += '<img src="' + Drupal.settings.kwresearch.module_path + '/icons/keyword_edit.png" title="' + title + '" />';
			    str += '</a>';   	  
			}
		    if ((Drupal.settings.kwresearch.form != null) && (Drupal.settings.kwresearch.form == 'admin_keyword_list') && !(d[keyword]['page_count'] > 0)) {
		    	var title = Drupal.t('Delete keyword');
			    str += '<a href="#" onclick="kwresearch.kwresearch_delete_keyword(\'' + escape(keyword) + '\', ' + d[keyword]['kid'] + '); return false;" title="' + title + '" class="kwresearch-tool-button">';
			    str += '<img src="' + Drupal.settings.kwresearch.module_path + '/icons/keyword_delete.png" title="' + title + '" />';
			    str += '</a>';   	  
		    }	  
		  }
		  if (type == 'pagekw') {  
		    if (Drupal.settings.kwresearch.enable_page_keyword_tool) { // TODO add admin permission logic
		      add = 1;
		      img = 'add';
		      title = Drupal.t('Add keyword to page keyword list');
		      var d = Drupal.settings.kwresearch.page_keywords_data;
		      var activei = 0;
		      if ((d[keyword] != null) && (d[keyword]['priority'] > 0)) {
		        add = 0;
		        img = 'delete'
		        title = Drupal.t('Remove keyword from page keyword list');
		        activei = d[keyword]['priority'];
		      }
		      /*
		      str += '<a href="#" onclick="kwresearch_toggle_pagekw_keyword(\'' + keyword + '\', ' + add + ', this); return false;" title="' + title + '" class="kwresearch-tool-button">';
		      str += '<img src="' + Drupal.settings.kwresearch.module_path + '/icons/page_keyword_' + img + '.png" title="' + title + '" />';
		      str += '</a>';
		      */      
		      str += '<div onmouseover="kwresearch.kwresearch_display_tool_page_keyword_menu(this, 1);" onmouseout="kwresearch.kwresearch_display_tool_page_keyword_menu(this, 0);" class="kwresearch-tool-group kwresearch-tool-button kwresearch-tool-button-page-keyword-' + keywordns + '">'
		      str += '<a href="#" onclick="kwresearch.kwresearch_toggle_pagekw_keyword(\'' + keyword + '\', ' + add + ', \'' + keywordns + '\'); return false;" title="' + title + '" >';
		      str += '<img src="' + Drupal.settings.kwresearch.module_path + '/icons/page_keyword_' + img + '.png" title="' + title + '" />';
		      str += '</a>';      

		      str += '<ul class="kwresearch-tool-menu kwresearch-tool-menu-site-priority-' + keyword + '" style="display: none; left: 18px; top: 18px;">';
		      op = Drupal.settings.kwresearch.page_priority_options;
		      for ( var i in op ) {
		        active = '';
		        if (activei == i) {
		          active = 'active';
		        }
		        str += '<li class="' + active + '"><a href="#" onclick="kwresearch.kwresearch_toggle_pagekw_keyword(\'' + keyword + '\', ' + add + ', \'' + keywordns + '\', ' + i + '); return false;">' + op[i] + '</a></li>';
		      }
		      str += '</ul>';    
		      str += '</div>';      
		      
		    }
		  }
		  else if (type == 'vocab') {
		    if (Drupal.settings.kwresearch.keyword_tag_vocabulary 
		      && ($('#edit-taxonomy-tags-' + Drupal.settings.kwresearch.keyword_tag_vocabulary).size() > 0)) {
		      add = 1;
		      img = 'add';
		      title = Drupal.t('Add keyword to keyword vocabulary');
		      
		      if ($$.kwresearch_in_array(keyword, keyword_list)) {
		        add = 0;
		        img = 'delete'
		        title = Drupal.t('Remove keyword from keyword vocabulary');
		      }
		      keyword
		      str += '<a href="#" onclick="kwresearch.kwresearch_toggle_vocab_keyword(\'' + keyword + '\', ' + add + ', this); return false;" title="' + title + '" class="kwresearch-tool-button">';
		      str += '<img src="' + Drupal.settings.kwresearch.module_path + '/icons/vocab_' + img + '.png" title="' + title + '" />';
		      str += '</a>';       
		    }
		  }
		  else if (type == 'mlt') {  
		    if ($('#edit-morelikethis-terms').size() > 0) {
		      add = 1;
		      img = 'add';
		      title = Drupal.t('Add keyword to More Like This');
		      if ($$.kwresearch_in_array(keyword, keyword_list)) {
		        add = 0;
		        img = 'delete'
		        title = Drupal.t('Remove keyword from More Like This');
		      }
		      str += '<a href="#" onclick="kwresearch.kwresearch_toggle_mlt_keyword(\'' + keyword + '\', ' + add + ', this); return false;" title="' + title + '" class="kwresearch-tool-button">';
		      str += '<img src="' + Drupal.settings.kwresearch.module_path + '/icons/mlt_' + img + '.png" title="' + title + '" />';
		      str += '</a>';
		    }
		  }
		  else if (type == 'meta_keywords') {  
		    if ($('#edit-nodewords-keywords-value').size() > 0) {
		      add = 1;
		      img = 'add';
		      title = Drupal.t('Add keyword to meta keywords');
		      if ($$.kwresearch_in_array(keyword, keyword_list)) {
		        add = 0;
		        img = 'delete'
		        title = Drupal.t('Remove keyword to meta keywords');
		      }
		      str += '<a href="#" onclick="kwresearch.kwresearch_toggle_meta_keyword(\'' + keyword + '\', ' + add + ', this); return false;" title="' + title + '" class="kwresearch-tool-button">';
		      str += '<img src="' + Drupal.settings.kwresearch.module_path + '/icons/metakeywords_' + img + '.png" title="' + title + '" />';
		      str += '</a>';
		    }
		  }
		  return str
		},

		kwresearch_display_tool_site_keyword_menu: function(theDiv, state) {
		  if (state == 1) {
		    $(theDiv).children('ul').show();
		  }
		  else {
		    $(theDiv).children('ul').hide();
		  }
		},

		kwresearch_display_tool_page_keyword_menu: function(theDiv, state) {
		  if (state == 1) {
		    $(theDiv).children('ul').show();
		  }
		  else {
		    $(theDiv).children('ul').hide();
		  }
		},

		kwresearch_launch_report: function(keyword) {
		  if (Drupal.settings.kwresearch.form.substr(0,5) == 'admin') {
		    window.location = Drupal.settings.kwresearch.analyze_path + keyword;
		    return false;
		  }
		  //alert(keyword);
		  $('#edit-kwresearch-keyword').val(keyword);
		  contentanalysis.contentanalysis_show_analyzer_tab(document.getElementById('contentanalysis-analyzer-tab-kwresearch'));
		  $$.kwresearch_analyze();
		  return false;
		},

		kwresearch_toggle_sitekw_keyword: function(keyword, add, keywordns, priority) {
		  var data = { 
		    'kwresearch_keyword': keyword,
		    'priority': -1,
		    'form': Drupal.settings.kwresearch.form
		  };
		  if (priority != null) {
		    data.priority = priority;
		    $('.kwresearch_actions').hide();
		  }
		  else if (add == 1) {
		    data.priority = 0;  
		  }  

		  $.ajax({
		    type: 'POST',
		    url: Drupal.settings.kwresearch.toggle_site_keyword_callback,
		    data: data,
		    dataType: 'json',
		    success: function(data, textStatus) {
			  var keyword = String(data.data['keyword']).toString();
		      if (Drupal.settings.kwresearch.site_keywords_data[keyword] == null) {
		        Drupal.settings.kwresearch.site_keywords_data[keyword] = {
		          'priority': data.data['priority']
		        }
		      }
		      else {
		        Drupal.settings.kwresearch.site_keywords_data[keyword]['priority'] = data.data['priority'];
		      }
		//alert(Drupal.settings.kwresearch.site_keywords_data[data.data['keyword']]['priority']);
		      $('.kwresearch-tool-button-site-keyword-' + keywordns).replaceWith($$.kwresearch_get_toggle_button(keyword, 'sitekw'));
		      //$(theLink).replaceWith(kwresearch_get_toggle_button(keyword, 'sitekw'));
		      if (Drupal.settings.kwresearch.form == 'admin_keyword_list') {
		    	$('#kid-' + data.data['kid']).hide();
		    	$('#kid-' + data.data['kid'] + ' .site_priority').replaceWith('<td class="site_priority">' + data.data['priority_out'] + "</td>");
		        $('#kid-' + data.data['kid'] + ' .value').replaceWith('<td class="value">' + data.data['value_out'] + "</td>");
		        $('#kid-' + data.data['kid'] + ' .user').replaceWith('<td class="user">' + data.data['user_out'] + "</td>");        
		        $('#kid-' + data.data['kid']).fadeIn(100);
		      }
		      if (Drupal.settings.kwresearch.form == 'admin_keyword_stats') {
		      	$('#kid-' + data.data['kid']).hide();
		      	$('#kid-' + data.data['kid'] + ' .site_priority').replaceWith('<td class="site_priority">' + data.data['priority_out'] + "</td>");
		        $('#kid-' + data.data['kid'] + ' .value').replaceWith('<td class="value">' + data.data['value_out'] + "</td>");
		        $('#kid-' + data.data['kid'] + ' .user').replaceWith('<td class="user">' + data.data['user_out'] + "</td>");
		        $('#kid-' + data.data['kid']).fadeIn(100);
		      }
		      if (Drupal.settings.kwresearch.form == 'node_edit') {
			    	$('#kid-' + data.data['kid']).hide();
			    	$('#kid-' + data.data['kid'] + ' .site_priority').replaceWith('<td class="site_priority">' + data.data['priority_out'] + "</td>");
			        $('#kid-' + data.data['kid'] + ' .value').replaceWith('<td class="value">' + data.data['value_out'] + "</td>");
			        $('#kid-' + data.data['kid'] + ' .user').replaceWith('<td class="user">' + data.data['user_out'] + "</td>");        
			        $('#kid-' + data.data['kid']).fadeIn(100);
			      }
		    },
		    error: function(XMLHttpRequest, textStatus, errorThrown) {

		    }
		  });

		  return false;  
		},

		kwresearch_edit_keyword: function(kid) {
			var loc = Drupal.settings.kwresearch.keyword_edit_path + kid;
			if (Drupal.settings.kwresearch.return_destination) {
			  loc += '?destination=' + Drupal.settings.kwresearch.return_destination;
			}
			window.location	= loc;
			return false;
		},

		kwresearch_delete_keyword: function(keyword, kid) {
		  keyword = unescape(keyword);
		  if (Drupal.settings.kwresearch.site_keywords_data[keyword]['priority'] > 0) {
			if (!confirm(Drupal.t('This keyword has a site priority. Are you sure you want to delete it?'))) {
				return false;
			}
		  }
		  var data = { 
		    'kwresearch_keyword': keyword,
		    'kid': kid,
		    'form': Drupal.settings.kwresearch.form
		  };

		  $.ajax({
		    type: 'POST',
		    url: Drupal.settings.kwresearch.delete_site_keyword_callback,
		    data: data,
		    dataType: 'json',
		    success: function(data, textStatus) {
			  	if (data.data['deleted']) {
		// TODO this does not work with multiple deletes
		    	  $('#kid-' + data.data['kid']).fadeOut(100);
		    	  $('#kid-' + data.data['kid']).remove();
			  	}
		    },
		    error: function(XMLHttpRequest, textStatus, errorThrown) {

		    }
		  });

		  return false;  
		},

		kwresearch_toggle_pagekw_keyword: function(keyword, add, keywordns, priority) {
		  
		  // update sync vocabulary
		  v = $('#edit-' + Drupal.settings.kwresearch.sync_vocab_field).val();
		  if (add) {    
		    nv = v + (v ? ', ' : '') + keyword;    
		  }
		  else {
		    nv = $$.kwresearch_remove_phrase_from_list(keyword, v);
		  }
		  $('#edit-' + Drupal.settings.kwresearch.sync_vocab_field).val(nv);
		  
		  // do ajax call to store in database
		  var data = { 
		    'kwresearch_keyword': keyword,
		    'priority': 0,
		    'nid': Drupal.settings.contentanalysis.nid
		  };
		  if (priority != null) {
		    data.priority = priority;
		    $('.kwresearch_actions').hide();
		  }
		  else if (add) {    
		    data.priority = 50;  
		  } 

		  $.ajax({
		    type: 'POST',
		    url: Drupal.settings.kwresearch.toggle_page_keyword_callback,
		    data: data,
		    dataType: 'json',
		    success: function(data, textStatus) {
		      if (Drupal.settings.kwresearch.page_keywords_data[data.data['keyword']] == null) {
		        Drupal.settings.kwresearch.page_keywords_data[data.data['keyword']] = {
		          'priority': data.data['priority']
		        }
		      }
		      else {
		        Drupal.settings.kwresearch.page_keywords_data[data.data['keyword']]['priority'] = data.data['priority'];
		      }
		      //$(theLink).replaceWith(kwresearch_get_toggle_button(keyword, 'pagekw'));
		      $('.kwresearch-tool-button-page-keyword-' + keywordns).replaceWith($$.kwresearch_get_toggle_button(data.data['keyword'], 'pagekw'));

		    },
		    error: function(XMLHttpRequest, textStatus, errorThrown) {

		    }
		  });

		  return false;  
		},

		kwresearch_toggle_vocab_keyword: function(keyword, add, theLink) {
		  v = $('#edit-' + Drupal.settings.kwresearch.sync_vocab_field).val();
		  if (add) {    
		    nv = v + (v ? ', ' : '') + keyword;    
		  }
		  else {
		    nv = $$.kwresearch_remove_phrase_from_list(keyword, v);
		  }
		  $('#edit-' + Drupal.settings.kwresearch.sync_vocab_field).val(nv);
		  $(theLink).replaceWith($$.kwresearch_get_toggle_button(keyword, 'vocab'));
		  return false;
		},

		kwresearch_toggle_mlt_keyword: function(keyword, add, theLink) {
		  v = $('#edit-morelikethis-terms').val();
		  if (add) {    
		    nv = v + (v ? ', ' : '') + keyword;    
		  }
		  else {
		    nv = $$.kwresearch_remove_phrase_from_list(keyword, v);
		  }
		  $('#edit-morelikethis-terms').val(nv);
		  $(theLink).replaceWith($$.kwresearch_get_toggle_button(keyword, 'mlt'));
		  return false;
		},

		kwresearch_toggle_meta_keyword: function(keyword, add, theLink) {
		  v = $('#edit-metatags-keywords-value').val();
		  if (add) {    
		    nv = v + (v ? ', ' : '') + keyword;    
		  }
		  else {
		    nv = $$.kwresearch_remove_phrase_from_list(keyword, v);
		  }
		  $('#edit-metatags-keywords-value').val(nv);
		  $(theLink).replaceWith($$.kwresearch_get_toggle_button(keyword, 'meta_keywords'));
		  return false;
		},

		kwresearch_remove_phrase_from_list: function(keyword, list) {
		  kws0 = list.split(',');  
		  kws1 = new Array();
		  j = 0;
		  for(var i in kws0) {    
		    k = jQuery.trim(kws0[i].toLowerCase());
		    if (k != keyword) {
		      kws1[j] = k;
		      j++;
		    }    
		  }  
		  return kws1.join(', ');
		},

		kwresearch_analyze: function() {
		  // if TinyMCE is used, turn off and on to save body text to textarea

		  var data = { 
		    'kwresearch_keyword': '',
		    'kwresearch_include_misspellings': 0,
		    'kwresearch_include_plurals': 0,
		    'kwresearch_adult_filter':$('#edit-kwresearch-adult-filter:selected').val(),
		    'kwresearch_nid': -1
		  };
		  data.kwresearch_keyword = $('#edit-kwresearch-keyword').val();
		  if ($('#edit-kwresearch-include-misspellings:checked').val() != null) {
		    data.kwresearch_include_misspellings = 1;
		  }
		  if ($('#edit-kwresearch-include-plurals:checked').val() != null) {
		    data.kwresearch_include_plurals = 1;
		  }
		  if (Drupal.settings.contentanalysis.nid > 0) {
		    data.kwresearch_nid = Drupal.settings.contentanalysis.nid;
		  }
		  
		  $('.kwresearch-result-block').hide();
		  var id = 'kwresearch-result-block-' + data.kwresearch_keyword.replace(/ /g, '-').toLowerCase();
		  var existing = $('#' + id);
		  if (existing.size() > 0) {
		    $(existing).show();
		  } else {
		    $('#kwresearch-submit-button').after('<div class="ahah-progress ahah-progress-throbber"><div class="throbber">&nbsp;</div><div class="message">' + Drupal.t('Analyzing...') + '</div></div>');
		    $('#kwresearch-submit-button').hide();  
		    $.ajax({
		      type: 'POST',
		      url: Drupal.settings.kwresearch.analyze_callback,
		      data: data,
		      dataType: 'json',
		      success: function(data, textStatus) {
		        $('#kwresearch-report').append(data.report['output']);
		        $$.kwresearch_init();
		        $('.ahah-progress-throbber').remove();
		        $('#kwresearch-submit-button').show();
		        //$$.kwresearch_keyword_data = $$.kwresearch_keyword_data.concat(data.report['data']);
		        //alert(pop(data.report['data']));
		      },
		      error: function(XMLHttpRequest, textStatus, errorThrown) {
		        //alert("error " + XMLHttpRequest.toString());
		        $('.ahah-progress-throbber').remove();
		        $('#kwresearch-submit-button').show();
		      }
		    });
		  }
		  return false;	
		},
		
		kwresearch_refresh_tax_report: function(vid) {
		  $('.kwresearch-refresh-link-' + vid).replaceWith('<div class="ahah-progress ahah-progress-throbber"><div class="throbber">&nbsp;</div></div>');
		  var data = { 
		    'keywords': $('#edit-taxonomy-tags-' + vid + '-wrapper input').val(),
		    'vid': vid,
		  };
		 
		  $.ajax({
		    type: 'POST',
		    url: Drupal.settings.kwresearch.tax_report_callback,
		    data: data,
		    dataType: 'json',
		    success: function(data, textStatus) {
			  vid = data.inputs['vid'];
			  $('#kwresearch-tax-report-'+vid).replaceWith(data.report['output']);
			  $('.ahah-progress-throbber').remove();
		      h = '<a href="#" class="kwresearch-refresh-link-' + vid + '" onclick="kwresearch.kwresearch_refresh_tax_report(\'' + vid + '\'); return false;" title="refresh report">';
		      h += '<img src="' + Drupal.settings.kwresearch.path_to_module + '/icons/refresh.png" alt="refresh report" />';
		      h += '</a>';
		      $('.kwresearch-tax-report-' + vid + ' label').append(h);      
		    },
		    error: function(XMLHttpRequest, textStatus, errorThrown) {
		      alert("error " + errorThrown.toString());
		      $('.ahah-progress-throbber').remove();
		      
		    }
		  });
		  return false;	
		}
	});	

	Drupal.behaviors.kwresearch_init = {
	  attach: function (context, settings) {
		$$.init();
	  }
	}

})(jQuery, kwresearch);

//Implementation of hook_contentanalysis_analysis_success
var kwresearch_contentanalysis_analysis_success = function(aid) {
  kwresearch.kwresearch_process_keywords();
}