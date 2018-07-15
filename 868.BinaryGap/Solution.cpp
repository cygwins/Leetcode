/*
 * brief
 */
#include "catch.hpp"

class Solution {
public:
    int binaryGap(int N) {
        int maxdist = 0, dist = 0;
        bool head = false;
        while(N) {
            if(N % 2) {
                head = true;
                maxdist = max(maxdist, dist);
                dist = 1;
            } else {
                if(head) ++dist;
            }
            N /= 2;
        }
        return maxdist;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    CHECK(s.binaryGap(22) == 2);
    CHECK(s.binaryGap(5) == 2);
    CHECK(s.binaryGap(6) == 1);
    CHECK(s.binaryGap(8) == 0);
}

