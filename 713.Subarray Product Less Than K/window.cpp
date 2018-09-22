/*
 * expand to right as possible, then shrink from left in order to expand again
 * add the newly introduced set on each success expand
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include "catch.hpp"
using std::vector;

static int n = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = 0, product = 1;
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            product *= nums[right]; // expanding
            while(left <= right && product >= k) { // shrinking
                product /= nums[left];
                ++left;
            }
            n += right - left + 1;
        }
        return n;
    }
};

TEST_CASE("expanding", "[numSubarrayProductLessThanK]") {
    Solution s;
    vector<int> nums{10, 5, 2, 6};
    CHECK(s.numSubarrayProductLessThanK(nums, 100) == 8);
}
