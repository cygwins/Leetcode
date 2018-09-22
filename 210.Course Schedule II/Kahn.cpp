/*
 * Topological sorting using Kahn's algorithm
 * extract node without incoming edge, remove related edges, repeat
 */
#include <iostream>
#include <vector>
#include <utility> // pair
#include <queue>
#include "catch.hpp"
using std::vector;
using std::pair;
using std::queue;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> inD(numCourses, 0); // in-degree of node
        vector<vector<int>> outN(numCourses, vector<int>{}); // out going neighbor from node
        queue<int> availables;
        vector<int> sorted;
        for(auto &p : prerequisites) { // p.first <-- p.second
            ++inD[p.first];
            outN[p.second].push_back(p.first);
        }
        for(int i = 0; i < numCourses; ++i) if(inD[i] == 0) availables.push(i);
        while(!availables.empty()) {
            int u = availables.front();
            sorted.push_back(u);
            availables.pop();
            for(int &v : outN[u]) if(--inD[v] == 0) availables.push(v);
        }
        return sorted.size() == numCourses ? sorted : vector<int>{};
    }
};

TEST_CASE("checking queue-based Khan's algorithm topological sorting", "[findOrder]") {
    Solution s;
    vector<pair<int, int>> g{{1,0}}, h{{1,0},{2,0},{3,1},{3,2}}, l{{1,0},{1,2},{0,1}};
    CHECK(s.findOrder(2,g) == vector<int>{0,1});
    CHECK((s.findOrder(4,h) == vector<int>{0,1,2,3}
        || s.findOrder(4,h) == vector<int>{0,2,1,3}));
    CHECK(s.findOrder(3,l) == vector<int>{});
}
