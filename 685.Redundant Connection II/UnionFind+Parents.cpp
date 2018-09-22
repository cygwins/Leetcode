/*
 * check double parents,
 * return cycle parent (one must be in the cycle),
 * or second parent (if no cycle),
 * or last in cycle (if no double parents).
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        vector<int> parent(edges.size() + 1, 0), firstP, secondP;
        for(auto &v : edges) // double parents check
            if(parent[v[1]]) { firstP = {parent[v[1]], v[1]}; secondP = v; break; }
            else parent[v[1]] = v[0];
        for(int i = 1; i < edges.size() + 1; ++i) parent[i] = i; // ready for union find
        for(auto &v : edges) // regular cycle check when each has only one parent
            if(v == secondP) continue;
            else if(find(parent, v[0]) == v[1]) // cycle! return last or cycle parent
                return firstP.empty() ? v : find(parent, firstP[0]) == v[1] ? firstP : secondP;
            else parent[v[1]] = parent[v[0]]; // v[1] was root before
        return secondP; // no cycle in the graph, return second parent
    }
    int find(vector<int> &parent, int i) { // find i's root
        if(parent[i] != i) parent[i] = find(parent, parent[i]); // recursive compression
        return parent[i];
    }
};

TEST_CASE("finding parents & cycle", "[findRedundantDirectedConnection]") {
    Solution s;
    vector<vector<int>> parents{{1,2},{1,3},{2,3}};
    vector<vector<int>> cycle{{1,2},{2,3},{3,4},{4,1},{1,5}};
    vector<vector<int>> parentsCycle{{2,1},{3,1},{4,2},{1,4}};
    vector<vector<int>> parentsCycle1{{3,4},{4,1},{2,3},{1,2},{5,1}};
    vector<vector<int>> parentsCycle2{{3,4},{5,1},{2,3},{1,2},{4,1}};
    CHECK(s.findRedundantDirectedConnection(parents) == vector<int>{2,3});
    CHECK(s.findRedundantDirectedConnection(cycle) == vector<int>{4,1});
    CHECK(s.findRedundantDirectedConnection(parentsCycle) == vector<int>{2,1});
    CHECK(s.findRedundantDirectedConnection(parentsCycle1) == vector<int>{4,1});
    CHECK(s.findRedundantDirectedConnection(parentsCycle2) == vector<int>{4,1});
}
