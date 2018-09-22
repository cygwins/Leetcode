/*
 * pin first, bring second and third together
 */
#include <algorithm> // sort
#include <cmath> // abs
#include "catch.hpp"
using std::vector;
using std::sort;
using std::abs;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int sum, tmp;
        unsigned diff = -1;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size() - 2; ++i) {
            for(int j = i + 1, k = nums.size() - 1; j < k; ) {
                tmp = nums[i] + nums[j] + nums[k];
                if(abs(target - tmp) < diff) {
                    sum = tmp;
                    diff = abs(target - tmp);
                }
                tmp < target ? ++j : --k;
            }
        }
        return sum;
    }
};

TEST_CASE("finding threes", "[threeSumClosest]") {
    Solution s;
    vector<int> a{-1, 2, 1, -4};
    CHECK(s.threeSumClosest(a, 1) == 2);
}
