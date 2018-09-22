/*
 * dp[i][j] = isMatch( s.substr(i), p.substr(j) );
 * p[j+1] == '*': dp[i][j] = && ( firstMatch && dp[i+1][j]  || dp[i][j+2] )
 * p[j+1] != '*': dp[i][j] = firstMatch && dp[i+1][j+1]
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
        for( int i = S; i >= 0; --i ) { // i = S: check empty s match trailing p
            for( int j = P - 1; j >= 0; --j ) {
                bool firstMatch = i < S && ( s[i] == p[j] || p[j] == '.' );
                if( j + 1 < P && p[j + 1] == '*' )
                    dp[i][j] = dp[i][j + 2] || // match 0
                               ( firstMatch && dp[i + 1][j] );
                else
                    dp[i][j] = firstMatch && dp[i + 1][j + 1];
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
    CHECK( s.isMatch( "aa", "a*" ) == true );
    CHECK( s.isMatch( "ab", ".*" ) == true );
    CHECK( s.isMatch( "aab", "c*a*b" ) == true );
    CHECK( s.isMatch( "mississippi", "mis*is*p*." ) == false );
}
