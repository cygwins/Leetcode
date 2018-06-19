/*
 * carry from lower digit if neccessary
 */
#include <vector>
#include "catch.hpp"
using std::vector;

class Solution {
public:
    vector<int> plusOne( vector<int>& digits ) {
        vector<int> d( digits );
        int i = d.size() - 1;
        while( i >= 0 && d[i] == 9 ) {
            d[i] = 0;
            --i;
        }
        if( i >= 0 ) ++d[i];
        else d.insert( d.begin(), 1 );
        return d;
    }
};

TEST_CASE("carrying", "[plusOne]") {
    Solution s;
    vector<int> num1{1,2,3};
    CHECK(s.plusOne(num1) == vector<int>{1,2,4});
    vector<int> num2{9,9,9};
    CHECK(s.plusOne(num2) == vector<int>{1,0,0,0});
}
