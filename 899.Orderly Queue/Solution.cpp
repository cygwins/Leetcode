/*
 * brief
 */
#include <string>
#include <set>
#include "catch.hpp"
using std::string;
using std::multiset;

class Solution {
public:
    string orderlyQueue(string S, int K) {
    if( K >= 2 ) { // least possible lexicographical order string is reachable
        multiset<char> s;
        for(auto c : S) s.insert(c);
        string ans;
        for(auto c : s) ans += c;
        return ans;
    } else { // only shifting
        multiset<string> s;
        auto per = S;
        for(int i = 0; i < S.size(); ++i) {
            s.insert(per);
            per = per.substr(1) + per[0];
        }
        return *s.begin();
    }
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    CHECK(s.orderlyQueue("cba", 1) == "acb");
    CHECK(s.orderlyQueue("baaca", 2) == "aaabc");
}
