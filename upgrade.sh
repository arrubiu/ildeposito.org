#!/bin/bash
drush rr
drush updb -y
drush en entityreference_migration -y
drush en imagecache_token -y
drush emr

drush dis -y emptyparagraphkiller, htmlpurifier, checklistapi, oauth_common, rss_category, rss_enclosure, site_verify, services, uuid_path, feeds, feeds_tamper, forum, custom_formatters, better_revisions, backup_migrate_dropbox, backup_migrate_sftp, blockcache_alter, block_class,  commitlog, versioncontrol, git_status, versioncontrol_git, date_facets, date_repeat_presets, delta_ui, delta, dismiss, field_label_plurals, flag_lists, hidden_comment, linkit_picker, linkit_views, magic, memcache_status, metatag_facebook, metatag_opengraph, omega_tools, simplenews_rules, trigger, user_picture_field, back_to_top, job_scheduler, varnish_status, print, actions_permissions, ds, references, node_reference, noderefcreate, variable_email, rh_taxonomy, autofloat, rdf

drush dis entityreference_migration -y

if [ $(hostname) == 'portatilinux' ];
then
    drush dis cdn, smtp entitycache, varnish, memcache_storage -y
    drush vset eu_cookie_compliance_domain '' -y
fi

drush cc all
drush fl
