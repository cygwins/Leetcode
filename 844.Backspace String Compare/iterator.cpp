/*
 * using iterator to process the string
 * space complexity is O(1)
 */
#include <iostream>
#include <string>
#include <stack>
#include "catch.hpp"
using std::string;
using std::cin;
using std::stack;

class Solution {
public:
    bool backspaceCompare(string S, string T) {
        process(S);
        process(T);
        return S == T;
    }
    void process(string &S) {
        auto it = S.begin();
        for(auto &c : S) {
            if(c == '#') { if (it != S.begin()) --it; }
            else *it++ = c;
        }
        S.erase(it, S.end());
    }
};

TEST_CASE("simulating", "[backspaceCompare]") {
    Solution s;
    string S1{"ab#c"}, T1{"ad#c"};
    CHECK(s.backspaceCompare(S1, T1) == true);
    string S2{"ab##"}, T2{"c#d#"};
    CHECK(s.backspaceCompare(S2, T2) == true);
    string S3{"a##c"}, T3{"#a#c"};
    CHECK(s.backspaceCompare(S3, T3) == true);
    string S4{"a#c"}, T4{"b"};
    CHECK(s.backspaceCompare(S4, T4) == false);
    string S5{"y#fo##f"}, T5{"y#f#o##f"};
    CHECK(s.backspaceCompare(S5, T5) == true);
}
