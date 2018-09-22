/*
 * Put n items into k bucket so each bucket has same total item value.
 * - For each bucket, try all possible content O(k*2^n) -- no good.
 * - For each item, try all possible destined bucket O(n^k) -- doable.
 */
#include <vector>
#include <algorithm> // sort, reverse
#include "catch.hpp"
using std::vector;

class Solution {
public:
    // use global variables to avoid long parameter list
    int target; // of each bucket
    vector< int > ns;
    vector< int > bucket;

    bool canPartitionKSubsets( vector<int>& nums, int k ) {
        int sum = 0;
        for( int &n : nums ) sum += n;
        if( sum % k ) return false; // not divisible
        target = sum / k;
        ns = vector< int >( nums );
        bucket = vector< int >( k, 0 );
        // starting with bigger ones makes it faster
        sort( ns.begin(), ns.end() );
        reverse( ns.begin(), ns.end() );
        return put( 0 );
    }

    // put #n item of ns into some bucket to meet target
    bool put( int n ) {
        for( int i = 0; i < bucket.size(); ++i ) {
            if( bucket[i] + ns[n] > target ) continue; // try next bucket
            bucket[i] += ns[n]; // put it in!
            if( n == ns.size() - 1 ) return true; // all items in bucket, no overflow
            if( put( n + 1 ) ) return true; // move on to next item
            else { // no solution = wrong bucket
                bucket[i] -= ns[n]; // take it out
                if( bucket[i] == 0 ) return false; // no need to try other empty bucket
            }
        }
        return false; // no bucket fits
    }
};

TEST_CASE( "allocating", "[canPartitionKSubsets]" ) {
    Solution s;
    vector< int > nums{ 4, 3, 2, 3, 5, 2, 1 };
    CHECK( s.canPartitionKSubsets( nums, 4 ) == true );
    CHECK( s.canPartitionKSubsets( nums, 5 ) == false );
}
