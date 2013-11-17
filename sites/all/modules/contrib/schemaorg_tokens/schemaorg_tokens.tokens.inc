<?php

/**
 * @file
 * Token callbacks for the schemaorg_tokens module.
 */

/**
 * Implements hook_token_info().
 *
 * @ingroup schemaorg_tokens
 */
function schemaorg_tokens_token_info() {

  // Node tokens.
  $info['tokens']['node']['schemaorg-image'] = array(
      'name' => t('Image'),
      'description' => t("URL of an image of the node."),
  );
  $info['tokens']['node']['schemaorg-image-2'] = array(
      'name' => t('Image2'),
      'description' => t("URL of the second image of the node."),
  );
  $info['tokens']['node']['schemaorg-image-all'] = array(
      'name' => t('All Images'),
      'description' => t("Coma seperated URL's of all images of the node."),
  );
  $info['tokens']['node']['schemaorg-description'] = array(
      'name' => t('Description'),
      'description' => t("A short description of the node."),
  );
  $info['tokens']['node']['schemaorg-url'] = array(
      'name' => t('URL'),
      'description' => t("URL in the node."),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 *
 * @ingroup schemaorg_tokens
 */
function schemaorg_tokens_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  $sanitize = !empty($options['sanitize']);

  // Node tokens.
  if ($type == 'node' && !empty($data['node'])) {
    $node = $data['node'];
    // Extracts relevant values from the product entity using Entity API wrapper.
    if(isset(entity_metadata_wrapper('node', $node)->field_product)){
      $commerce_price = entity_metadata_wrapper('node', $node)->field_product[0]->commerce_price->value();
      $commerce_image = entity_metadata_wrapper('node', $node)->field_product[0]->field_images->value();
      if(!empty($commerce_image)){
        $uri = $commerce_image[0]['uri'];
        $output = file_create_url($uri);
        if(isset($tokens['schemaorg-image'])){
          $replacements[$tokens['schemaorg-image']] = $sanitize ? filter_xss($output) : $output;
        }
        $uri = $commerce_image[1]['uri'];
        $output = file_create_url($uri);
        if(isset($tokens['schemaorg-image-2'])){
          $replacements[$tokens['schemaorg-image-2']] = $sanitize ? filter_xss($output) : $output;
        }
        $output = "";
        foreach ($commerce_image as $file_value) {
          $uri = $file_value['uri'];
          $output .= ",".file_create_url($uri);
        }
        $output = trim($output, ",");
        if(isset($tokens['schemaorg-image-all'])){
          $replacements[$tokens['schemaorg-image-all']] = $sanitize ? filter_xss($output) : $output;
        }
      }
    }
    $mapping = rdf_mapping_load("node", $node->type);
    foreach ($mapping as $field_key => $schema_value) {
      if(isset($schema_value['predicates']) && isset($schema_value['predicates'][0])){
        switch ($schema_value['predicates'][0]){
          case 'schema:image':
            if(isset($node->{$field_key}[$node->language])){
              $field_image = $node->{$field_key}[$node->language];
            }else{
              $field_image = $node->{$field_key}['und'];
            }
            if(isset($field_image[0]['uri'])){
              $uri = $field_image[0]['uri'];
              $output = file_create_url($uri);
              if(isset($tokens['schemaorg-image'])){
                $replacements[$tokens['schemaorg-image']] = $sanitize ? filter_xss($output) : $output;
              }
            }

            if(isset($field_image[1])){
              if(isset($field_image[1]['uri'])){
                $uri = $field_image[1]['uri'];
                $output = file_create_url($uri);
                if(isset($tokens['schemaorg-image-2'])){
                  $replacements[$tokens['schemaorg-image-2']] = $sanitize ? filter_xss($output) : $output;
                }
              }
            }

            $output = "";
            foreach ($field_image as $file_value) {
              if(isset($file_value['uri'])){
                $uri = $file_value['uri'];
                $output .= ",".file_create_url($uri);
              }
            }
            $output = trim($output, ",");
            if(isset($tokens['schemaorg-image-all'])){
              $replacements[$tokens['schemaorg-image-all']] = $sanitize ? filter_xss($output) : $output;
            }
            break;
          case 'schema:summary':
            if(isset($node->{$field_key}[$node->language])){
              $output = $node->{$field_key}[$node->language][0]['value'];
            }else{
              $output = $node->{$field_key}['und'][0]['value'];
            }
            if(isset($tokens['schemaorg-description'])){
              $replacements[$tokens['schemaorg-description']] = $sanitize ? filter_xss($output) : $output;
            }
            break;
          case 'schema:url':
            if(isset($node->{$field_key})){
              if(isset($node->{$field_key}[$node->language])){
                $output = $node->{$field_key}[$node->language][0]['url'];
              }else{
                $output = $node->{$field_key}['und'][0]['url'];
              }
            }
            if(empty($output)){
              $output = url("node/".$node->nid, array('absolute' => true));
            }
            if(isset($tokens['schemaorg-url'])){
              $replacements[$tokens['schemaorg-url']] = $sanitize ? filter_xss($output) : $output;
            }
            break;


        }
      }
    }
  }

  return $replacements;
}
