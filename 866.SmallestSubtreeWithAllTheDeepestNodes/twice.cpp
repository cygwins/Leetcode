/*
 * map TreeNode to depth of subtree,
 * return first one that has 2 children of same max depth
 */
#include <iostream> // max
#include <algorithm> // max
#include <map>
#include "../Tree.hpp" // parseTree & printTree
#include "catch.hpp"
using std::vector;
using std::max;
using std::map;

class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if( ! root ) return NULL;
        nodeDepth.clear();
        nodeDepth[NULL] = 0;
        getDepth( root ); // traverse through the tree to get depth of each node
        TreeNode* ans = root;
        while( nodeDepth[ans -> left] != nodeDepth[ans -> right] ) {
            // if( ans ) std::cout << "now: " << ans -> val << std::endl;
            if( nodeDepth[ans -> left] > nodeDepth[ans-> right] ) {
                ans = ans -> left;
            } else if ( nodeDepth[ans -> left] < nodeDepth[ans-> right] ) {
                ans = ans -> right;
            }
        }
        return ans;
    }
    int getDepth(TreeNode* root) {
        if( ! root ) return 0;
        int d = max(getDepth(root -> left), getDepth(root -> right)) + 1;
        nodeDepth[root] = d;
        // std::cout << root -> val << " -- " << d << std::endl;
        return d;
    }
private:
    map<TreeNode*, int> nodeDepth;
};

TEST_CASE("traversing", "[subtreeWithAllDeepest]") {
    Solution s;
    CHECK( printTree( s.subtreeWithAllDeepest( parseTree("[3,5,1,6,2,0,8,null,null,7,4]")))
            == "[2,7,4]");

    // test my Tree parser & printer
    CHECK(printTree(parseTree("[1,null,2,null,3]")) == "[1,null,2,null,3]");
}
