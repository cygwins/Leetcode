/*
 * dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
 * save some space by store only last column
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    int uniquePaths (int m, int n) { // m columns, n rows
        vector<int> col (n, 1);         
        for (int i = 1; i < m; ++i) {     // # of path to reach grid i, j
            for (int j = 1; j < n; ++j) { // = col[j] in i-th iteration
                col[j] += col[j - 1];
            }
        }
        return col[n - 1];
    }
};

TEST_CASE("dp", "[uniquePaths]") {
    Solution s;
    CHECK(s.uniquePaths(3,2) == 3);
    CHECK(s.uniquePaths(7,3) == 28);
}
