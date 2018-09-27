/*
 * Greedy: while time goes, update the amount of course could be taken before this time.
 * Sort the courses by end time, and iterate through to examine one by one..
 * If a course cannot be added to the taken list, try replace it with the longest duration already taken,
 * so the amount of course would remain same, but the finish time is shifted earlier.
 * Maintain a priority queue of the taken courses by their duration to get longest.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // sort
#include "catch.hpp"
using std::vector;
using std::sort;
using std::priority_queue;

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        if( courses.empty() ) return 0;
        auto lessDur = [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; };
        auto lessEnd = [](vector<int>& a, vector<int>& b) { return a[1] < b[1]; };
        sort(courses.begin(), courses.end(), lessEnd);
        priority_queue<vector<int>, vector<vector<int>>, decltype(lessDur)> q(lessDur);
        int curT = 0, count = 0;
        for(auto &c : courses) {
            if( curT + c[0] <= c[1] ) { // add to list
                count++;
                curT += c[0];
                q.push(c);
            } else if ( !q.empty() ) {
                int l = q.top()[0];
                if( l > c[0] && curT - l + c[0] <= c[1] ) {
                    curT -= l - c[0]; // shift earlier by changing longest course to this one
                    q.pop();
                    q.push(c); // count doesn't change
                }
            }
        }
        return count;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<vector<int>> c1{{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
    CHECK(s.scheduleCourse(c1) == 3);
}
