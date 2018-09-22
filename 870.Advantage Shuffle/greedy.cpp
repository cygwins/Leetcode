/*
 * greedy
 */
#include <vector>
#include <set>
#include "catch.hpp"
using std::vector;
using std::multiset;

class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        multiset<int> Aset;
        vector<int> ans;
        for(int &a : A) {
            Aset.insert(a);
        }
        for(int &b : B) {
            auto it = Aset.upper_bound(b); // try to win less
            if(it == Aset.end()) { // can't win, use worst horse
                it = Aset.begin();
            }
            ans.push_back(*it);
            Aset.erase(it);
        }
        return ans;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<int> A1{2,7,11,15}, B1{1,10,4,11}, C1{2,11,7,15};
    CHECK(s.advantageCount(A1, B1) == C1);
    vector<int> A2{12,24,8,32}, B2{13,25,32,11}, C2{24,32,8,12};
    CHECK(s.advantageCount(A2, B2) == C2);
}
