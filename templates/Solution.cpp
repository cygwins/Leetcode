/*
 * brief
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include "catch.hpp"
using std::vector;

static int n = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    return 0;
}();

class Solution {
public:
    int methodName(vector<int> &nums) {
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<int> nums{};
    CHECK(s.methodName(nums) == vector<int>{2,3});
}
