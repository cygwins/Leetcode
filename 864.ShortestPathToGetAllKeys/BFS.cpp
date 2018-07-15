/*
 * BFS
 * each tile can be stepped on once with same set of keys
 */
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include "catch.hpp"
using std::vector;
using std::string;
using std::set;
using std::unordered_set;
using std::to_string;

class Solution {
public:
    struct State{
        int xPos; // row
        int yPos; // column
        int step;
        set<char> keys;
        State(int x, int y, int s, set<char> k) : xPos(x), yPos(y), step(s), keys(k) { }
        bool operator==(const State& other) const {
            return xPos == other.xPos && yPos == other.yPos && keys == other.keys;
        }
        string operator()() const { // as a hash function
            string combine = to_string(xPos) + "," + to_string(yPos);
            for(auto &k : keys) combine += k;
            return combine;
        }
    };

    int shortestPathAllKeys(vector<string>& grid) {
        int R = grid.size();
        int C = grid[0].size();
        vector<State> Q;
        set<char> goal;
        unordered_set<string> visited;
        for(int i = 0; i < R; ++i) {
            for(int j = 0; j < C; ++j) {
                if(grid[i][j] == '@') {
                    State start(i, j, 0, set<char>{});
                    Q.push_back( start );
                    visited.insert( start() );
                }
                if(grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                    goal.insert( grid[i][j] );
                }
            }
        }
        if(goal.empty()) return 0;
        vector<vector<int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};
        int now = 0;
        while( now < Q.size() ) {
            for(auto &d : dirs) {
                int x = Q[now].xPos + d[0];
                int y = Q[now].yPos + d[1];
                auto keys = Q[now].keys;
                if(x >= 0 && x < R && y >= 0 && y < C && grid[x][y] != '#') {
                    if(grid[x][y] >= 'a' && grid[x][y] <= 'f') {
                        keys.insert( grid[x][y] );
                    }
                    if(keys == goal) return Q[now].step + 1;
                    bool locked = grid[x][y] >= 'A' && grid[x][y] <= 'F'
                        && keys.find(grid[x][y] - 'A' + 'a') == keys.end();
                    State next(x, y, Q[now].step + 1, keys);
                    if( !locked && visited.find( next() ) == visited.end() ) {
                        Q.push_back( next );
                        visited.insert( next() );
                        // std::cout << next.step << " " << next() << std::endl;
                    }
                }
            }
            ++now;
        }
        return -1;
    }
};

TEST_CASE("finding path", "[shortestPathAllKeys]") {
    Solution s;
    vector<string> m1{"@.a.#","###.#","b.A.B"};
    CHECK(s.shortestPathAllKeys(m1) == 8);
    vector<string> m2{"@..aA","..B#.","....b"};
    CHECK(s.shortestPathAllKeys(m2) == 6);
    vector<string> m3{"@Aa"};
    CHECK(s.shortestPathAllKeys(m3) == -1);
    vector<string> m4{"bA@aBcC"};
    CHECK(s.shortestPathAllKeys(m4) == 9);
    vector<string> m5{
        "#.............c.#.#...#.#.#.C.",
        ".##...#....#..#..##...........",
        "....##..........#...#..#....#.",
        ".a......#..#.#...#...#......##",
        "........#......##.............",
        "..#......E.#..##.......#......",
        ".#........B.#.#....#.........#",
        "A....#.##.....#..#............",
        "..#F#.#....#..###..##..#..##..",
        "...#.##.#..........#..#.......",
        "#....#....#..#......#...#....#",
        "#..#.#...........#........#.#.",
        "#.#.....##....#..#..#....##.#.",
        ".#..D..##...##.....###......#.",
        "...#.....###...#....#.#...#.#.",
        "#......#.......##..###........",
        ".............##..#.......#....",
        ".#####...##.....#...#....#.#..",
        "..#....@..#.#.#.....#..##.....",
        "#..##.#..#..#..f.#.#..........",
        ".#.......#....#.......#.#..#..",
        "..........#.........d#.......#",
        "......#....................#..",
        "#..#...#...#...#....#...#e.#..",
        ".............#.....#..b.....##",
        ".#......#...........##..#.....",
        ".....#................###.....",
        "....#....#..#..#..#......#..#.",
        "......##.....#.##.#.#...#....#",
        ".....##.#.......#.#....#.#.##."};
    CHECK(s.shortestPathAllKeys(m5) == 83);
}
