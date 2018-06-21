/*
 * switch K to 0-base index
 * iff K is odd, K-th in N is different to K/2 -th in N-1
 * so K is changed (from 0) for T times,
 * T is the total number of 1 in K's binary representation
 * so only check is T
 * by xor-ing self with folding half each time
 */
#include "catch.hpp"

class Solution {
public:
    int kthGrammar(int N, int K) {
        --K; // 1-base -> 0-base
        int n = 16; // K has at most 30 digit
        while( n ) {
            K ^= K >> n;
            n >>= 1;
        }
        return K & 1;
    }
};

TEST_CASE("counting", "[kthGrammar]") {
    Solution s;
    CHECK( s.kthGrammar( 1, 1 ) == 0 );
    CHECK( s.kthGrammar( 2, 1 ) == 0 );
    CHECK( s.kthGrammar( 2, 2 ) == 1 );
    CHECK( s.kthGrammar( 4, 5 ) == 1 );
}
