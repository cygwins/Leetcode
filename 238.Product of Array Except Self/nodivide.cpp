/*
 * product of array except self = product of left * product of right
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> ans(nums.size(), 1);
        int left = 1, right = 1;
        for( int i = 1; i < nums.size(); ++i ) {
            ans[i] *= left *= nums[i - 1];
        }
        for( int i = nums.size() - 2; i >= 0; --i ) {
            ans[i] *= right *= nums[i + 1];
        }
        return ans;
    }
};

TEST_CASE("rounding", "[productExceptSelf]") {
    Solution s;
    vector<int> nums1{1,2,3,4};
    CHECK(s.productExceptSelf(nums1) == vector<int>{24,12,8,6});
    vector<int> nums2{1,2,0,4};
    CHECK(s.productExceptSelf(nums2) == vector<int>{0,0,8,0});
    vector<int> nums3{1,0,3,0};
    CHECK(s.productExceptSelf(nums3) == vector<int>{0,0,0,0});
}
