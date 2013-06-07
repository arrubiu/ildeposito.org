<?php

/**
 * Implementation of hook_analytics_default_provider()
 */
function analytics_omniture_analytics_default_provider() {
  $providers = array();
  
  // Omniture
  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a provider pool disabled initially */
  $provider->api_version = 1;
  $provider->machine_name = "omniture";
  $provider->description = "Omniture";
  $provider->libraries =  "sites/default/files/s_code.js";
  $provider->header_code = "<!-- Put your SiteCatalyst version and copyright information here -->";
  $provider->footer_code = "<script language=\"JavaScript\" type=\"text/javascript\">
    var s_code=s.t();if(s_code)document.write(s_code)//--></script>
    <script language=\"JavaScript\" type=\"text/javascript\"><!--
    if(navigator.appVersion.indexOf('MSIE')>=0)document.write(unescape('%3C')+'\!-'+'-')
    //--></script><noscript><img src=\"/path/to/site/catalyst/image/file\"
    height=\"1\" width=\"1\" border=\"0\" alt=\"\" /></noscript>
    <!-- End SiteCatalyst code -->";
  $providers["omniture"] = $provider;

  return $providers;
}