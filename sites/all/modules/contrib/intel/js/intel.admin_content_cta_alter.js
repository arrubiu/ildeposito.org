(function ($) {

  Drupal.behaviors.intel_admin_content_cta_alter = {
    attach: function (context, settings) {
    
    // if standard admin form
    if (jQuery(".block-page-content").length > 0) {
      var colIndex = 0;
      var colCount = 0;
      jQuery('.block-page-content thead tr:nth-child(1) th').each(function () {

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
    $(".block-page-content thead th:eq(" + (colIndex-1) + ")").after('<th>Impns</th><th>Clicks</th><th>Click%</th><th>Convs</th><th>Conv%</th>');
    $(".block-page-content tr").each ( function( index ) {
      var href = $(this).find("td:eq(0) a").attr("href");
      if (typeof href != 'undefined') {
        var imgsrc = Drupal.settings.intel.script_domain + Drupal.settings.intel.module_path + "/images/ajax_loader_row.gif";
        $(this).find("td:eq(" + (colIndex-1) + ")").after('<td data-path="' + href + '" colspan="5" style="text-align:center;"><img src="' + imgsrc + '"></td>');        
      }
    }
        
    );
    //var query = (window.location.href.indexOf('?') > 0) ? window.location.href.substring(window.location.href.indexOf('?'), window.location.href.length) : '';
    //query = query.replace("render=overlay", "");  // remove overlay shenanigans
      var url = Drupal.settings.intel.script_domain + "intel/admin_content_cta_alter_js"; //?callback=?";
      jQuery.getJSON(url).success(function(data) { 
        $(".block-page-content tr").each ( function( index ) {
          var href = $(this).find("td:eq(0) a").attr("href");
        if (typeof href != 'undefined') {
        if (typeof data.rows[href] != 'undefined') {
          $(this).find("td:eq(" + colIndex + ")").replaceWith(data.rows[href]);
        }
        else {
          $(this).find("td:eq(" + colIndex + ")").replaceWith('<td colspan="5" style="text-align:center;">NA</td>');
        }
        }
      });
      });  
    }
  };

})(jQuery);

// jQuery('#node-admin-content thead tr:nth-child(1) th').css("border","5px solid red");