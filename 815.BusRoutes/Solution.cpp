/*
 * BFS with route as node, two routes are connected if share same stop(s)
 */
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "catch.hpp"
using std::vector;
using std::queue;
using std::unordered_set;
using std::unordered_map;
using std::max;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        int N = routes.size();
        int M = 0; // max stop number
        unordered_map<int, unordered_set<int>> routelist; // routes on stop
        for( int r = 0; r < N; ++r ) {
            for( int &s : routes[ r ] ) {
                routelist[ s ].insert( r );
                M = max( M, s );
            }
        }
        queue<vector<int>> Q;
        vector< bool > taken( N, false );
        vector< bool > been( M + 1, false );
        Q.push( {S, 0} );
        been[ S ] = true;
        while( !Q.empty() ) {
            int curS = Q.front()[0];
            int step = Q.front()[1];
            if( curS == T ) return step;
            for( auto &r : routelist[ curS ] ) {
                if( !taken[ r ] ) {
                    for( auto &s : routes[r] ) {
                        if( !been[ s ] ) {
                            Q.push( {s, step + 1} );
                            been[ s ] = true;
                        }
                    }
                    taken[ r ] = true;
                }
            }
            Q.pop();
        }
        return -1;
    }
};

TEST_CASE("routing", "[numBusesToDestination]") {
    Solution s;
    vector<vector<int>> r1 = {{1, 2, 7}, {3, 6, 7}};
    CHECK(s.numBusesToDestination(r1, 1, 6) == 2);
    CHECK(s.numBusesToDestination(r1, 1, 1) == 0);
}
