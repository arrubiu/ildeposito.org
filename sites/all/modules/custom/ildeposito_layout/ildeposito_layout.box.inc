<?php
/**
 * @file
 * ildeposito_layout.box.inc
 */

/**
 * Implements hook_default_box().
 */
function ildeposito_layout_default_box() {
  $export = array();

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'box_contatti';
  $box->plugin_key = 'simple';
  $box->title = '';
  $box->description = 'Box Contatti';
  $box->options = array(
    'body' => array(
      'value' => '<p>Per contattarci potete usare i seguenti modi:</p>

<ul>
	<li>mandare un\'email all\'indirizzo &nbsp;<strong>info _at_ ildeposito.org</strong></li>
	<li>utilizzare il nostro account <a href="http://www.facebook.com/ildeposito.org">Facebook</a></li>
	<li>utilizzare il nostro account <a href="http://twitter.com/ildeposito">Twitter</a></li>
	<li>utilizzare il nostro account <a href="https://plus.google.com/u/0/113629455468042353975/">Google+</a></li>
</ul>

<p>In alternativa potete utilizzare il seguente modulo di contatto.</p>
',
      'format' => 'full_html',
    ),
    'additional_classes' => '',
  );
  $export['box_contatti'] = $box;

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'footer_left';
  $box->plugin_key = 'simple';
  $box->title = '';
  $box->description = 'Footer Left';
  $box->options = array(
    'body' => array(
      'value' => '<p>ilDeposito.org - archivio online dal 4 ottobre 2004, Ideato e realizzato da Sergio Durzu con la collaborazione dello staff de ilDeposito<br />
Per informazione e contatti visitare la pagina <a href="contatti">Contatti</a> | <a href="https://https://plus.google.com/u/0/b/113629455468042353975?
   rel=author">di ilDeposito.org</a></p>

<p>Sito realizzato e gestito con <a href="informazioni/informazioni-tecniche">Software Libero</a> - <a href="informazioni">Licenze, disclaimer e condizioni d\'uso</a></p>
',
      'format' => 'full_html',
    ),
    'additional_classes' => '',
  );
  $export['footer_left'] = $box;

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'footer_right';
  $box->plugin_key = 'simple';
  $box->title = '';
  $box->description = 'Footer Right';
  $box->options = array(
    'body' => array(
      'value' => 'Credits | Info e contatti<br />
Tecnicaglie',
      'format' => 'filtered_html',
    ),
    'additional_classes' => '',
  );
  $export['footer_right'] = $box;

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'social_top';
  $box->plugin_key = 'simple';
  $box->title = '';
  $box->description = 'Social TOP';
  $box->options = array(
    'body' => array(
      'value' => '<p><a href="http://twitter.com/ildeposito"><img alt="Twitter" class="file-only-image media-element" src="http://www.ildeposito.org/sites/default/files/twitter.png" style="height:36px; width:36px" title="Seguici su Twitter!" /></a><a href="https://www.facebook.com/ildeposito.org"><img alt="Facebook" class="file-only-image media-element" src="http://www.ildeposito.org/sites/default/files/facebook.png" style="height:36px; width:36px" title="Seguici su Facebook!" /></a><a href="http://www.youtube.com/ildeposito"><img alt="YouTube" class="file-only-image media-element" src="http://www.ildeposito.org/sites/default/files/youtube.png" style="height:36px; width:36px" title="Segui il nostro canale di YouTube!" /></a><a href="http://www.ildeposito.org/contatti"><img alt="Mail" class="file-only-image media-element" src="http://www.ildeposito.org/sites/default/files/mail.png" style="height:36px; width:36px" title="Contattaci!" /></a><a href="http://www.ildeposito.org/rss.xml"><img alt="Feed RSS" class="file-only-image media-element" src="http://www.ildeposito.org/sites/default/files/rss.png" style="height:36px; width:36px" title="Iscriviti ai Feed RSS" /></a></p>
',
      'format' => 'full_html',
    ),
    'additional_classes' => '',
  );
  $export['social_top'] = $box;

  $box = new stdClass();
  $box->disabled = FALSE; /* Edit this to true to make a default box disabled initially */
  $box->api_version = 1;
  $box->delta = 'storiacantata_icone';
  $box->plugin_key = 'simple';
  $box->title = '';
  $box->description = 'Storia cantata - Icone';
  $box->options = array(
    'body' => array(
      'value' => '<div id="storiacantata"><div class="grid-9 ildeposito-col odd"><a href="archivio/storiacantata/percorsi">Percorsi</a><p>Gli eventi della Storia Cantata permettono di proporre e ricreare dei percorsi, trasversali rispetto ai periodi storici. Un modo per tracciare collegamenti tra eventi, epoche e canti.</p></div><div class="grid-9 ildeposito-col even"><a href="archivio/storiacantata/mappa">Mappa</a><p>Ogni evento, oltre la data, ha anche una localizzazione. Tramite questa mappa potrete navigare tra tutti gli eventi della Storia Cantata, per ricostruire la storia di singoli paesi o territori.</p></div><div class="grid-9 ildeposito-col odd"><a href="archivio/storiacantata/calendario">Calendario</a><p>Il Calendario Cantato propone gli eventi con visualizzazioni annuali o mensili, un modo per non dimenticare nessun anniversario o ricorrenza, uno dei modi migliori per riproporre gli eventi.</p></div><div class="grid-9 ildeposito-col even"><a href="archivio/storiacantata/linea-del-tempo">Linea del Tempo</a><p>Una linea del tempo multimediale, interattiva, che riproduce l\'andamento stesso della storia, con le sue sovrapposizioni di temi, tempi e luoghi.</p></div><div class="grid-9 ildeposito-col odd"><a href="archivio/storiacantata/elenco">Elenco</a><p>Il "classico" elenco di eventi, ordinati in ordine cronologico e filtrabili in base alle categorie presenti nell\'archivio. Uno strumento classico di consultazione di contenuti.</p></div><div class="grid-9 ildeposito-col even">&nbsp;</div></div>',
      'format' => 'full_html',
    ),
    'additional_classes' => '',
  );
  $export['storiacantata_icone'] = $box;

  return $export;
}
