#!/bin/bash
drush rr
drush updb -y
drush en entityreference_migration imagecache_token ildepositoboot -y
drush emr

## Moduli contrib
drush dis -y emptyparagraphkiller, htmlpurifier, checklistapi, oauth_common, rss_category, rss_enclosure, site_verify, services, uuid_path, feeds, feeds_tamper, forum, custom_formatters, better_revisions, backup_migrate_dropbox, backup_migrate_sftp, blockcache_alter, block_class,  commitlog, versioncontrol, git_status, versioncontrol_git, date_facets, date_repeat_presets, delta_ui, delta, dismiss, field_label_plurals, flag_lists, hidden_comment, linkit_picker, linkit_views, magic, memcache_status, metatag_facebook, metatag_opengraph, omega_tools, simplenews_rules, trigger, user_picture_field, back_to_top, job_scheduler, varnish_status, print, actions_permissions, ds, references, node_reference, noderefcreate, variable_email, autofloat, entityreference_migration

## Moduli custom
drush dis -y ildeposito_purge, stampa, ildeposito_news, ildeposito_social, ildeposito_cron, alterator, elenchi, ildeposito_app
drush pm-uninstall -y ildeposito_purge, stampa, ildeposito_news, ildeposito_social, ildeposito_cron, alterator, elenchi, ildeposito_app

## Temi
drush dis best_responsive sky bartik ildeposito -y

## Variabili
drush vset theme_default ildepositoboot -y

if [ $(hostname) == 'portatilinux' ];
then
    drush dis cdn, smtp entitycache, varnish, memcache_storage -y
    drush vset eu_cookie_compliance_domain '' -y
fi

drush cc all
drush fl
