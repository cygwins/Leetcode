/*
 * This algorithm solve all problems like "find the only number appears m times where all other appear k times"
 * where m is not divisible by k
 * Solution is provided by @fun4leetcode
 */
#include <iostream>
#include <vector>
#include <bitset>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        return allk1m( nums, 3, 1 );
    }
    int allk1m(vector<int> &nums, int k, int m) {
        int e;
        for(e = 1; 1 << e < k; ++e); // we need this much counters to allow "count to k then restart from 0"
        vector<int> counters( e, 0 );
        for(auto &n : nums) {
            // std::cout << "--> " << n << std::endl;
            for(int i = e - 1; i >= 0; --i) { // update counter from most significant digit to least significant digit
                int carry = ~0;
                for(int j = 0; j < i; ++j) carry &= counters[j]; // only update if all less significant digits are 1
                counters[i] ^= carry & n;
            }
            int mask = ~0;
            for(int i = 0; i < e; ++i) {
                if( 1 << i & k ) mask &= counters[i];
                else mask &= ~counters[i];
            }
            mask = ~mask; // mask == 0 <==> counters showing k count together
            for(int i = 0; i < e; ++i) counters[i] &= mask;
            // for(int i = 0; i < e; ++i) std::cout << i << ": " << std::bitset<8>(counters[i]) << std::endl;
        }
        for(int i = 0; i < e; ++i) {
            if( 1 << i & (m % k) ) return counters[i]; // any digit that m % k has 1 on it can do the job
        }
        throw "Is m divisible by k?";
    }
};

TEST_CASE("finding", "[singleNumber]") {
    Solution s;
    vector<int> nums1{1,2,3,3,2,1,42,6,1,3,2,6,6};
    CHECK(s.singleNumber(nums1) == 42);
}
