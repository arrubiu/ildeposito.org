<?php
/**
 * @file
 * class WdTaxonomyTermWrapper
 */

class WdTaxonomyTermWrapper extends WdEntityWrapper {

  protected $entity_type = 'taxonomy_term';

  /**
   * Create a new taxonomy_term.
   *
   * @param array $values
   * @param string $language
   *
   * @return WdTaxonomyTermWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $vocabulary = taxonomy_vocabulary_machine_name_load($values['bundle']);
    $values += array(
      'entity_type' => 'taxonomy_term',
      'vocabulary_machine_name' => $values['bundle'],
      'vid' => $vocabulary->vid,
    );
    $entity_wrapper = parent::create($values, $language);
    return new WdTaxonomyTermWrapper($entity_wrapper->value());
  }

  /**
   * Retrieves tid
   *
   * @return int
   */
  public function getTid() {
    return $this->getIdentifier();
  }

  /**
   * Retrieves name
   *
   * @return string
   */
  public function getName($format = WdEntityWrapper::FORMAT_DEFAULT, $markup_format = NULL) {
    return $this->getText('name', $format, $markup_format);
  }

  /**
   * Sets name
   *
   * @param mixed $value
   *
   * @return $this
   */
  public function setName($value) {
    $this->set('name', $value);
    return $this;
  }

  /**
   * Retrieves description
   *
   * @return string
   */
  public function getDescription($format = WdEntityWrapper::FORMAT_DEFAULT, $markup_format = NULL) {
    $term = $this->value();
    $default_format = $term->format;
    if ($format == WdEntityWrapper::FORMAT_DEFAULT) {
      return check_markup($term->description, $default_format);
    }
    elseif ($format == WdEntityWrapper::FORMAT_RAW) {
      return $term->description;
    }
    elseif ($format == WdEntityWrapper::FORMAT_PLAIN) {
      return check_plain($term->description);
    }
    elseif ($format == WdEntityWrapper::FORMAT_MARKUP) {
      return check_markup($term->description, $markup_format);
    }
    return $this->get('description');
  }

  /**
   * Sets description
   *
   * @param string $value
   *
   * @return $this
   */
  public function setDescription($value) {
    $this->set('description', $value);
    return $this;
  }

  /**
   * Retrieves weight
   *
   * @return int
   */
  public function getWeight() {
    return $this->get('weight');
  }

  /**
   * Sets weight
   *
   * @param int $value
   *
   * @return $this
   */
  public function setWeight($value) {
    $this->set('weight', $value);
    return $this;
  }

  /**
   * Retrieves node_count
   *
   * @return int
   */
  public function getNodeCount() {
    return $this->get('node_count');
  }

  /**
   * Retrieves url
   *
   * @return string
   */
  public function getUrl() {
    return $this->get('url');
  }

  /**
   * Retrieves vocabulary
   *
   * @return WdTaxonomyVocabularyWrapper
   */
  public function getVocabulary() {
    $value = $this->get('vocabulary');
    if (!empty($value)) {
      return new WdTaxonomyVocabularyWrapper($value);
    }
    return NULL;
  }

  /**
   * Sets vocabulary
   *
   * @param int|object|WdTaxonomyVocabularyWrapper $value
   *
   * @return $this
   */
  public function setVocabulary($value) {
    if ($value instanceof WdEntityWrapper) {
      $value = $value->value();
    }
    $this->set('vocabulary', $value);
    return $this;
  }

  /**
   * Retrieves parent
   *
   * @return WdTaxonomyTermWrapper[]
   */
  public function getParent() {
    $items = array();
    $values = $this->get('parent');
    if (!empty($values)) {
      foreach ($values as $value) {
        $items[] = new WdTaxonomyTermWrapper($value);
      }
    }
    return $items;
  }

  /**
   * Sets parent
   *
   * @param array|WdTaxonomyTermWrapper[] $values
   *
   * @return $this
   */
  public function setParent($values) {
    if (!empty($values)) {
      foreach ($values as $i => $value) {
        if ($value instanceof WdEntityWrapper) {
          $values[$i] = $value->value();
        }
      }
    }
    $this->set('parent', $values);
    return $this;
  }

  /**
   * Retrieves parents_all
   *
   * @return WdTaxonomyTermWrapper[]
   */
  public function getParentsAll() {
    $items = array();
    $values = $this->get('parents_all');
    if (!empty($values)) {
      foreach ($values as $value) {
        $items[] = new WdTaxonomyTermWrapper($value);
      }
    }
    return $items;
  }

}
