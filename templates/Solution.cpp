/*
 * brief
 */
#include <iostream>
#include <../Tree.hpp>
#include <cstdio>
#include <vector>
#include "catch.hpp"
using std::vector;
using namespace Tree;

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
    TreeNode* root = parseTree("[1,null,2,null,3]");
    CHECK(s.methodName(nums) == vector<int>{2,3});
}
