#include <iostream>
#include <cstdio>
#include <string>
#include "catch.hpp"
using std::string;
using std::cin;

static int n = []() { 
    std::ios::sync_with_stdio(false); 
    cin.tie(NULL);  
    return 0; 
}();

class Solution {
public:
    int titleToNumber(string s) {
        int n = 0;
        for(int i = 0; i < s.size(); ++i) {
            n *= 26;
            n += static_cast<int>(s[i]) - static_cast<int>('A') + 1;
        }
        return n;
    }
};

TEST_CASE("parsing to int", "[titleToNumber]") {
    Solution s;
    CHECK(s.titleToNumber("A") == 1);
    CHECK(s.titleToNumber("AB") == 28);
    CHECK(s.titleToNumber("ZY") == 701);
}
