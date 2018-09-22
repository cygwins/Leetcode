/*
 * recursive match first char in string
 */
#include <string>
#include "catch.hpp"
using std::string;

class Solution {
public:
    bool isMatch(string s, string p) {
        if( p.empty() ) return s.empty();
        bool firstMatch = !s.empty() && ( s[0] == p[0] || p[0] == '.' );
        if( p.size() > 1 && p[1] == '*' )
            return ( firstMatch && isMatch( s.substr(1), p ) ) || 
                   isMatch( s, p.substr(2) ); // match 0
        else
            return firstMatch && isMatch( s.substr(1), p.substr(1) );
    }
};

TEST_CASE("matching", "[isMatch]") {
    Solution s;
    CHECK( s.isMatch( "aa", "a" ) == false );
    CHECK( s.isMatch( "aa", "a*" ) == true );
    CHECK( s.isMatch( "ab", ".*" ) == true );
    CHECK( s.isMatch( "aab", "c*a*b" ) == true );
    CHECK( s.isMatch( "mississippi", "mis*is*p*." ) == false );
}
