/*
 * divide and conquer method:
 * totalMax = max({leftMax, rightMax, combineMax});
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include "catch.hpp"
using std::vector;
using std::max;
using std::max_element;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.size() == 1) return nums[0]; // at least one chosen
        int mid = nums.size() / 2;
        auto left = vector<int>(nums.begin(), nums.begin() + mid);
        auto right = vector<int>(nums.begin() + mid, nums.end());
        vector<int> candidate, combine;
        if(left.size() > 0) {
            candidate.push_back(maxSubArray(left)); // leftMax
            int leftEndMax = nums[mid - 1];
            for(int i = mid - 2, sum = leftEndMax; i >= 0; --i) {
                sum += nums[i];
                leftEndMax = max(sum, leftEndMax);
            }
            combine.push_back(leftEndMax);
        }
        if(right.size() > 0) {
            candidate.push_back(maxSubArray(right)); // rightMax
            int rightEndMax = nums[mid];
            for(int i = mid + 1, sum = rightEndMax; i < nums.size(); ++i) {
                sum += nums[i];
                rightEndMax = max(sum, rightEndMax);
            }
            combine.push_back(rightEndMax);
        }
        if(combine.size() == 2) candidate.push_back(combine[0] + combine[1]); // combineMax
        return *max_element(candidate.begin(), candidate.end());
    }
};

TEST_CASE("dividing and conquering", "[maxSubArray]") {
    Solution s;
    vector<int> n0{-2,1,-3,4,-1,2,1,-5,4}, n1{-1}, n2{-3,-1,-4};
    CHECK(s.maxSubArray(n0) == 6);
    CHECK(s.maxSubArray(n1) == -1);
    CHECK(s.maxSubArray(n2) == -1);
}
