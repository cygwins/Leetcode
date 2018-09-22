/*
 * store all possibilities
 */
#include <set>
#include "catch.hpp"
using std::set;
using std::multiset;

class Solution {
public:
    set<multiset<int>> all;
    Solution() {
        all.clear();
        for(int n = 1; n <= 1e9; n *= 2) {
            all.insert( digits(n) );
        }
    }
    bool reorderedPowerOf2(int N) {
        return all.find( digits(N) ) != all.end();
    }
    multiset<int> digits(int i) {
        multiset<int> d;
        while(i) {
            d.insert(i % 10);
            i /= 10;
        }
        return d;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    CHECK(s.reorderedPowerOf2(1) == true);
    CHECK(s.reorderedPowerOf2(10) == false);
    CHECK(s.reorderedPowerOf2(16) == true);
    CHECK(s.reorderedPowerOf2(24) == false);
    CHECK(s.reorderedPowerOf2(46) == true);
    CHECK(s.reorderedPowerOf2(123567890) == true);
}
