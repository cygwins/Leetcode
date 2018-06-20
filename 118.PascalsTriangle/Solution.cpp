#include <iostream>
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> tri;
        for(int i = 0; i < numRows; ++i) {
            vector<int> row(i + 1, 1);
            for(int j = 1; j < i; ++j) {
                row[j] = tri[i - 1][j - 1] + tri[i - 1][j];
            }
            tri.push_back(row);
        }
        return tri;
    }
};

TEST_CASE("generating", "[generate]") {
    Solution s;
    vector<vector<int>> tri5{{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1}};
    CHECK(s.generate(5) == tri5);
}
