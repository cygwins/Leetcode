/*
 * O( m + n )
 * record all rows and colums need to be bombed
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int R = matrix.size(), C = matrix[0].size();
        vector< bool > row( R, false ), col( C, false );
        for( int i = 0; i < R; ++i )
            for( int j = 0; j < C; ++j )
                if( !matrix[i][j] )
                    row[i] = col[j] = true;
        for( int i = 0; i < R; ++i )
            if( row[i] )
                for( int j = 0; j < C; ++j )
                    matrix[i][j] = 0;
        for( int j = 0; j < C; ++j )
            if( col[j] )
                for( int i = 0; i < R; ++i )
                    matrix[i][j] = 0;
    }
};

TEST_CASE("recording", "[setZeroes]") {
    Solution s;
    vector< vector< int >> m1 = {{1,1,1},{1,0,1},{1,1,1}},
                           r1 = {{1,0,1},{0,0,0},{1,0,1}};
    s.setZeroes( m1 ); 
    CHECK( m1 == r1 );
}
