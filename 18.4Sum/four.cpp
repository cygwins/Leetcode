/*
 * O( n ^ 3 )
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include "catch.hpp"
using std::vector;
using std::sort;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        if( nums.size() < 4 ) return {};
        sort( nums.begin(), nums.end() );
        vector<vector<int>> ans;
        for( int i = 0; i < nums.size() - 3; ++i ) {
            if( 4 * nums[i] > target ) break;
            if( nums[i] + 3 * nums[nums.size() - 1] < target ) continue;
            for(int j = i + 1; j < nums.size() - 2; ++j) {
                if( nums[i] + 3 * nums[j] > target ) break;
                if( nums[i] + nums[j] + 2 * nums[nums.size() - 1] < target ) continue;
                for(int k = j + 1, l = nums.size() - 1; k < l; ) {
                    int sum = nums[i] + nums[j] + nums[k] + nums[l];
                    if( sum == target ) {
                        ans.push_back( { nums[i], nums[j], nums[k], nums[l] } );
                    }
                    if( sum < target ) {
                        while( k < l && nums[k] == nums[k+1] ) ++k;
                        ++k;
                    } else {
                        while( k < l && nums[l] == nums[l-1] ) --l;
                        --l;
                    }
                }
                while( j < nums.size() - 2 && nums[j] == nums[j+1] ) ++j;
            }
            while( i < nums.size() - 3 && nums[i] == nums[i+1] ) ++i;
        }
        return ans;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<int> nums1{1, 0, -1, 0, -2, 2};
    vector<vector<int>> ans1{ {-2, -1, 1, 2}, {-2,  0, 0, 2}, {-1,  0, 0, 1} };
    CHECK(s.fourSum(nums1, 0) == ans1);
    vector<int> nums2;
    vector<vector<int>> ans2;
    CHECK(s.fourSum(nums2, 0) == ans2);
    vector<int> nums3{0};
    vector<vector<int>> ans3;
    CHECK(s.fourSum(nums3, 0) == ans3);
}
