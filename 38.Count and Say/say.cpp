/*
 * just count and say...
 */
#include <string>
#include "catch.hpp"
using std::string;
using std::to_string;

class Solution {
public:
    string countAndSay( int n ) {
        string s = "1";
        for(int i = 1; i < n; ++i) s = countAndSay(s);
        return s;
    }
    string countAndSay( string &s ) {
        string say{""};
        int count, digit, head = 0, tail = 0;
        while( head < s.size() ) {
            count = 0, digit = s[tail] - '0';
            for( ; head < s.size() && s[head] == s[tail]; ++head ) ++count;
            say += to_string( count );
            say += to_string( digit );
            tail = head;
        }
        return say;
    }
};

TEST_CASE("counting and saying", "[countAndSay]") {
    Solution s;
    CHECK(s.countAndSay(1) == string{"1"});
    CHECK(s.countAndSay(2) == string{"11"});
    CHECK(s.countAndSay(4) == string{"1211"});
    CHECK(s.countAndSay(15) == string{"311311222113111231131112132112311321322112111312211312111322212311322113212221"}); // A005150 - OEIS
}
