/*
 * Advance pointer for both string and pattern simultaneously.
 * Upon contact with '*', record both pointers and advance only pattern (skip '*'),
 * rewind if not match and continue advancing both.
 * Note: there is no need to record more than one '*', because
 * after skipping '*', there could only be same char "aaa" to match the pattern,
 * if there is "aaab", either not match to rewind or previous '*' is ought to be skipped.
 * "**" is same as single "*", working as ".*" in regular expression.
 * The reason why regex can't use this O(n) method is "a*", so a stack of pointers are required.
 */
#include <iostream>
#include <string>
#include <vector>
#include "catch.hpp"
using std::string;
using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    bool isMatch(string s, string p) {
        int i = 0, j = 0, star = -1, rewind = 0;
        while( i < s.size() ) {
            if( j < p.size() && ( s[i] == p[j] || p[j] == '?' )) { // 1-1 match
                ++i;
                ++j;
            } else if( j < p.size() && p[j] == '*' ) { // record, only advance pattern
                star = j;
                rewind = i;
                ++j;
            } else if( star != -1 ) { // if star is set, j won't >= p.size()
                j = star;
                i = rewind + 1;
            } else return false;
        }
        while( j < p.size() && p[j] == '*' ) ++j; // trailing *
        return j == p.size();
    }
};

TEST_CASE("matching", "[isMatch]") {
    Solution s;
    CHECK( s.isMatch( "aa", "a" ) == false );
    CHECK( s.isMatch( "aa", "*" ) == true );
    CHECK( s.isMatch( "cb", "?a" ) == false );
    CHECK( s.isMatch( "adceb", "*a*b" ) == true );
    CHECK( s.isMatch( "acdcb", "a*c?b" ) == false );
}
