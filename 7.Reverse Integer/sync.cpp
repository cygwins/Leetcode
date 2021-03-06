#include <iostream>
#include "catch.hpp"
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    int reverse(int x) {
        int result = 0;
        while (x)
        {
            pr = result * 10 + x % 10;
            if (result != pr / 10) return 0;
            result = pr;
            x /= 10;
        }
        return result;
    }
};

TEST_CASE("reversing int", "[reverse]") {
    Solution s;
    CHECK(s.reverse(123) == 321);
    CHECK(s.reverse(-123) == -321);
    CHECK(s.reverse(120) == 21);
    CHECK(s.reverse(1534236469) == 0);
    CHECK(s.reverse(-2147483648) == 0);
}
