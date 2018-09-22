/*
 * DFS to find if there is any cycle
 * ref: https://leetcode.com/problems/course-schedule/discuss/58509/18-22-lines-C++-BFSDFS-Solutions
 */
#include <iostream>
#include <vector>
#include <utility> // pair
#include "catch.hpp"
using std::vector;
using std::pair;

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        outN = vector<vector<int>>(numCourses, vector<int>{});
        visited = inStack = vector<bool>(numCourses, false);
        for(auto &p : prerequisites) outN[p.second].push_back(p.first);
        for(int u = 0; u < numCourses; ++u) if(hasCycle(u)) return false;
        return true; // all nodes visited without finding any cycle
    }
    bool hasCycle(int u) {
        if(visited[u]) return false; // same as reaching a leaf
        visited[u] = inStack[u] = true;
        for(int &v : outN[u]) if(inStack[v] || hasCycle(v)) return true;
        return inStack[u] = false;
    }

private:
    vector<vector<int>> outN; // out going neighbor from node
    vector<bool> visited; // ever
    vector<bool> inStack; // currently in DFS stack
};

TEST_CASE("detecting cycle", "[canFinish]") {
    Solution s;
    vector<pair<int, int>> g{{1,0}}, h{{1,0},{0,1}};
    CHECK(s.canFinish(2,g) == true);
    CHECK(s.canFinish(2,h) == false);
}
