/**
 * @file
 * jQuery to call captcha_free_headers.php, control the "no JavaScript enabled"
 * warning, and add a hidden input type.
 */
(function ($) {
  $(document).ready( function(){
    $('.warning').remove();
    $.get("/" + Drupal.settings.captchaFree.path + "/cap_sub/captcha_free_headers.php",function(txt){
    $("#" + Drupal.settings.captchaFree.selector + "").append('<input type="hidden" name="ts" value="'+txt+'" />');
    });
  });
})(jQuery);