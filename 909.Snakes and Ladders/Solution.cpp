/*
 * bfs
 */
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <utility>
#include "catch.hpp"
using std::vector;
using std::queue;
using std::unordered_set;
using std::make_pair;
using std::pair;

class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int N = board.size();
        queue<pair<int,int>> q; // step, position
        unordered_set<int> been;
        q.push(make_pair(0,1));
        been.insert(1);
        while(!q.empty()) {
            int step = q.front().first;
            int pos = q.front().second;
            if(pos == N * N) return step;
            // std::cout << "Now: " << step << " " << pos << std::endl;
            q.pop();
            if( step > N * N ) return -1;
            for(int i = 1; i <= 6; ++i) {
                if( pos + i <= N * N ) {
                    auto rc = n2rc( pos + i, N );
                    int r = rc.first, c = rc.second;
                    // std::cout << "S: " << r << " " << c << std::endl;
                    if(board[r][c] == -1 && been.find(pos + i) == been.end() ) {
                        q.push(make_pair(step + 1, pos + i));
                        been.insert(pos + i);
                    } else if(been.find(board[r][c]) == been.end()){
                        q.push(make_pair(step + 1, board[r][c]));
                        been.insert(board[r][c]);
                    }
                }
            }
        }
        return -1;
    }
    pair<int, int> n2rc(int n, int N) {
        int r = (n - 1) / N;
        int c = r % 2 ? N - (n - r * N) : n - r * N - 1;
        return make_pair(N - 1 - r, c);
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<vector<int>> b1{
        vector<int>{-1,-1,-1,-1,-1,-1},
        vector<int>{-1,-1,-1,-1,-1,-1},
        vector<int>{-1,-1,-1,-1,-1,-1},
        vector<int>{-1,35,-1,13,-1,-1},
        vector<int>{-1,-1,-1,-1,-1,-1},
        vector<int>{-1,15,-1,-1,-1,-1}};
    CHECK(s.snakesAndLadders(b1) == 4);
}
