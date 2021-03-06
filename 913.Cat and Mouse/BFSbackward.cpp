/*
 * begin from all final state, deduce previous states lead to it.
 * BFS update a state if its neighbor has been updated
 * state: ( Mouse position, Cat position, who's turn, who wins )
 * using queue for states to be update, avoid putting same state into the update list
 */
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#include "catch.hpp"
using std::find;
using std::vector;
using std::queue;
using std::cout;
using std::endl;
using std::setw;

#define MOUSE 1
#define CAT 2

/*
class State {
public:
    State() : State( -1, -1, -1 ) { }
    State( int mp, int cp, int t ) : mPos( mp ), cPos( cp ), turn( t ) { }
    int mPos, cPos, turn, win = -1;
    bool inQ = false;
};

bool operator==(const State &a, const State &b) { return a.mPos == b.mPos && a.cPos == b.cPos && a.turn == b.turn; }
*/

class Solution {
public:
    int catMouseGame( vector<vector<int>> &graph ) {
        int N = graph.size();
        auto W = vector<vector<vector<int>>>( N, vector<vector<int>>( N, vector<int>( 3, 0 ) ) );
        // auto inQ = vector<vector<vector<bool>>>( N, vector<vector<bool>>( N, vector<bool>( 3, false ) ) );
        queue<vector<int>> todo;
        for( int i = 1; i < N; ++i ) {
            W[0][i][CAT] = MOUSE; todo.push( {0,i,CAT} ); // mouse just gotten into hole
            W[i][i][CAT] = CAT;   todo.push( {i,i,CAT} ); // mouse just ran into cat
            W[i][i][MOUSE] = CAT; todo.push( {i,i,MOUSE} ); // cat just caught mouse
            W[0][i][MOUSE] = MOUSE; todo.push( {0,i,MOUSE} );
        }
        while( !todo.empty() ) {
            int mPos = todo.front()[0], cPos = todo.front()[1], turn = todo.front()[2];
            int win = W[ mPos ][ cPos ][ turn ];
            todo.pop();
            if( turn == MOUSE ) { // update previous cat's turn
                if( win == CAT ) {
                    for( int cPre : graph[ cPos ] ) {
                        if( cPre == 0 ) continue; // cat can't come from hole
                        if( W[ mPos ][ cPre ][ CAT ] != CAT ) {
                            W[ mPos ][ cPre ][ CAT ] = CAT;
                            // cout << mPos << " " << cPre << " CAT = CAT" << endl;
                            todo.push( {mPos, cPre, CAT} );
                            // inQ[ mPos ][ cPre ][ CAT ] = true;
                        }
                    }
                }
                if( win == MOUSE ) {
                    for( int cPre : graph[ cPos ] ) {
                        if( cPre == 0 || W[ mPos ][ cPre ][ CAT ] ) continue;
                        bool mouseAlwaysWin = true;
                        for( int cNxt : graph[ cPre ] ) { // if all possible cat move lead to mouse win
                            if( cNxt == 0 ) continue; // cat can't go into hole
                            if( W[ mPos ][ cNxt ][ MOUSE ] != MOUSE ) {
                                mouseAlwaysWin = false;
                                break;
                            }
                        }
                        if( mouseAlwaysWin == true ) {
                            W[ mPos ][ cPre ][ CAT ] = MOUSE;
                            // cout << mPos << " " << cPre << " CAT = MOUSE" << endl;
                            todo.push( {mPos, cPre, CAT} );
                            // inQ[ mPos ][ cPre ][ CAT ] = true;
                        }
                    }
                }
            }
            if( turn == CAT ) {
                if( win == MOUSE ) {
                    for( int mPre : graph[ mPos ] ) {
                        if( mPre == cPos ) continue; // can't escape from cat like that
                        if( W[ mPre ][ cPos ][ MOUSE ] != MOUSE ) {
                            W[ mPre ][ cPos ][ MOUSE ] = MOUSE;
                            // cout << mPre << " " << cPos << " MOUSE = MOUSE" << endl;
                            todo.push( {mPre, cPos, MOUSE} );
                            // inQ[ mPre ][ cPos ][ MOUSE ] = true;
                        }
                    }
                }
                if( win == CAT ) {
                    for( int mPre : graph[ mPos ] ) {
                        if( mPre == 0 || W[ mPre ][ cPos ][ MOUSE ] ) continue;
                        bool catAlwaysWin = true;
                        for( int mNxt : graph[ mPre ] ) { // if all possible mouse move lead to cat win
                            if( W[ mNxt ][ cPos ][ CAT ] != CAT ) {
                                catAlwaysWin = false;
                                break;
                            }
                        }
                        if( catAlwaysWin == true ) {
                            W[ mPre ][ cPos ][ MOUSE ] = CAT;
                            // cout << mPre << " " << cPos << " MOUSE = CAT" << endl;
                            todo.push( {mPre, cPos, MOUSE} );
                        }
                    }
                }
            }
            // inQ[ mPos ][ cPos ][ turn ] = false;
        }
        cout << "MOUSE move:" << endl << " ";
        for( int i = 0; i < N; ++i ) cout << setw(3) << i; cout << endl;
        for( int i = 0; i < N; ++i ) {
            cout << i;
            for( int j = 0; j < N; ++j ) {
                cout << setw(3) << W[i][j][MOUSE];
            }
            cout << endl;
        }
        cout << "CAT move:" << endl << " ";
        for( int i = 0; i < N; ++i ) cout << setw(3) << i; cout << endl;
        for( int i = 0; i < N; ++i ) {
            cout << i;
            for( int j = 0; j < N; ++j ) {
                cout << setw(3) << W[i][j][CAT];
            }
            cout << endl;
        }
        if( W[1][2][MOUSE] ) return W[1][2][MOUSE];
        else return 0;
    }
};

TEST_CASE( "searching", "[catMouseGame]" ) {
    Solution s;
    // 4---3---1
    // |   |
    // 2---5
    //  \ /
    //   0
    vector<vector<int>> g1{{2,5},{3},{0,4,5},{1,4,5},{2,3},{0,2,3}};
    CHECK( s.catMouseGame(g1) == 0 ); // draw

    // 4---1
    // |   |
    // 2   3
    //  \ /
    //   0
    vector<vector<int>> g2{{2,3},{3,4},{0,4},{0,1},{1,2}};
    CHECK( s.catMouseGame(g2) == 1 );

    vector<vector<int>> g3{{2,4,7,8},{2,3,4,5,7,8,9},{0,1,3,4,5,7,8,9},{1,2,5},{0,1,2,5,6,7,9},{1,2,3,4,6,7},{4,5,8,9},{0,1,2,4,5,9},{0,1,2,6,9},{1,2,4,6,7,8}};
    CHECK( s.catMouseGame(g3) == 2 ); // TLE for dfs only

    // vector<vector<int>> g4{{3,4,6,7,9,15,16,18},{4,5,8,19},{4,5,6,7,9,18},{0,10,11,15},{0,1,2,6,10,12,14,16},{1,2,7,9,15,17,18},{0,2,4,7,9,10,11,12,13,14,15,17,19},{0,2,5,6,9,16,17},{1,9,14,15,16,19},{0,2,5,6,7,8,10,11,13,15,16,17,18},{3,4,6,9,17,18},{3,6,9,12,19},{4,6,11,15,17,19},{6,9,15,17,18,19},{4,6,8,15,19},{0,3,5,6,8,9,12,13,14,16,19},{0,4,7,8,9,15,17,18,19},{5,6,7,9,10,12,13,16},{0,2,5,9,10,13,16},{1,6,8,11,12,13,14,15,16}};
    // CHECK( s.catMouseGame(g4) == 1 );

    // vector<vector<int>> g5{{2,9,14},{2,5,7},{0,1,3,8,9,11,14},{2,12},{5,11,18},{1,4,18},{9,17,19},{1,11,12,13,14,17,19},{2,16,17},{0,2,6,12,14,18},{14},{2,4,7},{3,7,9,13},{7,12,14},{0,2,7,9,10,13,17},{18},{8,19},{6,7,8,14,19},{4,5,9,15},{6,7,16,17}};
    // CHECK( s.catMouseGame(g5) == 1 );
}
