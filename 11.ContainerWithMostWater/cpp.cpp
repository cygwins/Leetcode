/*
 * start from left-most and right-most line, move the shorter towards the other
 */
#include <algorithm>
#include "catch.hpp"
using std::vector;
using std::min;
using std::max;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int water = 0, i = 0, j = height.size() - 1;
        while(i < j) {
            water = max(water, (j - i) * min(height[i], height[j]));
            height[i] < height[j] ? ++i : --j;
        }
        return water;
    }
};

TEST_CASE("Calculating water", "[maxArea]") {
    Solution s;
    vector<int> a{1, 2, 3, 4, 5};
    CHECK(s.maxArea(a) == 6);
}
