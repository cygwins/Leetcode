/*
 * # of paths in m * n grid:
 * ((m - 1) + (n - 1))! / ((m - 1)! * (n - 1)!)
 * = (m + n - 2)(m + n - 3)...(m) / (n - 1)(n - 2)...(1)
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    int uniquePaths (int m, int n) { // m columns, n rows
        long long int ans = 1; // may overflow
        for (int i = 1; i < n; ++i) {
            ans *= (m - 1 + i);
            ans /= i; // product of k continuous numbers can be divided by k
        }
        return ans;
    }
};

TEST_CASE("dp", "[uniquePaths]") {
    Solution s;
    CHECK(s.uniquePaths(3,2) == 3);
    CHECK(s.uniquePaths(7,3) == 28);
    CHECK(s.uniquePaths(51,9) == 1916797311);
}
