#!/bin/bash
drush sql-drop -y && \
drush sql-sync @ildeposito.prod @ildeposito.local -y && \
drush rr
drush  updb -y && \
drush dis smtp -y && \
drush en entityreference_migration -y && \
drush emr && \
drush dis -y emptyparagraphkiller, htmlpurifier, checklistapi, oauth_common, rss_category, rss_enclosure, site_verify, services, uuid_path, feeds*, ds*, forum, custom_formatters, better_revisions, backup_migrate_dropbox, backup_migrate_sftp, blockcache_alter, block_class,  commitlog, versioncontrol, git_status, versioncontrol_git, date_facets, date_repeat_presets, delta_ui, delta, dismiss, field_label_plurals, flag_lists, hidden_comment, linkit_picker, linkit_views, magic, memcache_status, metatag_facebook, metatag_opengraph, omega_tools, simplenews_rules, trigger, user_picture_field, back_to_top, job_scheduler


