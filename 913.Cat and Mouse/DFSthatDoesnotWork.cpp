/*
 * DFS, store all possible outcome for current state, return best for that player
 * state: ( Mouse position, Cat position, who's turn )
 * Time Limit Exceed for simple DFS, must prune with hash table
 */
#include <iostream>
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    const int hole = 0, mouseStart = 1, catStart = 2;
    const int draw = 0, mouseWin   = 1, catWin   = 2;
    const int           mouseTurn  = 1, catTurn  = 0;
    int d = 0;

    int catMouseGame( vector<vector<int>> &graph ) {
        int N = graph.size();
        // std::cout << std::endl << "N = " << N << std::endl;
        auto table = vector<vector<vector<int>>>( N, vector<vector<int>>( N, vector<int>( 2, -1 ) ) );
        return check( mouseStart, catStart, mouseTurn, table, graph );
    }

    int check( int mousePos, int catPos, int turn, vector<vector<vector<int>>> &table, vector<vector<int>> &graph ) {
        int &current = table[ mousePos ][ catPos ][ turn ];
        if( current != -1 ) return current;
        current = draw; // visited, if no win strategy is found, draw is the best result
        bool canDraw = false;
        if( turn == mouseTurn ) { // Mouse's turn
            for( int &mouseDes : graph[ mousePos ] ) if( mouseDes == hole ) {
                // std::cout << d << "[" << mousePos << "][" << catPos << "][m] = mouse: sweet home" << std::endl;
                return current = mouseWin; // check for win first
            }
            for( int &mouseDes : graph[ mousePos ] ) {
                if( mouseDes == catPos ) continue; // don't run into cat
                d++;
                int ans = check( mouseDes, catPos, catTurn, table, graph );
                d--;
                if( ans == mouseWin ) {
                    std::cout << d << "[" << mousePos << "][" << catPos << "][m] = mouse" << std::endl;
                    return current = mouseWin;
                }
                if( ans == draw ) canDraw = true;
            }
            if( !canDraw ) {
                std::cout << d << "[" << mousePos << "][" << catPos << "][m] = doom" << std::endl;
                return current = catWin;
            }
        } else { // Cat's turn
            for( int &catDes : graph[ catPos ] ) if( catDes == mousePos ) {
                std::cout << d << "[" << mousePos << "][" << catPos << "][c] = cat: get 'em" << std::endl;
                return current = catWin;
            }
            for( int &catDes : graph[ catPos ] ) {
                if( catDes == hole ) continue; // can't go into hole
                d++;
                int ans = check( mousePos, catDes, mouseTurn, table, graph );
                d--;
                if( ans == catWin ) {
                    std::cout << d << "[" << mousePos << "][" << catPos << "][c] = cat" << std::endl;
                    return current = catWin;
                }
                if( ans == draw ) canDraw = true;
            }
            if( !canDraw ) {
                std::cout << d << "[" << mousePos << "][" << catPos << "][c] = lost target" << std::endl;
                return current = mouseWin;
            }
        }
        std::cout << d << "[" << mousePos << "][" << catPos << "][" << (turn==catTurn?"c":"m") << "] = draw" << std::endl;
        return draw;
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

    vector<vector<int>> g4{{3,4,6,7,9,15,16,18},{4,5,8,19},{4,5,6,7,9,18},{0,10,11,15},{0,1,2,6,10,12,14,16},{1,2,7,9,15,17,18},{0,2,4,7,9,10,11,12,13,14,15,17,19},{0,2,5,6,9,16,17},{1,9,14,15,16,19},{0,2,5,6,7,8,10,11,13,15,16,17,18},{3,4,6,9,17,18},{3,6,9,12,19},{4,6,11,15,17,19},{6,9,15,17,18,19},{4,6,8,15,19},{0,3,5,6,8,9,12,13,14,16,19},{0,4,7,8,9,15,17,18,19},{5,6,7,9,10,12,13,16},{0,2,5,9,10,13,16},{1,6,8,11,12,13,14,15,16}};
    CHECK( s.catMouseGame(g4) == 1 );

    vector<vector<int>> g5{{2,9,14},{2,5,7},{0,1,3,8,9,11,14},{2,12},{5,11,18},{1,4,18},{9,17,19},{1,11,12,13,14,17,19},{2,16,17},{0,2,6,12,14,18},{14},{2,4,7},{3,7,9,13},{7,12,14},{0,2,7,9,10,13,17},{18},{8,19},{6,7,8,14,19},{4,5,9,15},{6,7,16,17}};
    CHECK( s.catMouseGame(g5) == 1 );
}
