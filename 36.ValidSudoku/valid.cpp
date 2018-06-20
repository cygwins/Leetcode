/*
 * brief
 */
#include <iostream>
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    bool isValidSudoku( vector< vector< char>> &board) {
        for( int i = 0; i < 9; ++i) if( rowConflict( board, i)) return false;
        for( int j = 0; j < 9; ++j) if( colConflict( board, j)) return false;
        for( int n = 0; n < 9; ++n) if( regConflict( board, n)) return false;
        return true;
    }
    bool rowConflict( vector< vector< char>> &board, int row) {
        vector< int> count(9, 0);
        for( int j = 0; j < 9; ++j) if( board[row][j] != '.') ++count[ board[row][j] - '1'];
        for( int n = 0; n < 9; ++n) if( count[n] > 1) return true;
        return false;
    }
    bool colConflict( vector< vector< char>> &board, int col) {
        vector< int> count(9, 0);
        for( int i = 0; i < 9; ++i) if( board[i][col] != '.') ++count[ board[i][col] - '1'];
        for( int n = 0; n < 9; ++n) if( count[n] > 1) return true;
        return false;
    }
    bool regConflict( vector< vector< char>> &board, int reg) {
        vector< int> count(9, 0);
        int regRow = reg / 3, regCol = reg % 3;
        for( int i = regRow * 3; i < regRow * 3 + 3; ++i)
            for( int j = regCol * 3; j < regCol * 3 + 3; ++j)
                if( board[i][j] != '.') ++count[ board[i][j] - '1'];
        for( int n = 0; n < 9; ++n) if( count[n] > 1) return true;
        return false;
    }
};

TEST_CASE("validating", "[isValidSudoku]") {
    Solution s;
    vector< vector< char>> b1{
        vector< char>{'5','3','.','.','7','.','.','.','.'},
        vector< char>{'6','.','.','1','9','5','.','.','.'},
        vector< char>{'.','9','8','.','.','.','.','6','.'},
        vector< char>{'8','.','.','.','6','.','.','.','3'},
        vector< char>{'4','.','.','8','.','3','.','.','1'},
        vector< char>{'7','.','.','.','2','.','.','.','6'},
        vector< char>{'.','6','.','.','.','.','2','8','.'},
        vector< char>{'.','.','.','4','1','9','.','.','5'},
        vector< char>{'.','.','.','.','8','.','.','7','9'} };
    CHECK( s. isValidSudoku( b1) == true);

    vector< vector< char>> b2{
        vector< char>{'8','3','.','.','7','.','.','.','.'},
        vector< char>{'6','.','.','1','9','5','.','.','.'},
        vector< char>{'.','9','8','.','.','.','.','6','.'},
        vector< char>{'8','.','.','.','6','.','.','.','3'},
        vector< char>{'4','.','.','8','.','3','.','.','1'},
        vector< char>{'7','.','.','.','2','.','.','.','6'},
        vector< char>{'.','6','.','.','.','.','2','8','.'},
        vector< char>{'.','.','.','4','1','9','.','.','5'},
        vector< char>{'.','.','.','.','8','.','.','7','9'} };
    CHECK( s. isValidSudoku( b2) == false);

    vector< vector< char>> b3{
        vector< char>{'1','2','3','.','.','.','.','.','.'},
        vector< char>{'4','5','6','.','.','.','.','.','.'},
        vector< char>{'7','8','.','9','.','.','.','.','.'},
        vector< char>{'.','.','.','.','.','.','.','.','.'},
        vector< char>{'.','.','.','.','.','.','.','.','.'},
        vector< char>{'.','.','.','.','.','.','.','.','.'},
        vector< char>{'.','.','.','.','.','.','.','.','.'},
        vector< char>{'.','.','.','.','.','.','.','.','.'},
        vector< char>{'.','.','.','.','.','.','.','.','.'} };
    // This is NOT valid! But leetcode only requires filled number to be checked
    CHECK( s. isValidSudoku( b3) == true);
    
    vector< vector< char>> b4{
        vector< char>{'.','.','.','.','.','.','.','.','.'},
        vector< char>{'.','.','.','.','.','.','.','.','.'},
        vector< char>{'.','9','.','.','.','.','.','.','1'},
        vector< char>{'8','.','.','.','.','.','.','.','.'},
        vector< char>{'.','9','9','3','5','7','.','.','.'},
        vector< char>{'.','.','.','.','.','.','.','4','.'},
        vector< char>{'.','.','.','8','.','.','.','.','.'},
        vector< char>{'.','1','.','.','.','.','4','.','9'},
        vector< char>{'.','.','.','5','.','4','.','.','.'} };
    CHECK( s. isValidSudoku( b4) == false);
}
