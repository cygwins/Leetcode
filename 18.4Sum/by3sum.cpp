/*
 * using O(n^2) method solving 3sum
 */
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "catch.hpp"
using std::vector;
using std::sort;
using std::set;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        if( nums.size() < 4 ) return {};
        sort( nums.begin(), nums.end() );
        set<vector<int>> ans;
        for( int i = 0; i < nums.size() - 3; ++i ) {
            auto triple = threeSum( nums, target - nums[i], i + 1 );
            if( !triple.empty() ) {
                for( auto t : triple ) {
                    ans.insert({ nums[i], t[0], t[1], t[2] });
                }
            }
            while( i < nums.size() - 3 && nums[i] == nums[i+1] ) ++i;
        }
        return vector<vector<int>>( ans.begin(), ans.end() );
    }
private:
    vector<vector<int>> threeSum(vector<int> &nums, int target, int start) {
        vector<vector<int>> ans;
        for(int i = start; i < nums.size() - 2; ++i) {
            for(int j = i + 1, k = nums.size() - 1; j < k; ) {
                int sum = nums[i] + nums[j] + nums[k];
                if( sum == target ) {
                    ans.push_back( { nums[i], nums[j], nums[k] } );
                }
                if( sum < target ) {
                    while( j < k && nums[j] == nums[j+1] ) ++j;
                    ++j;
                } else {
                    while( j < k && nums[k] == nums[k-1] ) --k;
                    --k;
                }
            }
            while( i < nums.size() - 2 && nums[i] == nums[i+1] ) ++i;
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
