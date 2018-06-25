/*
 * recursive
 */
#include <string>
#include "catch.hpp"
using std::string;

class Solution {
public:
    int scoreOfParentheses(string S) {
        if( S.empty() ) return 0;
        if( S == "()" ) return 1;
        int left = 0;
        for( int i = 0; i < S.size(); ++i ) {
            if( S[i] == '(' ) ++left;
            else --left;
            if( left == 0 ) {
                if( i == S.size() - 1 ) return 2 * scoreOfParentheses( S.substr( 1, S.size() - 2 ) );
                else return scoreOfParentheses( S.substr(0, i + 1) ) + scoreOfParentheses( S.substr(i + 1) );
            }
        }
    }
};

TEST_CASE("recursing", "[scoreOfParentheses]") {
    Solution s;
    CHECK(s.scoreOfParentheses("()") == 1 );
    CHECK(s.scoreOfParentheses("(())") == 2 );
    CHECK(s.scoreOfParentheses("()()") == 2 );
    CHECK(s.scoreOfParentheses("(()(()))") == 6 );
    CHECK(s.scoreOfParentheses("(())()") == 3 );
}
