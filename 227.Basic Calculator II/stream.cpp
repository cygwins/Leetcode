/*
 * use string stream to deal with the white spaces
 * submit the result of * and/or / when + or - found
 */
#include <sstream>
#include <string>
#include "catch.hpp"
using std::string;
using std::istringstream;

class Solution {
public:
    int calculate(string s) {
        istringstream sin( s );
        int ans = 0, product, tmp;
        char op;
        sin >> product;
        while( sin >> op ) {
            if( op == '+' || op == '-' ) {
                ans += product;
                sin >> product;
                if( op == '-' ) product *= -1;
            } else if( op == '*' || op == '/' ) {
                sin >> tmp;
                if( op == '*' ) product *= tmp;
                else if( op == '/' ) product /= tmp;
            }
        }
        ans += product; // last term
        return ans;
    }
};

TEST_CASE("calculating", "[calculate]") {
    Solution s;
    CHECK( s.calculate( "3+2*2" ) == 7 );
    CHECK( s.calculate( " 3/2 " ) == 1 );
    CHECK( s.calculate( " 3+5 / 2 " ) == 5 );
}
