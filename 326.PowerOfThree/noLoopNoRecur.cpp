/*
 * no loop no recurssion: mod by the biggest power of three an integer can hold
 */
#include "catch.hpp"

class Solution {
public:
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0; // 1162261467 is biggest power of 3 < INT_MAX
    }
};

int findMaxPower() {
    int m = 3;
    while(m * 3 / 3 == m) m *= 3;
    return m; // get 1162261467
}

TEST_CASE("moding", "[isPowerOfThree]") {
    Solution s;
    CHECK(s.isPowerOfThree(27) == true);
    CHECK(s.isPowerOfThree(0) == false);
    CHECK(s.isPowerOfThree(-3) == false);
    CHECK(s.isPowerOfThree(45) == false);
}
