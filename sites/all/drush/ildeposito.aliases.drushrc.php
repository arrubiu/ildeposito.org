<?php

$aliases['prod'] = array(
  'uri' => 'www.ildeposito.org', // indirizzo a cui risponde il sito (senza http://)
  'root' => '/home/sergej/websites/ildeposito.org/code', // path delle directory dell'applicazione
  'db-url' => 'mysql://ildepositodrupal:p4ssUOrdArs3n4l3@localhost/ildepositodrupal', // dati di connessione del database
  'remote-host' => 'ildeposito.org',  // per l'alias locale non è necessario
  'remote-user' => 'sergej',  // per l'alias locale non è necessario
  'path-aliases' => array(
    //'%drush' => '/usr/local/lib/drush/', // path alla directory di installazione di drush
    //'%drush-script' => '/usr/local/lib/drush/drush.php', // path all'eseguibile di drush
    '%dump-dir' => '/home/sergej/websites/ildeposito.org/drush-backup', // path della directory dove vengono salvati i dump di sql-sync
    '%files' => 'sites/default/files', // path della directory dei file "pubblici"
    '%features' => 'sites/all/modules/developer/features', // path delle features
    '%mod_develop' => 'sites/all/modules/developer/modules', // path dei moduli sviluppati
    '%mod_contrib' => 'sites/all/modules/contrib', // path dei moduli scaricati da drupal.org
    '%libraries' => 'sites/all/libraries', // path delle librerie
    '%themes' => 'sites/all/themes',  // path dei temi
  ),
  
  'command-specific' => array (
    'sql-sync' => array (
      'no-cache' => TRUE,
    ),
  ),
);
 
?>
