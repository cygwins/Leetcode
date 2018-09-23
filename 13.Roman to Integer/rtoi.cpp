#include <iostream>
#include <string>
#include <unordered_map>
#include "catch.hpp"
using std::string;
using std::cin;
using std::unordered_map;

class Solution {
public:
    int romanToInt(string s) {
        if(s.empty()) return 0;
        int n = R[s[0]];
        for(unsigned i = 1 ; i < s.size(); ++i) {
            n += R[s[i]];
            n -= R[s[i-1]] < R[s[i]] ? 2 * R[s[i-1]] : 0;
        }
        return n;
    }
    unordered_map<char, int> R = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
};

TEST_CASE("parsing to int", "[romanToInt]") {
    Solution s;
    CHECK(s.romanToInt("III") == 3);
    CHECK(s.romanToInt("IV") == 4);
    CHECK(s.romanToInt("IX") == 9);
    CHECK(s.romanToInt("LVIII") == 58);
    CHECK(s.romanToInt("MCMXCIV") == 1994);
}
