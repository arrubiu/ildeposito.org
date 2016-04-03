#!/bin/bash

if [ $(hostname) == 'portatilinux' ];
then
    drush sql-drop -y
    drush sql-sync -y @ildeposito.prod @ildeposito.local
fi

drush rr
drush updb -y

if [ $(hostname) == 'portatilinux' ];
then
    drush dis cdn, smtp, entitycache, varnish, memcache_storage -y
    drush vset eu_cookie_compliance_domain '' -y
fi

drush en entityreference_migration paragraphs ildeposito_utils ildeposito_libreria imagecache_token ildepositoboot ildeposito_autore ildeposito_customcontent ildeposito_canto ildeposito_articolo -y
drush emr

## Moduli contrib
drush dis -y emptyparagraphkiller, htmlpurifier, checklistapi, oauth_common, rss_category, rss_enclosure, site_verify, services, uuid_path, feeds, feeds_tamper, forum, custom_formatters, better_revisions, backup_migrate_dropbox, backup_migrate_sftp, blockcache_alter, block_class,  commitlog, versioncontrol, git_status, versioncontrol_git, date_facets, date_repeat_presets, delta_ui, delta, dismiss, field_label_plurals, flag_lists, hidden_comment, linkit_picker, linkit_views, magic, memcache_status, metatag_facebook, metatag_opengraph, omega_tools, simplenews_rules, trigger, user_picture_field, back_to_top, job_scheduler, varnish_status, print, actions_permissions, ds, references, node_reference, noderefcreate, variable_email, autofloat, entityreference_migration, speedy, simplehtmldom, xmlsitemap_custom, xmlsitemap_engines, service_links, general_services, widget_services, widgets_service_links, widgets, xmlsitemap_custom, xmlsitemap_engines

## Moduli custom
drush dis -y ildeposito_purge, stampa, ildeposito_news, ildeposito_social, ildeposito_cron, alterator, elenchi, ildeposito_app, ildeposito_ct_libreria, ildeposito_ct_canto, ildeposito_ct_customcontent, ildeposito_ct_autore, ildeposito_ct_articolo


## Variabili
drush vset theme_default ildepositoboot -y

## Temi
drush dis best_responsive sky bartik ildeposito -y

drush cc all
drush fl
