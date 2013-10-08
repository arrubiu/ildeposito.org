(function ($) {

  Drupal.behaviors.intel_webform_submission_results = {
    attach: function (context, settings) {
    // if standard admin form
    if (jQuery(".webform-results-per-page").length > 0) {
      var colIndex = 0;
      var colCount = 0;
      
      if (colIndex == 0) {
        jQuery('.page-node-webform-results table thead tr:nth-child(1) th').each(function () {
          if ((colIndex == 0) && ($(this).html() == "Operations")) {
            colIndex = colCount-1;
          }
          if ($(this).attr('colspan')) {
          colCount += +$(this).attr('colspan');
        } else {
          colCount++;
        }
        });  
      }
    }
    if (colIndex == 0) {
        return;
    }
    colCount = colCount/2;
// TODO switch to using colIndex
//alert("ci=" + colIndex + ", cc=" + colCount);
    $(".page-node-webform-results table thead tr:nth-child(1) th:eq(9)").attr('colspan',4);
    $(".page-node-webform-results table thead tr:nth-child(1) th:eq(9)").before('<th>Location</th>');
    var sids = {};
    $(".page-node-webform-results table tr:gt(1)").each ( function( index ) {
        var sid = $(this).find("td:eq(0)").html();
      if (typeof sid !== 'undefined') {
        sids[sid] = sid;
        var imgsrc = Drupal.settings.intel.script_domain + Drupal.settings.intel.module_path + "/images/ajax_loader_row.gif";
        $(this).find("td:eq(" + (colIndex) + ")").after('<td data-sid="' + sid + '" colspan="2"><img src="' + imgsrc + '"></td>');  
      }
    });
    var data = {
        'sids': sids,
        'path': window.location.pathname
    };
      var url = Drupal.settings.intel.script_domain + "intel_webform/admin_submission_results_alter_js"; //?callback=?";
      jQuery.ajax({
      dataType: 'json',
      url: url, 
      data: data,
      type: 'POST'
      })
      .done ( function(data) { 
        $(".page-node-webform-results table tr:gt(1)").each ( function( index ) {
          var sid = $(this).find("td:eq(0)").html();
        if (typeof sid != 'undefined') {
        if (typeof data.rows[sid] != 'undefined') {
          $(this).find("td:eq(" + (colIndex+1) + ")").replaceWith(data.rows[sid]);
          //$(this).find("td:eq(" + (colIndex+1) + ")").replaceWith(data.rows[sid]['op']);
        }
        else {
          $(this).find("td:eq(" + (colIndex+1) + ")").replaceWith('<td>-</td><td>-</td>');
        }
        }
      });
      });  
    }
  };

})(jQuery);

// jQuery('#node-admin-content thead tr:nth-child(1) th').css("border","5px solid red");