/*
 * start from out most hoop, shrink the hoop size
 * 00000
 * 3   1
 * 3   1
 * 22221
 */
#include <vector>
#include <algorithm>
#include "catch.hpp"
using std::vector;
using std::min;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        int row = matrix.size();
        if( !row ) return ans;
        int col = matrix[0].size();
        if( !col ) return ans;
        int num = (min(row, col) + 1) / 2; // number of hoops
        for( int hp = 0; hp < num; ++hp ) {
            for( int j = hp; j < col - hp; ++j ) // top
                ans.push_back( matrix[hp][j] );
            for( int i = hp + 1; i < row - hp; ++i ) // right
                ans.push_back( matrix[i][col - hp - 1] );
            if( row - hp - 1 > hp )
            for( int j = col - hp - 2; j >= hp; --j ) // bottom
                ans.push_back( matrix[row - hp - 1][j] );
            if( hp < col - hp - 1 )
            for( int i = row - hp - 2; i > hp; --i ) // left
                ans.push_back( matrix[i][hp] );
        }
        return ans;
    }
};

TEST_CASE("uncurling matrix", "[spiralOrder]") {
    Solution s;
    vector<vector<int>> z = {{}};
    CHECK(s.spiralOrder(z) == vector<int>{});
    vector<vector<int>> m = {{1}};
    CHECK(s.spiralOrder(m) == vector<int>{1});
    vector<vector<int>> m0 = { {1, 2},
                               {3, 4} };
    CHECK(s.spiralOrder(m0) == vector<int>{1,2,4,3});
    vector<vector<int>> m1 = { {1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 9} };
    CHECK(s.spiralOrder(m1) == vector<int>{1,2,3,6,9,8,7,4,5});
    vector<vector<int>> m2 = { {1, 2, 3},
                               {4, 5, 6} };
    CHECK(s.spiralOrder(m2) == vector<int>{1,2,3,6,5,4});
    vector<vector<int>> m3 = { {1, 2},
                               {3, 4},
                               {5, 6} };
    CHECK(s.spiralOrder(m3) == vector<int>{1,2,4,6,5,3});
    vector<vector<int>> m4 = { {1, 2, 3, 4},
                               {5, 6, 7, 8},
                               {9,10,11,12} };
    CHECK(s.spiralOrder(m4) == vector<int>{1,2,3,4,8,12,11,10,9,5,6,7});
    vector<vector<int>> m5 = { {1, 2, 3},
                               {4, 5, 6},
                               {7, 8, 9},
                               {10,11,12} };
    CHECK(s.spiralOrder(m5) == vector<int>{1,2,3,6,9,12,11,10,7,4,5,8});
    vector<vector<int>> m6 = { {1},
                               {2},
                               {3} };
    CHECK(s.spiralOrder(m6) == vector<int>{1,2,3});
}
