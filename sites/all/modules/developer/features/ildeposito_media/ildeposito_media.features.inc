<?php
/**
 * @file
 * ildeposito_media.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ildeposito_media_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "breakpoints" && $api == "default_breakpoint_group") {
    return array("version" => "1");
  }
  if ($module == "breakpoints" && $api == "default_breakpoints") {
    return array("version" => "1");
  }
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_type") {
    return array("version" => "1");
  }
  if ($module == "flexslider" && $api == "flexslider_default_preset") {
    return array("version" => "1");
  }
  if ($module == "picture" && $api == "default_picture_mapping") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function ildeposito_media_image_default_styles() {
  $styles = array();

  // Exported image style: articolo.
  $styles['articolo'] = array(
    'name' => 'articolo',
    'label' => 'articolo',
    'effects' => array(
      25 => array(
        'label' => 'Scala',
        'help' => 'La trasformazione in scala mantiene il rapporto delle dimensioni dell\'immagine originale. Se viene impostata una sola dimensione, l\'altra sarà calcolata di conseguenza.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 220,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: articolo_home.
  $styles['articolo_home'] = array(
    'name' => 'articolo_home',
    'label' => 'articolo_home',
    'effects' => array(
      32 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 100,
          'height' => 80,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: elenco_termine.
  $styles['elenco_termine'] = array(
    'name' => 'elenco_termine',
    'label' => 'elenco_termine',
    'effects' => array(
      3 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 150,
          'height' => 110,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: foto_autore.
  $styles['foto_autore'] = array(
    'name' => 'foto_autore',
    'label' => 'Foto autore',
    'effects' => array(
      1 => array(
        'label' => 'Javascript crop',
        'help' => 'Create a crop with a javascript toolbox.',
        'effect callback' => 'imagecrop_effect',
        'form callback' => 'imagecrop_effect_form',
        'summary theme' => 'imagecrop_effect_summary',
        'module' => 'imagecrop',
        'name' => 'imagecrop_javascript',
        'data' => array(
          'width' => 90,
          'height' => 90,
          'xoffset' => 'center',
          'yoffset' => 'center',
          'resizable' => 0,
          'downscaling' => 0,
          'aspect_ratio' => '',
          'disable_if_no_data' => 1,
        ),
        'weight' => 1,
      ),
      2 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 90,
          'height' => 90,
        ),
        'weight' => 2,
      ),
      3 => array(
        'label' => 'Desatura',
        'help' => 'Desatura converte un\'immagine in scala di grigi',
        'effect callback' => 'image_desaturate_effect',
        'dimensions passthrough' => TRUE,
        'module' => 'image',
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => 3,
      ),
    ),
  );

  // Exported image style: intestazione.
  $styles['intestazione'] = array(
    'name' => 'intestazione',
    'label' => 'intestazione',
    'effects' => array(
      1 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1180,
          'height' => 120,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: resp_articolobreakpoints_theme_ildeposito_mobile_1x.
  $styles['resp_articolobreakpoints_theme_ildeposito_mobile_1x'] = array(
    'name' => 'resp_articolobreakpoints_theme_ildeposito_mobile_1x',
    'label' => 'resp_articolobreakpoints_theme_ildeposito_mobile_1x',
    'effects' => array(
      26 => array(
        'label' => 'Scala',
        'help' => 'La trasformazione in scala mantiene il rapporto delle dimensioni dell\'immagine originale. Se viene impostata una sola dimensione, l\'altra sarà calcolata di conseguenza.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 150,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: resp_articolobreakpoints_theme_ildeposito_narrow_1x.
  $styles['resp_articolobreakpoints_theme_ildeposito_narrow_1x'] = array(
    'name' => 'resp_articolobreakpoints_theme_ildeposito_narrow_1x',
    'label' => 'resp_articolobreakpoints_theme_ildeposito_narrow_1x',
    'effects' => array(
      27 => array(
        'label' => 'Scala',
        'help' => 'La trasformazione in scala mantiene il rapporto delle dimensioni dell\'immagine originale. Se viene impostata una sola dimensione, l\'altra sarà calcolata di conseguenza.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 120,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: resp_articolobreakpoints_theme_ildeposito_normal_1x.
  $styles['resp_articolobreakpoints_theme_ildeposito_normal_1x'] = array(
    'name' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
    'label' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
    'effects' => array(
      28 => array(
        'label' => 'Scala',
        'help' => 'La trasformazione in scala mantiene il rapporto delle dimensioni dell\'immagine originale. Se viene impostata una sola dimensione, l\'altra sarà calcolata di conseguenza.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 180,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: resp_articolobreakpoints_theme_ildeposito_tv_1x.
  $styles['resp_articolobreakpoints_theme_ildeposito_tv_1x'] = array(
    'name' => 'resp_articolobreakpoints_theme_ildeposito_tv_1x',
    'label' => 'resp_articolobreakpoints_theme_ildeposito_tv_1x',
    'effects' => array(
      29 => array(
        'label' => 'Scala',
        'help' => 'La trasformazione in scala mantiene il rapporto delle dimensioni dell\'immagine originale. Se viene impostata una sola dimensione, l\'altra sarà calcolata di conseguenza.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 220,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: respbreakpoints_theme_ildeposito_mobile_1x.
  $styles['respbreakpoints_theme_ildeposito_mobile_1x'] = array(
    'name' => 'respbreakpoints_theme_ildeposito_mobile_1x',
    'label' => 'respbreakpoints_theme_ildeposito_mobile_1x',
    'effects' => array(
      20 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 10,
          'height' => 10,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: respbreakpoints_theme_ildeposito_narrow_1x.
  $styles['respbreakpoints_theme_ildeposito_narrow_1x'] = array(
    'name' => 'respbreakpoints_theme_ildeposito_narrow_1x',
    'label' => 'respbreakpoints_theme_ildeposito_narrow_1x',
    'effects' => array(
      21 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 700,
          'height' => 80,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: respbreakpoints_theme_ildeposito_normal_1x.
  $styles['respbreakpoints_theme_ildeposito_normal_1x'] = array(
    'name' => 'respbreakpoints_theme_ildeposito_normal_1x',
    'label' => 'respbreakpoints_theme_ildeposito_normal_1x',
    'effects' => array(
      22 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 940,
          'height' => 100,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: respbreakpoints_theme_ildeposito_tv_1x.
  $styles['respbreakpoints_theme_ildeposito_tv_1x'] = array(
    'name' => 'respbreakpoints_theme_ildeposito_tv_1x',
    'label' => 'respbreakpoints_theme_ildeposito_tv_1x',
    'effects' => array(
      23 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1180,
          'height' => 120,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: ricerca.
  $styles['ricerca'] = array(
    'name' => 'ricerca',
    'label' => 'Ricerca',
    'effects' => array(
      4 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 50,
          'height' => 50,
        ),
        'weight' => 1,
      ),
      5 => array(
        'label' => 'Desatura',
        'help' => 'Desatura converte un\'immagine in scala di grigi',
        'effect callback' => 'image_desaturate_effect',
        'dimensions passthrough' => TRUE,
        'module' => 'image',
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: sezioni_homebreakpoints_theme_ildeposito_mobile_1x.
  $styles['sezioni_homebreakpoints_theme_ildeposito_mobile_1x'] = array(
    'name' => 'sezioni_homebreakpoints_theme_ildeposito_mobile_1x',
    'label' => 'sezioni_homebreakpoints_theme_ildeposito_mobile_1x',
    'effects' => array(
      41 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 700,
          'height' => 160,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: sezioni_homebreakpoints_theme_ildeposito_narrow_1x.
  $styles['sezioni_homebreakpoints_theme_ildeposito_narrow_1x'] = array(
    'name' => 'sezioni_homebreakpoints_theme_ildeposito_narrow_1x',
    'label' => 'sezioni_homebreakpoints_theme_ildeposito_narrow_1x',
    'effects' => array(
      39 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 340,
          'height' => 160,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: sezioni_homebreakpoints_theme_ildeposito_normal_1x.
  $styles['sezioni_homebreakpoints_theme_ildeposito_normal_1x'] = array(
    'name' => 'sezioni_homebreakpoints_theme_ildeposito_normal_1x',
    'label' => 'sezioni_homebreakpoints_theme_ildeposito_normal_1x',
    'effects' => array(
      38 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 460,
          'height' => 160,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: sezioni_homebreakpoints_theme_ildeposito_tv_1x.
  $styles['sezioni_homebreakpoints_theme_ildeposito_tv_1x'] = array(
    'name' => 'sezioni_homebreakpoints_theme_ildeposito_tv_1x',
    'label' => 'sezioni_homebreakpoints_theme_ildeposito_tv_1x',
    'effects' => array(
      37 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 580,
          'height' => 160,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: termine_singolo.
  $styles['termine_singolo'] = array(
    'name' => 'termine_singolo',
    'label' => 'termine_singolo',
    'effects' => array(
      5 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 260,
          'height' => 160,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: utente_profile.
  $styles['utente_profile'] = array(
    'name' => 'utente_profile',
    'label' => 'utente_profile',
    'effects' => array(
      42 => array(
        'label' => 'Javascript crop',
        'help' => 'Create a crop with a javascript toolbox.',
        'effect callback' => 'imagecrop_effect',
        'form callback' => 'imagecrop_effect_form',
        'summary theme' => 'imagecrop_effect_summary',
        'module' => 'imagecrop',
        'name' => 'imagecrop_javascript',
        'data' => array(
          'width' => 100,
          'height' => 100,
          'xoffset' => 'center',
          'yoffset' => 'center',
          'resizable' => 0,
          'downscaling' => 0,
          'aspect_ratio' => '',
          'disable_if_no_data' => 0,
        ),
        'weight' => -10,
      ),
    ),
  );

  // Exported image style: utente_thumb.
  $styles['utente_thumb'] = array(
    'name' => 'utente_thumb',
    'label' => 'utente_thumb',
    'effects' => array(
      24 => array(
        'label' => 'Scala e ritaglia',
        'help' => 'Scala e ritaglia preserva il rapporto di dimensioni dell\'immagine originale per poi ritagliare la dimensione in eccesso. Questo metodo è utile nei casi in cui si desidera ottenere delle miniature perfettamente quadrate senza deformare l\'immagine.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 40,
          'height' => 40,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
