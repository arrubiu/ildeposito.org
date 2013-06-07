<?php

/**
 * Implementation of hook_analytics_default_tag()
 */
function analytics_omniture_analytics_default_tag() {
  $tags = array();

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "channel";
  $tag->description = "Channel";
  $tag->tag_code = "s.channel=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["channel"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "events";
  $tag->description = "Events";
  $tag->tag_code = "s.events=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["events"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "hierarchy_1";
  $tag->description = "Hierarchy 1";
  $tag->tag_code = "s.hier1=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["hierarchy_1"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "page_name";
  $tag->description = "Page name";
  $tag->tag_code = "s.pageName=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["page_name"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "page_type";
  $tag->description = "Page type";
  $tag->tag_code = "s.pageType=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "<404>
  <403>";
  $tag->roles = array();
  $tags["page_type"] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "products";
  $tag->description = "Products";
  $tag->tag_code = "s.products=\"[%products]\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["products"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "purchase_id";
  $tag->description = "Purchase ID";
  $tag->tag_code = "s.purchaseID=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["purchase_id"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "campaign";
  $tag->description = "Campaign";
  $tag->tag_code = "s.campaign=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["campaign"] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_1";
  $tag->description = "Prop 1";
  $tag->tag_code = "s.prop1=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_1"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_2";
  $tag->description = "Prop 2";
  $tag->tag_code = "s.prop2=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_2"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_3";
  $tag->description = "Prop 3";
  $tag->tag_code = "s.prop3=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_3"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_4";
  $tag->description = "Prop 4";
  $tag->tag_code = "s.prop4=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_4"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_5";
  $tag->description = "Prop 5";
  $tag->tag_code = "s.prop5=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_5"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_6";
  $tag->description = "Prop 6";
  $tag->tag_code = "s.prop6=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_6"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_7";
  $tag->description = "Prop 7";
  $tag->tag_code = "s.prop7=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_7"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_8";
  $tag->description = "Prop 8";
  $tag->tag_code = "s.prop8=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_8"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_9";
  $tag->description = "Prop 9";
  $tag->tag_code = "s.prop9=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_9"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_10";
  $tag->description = "Prop 10";
  $tag->tag_code = "s.prop10=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_10"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_11";
  $tag->description = "Prop 11";
  $tag->tag_code = "s.prop11=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_11"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_12";
  $tag->description = "Prop 12";
  $tag->tag_code = "s.prop12=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_12"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_13";
  $tag->description = "Prop 13";
  $tag->tag_code = "s.prop13=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_13"] = $tag;
 
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_14";
  $tag->description = "Prop 14";
  $tag->tag_code = "s.prop14=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_14"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_15";
  $tag->description = "Prop 15";
  $tag->tag_code = "s.prop15=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_15"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_16";
  $tag->description = "Prop 16";
  $tag->tag_code = "s.prop16=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_16"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_17";
  $tag->description = "Prop 17";
  $tag->tag_code = "s.prop17=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["prop_17"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_18";
  $tag->description = "Prop 18";
  $tag->tag_code = "s.prop18=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_18"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_19";
  $tag->description = "Prop 19";
  $tag->tag_code = "s.prop19=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_19"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_20";
  $tag->description = "Prop 20";
  $tag->tag_code = "s.prop20=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_20"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_21";
  $tag->description = "Prop 21";
  $tag->tag_code = "s.prop21=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["prop_21"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_22";
  $tag->description = "Prop 22";
  $tag->tag_code = "s.prop22=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["prop_22"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_23";
  $tag->description = "Prop 23";
  $tag->tag_code = "s.prop23=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array("2");
  $tags["prop_23"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_24";
  $tag->description = "Prop 24";
  $tag->tag_code = "s.prop24=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_24"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_25";
  $tag->description = "Prop 25";
  $tag->tag_code = "s.prop25=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_25"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_26";
  $tag->description = "Prop 26";
  $tag->tag_code = "s.prop27=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_26"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_27";
  $tag->description = "Prop 27";
  $tag->tag_code = "s.prop26=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_27"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_28";
  $tag->description = "Prop 28";
  $tag->tag_code = "s.prop28=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_28"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_29";
  $tag->description = "Prop 29";
  $tag->tag_code = "s.prop29=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_29"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_30";
  $tag->description = "Prop 30";
  $tag->tag_code = "s.prop30=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_30"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_31";
  $tag->description = "Prop 31";
  $tag->tag_code = "s.prop31=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_31"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_32";
  $tag->description = "Prop 32";
  $tag->tag_code = "s.prop32=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_32"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_33";
  $tag->description = "Prop 33";
  $tag->tag_code = "s.prop33=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_33"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_34";
  $tag->description = "Prop 34";
  $tag->tag_code = "s.prop34=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_34"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_35";
  $tag->description = "Prop 35";
  $tag->tag_code = "s.prop35=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_35"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "prop_36";
  $tag->description = "Prop 36";
  $tag->tag_code = "s.prop36=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["prop_36"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_1";
  $tag->description = "eVar 1";
  $tag->tag_code = "s.eVar1=s.prop8";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_1"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_2";
  $tag->description = "eVar 2";
  $tag->tag_code = "s.eVar2=s.prop9";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_2"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_3";
  $tag->description = "eVar 3";
  $tag->tag_code = "s.eVar3=s.prop10";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_3"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_4";
  $tag->description = "eVar 4";
  $tag->tag_code = "s.eVar4=s.purchaseID";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_4"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_5";
  $tag->description = "eVar 5";
  $tag->tag_code = "s.eVar5=s.prop17";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_5"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_6";
  $tag->description = "eVar 6";
  $tag->tag_code = "s.eVar6=s.prop23";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_6"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_7";
  $tag->description = "eVar 7";
  $tag->tag_code = "s.eVar7=s.prop18";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_7"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_9";
  $tag->description = "eVar 9";
  $tag->tag_code = "s.eVar9=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_9"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_10";
  $tag->description = "eVar 10";
  $tag->tag_code = "s.eVar10=s.prop10";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_10"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_11";
  $tag->description = "eVar 11";
  $tag->tag_code = "s.eVar11=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_11"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_14";
  $tag->description = "eVar 14";
  $tag->tag_code = "s.eVar14=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_14"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_15";
  $tag->description = "eVar 15";
  $tag->tag_code = "s.eVar15=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_15"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_17";
  $tag->description = "eVar 17";
  $tag->tag_code = "s.eVar17=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_17"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_18";
  $tag->description = "eVar 18";
  $tag->tag_code = "s.eVar18=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_18"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_19";
  $tag->description = "eVar 19";
  $tag->tag_code = "s.eVar19=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_19"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_23";
  $tag->description = "eVar 23";
  $tag->tag_code = "s.eVar23=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_23"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_24";
  $tag->description = "eVar 24";
  $tag->tag_code = "s.eVar24=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_24"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_25";
  $tag->description = "eVar 25";
  $tag->tag_code = "s.eVar25=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_25"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_26";
  $tag->description = "eVar 26";
  $tag->tag_code = "s.eVar26=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["evar_26"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_27";
  $tag->description = "eVar 27";
  $tag->tag_code = "s.eVar27=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "*";
  $tag->roles = array();
  $tags["evar_27"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_28";
  $tag->description = "eVar 28";
  $tag->tag_code = "s.eVar28=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_28"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_29";
  $tag->description = "eVar 29";
  $tag->tag_code = "s.eVar29=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_29"] = $tag;
  
  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machine_name = "evar_30";
  $tag->description = "eVar 30";
  $tag->tag_code = "s.eVar30=\"\"";
  $tag->provider = "omniture";
  $tag->auto_include = "";
  $tag->roles = array();
  $tags["evar_30"] = $tag;
  
  return $tags;
}