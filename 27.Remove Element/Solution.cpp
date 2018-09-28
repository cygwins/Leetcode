/*
 * brief
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include "catch.hpp"
using std::vector;
using std::find;
using std::sort;

inline bool numsHasVal( vector<int>& nums, int len, int val ) {
    return find(nums.begin(), nums.begin() + len, val) != nums.begin() + len;
}

void print(vector<int>& nums) {
    for(auto &i : nums) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        auto cmp1 = [val](int a, int b) { return a != val && b == val; };
        sort(nums.begin(), nums.end(), cmp1);
        // print(nums);
        return find(nums.begin(), nums.end(), val) - nums.begin();
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<int> nums1{0,1,2,2,3,0,4,2};
    CHECK(s.removeElement(nums1, 2) == 5);
    CHECK(numsHasVal(nums1, s.removeElement(nums1, 2), 2) == false);
    vector<int> nums2{7,25,21,2,20,7,24,9,24,24,6,22,5,1,26,17,18,29,25,9,8,27,6,26,8,5,27,5,0,29,26,29,24,18,23,14,25,17,15,20,11,22,4,17,15,0,26,3,21,21,12,0,10,10,26,19,15,23,16,7,14,12,7,8,0,0,14,26,18,22,8,21,6,12,0,21,4,26,16,26,18,21};
    CHECK(s.removeElement(nums2, 26) == nums2.size() - 8);
    CHECK(numsHasVal(nums2, s.removeElement(nums2, 26), 26) == false);
}
