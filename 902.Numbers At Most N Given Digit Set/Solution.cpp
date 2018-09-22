/*
 * after all smaller possibilities, check most possible digits from high to low
 */
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include "catch.hpp"
using std::vector;
using std::find;
using std::string;
using std::to_string;
using std::stoi;

class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& D, int N) {
        int n = D.size();
        if( n == 0 ) return 0;
        int sub = 1, ret = 0;
        vector<int> all{1};
        string Ns = to_string( N );
        for( int i = 1; i < Ns.size(); ++i ) {
            sub *= n;
            ret += sub;
            all.push_back( sub );
        }
        for( int i = 0; i < Ns.size(); ++i ) {
            int j = 0;
            while( j < n && stoi(D[j]) < Ns[i] - '0' ) { ++j; }
            if( j < n && stoi(D[j]) == Ns[i] - '0' ) {
                if( i == Ns.size() - 1 ) {
                    ret += j + 1;
                    break;
                }
                ret += j * all[ Ns.size() - i - 1 ];
                continue;
            } else {
                ret += j * all[ Ns.size() - i - 1 ];
                break;
            }
        }
        return ret;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<string> d1{"1","3","5","7"};
    CHECK(s.atMostNGivenDigitSet( d1, 100 ) == 20 );
    vector<string> d2{"1","4","9"};
    CHECK(s.atMostNGivenDigitSet( d2, 1000000000 ) == 29523 );
    vector<string> d3{"3","4","9"};
    CHECK(s.atMostNGivenDigitSet( d3, 4 ) == 2 );
    vector<string> d4{"1"};
    CHECK(s.atMostNGivenDigitSet( d4, 838 ) == 3 );
}
