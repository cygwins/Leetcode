/*
 * using stack to process the string
 * space complexity is O(n), not O(1)
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
        return process(S) == process(T);
    }
    string process(string &S) {
        stack<char> s;
        string p;
        for(auto &c : S) {
            if(c == '#') { if (!s.empty()) s.pop(); }
            else s.push(c);
        }
        while(!s.empty()) {
            p += string{s.top()};
            s.pop();
        }
        return p;
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
