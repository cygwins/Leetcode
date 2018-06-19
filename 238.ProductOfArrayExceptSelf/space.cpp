/*
 * product of array divided by self
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int p = 1, zcount = 0, zpos;
        for( int i = 0; i < nums.size(); ++i ) {
            if( nums[i] == 0 ) {
                ++zcount;
                zpos = i;
                if( zcount > 1 ) return vector<int>( nums.size(), 0 );
                continue;
            }
            p *= nums[i];
        }
        if( zcount == 1 ) {
            vector<int> only( nums.size(), 0 );
            only[zpos] = p;
            return only;
        }
        vector<int> ans( nums.size(), 0 );
        for( int i = 0; i < nums.size(); ++i ) ans[i] =  p / nums[i];
        return ans;
    }
};

TEST_CASE("dividing", "[productExceptSelf]") {
    Solution s;
    vector<int> nums1{1,2,3,4};
    CHECK(s.productExceptSelf(nums1) == vector<int>{24,12,8,6});
    vector<int> nums2{1,2,0,4};
    CHECK(s.productExceptSelf(nums2) == vector<int>{0,0,8,0});
    vector<int> nums3{1,0,3,0};
    CHECK(s.productExceptSelf(nums3) == vector<int>{0,0,0,0});
}
