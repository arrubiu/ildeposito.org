<?php
/**
 * @file
 * class WdTaxonomyVocabularyWrapper
 */

class WdTaxonomyVocabularyWrapper extends WdEntityWrapper {

  protected $entity_type = 'taxonomy_vocabulary';

  /**
   * Create a new taxonomy_vocabulary.
   *
   * @param array $values
   * @param string $language
   *
   * @return WdTaxonomyVocabularyWrapper
   */
  public static function create($values = array(), $language = LANGUAGE_NONE) {
    $values += array('entity_type' => 'taxonomy_vocabulary');
    $entity_wrapper = parent::create($values, $language);
    return new WdTaxonomyVocabularyWrapper($entity_wrapper->value());
  }

  /**
   * Retrieves vid
   *
   * @return int
   */
  public function getVid() {
    return $this->getIdentifier();
  }

  /**
   * Retrieves name
   *
   * @return mixed
   */
  public function getName($format = WdEntityWrapper::FORMAT_DEFAULT, $markup_format = NULL) {
    return $this->getText('name', $format, $markup_format);
  }

  /**
   * Sets name
   *
   * @param string $value
   *
   * @return $this
   */
  public function setName($value) {
    $this->set('name', $value);
    return $this;
  }

  /**
   * Retrieves machine_name
   *
   * @return string
   */
  public function getMachineName() {
    return $this->get('machine_name');
  }

  /**
   * Sets machine_name
   *
   * @param string $value
   *
   * @return $this
   */
  public function setMachineName($value) {
    $this->set('machine_name', $value);
    return $this;
  }

  /**
   * Retrieves description
   *
   * @return string
   */
  public function getDescription($format = WdEntityWrapper::FORMAT_DEFAULT, $markup_format = NULL) {
    return $this->getText('description', $format, $markup_format);
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
   * Retrieves term_count
   *
   * @return int
   */
  public function getTermCount() {
    return $this->get('term_count');
  }

}
