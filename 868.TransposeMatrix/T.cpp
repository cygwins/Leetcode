/*
 * brief
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& A) {
        int row = A.size();
        int col = A[0].size();
        vector<vector<int>> B( col, vector<int>( row, 0 ));
        for( int i = 0; i < row; ++i ) {
            for( int j = 0; j < col; ++j ) {
                B[j][i] = A[i][j];
            }
        }
        return B;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6} };
    vector<vector<int>> B = {
        {1, 4},
        {2, 5},
        {3, 6} };
    CHECK( s.transpose(A) == B );
}
