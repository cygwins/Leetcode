#include "catch.hpp"

class Solution {
public:
    int reverse(int x) {
        int sign = x < 0 ? -1 : 1, answer = 0, tmp;
        while(x) {
            tmp = answer * 10 + x % 10 * sign; // x and x % 10 has same sign
            if(tmp / 10 != answer) return 0; // check overflow more generally
            answer = tmp;
            x /= 10;
        }
        return answer * sign;
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
