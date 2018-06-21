/*
 * recursively add legal '(' or ')' to current string
 */
#include <vector>
#include <string>
#include "catch.hpp"
using std::vector;
using std::string;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        add( ans, "", 0, 0, n );
        return ans;
    }
    void add( vector< string > &v, string s, int left, int right, int n ) {
        if( left == n && right == n ) v.push_back( s );
        else {
            if( left < n ) add( v, s + "(", left + 1, right, n );
            if( right < left ) add ( v, s + ")", left, right + 1, n );
        }
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<string> ans1{"((()))","(()())","(())()","()(())","()()()"};
    CHECK( s.generateParenthesis(3) == ans1 ); 
}
