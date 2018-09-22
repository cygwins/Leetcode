/*
 * dp[i][j] = # of length i+1 with last one the j+1 th least
 * 2D -> 1D dp: cur[i] is # of length cur.size() with last one the i+1 -th least
 */
#include <vector>
#include <string>
#include "catch.hpp"
using std::vector;
using std::string;

class Solution {
public:
    int numPermsDISequence(string S) {
        int n = S.size(), mod = 1e9 + 7;
        vector<int> cur{1};
        for( int i = 0; i < n; ++i ) {
            vector<int> next( cur.size() + 1, 0 );
            int sum = 0;
            if( S[i] == 'D' ) {
                for( int j = cur.size() - 1; j >= 0; --j ) {
                    sum += cur[j]; sum %= mod;
                    next[j] = sum;
                }
            } else { // 'I'
                for( int j = 0; j < cur.size(); ++j ) {
                    sum += cur[j]; sum %= mod;
                    next[j + 1] = sum;
                }
            }
            cur = next;
        }
        int ret = 0;
        for( int i = 0; i < cur.size(); ++i ) {
            ret += cur[i]; ret %= mod;
        }
        return ret;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    CHECK(s.numPermsDISequence("DID") == 5);
    CHECK(s.numPermsDISequence("DIDD") == 9);
}
