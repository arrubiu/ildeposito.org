(function(a){Drupal.behaviors.blockSettingsSummary={attach:function(b){if(typeof jQuery.fn.drupalSetSummary=="undefined")return;a("fieldset#edit-path",b).drupalSetSummary(function(b){return a('textarea[name="pages"]',b).val()?Drupal.t("Restricted to certain pages"):Drupal.t("Not restricted")}),a("fieldset#edit-node-type",b).drupalSetSummary(function(b){var c=[];return a('input[type="checkbox"]:checked',b).each(function(){c.push(a.trim(a(this).next("label").text()))}),c.length||c.push(Drupal.t("Not restricted")),c.join(", ")}),a("fieldset#edit-role",b).drupalSetSummary(function(b){var c=[];return a('input[type="checkbox"]:checked',b).each(function(){c.push(a.trim(a(this).next("label").text()))}),c.length||c.push(Drupal.t("Not restricted")),c.join(", ")}),a("fieldset#edit-user",b).drupalSetSummary(function(b){var c=a('input[name="custom"]:checked',b);return c.val()==0?Drupal.t("Not customizable"):c.next("label").text()})}},Drupal.behaviors.blockDrag={attach:function(b,c){if(typeof Drupal.tableDrag=="undefined"||typeof Drupal.tableDrag.blocks=="undefined")return;var d=a("table#blocks"),e=Drupal.tableDrag.blocks;e.row.prototype.onSwap=function(a){f(d,this)},Drupal.theme.tableDragChangedWarning=function(){return'<div class="messages warning">'+Drupal.theme("tableDragChangedMarker")+" "+Drupal.t("The changes to these blocks will not be saved until the <em>Save blocks</em> button is clicked.")+"</div>"},e.onDrop=function(){dragObject=this;var b=a(dragObject.rowObject.element).prevAll("tr.region-message").get(0),c=b.className.replace(/([^ ]+[ ]+)*region-([^ ]+)-message([ ]+[^ ]+)*/,"$2"),d=a("select.block-region-select",dragObject.rowObject.element);if(a("option[value="+c+"]",d).length==0)alert(Drupal.t("The block cannot be placed in this region.")),d.change();else if(a(dragObject.rowObject.element).prev("tr").is(".region-message")){var e=a("select.block-weight",dragObject.rowObject.element),f=e[0].className.replace(/([^ ]+[ ]+)*block-weight-([^ ]+)([ ]+[^ ]+)*/,"$2");d.is(".block-region-"+c)||(d.removeClass("block-region-"+f).addClass("block-region-"+c),e.removeClass("block-weight-"+f).addClass("block-weight-"+c),d.val(c))}},a("select.block-region-select",b).once("block-region-select",function(){a(this).change(function(b){var c=a(this).closest("tr"),g=a(this);e.rowObject=new e.row(c),d.find(".region-"+g[0].value+"-message").nextUntil(".region-message").last().before(c),f(d,c),g.get(0).blur()})});var f=function(b,c){a("tr.region-message",b).each(function(){a(this).prev("tr").get(0)==c.element&&(c.method!="keyboard"||c.direction=="down")&&c.swap("after",this),a(this).next("tr").is(":not(.draggable)")||a(this).next("tr").length==0?a(this).removeClass("region-populated").addClass("region-empty"):a(this).is(".region-empty")&&a(this).removeClass("region-empty").addClass("region-populated")})}}}})(jQuery);