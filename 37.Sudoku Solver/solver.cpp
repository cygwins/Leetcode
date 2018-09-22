/*
 * 1. Start from blank board, set given cells.
 * 2. Update possibilities of cells in its row / column / region after each setting.
 * 3. If cell has only one possible number after updating, set it (then update again).
 * 4. If unsolved, we need to guess. Restore to the snapshot before to guess again.
 */
#include <iostream>
#include <vector>
#include <string>
#include "catch.hpp"
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Solution {
public:
    void solveSudoku( vector< vector< char >>& board ) {
        Board = vector< vector< Cell >>( 9, vector< Cell >( 9, Cell()));
        // read input
        for( int i = 0; i < 9; ++i )
            for( int j = 0; j < 9; ++j )
                if( board[i][j] != '.' && !set( i, j, board[i][j] - '0' ) )
                        return; // incorrect puzzle
        if( !guess() ) return; // unsolvable
        // copy back
        for( int i = 0; i < 9; ++i )
            for( int j = 0; j < 9; ++j )
                board[i][j] = '0' + Board[i][j].val;
    }

private:
    struct Cell{
        int val, possibleCount;
        vector< bool > possible;
        Cell( int v ) : val( v ), possibleCount( 1 ), possible( vector< bool >( 10, false ))
        { possible[v] = true; }
        Cell() :        val( 0 ), possibleCount( 9 ), possible( vector< bool >( 10, true ))
        { possible[0] = false; }
    }; 
    vector< vector< Cell >> Board;

    bool set( int row, int col, int val ) {
        if( Board[row][col].val == val ) return true;
        if(( Board[row][col].val != 0 && Board[row][col].val != val ) ||
           ( !Board[row][col].possible[val] )) {
            return false;
        }
        Board[row][col] = Cell( val );
        for( int i = 0; i < 9; ++i ) {
            if( i != col && !update( row, i, val )) return false;
            if( i != row && !update( i, col, val )) return false;
            int regR = row / 3 * 3 + i / 3, regC = col / 3 * 3 + i % 3;
            if(( regR != row || regC != col ) && !update( regR, regC, val )) return false;
        }
        return true;
    }

    bool update( int row, int col, int noVal ) {
        if( Board[row][col].val == noVal ) return false;
        if( !Board[row][col].possible[noVal] ) return true;
        Board[row][col].possible[noVal] = false;
        if( --Board[row][col].possibleCount == 1 )
            for( int n = 1; n <= 9; ++n )
                if( Board[row][col].possible[n] )
                    return set( row, col, n );
        return true;
    }

    bool guess() { // guess a cell with least possible numbers
        if( solved() ) return true;
        int leastPossible = 10, row, col;
        for( int i = 0; i < 9; ++i ) {
            for( int j = 0; j < 9; ++j ) {
                if( Board[i][j].val ) continue;
                if( Board[i][j].possibleCount < leastPossible ) {
                    row = i;
                    col = j;
                }
            }
        }
        vector< vector< Cell >> snapshot = Board;
        for( int n = 1; n <= 9; ++n ) {
            if( !Board[row][col].possible[n] ) continue;
            if( set( row, col, n ) && guess() ) // keep on until solved
                return true;
            Board = snapshot; // wrong, guess next possible number
        }
        return false; // unsolvable puzzle
    }

    bool solved() {
        for( int i = 0; i < 9; ++i )
            for( int j = 0; j < 9; ++j )
                if( Board[i][j].possibleCount > 1 )
                    return false;
        return true;
    }

    void print() {
        for( int i = 0; i < 9; ++i ) {
            if( i % 3 == 0 ) cout << string(19, '-') << endl;
            for( int j = 0; j < 9; ++j ) {
                cout << ( j % 3 ? ' ' : '|');
                if( Board[i][j].val ) cout << Board[i][j].val;
                else cout << ' ';
            }
            cout << '|' << endl;
        }
        cout << string(19, '-') << endl;
    }

    void printPossible() {
        for( int i = 0; i < 27; ++i ) {
            if( i % 9 == 0 ) cout << string(37, '-') << endl;
            for( int j = 0; j < 27; ++j ) {
                int n = 1 + i % 3 * 3 + j % 3;
                if( j % 9 == 0 ) cout << '|';
                else if( j % 3 == 0 ) cout << ' ';
                if( Board[i/3][j/3].possible[n] ) cout << n;
                else cout << ' ';
            }
            cout << '|' << endl;
        }
        cout << string(37, '-') << endl;
    }
};

TEST_CASE("solving", "[solveSudoku]") {
    Solution s;
    vector< vector< char >> puzzle1 =
    {{'5','3','.','.','7','.','.','.','.'},
     {'6','.','.','1','9','5','.','.','.'},
     {'.','9','8','.','.','.','.','6','.'},
     {'8','.','.','.','6','.','.','.','3'},
     {'4','.','.','8','.','3','.','.','1'},
     {'7','.','.','.','2','.','.','.','6'},
     {'.','6','.','.','.','.','2','8','.'},
     {'.','.','.','4','1','9','.','.','5'},
     {'.','.','.','.','8','.','.','7','9'}};
    vector< vector< char >> solution1 =
    {{'5','3','4','6','7','8','9','1','2'},
     {'6','7','2','1','9','5','3','4','8'},
     {'1','9','8','3','4','2','5','6','7'},
     {'8','5','9','7','6','1','4','2','3'},
     {'4','2','6','8','5','3','7','9','1'},
     {'7','1','3','9','2','4','8','5','6'},
     {'9','6','1','5','3','7','2','8','4'},
     {'2','8','7','4','1','9','6','3','5'},
     {'3','4','5','2','8','6','1','7','9'}};
    s.solveSudoku( puzzle1 );
    CHECK( puzzle1 == solution1 );

    vector< vector< char >> puzzle2 =
    {{'.','.','9','7','4','8','.','.','.'},
     {'7','.','.','.','.','.','.','.','.'},
     {'.','2','.','1','.','9','.','.','.'},
     {'.','.','7','.','.','.','2','4','.'},
     {'.','6','4','.','1','.','5','9','.'},
     {'.','9','8','.','.','.','3','.','.'},
     {'.','.','.','8','.','3','.','2','.'},
     {'.','.','.','.','.','.','.','.','6'},
     {'.','.','.','2','7','5','9','.','.'}};
    vector< vector< char >> solution2 =
    {{'5','1','9','7','4','8','6','3','2'},
     {'7','8','3','6','5','2','4','1','9'},
     {'4','2','6','1','3','9','8','7','5'},
     {'3','5','7','9','8','6','2','4','1'},
     {'2','6','4','3','1','7','5','9','8'},
     {'1','9','8','5','2','4','3','6','7'},
     {'9','7','5','8','6','3','1','2','4'},
     {'8','3','2','4','9','1','7','5','6'},
     {'6','4','1','2','7','5','9','8','3'}};
    s.solveSudoku( puzzle2 );
    CHECK( puzzle2 == solution2 );
}
