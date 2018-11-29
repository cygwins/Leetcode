/*
 * Gift Wrapping / Jarvis March, O(nh), h is # of points on convex hull
 * each step, find the most clockwise one (if colinear, the shortest one)
 */
#include "../Point.hpp"
#include <vector>
#include <set>
#include "catch.hpp"
using std::vector;
using std::set;
using namespace Geometry;

class Solution {
public:
    vector<Point> outerTrees(vector<Point>& points) {
        if(points.size() < 4) return points;
        set<Point> all(points.begin(), points.end()), hull;
        Point start = *all.begin(), cur = start, nxt; // by < order start is leftmost-then-lowest point
        do {
            hull.insert(cur); // points on hull should go anti-clockwise
            nxt = cur == start ? *(all.begin()++) : start; // get a valid start point for searching nxt
            for(auto &tmp : all) {
                int orient = Xprod(nxt - cur, tmp - cur);
                if( orient < 0 ||  // nxt should be the most clockwise one
                    (orient == 0 && hull.find(tmp) == hull.end() && // collinear and closest to cur
                     (nxt == start || len(tmp - cur) < len(nxt - cur))) ) {
                    nxt = tmp;
                }
            }
            cur = nxt;
        } while( nxt != start );
        return vector<Point>(hull.begin(), hull.end());
    }
};

bool equivalent(const vector<Point> &A, const vector<Point> &B) {
    set<Point> a, b;
    for(auto &i : A) a.insert(i);
    for(auto &i : B) b.insert(i);
    return a == b;
}

bool isHull(Solution &s, const vector<vector<int>> &hull, const vector<vector<int>> &points) {
    vector<Point> p = parsePoints( points );
    return equivalent( s.outerTrees( p ), parsePoints( hull ));
}

TEST_CASE("gift wrapping", "[Jarvis Convex Hull]") {
    Solution s;
    CHECK( isHull( s, {{0,0}, {1,0}, {0,1}}, {{0,0}, {1,0}, {0,1}} ));
    CHECK( isHull( s, {{1,1},{2,0},{4,2},{3,3},{2,4}}, {{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}} ));
    CHECK( isHull( s, {{0,3},{1,2},{2,1},{3,0},{4,0},{5,0},{6,1},{7,2},{7,3},{7,4},{6,5},{5,5},{4,5},{3,5},{2,5},{1,4}}, {{3,0},{4,0},{5,0},{6,1},{7,2},{7,3},{7,4},{6,5},{5,5},{4,5},{3,5},{2,5},{1,4},{1,3},{1,2},{2,1},{4,2},{0,3}} ));
}
