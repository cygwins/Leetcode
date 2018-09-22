/*
 * brief
 */
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
#include "../Tree.hpp"
#include "catch.hpp"
using std::stack;
using std::vector;
using namespace Tree;

static int n = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    return 0;
}();

class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        pushLeft(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s.empty();
    }

    /** @return the next smallest number */
    int next() {
        auto current = s.top();
        s.pop();
        if(current -> right) pushLeft(current -> right);
        return current -> val;
    }
    
    /** push left and left of left and ... */
    void pushLeft(TreeNode *p) {
        while(p) {
            s.push(p);
            p = p -> left;
        }
    }
private:
    stack<TreeNode*> s;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

TEST_CASE("iterating", "[next]") {
    /* Tree: [2,1,4,null,null,3,5]
     *      2
     *    /   \
     *   1     4
     *       /   \
     *      3     5
     */
    vector<int> seq;
    BSTIterator i = BSTIterator(parseTree("[2,1,4,null,null,3,5]"));
    while(i.hasNext()) seq.push_back(i.next());
    CHECK(vector<int>{1,2,3,4,5} == seq);
}
