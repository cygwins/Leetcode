/*
 * copy the prediction back
 */
#include <iostream>
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    void gameOfLife( vector< vector< int>> &board) {
        vector< vector< int>> next(board);
        int row = board.size(), col = board[0].size();
        for( int i = 0; i < row; ++i) {
            for( int j = 0; j < col; ++j) {
                int neighbor = 0;
                if( i > 0     && j > 0    ) neighbor += board[i-1][j-1]; // ↖
                if( i > 0                 ) neighbor += board[i-1][j  ]; // ↑
                if( i > 0     && j < col-1) neighbor += board[i-1][j+1]; // ↗
                if( j < col-1             ) neighbor += board[i  ][j+1]; // →
                if( i < row-1 && j < col-1) neighbor += board[i+1][j+1]; // ↘
                if( i < row-1             ) neighbor += board[i+1][j  ]; // ↓
                if( i < row-1 && j > 0    ) neighbor += board[i+1][j-1]; // ↙
                if( j > 0                 ) neighbor += board[i  ][j-1]; // ←
                if( board[i][j] == 1 && (neighbor < 2 || neighbor > 3))
                    next[i][j] = 0; // die
                else if( board[i][j] == 0 && neighbor == 3)
                    next[i][j] = 1; // born
                else
                    next[i][j] = board[i][j];
            }
        }
        board = next;
    }
};

TEST_CASE( "generating", "[gameOfLife]") {
    Solution s;
    vector< vector< int>>
    o1{ vector< int>{0,1,0},
        vector< int>{0,0,1},
        vector< int>{1,1,1},
        vector< int>{0,0,0} },
    n1{ vector< int>{0,0,0},
        vector< int>{1,0,1},
        vector< int>{0,1,1},
        vector< int>{0,1,0} };
    s. gameOfLife( o1);
    CHECK( o1 == n1);
}
