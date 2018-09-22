/*
 * using Union Find to check if the two nodes of an edge are already connected
 */
#include <iostream>
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        vector<int> parent(edges.size() + 1, 0);
        for(auto &v : edges) {
            if(find(parent, v[0]) == find(parent, v[1])) return vector<int>{v[0], v[1]};
            else join(parent, v[0], v[1]);
        }
        return vector<int>{}; // won't reach here
    }
    int find(vector<int> &parent, int i) { // find i's root
        if(parent[i] == 0) parent [i] = i; // new isolated point
        int root = i;
        while(root != parent[root]) root = parent[root];
        int p = i, temp;
        while(p != root) { // compress all ancestors to root
            temp = parent[p]; // save original parent
            parent[p] = root;
            p = temp;
        }
        return parent[i];
    }
    void join(vector<int> &parent, int i, int j) {
        parent[parent[i]] = parent[j];
    }
};

TEST_CASE("finding parent", "[findRedundantConnection]") {
    Solution s;
    vector<vector<int>> e{{1,2},{1,3},{2,3}},f{{1,2},{2,3},{3,4},{1,4},{4,5}};
    CHECK(s.findRedundantConnection(e) == vector<int>{2,3});
    CHECK(s.findRedundantConnection(f) == vector<int>{1,4});
}
