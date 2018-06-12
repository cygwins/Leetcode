/*
 * using dynamic programming on a tree to calculate the tree height H[u] with u as root
 * H[u] = max(upperH[u], lowerH[u])
 * https://github.com/lydxlx1/LeetCode/blob/master/src/_310_1.java
 */
#include <iostream>
#include <vector>
#include <algorithm> // max
#include <utility>
#include "catch.hpp"
using std::vector;
using std::pair;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
        upperH = vector<int>(n, 0); // upper tree height
        lowerH = vector<int>(n, 0); // lower tree height
        lowerH2 = vector<int>(n, 0); // second high lower tree branch
        H = vector<int>(n, 0); // tree height if u is root
        E = vector<vector<int>>(n, vector<int>{}); // neighbors of u
        minH = -1; // best root not found yet
        for(auto &p : edges) {
            E[p.first].push_back(p.second);
            E[p.second].push_back(p.first);
        }
        solveLowerHs(0, -1);
        solveH(0, -1);
        vector<int> answer;
        for(int u = 0; u < n; ++u) {
            if(H[u] == minH) {
                answer.push_back(u);
            }
        }
        return answer;
    }
private:
    // upperH[u]: in the sub-tree removing all u's descendants,
    // the length of the longest path starting from u, or, the height of u when up-side-down
    vector<int> upperH;

    // lowerH[u]: in the sub-tree of u and all u's descendants,
    // the length of the longest path starting from u, or, the height of u in original tree
    vector<int> lowerH;

    // lowerH2[u]: like lowerH[u],
    // the second longest path starting from u and first going through ANOTHER direct child
    vector<int> lowerH2;

    // H[u] = max(upperH[u], lowerH[u]);
    vector<int> H;

    // E[u]: all u's neighbor - parent and children
    vector<vector<int>> E;

    int minH; // minimum height of all H[u];

    // solve for lowerH and lowerH2, bottom up
    void solveLowerHs(int u, int parent) {
        for(int &v : E[u]) {
            if(v != parent) { // only go for child
                solveLowerHs(v, u);
                int h = lowerH[v] + 1;
                if(h > lowerH[u]) { // longest to bottom via v
                    lowerH2[u] = lowerH[u];
                    lowerH[u] = h;
                } else if (h > lowerH2[u]) { // second longest to bottom via v 
                    lowerH2[u] = h;
                }
            }
        }
    }

    // solve for upperH and thus H, top down
    void solveH(int u, int parent) {
        H[u] = std::max(upperH[u], lowerH[u]);
        if(H[u] < minH || minH == -1) { // best root
            minH = H[u];
        }
        for(int &v : E[u]) {
            if(v != parent) {
                int h1; // length of path that come up to u and then down to other sibling
                if(lowerH[v] + 1 == lowerH[u]) { // v leads to that longest path
                    h1 = lowerH2[u] + 1;
                } else { // v has a longer sibling
                    h1 = lowerH[u] + 1;
                }
                int h2 = upperH[u] + 1; // path come up to u and further upward
                upperH[v] = std::max(h1, h2);
                solveH(v, u);
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
