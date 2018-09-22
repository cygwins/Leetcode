/*
 * each node can be:
 * 1. in the middle of a univalue path
 * 2. at one end of a univalue path
 * 3. out of the max path
 * note the 3rd case has to be one of the first two cases of some node,
 * so we only need to pass on the 2nd case to accumulate,
 * and update 1st when calculated.
 *
 * in the sub tree of node n,
 * maxEnd = max(leftEnd + 1, rightEnd + 1); (if exist and same val for each branch)
 * maxLen = max(leftMax, rightMax, leftEnd + rightEnd); (if same val for the 3rd)
 *                                 ^
 *                                 only need to update this
 */
#include <algorithm> // max
#include "../Tree.hpp"
#include "catch.hpp"
using std::vector;
using std::max;
using namespace Tree;

class Solution {
public:
    int longestUnivaluePath( TreeNode* root ) {
        if( !root ) return 0;
        maxLen = 0;
        maxEnd( root );
        return maxLen;
    }
    int maxEnd(TreeNode* root) {
        int end = 0, mid = 0;
        if( root -> left ) {
            int left = maxEnd( root -> left );
            if( root -> left -> val == root -> val ) {
                end = left + 1;
                mid += left + 1;
            }
        }
        if( root -> right ) {
            int right = maxEnd( root -> right );
            if( root -> right -> val == root -> val ) {
                end = max( end, right + 1 );
                mid += right + 1;
            }
        }
        maxLen = max(maxLen, mid);
        return end;
    }
private:
    int maxLen;
};

TEST_CASE("traversing", "[longestUnivaluePath]") {
    Solution s;
    
    // through root
    CHECK(s.longestUnivaluePath(parseTree("[5,4,5,1,1,5]")) == 2);

    // without root
    CHECK(s.longestUnivaluePath(parseTree("[1,4,5,4,4,5]")) == 2);

    // without root, root has same child
    CHECK(s.longestUnivaluePath(parseTree("[1,4,1,4,4,5]")) == 2);

    // 'Y' shape
    CHECK(s.longestUnivaluePath(parseTree("[1,1,2,1,1,2]")) == 2);

    // all diff
    CHECK(s.longestUnivaluePath(parseTree("[1,2,3,4,5,6]")) == 0);
}
