(function($){Drupal.behaviors.menuChangeParentItems={attach:function(context,settings){$("fieldset#edit-menu input").each(function(){$(this).change(function(){Drupal.menu_update_parent_list()})})}};Drupal.menu_update_parent_list=function(){var values=[];$("input:checked",$("fieldset#edit-menu")).each(function(){values.push(Drupal.checkPlain($.trim($(this).val())))});var url=Drupal.settings.basePath+"admin/structure/menu/parents";$.ajax({url:location.protocol+"//"+location.host+url,type:"POST",data:{"menus[]":values},dataType:"json",success:function(options){var selected=$("fieldset#edit-menu #edit-menu-parent :selected").val();$("fieldset#edit-menu #edit-menu-parent").children().remove();jQuery.each(options,function(index,value){$("fieldset#edit-menu #edit-menu-parent").append($("<option "+(index==selected?' selected="selected"':"")+"></option>").val(index).text(value))})}})}})(jQuery);
