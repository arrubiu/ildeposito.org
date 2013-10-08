(function ($) {

  Drupal.behaviors.intel_admin_content_alter = {
    attach: function (context, settings) {
    // if standard admin form
    if (jQuery("#node-admin-content").length > 0) {
      var colIndex = 0;
      var colCount = 0;
      jQuery('#node-admin-content thead tr:nth-child(1) th').each(function () {

        if ($(this).text() == "Title") {
          colIndex = colCount+1;
        }
        if ($(this).attr('colspan')) {
        colCount += +$(this).attr('colspan');
      } else {
        colCount++;
      }
      });
      //alert("ci=" + colIndex + ", cc=" + colCount);
    
    }
    if (colIndex == 0) {
      return;
    }
    $("#node-admin-content thead th:eq(" + (colIndex-1) + ")").after('<th>Score</th><th>Entrs</th><th>Views</th>');
    var hrefs = [];
    var imgsrc = Drupal.settings.intel.script_domain + Drupal.settings.intel.module_path + "/images/ajax_loader_row.gif";
    $("#node-admin-content tr").each ( function( index ) {
      var href = $(this).find("td:eq(1) a").attr("href");
      if (typeof href != 'undefined') {
        hrefs.push(href);
        $(this).find("td:eq(" + (colIndex-1) + ")").after('<td data-path="' + href + '" colspan="3" style="text-align:center;"><img src="' + imgsrc + '"></td>');        
      }
    }
        
    );
    var query = getUrlVars();
  
    var data = {
      'hrefs': hrefs
    };
    for (var i in query) {
    if (i == 'render') {
      continue;
    }
      data[i] = query[i];
    }

      var url = Drupal.settings.intel.script_domain + "intel/admin_content_alter_js"; //?callback=?";
      jQuery.getJSON(url, data).success(function(data) { 
        $("#node-admin-content tr").each ( function( index ) {
          var href = $(this).find("td:eq(1) a").attr("href");
        if (typeof href != 'undefined') {
        if (typeof data.rows[href] != 'undefined') {
          $(this).find("td:eq(" + colIndex + ")").replaceWith(data.rows[href]);
        }
        else {
          $(this).find("td:eq(" + colIndex + ")").replaceWith('<td colspan="3" style="text-align:center;">NA</td>');
        }
        }
      });
      });  
    }
  };
  
  function getUrlVars() {
      var vars = {}, hash;
      if (window.location.href.indexOf('?') == -1) {
        return vars;
      }
      var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
      for(var i = 0; i < hashes.length; i++)
      {
          hash = hashes[i].split('=');
          //vars.push(hash[0]);
          vars[hash[0]] = hash[1];
      }
      return vars;
  }

})(jQuery);

// jQuery('#node-admin-content thead tr:nth-child(1) th').css("border","5px solid red");