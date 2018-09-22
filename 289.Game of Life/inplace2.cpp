/*
 * % 2 to check dead / live,
 * / 2 to predict die / born.
 * 0: dead -> dead
 * 1: live -> dead
 * 2: dead -> live
 * 3: live -> live
 * so +2 = born / keep alive
 *    +0 = die / keep dead
 * and this won't impact neighbor's checking
 */
#include <iostream>
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    void gameOfLife( vector< vector< int>> &board) {
        int row = board.size(), col = board[0].size();
        for( int i = 0; i < row; ++i) {
            for( int j = 0; j < col; ++j) {
                int neighbor = 0;
                if( i > 0     && j > 0    ) neighbor += board[i-1][j-1] % 2; // ↖
                if( i > 0                 ) neighbor += board[i-1][j  ] % 2; // ↑
                if( i > 0     && j < col-1) neighbor += board[i-1][j+1] % 2; // ↗
                if( j < col-1             ) neighbor += board[i  ][j+1] % 2; // →
                if( i < row-1 && j < col-1) neighbor += board[i+1][j+1] % 2; // ↘
                if( i < row-1             ) neighbor += board[i+1][j  ] % 2; // ↓
                if( i < row-1 && j > 0    ) neighbor += board[i+1][j-1] % 2; // ↙
                if( j > 0                 ) neighbor += board[i  ][j-1] % 2; // ←
                if(( board[i][j] == 0 && neighbor == 3) || // new born
                   ( board[i][j] == 1 && neighbor > 1 && neighbor < 4)) // keep alive
                    board[i][j] += 2;
            }
        }
        for( int i = 0; i < row; ++i)
            for( int j = 0; j < col; ++j)
                board[i][j] /= 2;
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
