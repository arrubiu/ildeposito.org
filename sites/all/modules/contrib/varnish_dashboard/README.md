About
=====

This module provides an admin dashboard to display real-time traffic    
information from Varnish.

Key metrics displayed are:

* Cache-hit ratio
* Traffic volume (in requests-per-second)
* Bandwidth usage (in Mbps)


Prerequisites
=============

1. Varnish (3 or greater)    
   [https://www.varnish-cache.org/](https://www.varnish-cache.org/)    

2. Varnish agent 2    
   [http://github.com/varnish/vagent2](http://github.com/varnish/vagent2)    


Setup
=====

TL;DR
-----

1. Install the prerequisistes.
2. Enable the module.
3. Configure the Agent URL at *admin/config/varnish/dashboard*.
4. Visit the Dashboard at *admin/reports/varnish_dashboard*.


In detail
---------

Install the prerequisites according to their instructions. You may be able    
to install them from packages available in your distribution: for example    
*Ubuntu Precise* provides a Varnish 3 package.

Enable the *varnish dashboard* module. The module proxies data-requests for   
the Agent, so that access to the dashboard can be controlled using Drupal    
access-controls. The URL of the Agent needs to be configured, at the admin    
page *admin/config/varnish/dashboard*.

The configuration for the data-proxying can also be set using the variables:

* varnish_dashboard.url
* varnish_dashboard.user
* varnish_dashboard.pass

Once configured, the dashboard is displayed on the admin-reports page    
*admin/reports/varnish_dasboard*.


Inspiration
===========

* Inspired by the Varnish Agent Dashboard tool:    
  [https://github.com/pbruna/Varnish-Agent-Dashboard](https://github.com/pbruna/Varnish-Agent-Dashboard)

