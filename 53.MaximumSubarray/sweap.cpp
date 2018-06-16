/*
 * only draw more when hand is still positive
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int hand = nums[0], max = hand; // at least one hand
        for(int i = 1; i < nums.size(); ++i) {
            hand = hand + nums[i] < nums[i] ? nums[i] : hand + nums[i]; // discard hand or draw
            max = hand > max ? hand : max; // update max
        }
        return max;
    }
};

TEST_CASE("collecting", "[maxSubArray]") {
    Solution s;
    vector<int> n0{-2,1,-3,4,-1,2,1,-5,4}, n1{-1}, n2{-3,-1,-4};
    CHECK(s.maxSubArray(n0) == 6);
    CHECK(s.maxSubArray(n1) == -1);
    CHECK(s.maxSubArray(n2) == -1);
}
