# Overview

Classy paragraphs ships a new field type "Class list" which allows an editor to apply a selected class to paragraphs via a drop-down list. Site builders can add this functionality by creating a custom "Class list" field. Currently, classes can only be  added by implementing the `hook_classy_paragraph_list_options` hook.

# Installation

- Enable Classy paragraphs
- Add "Class list" field to desired paragraph type
- Defines classes by implementing the the `hook_classy_paragraph_list_options` hook.

## How It Works

This module allows an editor to select a class, via a drop-down list, which is added to the paragraph template.

The class is added to the template via the `classy_paragraphs_preprocess_entity` preprocess function. In this function we use `classy_paragraphs_get_class` to pull out the selected class from the paragraph_item entity. Once we have a class, then we add it to the template using `$variables['classes_array']`.

# Requirements

- Paragraphs