/*
 * swap non-zero number to tail of processed, O(n)
 */
#include <algorithm> // swap
#include "catch.hpp"
using std::vector;
using std::swap;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for(int scan = 0, tail = 0; scan < nums.size(); ++scan)
            if(nums[scan]) swap(nums[tail++], nums[scan]);
    }
};

TEST_CASE("moving zeroes", "[moveZeroes]") {
    Solution s;
    vector<int> a{0,1,0,3,12};
    vector<int> b{1,3,12,0,0};
    s.moveZeroes(a);
    CHECK(a == b);
}
