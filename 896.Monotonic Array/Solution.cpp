/*
 * brief
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        if( A.size() <= 2 ) return true;
        if( A[0] == A[1] ) return isMonotonicTBD( A, 1 );
        if( A[0] >= A[1] ) return isMonotonicDec( A, 1 );
        if( A[0] <= A[1] ) return isMonotonicInc( A, 1 );
    }
    bool isMonotonicTBD(vector<int>& A, int head) {
        if( A.size() - head <= 1 ) return true;
        if( A[head] == A[head + 1] ) return isMonotonicTBD( A, head + 1 );
        if( A[head] >= A[head + 1] ) return isMonotonicDec( A, head + 1 );
        if( A[head] <= A[head + 1] ) return isMonotonicInc( A, head + 1 );
    }
    bool isMonotonicInc(vector<int>& A, int head) {
        if( A.size() - head <= 1 ) return true;
        return A[head] <= A[head + 1] && isMonotonicInc( A, head + 1 );
    }
    bool isMonotonicDec(vector<int>& A, int head) {
        if( A.size() - head <= 1 ) return true;
        return A[head] >= A[head + 1] && isMonotonicDec( A, head + 1 );
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<int> a;
    a = vector<int>{1,2,2,3};
    CHECK(s.isMonotonic( a ) == true );
    a = vector<int>{3,2,2,1};
    CHECK(s.isMonotonic( a ) == true );
    a = vector<int>{1,3,2};
    CHECK(s.isMonotonic( a ) == false );
    a = vector<int>{1,1,1};
    CHECK(s.isMonotonic( a ) == true );
    a = vector<int>{1,1};
    CHECK(s.isMonotonic( a ) == true );
    a = vector<int>{1,};
    CHECK(s.isMonotonic( a ) == true );
    a = vector<int>{};
    CHECK(s.isMonotonic( a ) == true );
}
