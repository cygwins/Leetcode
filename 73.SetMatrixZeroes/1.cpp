/*
 * space O( 1 )
 * use two bool to record first row / column state
 * use first row / column as marker for other columns / rows
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int R = matrix.size(), C = matrix[0].size();
        bool left = false, top = false;
        for( int i = 0; i < R; ++i ) if( !matrix[i][0] ) left = true;
        for( int j = 0; j < C; ++j ) if( !matrix[0][j] ) top = true;
        for( int i = 1; i < R; ++i )
            for( int j = 1; j < C; ++j )
                if( !matrix[i][j] )
                    matrix[i][0] = matrix[0][j] = 0;
        for( int i = 1; i < R; ++i ) // =
            if( !matrix[i][0] )
                for( int j = 1; j < C; ++j )
                    matrix[i][j] = 0;
        for( int j = 1; j < C; ++j ) // ||
            if( !matrix[0][j] )
                for( int i = 1; i < R; ++i )
                    matrix[i][j] = 0;
        if( left ) for( int i = 0; i < R; ++i ) matrix[i][0] = 0;
        if( top ) for( int j = 0; j < C; ++j ) matrix[0][j] = 0;
    }
};

TEST_CASE("recording", "[setZeroes]") {
    Solution s;
    vector< vector< int >> m1 = {{1,1,1},{1,0,1},{1,1,1}},
                           r1 = {{1,0,1},{0,0,0},{1,0,1}};
    s.setZeroes( m1 ); 
    CHECK( m1 == r1 );
}
