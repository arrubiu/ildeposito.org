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
    return array("version" => "2");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function ildeposito_media_image_default_styles() {
  $styles = array();

  // Exported image style: articolo.
  $styles['articolo'] = array(
    'label' => 'articolo',
    'effects' => array(
      25 => array(
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
    'label' => 'articolo_home',
    'effects' => array(
      8 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 100,
          'height' => 100,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: elenco_termine.
  $styles['elenco_termine'] = array(
    'label' => 'elenco_termine',
    'effects' => array(
      3 => array(
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
    'label' => 'Foto autore',
    'effects' => array(
      1 => array(
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
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 90,
          'height' => 90,
        ),
        'weight' => 2,
      ),
      3 => array(
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => 3,
      ),
    ),
  );

  // Exported image style: intestazione.
  $styles['intestazione'] = array(
    'label' => 'intestazione',
    'effects' => array(
      1 => array(
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
    'label' => 'resp_articolobreakpoints_theme_ildeposito_mobile_1x',
    'effects' => array(
      26 => array(
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
    'label' => 'resp_articolobreakpoints_theme_ildeposito_narrow_1x',
    'effects' => array(
      27 => array(
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
    'label' => 'resp_articolobreakpoints_theme_ildeposito_normal_1x',
    'effects' => array(
      28 => array(
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
    'label' => 'resp_articolobreakpoints_theme_ildeposito_tv_1x',
    'effects' => array(
      29 => array(
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
    'label' => 'respbreakpoints_theme_ildeposito_mobile_1x',
    'effects' => array(
      20 => array(
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
    'label' => 'respbreakpoints_theme_ildeposito_narrow_1x',
    'effects' => array(
      21 => array(
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
    'label' => 'respbreakpoints_theme_ildeposito_normal_1x',
    'effects' => array(
      22 => array(
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
    'label' => 'respbreakpoints_theme_ildeposito_tv_1x',
    'effects' => array(
      23 => array(
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
    'label' => 'Ricerca',
    'effects' => array(
      6 => array(
        'name' => 'imagecrop_javascript',
        'data' => array(
          'width' => 50,
          'height' => 50,
          'xoffset' => 'center',
          'yoffset' => 'center',
          'resizable' => 0,
          'downscaling' => 0,
          'aspect_ratio' => '',
          'disable_if_no_data' => 1,
        ),
        'weight' => -10,
      ),
      4 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 50,
          'height' => 50,
        ),
        'weight' => -9,
      ),
      5 => array(
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => -8,
      ),
    ),
  );

  // Exported image style: sezioni_homebreakpoints_theme_ildeposito_mobile_1x.
  $styles['sezioni_homebreakpoints_theme_ildeposito_mobile_1x'] = array(
    'label' => 'sezioni_homebreakpoints_theme_ildeposito_mobile_1x',
    'effects' => array(
      41 => array(
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
    'label' => 'sezioni_homebreakpoints_theme_ildeposito_narrow_1x',
    'effects' => array(
      39 => array(
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
    'label' => 'sezioni_homebreakpoints_theme_ildeposito_normal_1x',
    'effects' => array(
      38 => array(
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
    'label' => 'sezioni_homebreakpoints_theme_ildeposito_tv_1x',
    'effects' => array(
      37 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 580,
          'height' => 160,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: square_thumbnail.
  $styles['square_thumbnail'] = array(
    'label' => 'Square thumbnail',
    'effects' => array(
      7 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 100,
          'height' => 100,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: termine_singolo.
  $styles['termine_singolo'] = array(
    'label' => 'termine_singolo',
    'effects' => array(
      5 => array(
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
    'label' => 'utente_profile',
    'effects' => array(
      42 => array(
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
    'label' => 'utente_thumb',
    'effects' => array(
      24 => array(
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
