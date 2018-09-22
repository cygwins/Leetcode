/*
 * procedure oriented
 */
#include <iostream>
#include <unordered_set>
#include <string>
#include "catch.hpp"
using std::string;
using std::unordered_set;

class Solution {
public:
    bool buddyStrings(string A, string B) { // A.swap( one, two ) == B
        if( A.size() != B.size() ) return false;
        int i = 0, one = -1, two = -1;
        bool repeat = false; // for self-swap
        unordered_set< char > exist;
        while( i < A.size() && A[i] == B[i] ) { // [0, one)
            if( exist.find( A[i] )  != exist.end() ) repeat = true;
            else exist.insert(A[i]);
            ++i;
        }
        if( i == A.size() )return repeat; // A == B: can self swap?
        one = i++;
        while( i < A.size() && A[i] == B[i] ) { // [one, two)
            ++i;
        }
        if( i == A.size() ) return false; // only one diff
        two = i++;
        while( i < A.size() && A[i] == B[i] ) { // [two, end)
            ++i;
        }
        if( i != A.size() ) return false; // more than two diff
        return A[one] == B[two] && A[two] == B[one];
    }
};

TEST_CASE("processing", "[buddyStrings]") {
    Solution s;
    CHECK(s.buddyStrings( "ab", "ba" ) == true );
    CHECK(s.buddyStrings( "ab", "ab" ) == false );
    CHECK(s.buddyStrings( "aa", "aa" ) == true );
    CHECK(s.buddyStrings( "aaaaaaabc", "aaaaaaacb" ) == true );
    CHECK(s.buddyStrings( "", "aa" ) == false );
}
