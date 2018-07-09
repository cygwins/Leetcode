/*
 * decompose string to special string unit,
 * recursively solve each unit,
 * rearrange them in lexicographical order
 */
#include <iostream>
#include <string>
#include <set>
#include "catch.hpp"
using std::string;
using std::multiset;

class Solution {
public:
    string makeLargestSpecial(string S) {
        if(S == "" || S == "10") return S;
        multiset<string> subSpecial;
        int head = 0, count = 0;
        for( int i = 0; i < S.size(); ++i ) {
            if( S[i] == '1' ) ++count;
            else if( S[i] == '0' ) --count;
            if( count == 0 ) { // closing 0 matched
                if( head == 0 && i == S.size() - 1 && S.size() > 2 ) { // can safely remove outmost 10
                    return "1" + makeLargestSpecial( S.substr( 1, S.size() - 2) ) + "0";
                }
                string subLargest = makeLargestSpecial( S.substr( head, i + 1 - head ) ); // maximize inner structure
                subSpecial.insert( subLargest );
                count = 0;
                head = i + 1;
            }
        }
        string ans = "";
        for( auto &s : subSpecial ) ans = s + ans; // big + small
        return ans;
    }
};

TEST_CASE("rearranging", "[makeLargestSpecial]") {
    Solution s;
    CHECK( s.makeLargestSpecial( "11011000" ) == "11100100" );
    CHECK( s.makeLargestSpecial( "111010001100" ) == "111010001100" );
    CHECK( s.makeLargestSpecial( "110011011000" ) == "111001001100" );
}
