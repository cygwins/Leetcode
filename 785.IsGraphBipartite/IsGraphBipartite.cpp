/*
 * Use recursive Depth-First Search to tag all nodes into two group
 */
#include <iostream>
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int N = graph.size();
        tags = vector<int>(N, -1); // tag all nodes as "untagged"
        for(int i = 0; i < N; ++i) { // graph may be disconnected
            if(tags[i] == -1 && !addTag(graph, i, 0)) { // tag each untagged node as group A
                return false; // false if fail to tag some node
            }
        }
        return true;
    }

    bool addTag(vector<vector<int>>& graph, int i, int tag) {
        if(tags[i] == -1) { // untagged
            tags[i] = tag;
            for(auto &j : graph[i]) { // for each i's neighbor
                if(!addTag(graph, j, 1 - tag)) {
                    return false;
                }
            }
        }
        else { // tagged, check if tag align
            return tags[i] == tag;
        }
        return true;
    }
private:
    vector<int> tags;
};

TEST_CASE("tagging nodes in graph", "[check bipartite]") {
    Solution s;
    vector<vector<int>> g{{1,3},{0,2},{1,3},{0,2}};
    CHECK(s.isBipartite(g) == true);
    vector<vector<int>> h{{1,2,3},{0,2},{0,1,3},{0,2}};
    CHECK(s.isBipartite(h) == false);
}
