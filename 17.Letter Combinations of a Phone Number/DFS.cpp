/*
 * DFS
 */
#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include "catch.hpp"
using std::vector;
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string &digits) {
        ans.clear();
        dfs(digits, "", 0);
        return ans;
    }
    void dfs(string &digits, string s, int d) {
        if( d && d == digits.size() ) {
            ans.push_back( s );
            return;
        }
        for( auto c : dict[digits[d] - '2'] ) dfs(digits, s + c, d + 1);
    }
private:
    vector<string> ans;
    vector<string> dict{"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    string str = "23";
    vector<string> ans = s.letterCombinations(str);
    vector<string> stdans{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"};
    bool miss = false;
    for(string s : stdans) {
        if(find(ans.begin(), ans.end(), s) == ans.end()) {
            miss = true;
        }
    }
    CHECK(!miss);
    CHECK(ans.size() == stdans.size());
}
