(function ($) {
  Drupal.behaviors.flagListsOps = {
    attach: function(context) {
      // Hide the go button, as it is not needed for JS enabled browsers.
      $('.flag-lists-ops-go', context).hide();

      // Make select all checkbox work
      $('input.flo-table-select-all', context).each(function(i) {
        var selectall = $(this);

        if (!selectall.hasClass('processed')) {
          selectall.change(function(e) {
            $('input.flo-select', $(this).parents('form')).attr('checked', $(this).attr('checked'));
          }).addClass('processed');
        }
      });

      // Animate the deletion for AJAX deleting.
      $('.flo-deleted-value', context).each(function(i) {
        var parent = $(this).parents('.view');
        $('.flo-select[value='+$(this).val()+']', parent).each(function(i) {
          $(this).parents('.views-row, tr').fadeOut().delay(300).remove();
        });
      });

      // Add new options to bottom of list ops dropdown to create new lists on the spot
      $('.flag-lists-ops-dropdown', context).each(function(i) {
        var select = $(this);
        if (!select.hasClass('new-list-processed')) {
          select.addClass('new-list-processed');

          if (Drupal.settings.flag_lists.types.length > 0) {
            $(this).after('<a href="#" class="create-a-new-list">New list?</a><div class="new-list-form"><form><select name="type" class="type"></select><label for="name">List name</label><input type="textfield" name="name" class="name" /></form></div>');
            var dialog = $('.new-list-form', $(this).parent()).dialog({
              autoOpen: false,
              height: 300,
              width: 350,
              modal: true,
              buttons: {
                "Create a new list": function() {
                  var name = $('input.name', $(this)).val();
                  var type = $('select.type', $(this)).val();

                  $.getJSON(Drupal.settings.flag_lists.json_path.replace('%', type)+'?name='+name, function(data) {
                    if (data.error) {
                      alert(data.error);
                    }
                    else {
                      select.append('<option value="'+data.flag.fid+'">'+data.flag.title+'</option>');
                      $('input.name', $(this)).val('');
                      dialog.dialog('close');
                    }
                  });
                },
                Cancel: function() {
                  dialog.dialog('close');
                }
              },
              close: function() {

              }
            });
            $('.create-a-new-list', $(this).parent())
              .button()
              .click(function(e) {
                dialog.dialog('open');
              });
          }

          // Put entries into the optgroup
          for (j in Drupal.settings.flag_lists.types) {
            var type = Drupal.settings.flag_lists.types[j];
            $('.new-list-form form select.type').append('<option value="'+type+'" class="'+type+'">List for '+type+'</option>');
          }
        }
      });
    }
  }
})(jQuery);
