/*
 * how many floors can be checked with fixed eggs and drops?
 */
#include <iostream>
#include <numeric> // iota
#include <vector>
#include "catch.hpp"
using std::vector;
using std::iota;

class Solution {
public:
    int superEggDrop(int K, int N) {
        // dp[k][n]: how many floors can be check with k eggs and n drops
        vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
        iota(dp[1].begin(), dp[1].end(), 0);
        for( int n = 1; n <= N; ++n ) std::cout<<dp[1][n];
        for( int k = 1; k <= K; ++k ) dp[k][1] = 1;
        for( int k = 2; k <= K; ++k ) {
            for( int n = 2; n <= N; ++n ) {
                dp[k][n] = 1 + dp[k][n-1] + dp[k-1][n-1];
            }
        }
        for( int n = 1; n <= N; ++n ){
            if( dp[K][n] >= N ) {
                return n;
            }
        }
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    CHECK(s.superEggDrop(1,2) == 2);
    CHECK(s.superEggDrop(2,2) == 2);
    CHECK(s.superEggDrop(2,6) == 3);
    CHECK(s.superEggDrop(3,14) == 4);
}
