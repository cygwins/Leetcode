#include "catch.hpp"

class Solution {
public:
    int mirrorReflection(int p, int q) {
        int d = gcd( p, q ), x = p / d, y = q / d;
        if( x % 2 == 1 && y % 2 == 0 ) return 0;
        if( x % 2 == 1 && y % 2 == 1 ) return 1;
        if( x % 2 == 0 && y % 2 == 1 ) return 2;
        return -1;
    }
    int gcd( int a, int b ) {
        if( a % b == 0 ) return b;
        return gcd( b, a % b );
    }
};

TEST_CASE("recursing", "[mirrorReflection]") {
    Solution s;
    CHECK(s.mirrorReflection(2,1) == 2 );
    CHECK(s.mirrorReflection(3,1) == 1 );
    CHECK(s.mirrorReflection(3,2) == 0 );
}

