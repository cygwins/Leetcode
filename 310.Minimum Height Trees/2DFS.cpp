/*
 * twice DFS:
 * 1. find the farthest node from 0: f
 * 2. find the farthest node from f: g
 * root must be mid point (or 2 mid points) of path f---g
 */
#include <iostream>
#include <vector>
#include <utility> // pair
#include "catch.hpp"
using std::vector;
using std::pair;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        if(n < 1) { return vector<int>{}; }
        if(n == 1) { return vector<int>{0}; }
        prev = vector<int>(n); // for path seeking
        E = vector<vector<int>>(n, vector<int>{}); // neighbors of u
        for(auto &p : edges) {
            E[p.first].push_back(p.second);
            E[p.second].push_back(p.first);
        }
        d = 0; maxL = 0; DFS(0, -1); f = farthest;
        d = 0; maxL = 0; DFS(f, -1); g = farthest;
        vector<int> answer;
        int u = g;
        for(int i = 0; i < maxL / 2; ++i) { // find mid point
            u = prev[u];
        }
        answer.push_back(u);
        if(maxL % 2 == 1) { // odd path length, two mid points
            answer.push_back(prev[u]); // note maxL >= 1
        }
        return answer;
    }
private:
    int farthest, f, g; // 0 -> f, f -> g
    int d, maxL; // current depth, length of longest path
    vector<vector<int>> E; // adjacency list
    vector<int> prev;
    void DFS(int u, int parent) {
        for(auto &v : E[u]) {
            if(v != parent) {
                ++d;
                prev[v] = u;
                if(d > maxL) { // farthest reached
                    maxL = d;
                    farthest = v;
                }
                DFS(v, u);
                --d;
            }
        }
    }
};

TEST_CASE("using tree DP", "[check findMinHeightTrees]") {
    Solution s;
    vector<pair<int,int>> g{{1,0},{1,2},{1,3}}, h{{0,3},{1,3},{2,3},{4,3},{5,4}};
    vector<int> a{1}, b{3,4};
    CHECK(s.findMinHeightTrees(4,g) == a);
    CHECK(s.findMinHeightTrees(6,h) == b);
}
