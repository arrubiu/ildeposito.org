// $Id: seotools.js,v 1.1.2.1 2010/12/28 17:45:39 randallknutson Exp $

/*
if (Drupal.jsEnabled) {
  $(document).ready(function () {
    seotools_init();
  });
}
*/

Drupal.behaviors.seotools_init = function (context) {
  seotools_init();
}

var seotools_charts = new Array();

var seotools_init = function () {
  var charts = Drupal.settings.seotools.charts;
  for(var id in charts) {
    var chart = charts[id];
    var width = $('.' + chart['location'] + '-wrapper').width();
    if (width > 1000) {
      width = 1000;
    }
    // replace width in 600 wide charts
    var chart_src = chart['src'].replace('chs=600', 'chs=' + width);
    // replace width in 440 wide charts
    chart_src = chart_src.replace('chs=440', 'chs=' + width);
    chart_src = chart_src.replace('chs=300', 'chs=' + width);
    seotools_charts[id] = $('<img />').attr('src', chart_src);
    if (!chart['load_only']) {
	  $('<img />').attr('src', chart_src).attr('class', chart['location'])
	    .load(function(){
	      var fixClass = $(this).attr('class');
		  $('.' + fixClass + '-wrapper').append( $(this) );
	    });
    }
  }
}

var seotools_show_main_chart = function(id) {
	var title = Drupal.settings.seotools.charts[id]['title'];
	$('#chart-main-title').replaceWith('<h4 id="chart-main-title">' + title + '</h4>');
	$('.chart-main-wrapper img').remove();
	$('.chart-main-wrapper').append(seotools_charts[id]);
	return false;
}