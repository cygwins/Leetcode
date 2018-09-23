/*
 *
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "catch.hpp"
using std::string;
using std::cin;
using std::vector;
using std::unordered_map;

static int n = []() { 
    std::ios::sync_with_stdio(false); 
    cin.tie(nullptr);  
    return 0; 
}();

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if(nums.size() < 2 || k < 0) return 0;
        int pairs = 0;
        unordered_map<int, int> count;
        for(auto &n : nums)
            if(count.find(n) == count.end()) count[n] = 1;
            else ++count[n];
        for(auto &p : count)
            if((k == 0 && p.second > 1) ||
               (k > 0 && count.find(p.first + k) != count.end())) // count on smaller in pair
                ++pairs;
        return pairs;
    }
};

TEST_CASE("finding pairs", "[findPairs]") {
    Solution s;
    vector<int> n1{3,1,4,1,5}, n2{1,2,3,4,5}, n3{1,3,1,5,4};
    int k1 = 2, k2 = 1, k3 = 0;
    CHECK(s.findPairs(n1, k1) == 2);
    CHECK(s.findPairs(n2, k2) == 4);
    CHECK(s.findPairs(n3, k3) == 1);
}
