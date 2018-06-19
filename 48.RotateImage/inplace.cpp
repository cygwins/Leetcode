/*
 * for each in upper left 1/4 rectangle, rotate it's group of 4
 * if odd length, make rectangle wider
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size(), tmp;
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < (n + 1) / 2; ++j) {
                tmp = matrix[i][j];
                matrix[i][j] = matrix[n-1-j][i];         // ↑
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j]; // ←
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i]; // ↓
                matrix[j][n-1-i] = tmp;                  // →
            }
        }
    }
};

TEST_CASE("rotating", "[rotate]") {
    Solution s;
    vector<vector<int>> img1{{1,2,3},
                             {4,5,6},
                             {7,8,9}},
                       img1r{{7,4,1},
                             {8,5,2},
                             {9,6,3}};
    s.rotate (img1);
    CHECK (img1 == img1r);
    vector<vector<int>> img2{{ 5, 1, 9,11},
                             { 2, 4, 8,10},
                             {13, 3, 6, 7},
                             {15,14,12,16}},
                       img2r{{15,13, 2, 5},
                             {14, 3, 4, 1},
                             {12, 6, 8, 9},
                             {16, 7,10,11}};
    s.rotate (img2);
    CHECK (img2 == img2r);
}
