// array to place 
var _chart = _chart || [];

function L10iCharts() { 
  this.init = function init() {
	  this.resizeCharts();
	  this.addCustomFormatters();
console.log(_chart);
      for (var id in _chart) {
    	this.drawChart(id);
      }
      
      jQuery(window).resize(function() {
    	 l10iCharts.resizeCharts();
      });
  };
  
  this.addCustomFormatters = function addCustomFormatters() {
    google.visualization.NumberDateFormat = function (options) {
      google.visualization.NumberDateFormat.options = options;

      this.format = function (dt, columnIndex) {
console.log(dt);
    	var options = google.visualization.NumberDateFormat.options;
        for (var i=0; i < dt.getNumberOfRows(); i++) {
          var date = new Date (dt.getValue(i, columnIndex));
          var formatter = new google.visualization.DateFormat(options);
          var formatted = formatter.formatValue(date);
          dt.setFormattedValue(i, columnIndex, formatted);
          //console.log(dt.getValue(i, columnIndex)); 
        }
      }
    }   
  };
	
  this.resizeCharts = function resizeCharts() {
    var processed = {};
    for (var id in _chart) {
      if (!(id in processed) && (typeof _chart[id][2] != 'undefined')) {
    	// check if we should not resize the chart
    	if ((2 in _chart[id]) && ('resize' in _chart[id][2]) && (_chart[id][2]['resize'] == 0)) {
    	  continue;
    	}
    	if (jQuery('#' + id).length > 0) {
          jQuery('#' + id).width(jQuery(this).parent().width());          
    	}
    	processed[id] = 1;
      }
    }
    processed = {};
  };
  
  this.drawChart = function drawChart(id) {
	var i, chart, data, charttype, e, formatter, method, method_name, cols, rows, dateCols;
console.log(id);
	charttype = id.split('-');
	charttype = charttype[0];	
	dateCols = [];
    
	// init data using DataTable or arrayToDataTable
	if ((_chart[id][2]['cols'] != undefined) && (_chart[id][2]['cols'].length > 0)) {   
      data = new google.visualization.DataTable();
      cols = _chart[id][2]['cols'];
console.log(cols);
      for (var i = 0; i < cols.length; i++) {
    	data.addColumn(cols[i]);
    	if (cols[i].type == 'date') {
    	  dateCols.push(i);
    	}
      }
      
      rows = _chart[id][2]['rows'];
console.log(rows);
      if (rows != undefined) {
    	  for (var i = 0; i < rows.length; i++) {
    		  for (var j in dateCols) {
    		    rows[i][j] = new Date(rows[i][j]);
    		  }
    	      data.addRow(rows[i]);
    	  }
      }
      else {
        data.addRows(_chart[id][0]);
      }  
      
      e = _chart[id][2]['formatters'];
      if (e != undefined) {
	      for (var i = 0; i < e.length; i++) {
	    	if (e[i].options != undefined) {
	    	  formatter = new google.visualization[e[i].name](e[i].options);
	    	}
	    	else {
	          formatter = new google.visualization[e[i].name]();
	    	}
	    	if (e[i].methods != undefined) {
	    		for (var j = 0; j < e[i].methods.length;j++) {
	    			method = e[i].methods[j];
	    			console.log(formatter);
	    			console.log(method);
	    			formatter[method.name].apply(formatter, method.args);
	    		}
	    	}
	        formatter.format(data, e[i].columnIndex);
	      }
      }
    }    
    else {
    	data = google.visualization.arrayToDataTable(_chart[id][0]);
    }
	
	// init chart
	if (charttype == 'table') {
	  chart = new google.visualization.Table(document.getElementById(id));
	}
    if (charttype == 'linechart') {
      chart = new google.visualization.LineChart(document.getElementById(id));
    }
    if (charttype == 'areachart') {
      chart = new google.visualization.AreaChart(document.getElementById(id));
    }
    if (charttype == 'piechart') {
      chart = new google.visualization.PieChart(document.getElementById(id));
    }
    if (charttype == 'bubblechart') {
      chart = new google.visualization.BubbleChart(document.getElementById(id));
    }
    if (charttype == 'columnchart') {
        chart = new google.visualization.ColumnChart(document.getElementById(id));
      }
    if (charttype == 'combochart') {
      chart = new google.visualization.ComboChart(document.getElementById(id));
    }
    if (charttype == 'gaugechart') {
      chart = new google.visualization.Gauge(document.getElementById(id));
    }
    if (charttype == 'timeline') {
    chart = new google.visualization.Timeline(document.getElementById(id));
  }
    
    // attach events
    if (charttype == 'table') {
	      google.visualization.events.addListener(chart, 'sort',
	        function(event) {
		      e = _chart[id][2]['cols'];
		      for (var i = 0; i < e.length; i++) {
		        if (e[i].type === 'number') {
		        	var j = 2;
		        	var selector = '#' + id + ' tr:nth-child(1) td:nth-child(' + (i+j) + ')';
		            jQuery(selector).addClass('numeric-header');
		        }
		      }
	      });
	      google.visualization.events.addListener(chart, 'ready',
	        function(event) {
		      e = _chart[id][2]['cols'];
		      for (var i = 0; i < e.length; i++) {
		    	var j = 2;
		        if (e[i].type === 'number') {	        	
		        	var selector = '#' + id + ' tr:nth-child(1) td:nth-child(' + (i+j) + ')';
		            jQuery(selector).addClass('numeric-header');
		        }
		      }
	      });
    }    
    
    chart.draw(data, _chart[id][1]);
  };
  
}

var l10iCharts = new L10iCharts();
jQuery(document).ready(function() {
	console.log(google.visualization);	
	l10iCharts.init();
});

/*
var l10iNumberDateFormat = function () {
  this.pattern = '';
  
  this.format = function (dt, columnIndex) {
    for (var i=0; i < dt.getNumberOfRows(); i++) {
      var date = new Date (dt.getValue(i, columnIndex));
      var formatter = new google.visualization.DateFormat({pattern: 'MMM d'});
      var formatted = formatter.formatValue(date);
      dt.setFormattedValue(i, column, formatted);
      console.log(dt.getValue(i, column)); 
    }
  }
}
*/

// jQuery('#node-admin-content thead tr:nth-child(1) th').css("border","5px solid red");