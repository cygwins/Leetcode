/*
 * each node tell its parent whether it is a valid BST and its range
 */
#include <algorithm> // max
#include "../Tree.hpp"
#include "catch.hpp"
using std::max;
using namespace Tree;

struct Info {
    bool valid; // is a valid BST
    int size;
    Num lowest, highest;
    Info(bool v, int s, Num l, Num h) : valid(v), size(s), lowest(l), highest(h) { }
};

struct Num {
    bool defined;
    int val;
    Num(int n) : defined(true), val(n) { }
    Num() : defined(false) { }
    Num(Num &n) { // copy constructor
        defined = n.defined;
        val = n.val;
    }
};

class Solution {
public:
    int largestBSTSubtree(TreeNode* root) {
        return BSTsize(root).size;
    }
    Info BSTsize(TreeNode* root) {
        if(!root) return Info(true, 0, Num(), Num());
        Info l = BSTsize(root -> left), r = BSTsize(root -> right);
        if(l.valid && r.valid &&
                l.highest.defined && l.highest.val <= root -> val &&
                r.lowest.defined && r.lowest.val >= root -> val)
            return Info(true, 1 + l.size + r.size,
                    l.lowest.defined ? l.lowest.val : root -> val,
                    r.highest.defined ? r.highest.val : root -> val);
        else return Info(false, max(l.size, r.size), Num(), Num());
    }
};

TEST_CASE("checking", "[largestBSTSubtree]") {
    Solution s;
    TreeNode* root = parseTree("[10,5,15,1,8,null,7]");
    CHECK(s.largestBSTSubtree(root) == 3);
}
