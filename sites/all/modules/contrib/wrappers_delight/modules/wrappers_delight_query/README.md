# Wrappers Delight Query Wrappers

This module provides wrappers around EntityFieldQuery that are entity 
and bundle specific.

## Examples

The entity-specific query wrappers can be used like this:

$results = WdNodeWrapperQuery::find()
            ->byAuthor(1)
            ->execute();
$user_node_links = array();
foreach ($results as $record) {
  $user_node_links[] = l($record->getTitle(), 'node/' . $record->getNid());
}

After enabling this module, calling "drush wrap ENTITY_TYPE" will generate
bundle query classes as well as a wrapper classes. With a bundle class, you
can query like this:

$results = ArticleNodeWrapperQuery::find()
            ->byCustomField("some_value")
            ->execute();

The query wrapper supports chaining and overriding the operator, so you can 
also do something like this:

$results = WdNodeWrapperQuery::find()
            ->byAuthor(1)
            ->byTitle('%Test%', 'LIKE')
            ->execute();


It supports order and range modifiers. 

$results = WdNodeWrapperQuery::find()
            ->byAuthor(1)
            ->orderByTitle('DESC')
            ->range(0, 10)
            ->execute();


It supports fields and their value columns using dot syntax:

$results = WdCommerceLineItemWrapperQuery::find()
            ->byUnitPrice(10000, 'USD', '>')
            ->orderByField('commerce_unit_price.amount', 'DESC')
            ->execute();


The drush command will generate orderBy() methods for every field in your bundle,
so the query above can be rewritten as:

$results = WdCommerceLineItemWrapperQuery::find()
            ->byUnitPrice(10000, 'USD', '>')
            ->orderByCommerceUnitPriceAmount('DESC')
            ->execute();
