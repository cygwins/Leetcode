/*
 * Total pay = Total quality of k workers * max wage per quality ratio of k workers
 * Start from k workers with lowest wage per quality ratio,
 * raise the ratio bar and kick out the worker with highest quality.
 */
#include <iostream>
#include <algorithm> // sort, min
#include <vector>
#include <queue>
#include "catch.hpp"
using std::vector;
using std::priority_queue;
using std::sort;
using std::min;

class Solution {
public:
    struct Worker {
        double quality;
        double wage;
        double ratio;
        Worker( double q, double w ) : quality(q), wage(w), ratio( wage / quality ) { }
    };
    double mincostToHireWorkers(vector<int> q, vector<int> w, int K) {
        vector<Worker> workers;
        for ( int i = 0; i < q.size(); ++i ) workers.push_back( Worker( q[i], w[i] ));
        sort( workers.begin(), workers.end(), // lowest ratio are chosen first
              [](Worker &a, Worker &b){ return a.ratio < b.ratio; });
        priority_queue<double> KQuality; // hold the qualities of current K workers
        double totalQuality = 0;
        for( int i = 0; i < K; ++i ) {
            KQuality.push( workers[i].quality );
            totalQuality += workers[i].quality;
        }
        double mincost = totalQuality * workers[K - 1].ratio;
        for ( int i = K; i < workers.size(); ++i ) {
            totalQuality += workers[i].quality;
            KQuality.push( workers[i].quality );
            totalQuality -= KQuality.top();
            KQuality.pop(); // if pop the one we just pushed, we get strictly larger cost
            mincost = min(mincost, totalQuality * workers[i].ratio);
        }
        return mincost;
    }
};

TEST_CASE("processing", "[mincostToHireWorkers]") {
    Solution s;
    vector<int> q1{10,20,5}, w1{70,50,30};
    CHECK(s.mincostToHireWorkers( q1, w1, 2 ) == Approx( 105.00000 ).epsilon(1e-5) );
    vector<int> q2{3,1,10,10,1}, w2{4,8,2,2,7};
    CHECK(s.mincostToHireWorkers( q2, w2, 3 ) == Approx( 30.66667 ).epsilon(1e-5) );
}
