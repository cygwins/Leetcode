/*
 * dp[i][j] = isMatch( s.substr(i), p.substr(j) );
 */
#include <iostream>
#include <string>
#include <vector>
#include "catch.hpp"
using std::string;
using std::vector;
using std::cout;
using std::endl;

class Solution {
public:
    bool isMatch(string s, string p) {
        int S = s.size(), P = p.size();
        vector< vector< bool >> dp( S + 1, vector< bool >( P + 1, false ));
        dp[S][P] = true; // isMatch( "", "" )
        for( int j = P - 1; j >= 0 && p[j] == '*'; --j ) dp[S][j] = true; // trailing * match ""
        for( int i = S - 1; i >= 0; --i ) {
            for( int j = P - 1; j >= 0; --j ) {
                dp[i][j] = ( s[i] == p[j] || p[j] == '?' || p[j] == '*' ) && dp[i + 1][j + 1]; // 1-1 match
                if( p[j] == '*' ) {
                    dp[i][j] = dp[i][j] || dp[i][j + 1]; // leading * match ""
                    dp[i][j] = dp[i][j] || dp[i + 1][j]; // * match multiple char
                }
            }
        }
        return dp[0][0];
    }
private:
    void print( string &s, string &p, vector< vector< bool >> &table, int i, int j ) {
        cout << ' ';
        for( int l = 0; l < p.size(); ++l ) cout << p[l];
        cout << endl;
        for( int k = 0; k <= s.size(); ++k ) {
            cout << ( k < s.size() ? s[k] : '$' );
            for( int l = 0; l <= p.size(); ++l ) {
                if( k < i || ( k == i && l < j )) cout << '.';
                else cout << table[k][l];
            }
            cout << endl;
        }
    }
};

TEST_CASE("matching", "[isMatch]") {
    Solution s;
    CHECK( s.isMatch( "aa", "a" ) == false );
    CHECK( s.isMatch( "aa", "*" ) == true );
    CHECK( s.isMatch( "cb", "?a" ) == false );
    CHECK( s.isMatch( "adceb", "*a*b" ) == true );
    CHECK( s.isMatch( "acdcb", "a*c?b" ) == false );
}
