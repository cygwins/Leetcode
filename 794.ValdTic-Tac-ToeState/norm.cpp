/*
 * count X's and O's, check win state;
 */
#include <vector>
#include <map>
#include <string>
#include "catch.hpp"
using std::vector;
using std::map;
using std::string;

class Solution {
public:
    bool validTicTacToe(vector<string>& board) {
        int Xs = 0, Os = 0;
        wins['X'] = 0, wins['O'] = 0;
        for( int i = 0; i < 3; ++i) {
            for( int j = 0; j < 3; ++j) {
                if( board[i][j] == 'X') ++Xs;
                if( board[i][j] == 'O') ++Os;
            }
        }
        checkWin( board[0] + board[1] + board[2]);
        if( Xs > Os + 1 || Xs < Os) return false;
        if( (Xs + Os) % 2 == 0 && wins['X'] > 0) return false; // O's turn
        if( (Xs + Os) % 2 == 1 && wins['O'] > 0) return false; // X's turn
        return true;
    }
    inline void checkWin( string b) {
        if(( b[0] != ' ' && b[0] == b[1] && b[2] == b[0])) // upper row
            ++ wins[b[0]];
        if(( b[3] != ' ' && b[3] == b[4] && b[5] == b[3])) // mid row
            ++ wins[b[3]];
        if(( b[6] != ' ' && b[6] == b[7] && b[8] == b[6])) // mid row
            ++ wins[b[6]];
        if(( b[0] != ' ' && b[0] == b[3] && b[6] == b[0])) // left col
            ++ wins[b[0]];
        if(( b[1] != ' ' && b[1] == b[4] && b[7] == b[1])) // mid col
            ++ wins[b[1]];
        if(( b[2] != ' ' && b[2] == b[5] && b[8] == b[2])) // right col
            ++ wins[b[2]];
        if(( b[0] != ' ' && b[0] == b[4] && b[8] == b[0])) // diagonal
            ++ wins[b[0]];
        if(( b[2] != ' ' && b[2] == b[4] && b[6] == b[2])) // anti diag
            ++ wins[b[2]];
    }
    map< char, int> wins;
};

TEST_CASE("counting", "[validTicTacToe]") {
    Solution s;
    vector< string> b1{"O  ","   ","   "},
                    b2{"XOX"," X ","   "},
                    b3{"XXX","   ","OOO"},
                    b4{"XOX","O O","XOX"},
                    b5{"XXX","XOO","XOO"};
    CHECK( s. validTicTacToe( b1) == false);
    CHECK( s. validTicTacToe( b2) == false);
    CHECK( s. validTicTacToe( b3) == false);
    CHECK( s. validTicTacToe( b4) == true);
    CHECK( s. validTicTacToe( b5) == true);
}
