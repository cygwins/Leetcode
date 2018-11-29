/*
 * Quick Hull, O(nlogn)
 * find leftmost point A and rightmost point C, for each half divided, find the point C furthest to line AB,
 * repeat with AC and furthest point outside ABC. Same with CB.
 */
#include "../Point.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "catch.hpp"
using std::vector;
using std::set;
using namespace Geometry;

class Solution {
public:
    vector<Point> outerTrees(vector<Point>& points) {
        if(points.size() < 4) return points;
        // sort points from left to right
        sort(points.begin(), points.end(), [](const Point &A, const Point &B) {
                return A.x < B.x; });
        Point A = points[0], B = points[points.size() - 1];
        set<Point> upper, lower, hull;
        hull.insert( A );
        hull.insert( B );
        for(auto &p : points) {
            int height = Xprod( B - A, p - A );
            if( height >= 0 ) upper.insert( p );
            if( height <= 0 ) lower.insert( p );
        }
        quickhull( upper, A, B, hull );
        quickhull( lower, B, A, hull );
        return vector<Point>(hull.begin(), hull.end());
    }

    void quickhull( set<Point> &points, Point &A, Point &B, set<Point> &hull ) {
        if( points.empty() ) return;
        Point C = A;
        int maxh = 0;
        for(auto &p : points) {
            int h = Xprod( B - A, p - A );
            if( h > maxh ) {
                maxh = h;
                C = p;
            }
        }
        if( maxh == 0 && C == A ) { // degenerated, all possible C are on AB
            for(auto &p : points) hull.insert( p );
            return;
        }
        hull.insert( C );
        set<Point> left, right;
        for(auto &p : points) {
            if( Xprod( C - A, p - A ) >= 0 ) left.insert( p );
            if( Xprod( B - C, p - C ) >= 0 ) right.insert( p );
        }
        quickhull( left, A, C, hull );
        quickhull( right, C, B, hull );
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

TEST_CASE("scanning", "[Graham Scan]") {
    Solution s;
    CHECK( isHull( s, {{0,0}, {1,0}, {0,1}}, {{0,0}, {1,0}, {0,1}} ));
    CHECK( isHull( s, {{1,1},{2,0},{4,2},{3,3},{2,4}}, {{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}} ));
    CHECK( isHull( s, {{0,3},{1,2},{2,1},{3,0},{4,0},{5,0},{6,1},{7,2},{7,3},{7,4},{6,5},{5,5},{4,5},{3,5},{2,5},{1,4}}, {{3,0},{4,0},{5,0},{6,1},{7,2},{7,3},{7,4},{6,5},{5,5},{4,5},{3,5},{2,5},{1,4},{1,3},{1,2},{2,1},{4,2},{0,3}} ));
}
