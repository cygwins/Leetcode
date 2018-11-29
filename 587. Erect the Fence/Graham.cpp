/*
 * Graham Scan, O(nlogn)
 * sort all points by angle w/ respect to first, pop non-hull in stack and push when proceeding
 */
#include "../Point.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>
#include "catch.hpp"
using std::vector;
using std::stack;
using std::set;
using namespace Geometry;

class Solution {
public:
    vector<Point> outerTrees(vector<Point>& points) {
        if(points.size() < 4) return points;
        stack<Point> hull;
        // first, find lowest-then leftmost as starting point. It is on hull
        sort(points.begin(), points.end(), [](const Point &A, const Point &B) {
                return A.y < B.y || (A.y == B.y && A.x < B.x); });
        Point start = points[0];

        // then, sort all points by the angle from start point to it with x axis
        sort(points.begin() + 1, points.end(), [start](const Point &A, const Point &B) {
                int turn = Xprod( A - start, B - start );
                if( turn > 0 ) return true;
                if( turn == 0 ) { return (A - start).x > 0 ? len(A - start) < len(B - start)
                                                           : len(A - start) > len(B - start); }
                return false; }); // alpha: 0 ~ pi

        // graham, accept/reject each point in order
        hull.push( start );
        hull.push( points[1] );
        for(int i = 2; i < points.size();) {
            Point top = hull.top(), second = secondTop( hull ), step1 = top - second, step2 = points[i] - top;
            int orient = Xprod( step1, step2 );
            if( orient > 0 || (orient == 0 && len(top - second) < len(points[i] - second)) ) { // turing left
                hull.push( points[i++] );
            } else { // turning right
                if(!hull.empty()) hull.pop();
                else break;
            }
        }
        vector<Point> answer;
        while( !hull.empty() ) {
            answer.push_back( hull.top() );
            hull.pop();
        }
        return answer;
    }

    Point secondTop(stack<Point> &s) {
        if(s.size() < 2) throw "There is no second top";
        Point top = s.top();
        s.pop();
        Point second = s.top();
        s.push(top);
        return second;
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
