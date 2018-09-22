/*
 * test data structure: tree, list
 */
#include "Tree.hpp"
#include "List.hpp"
#include "catch.hpp"
TEST_CASE("testing", "[data structure]") {
    // Tree
    CHECK(Tree::parseTree("") == NULL);
    CHECK(Tree::printTree(Tree::parseTree("[1,null,2,null,3]")) == "[1,null,2,null,3]");

    // List
    CHECK(List::parseList("") == NULL);
    CHECK(List::printList(List::parseList("1->2->3")) == "1->2->3");
}
