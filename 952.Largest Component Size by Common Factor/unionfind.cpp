/*
 * simply union find would Time Limit Exceed, use prime fators of numbers instead
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
#include "catch.hpp"
using std::vector;
using std::set;
using std::swap;
using std::unordered_map;
using std::max;
using std::cout;
using std::endl;

class Solution {
public:
    Solution() {
        init();
    }
    int largestComponentSize(vector<int>& A) {
        unordered_map<int, int> parent, count;
        for(auto a : A) {
            // cout << a << " = ";
            if(a == 1) continue;
            set<int> ps = decompose(a);
            // for(int p : ps) cout << p << ", "; cout << endl;
            for(int p : ps) { // create new union if necessary
                if(parent.find(p) == parent.end()) {
                    parent[p] = p;
                    count[p] = 0;
                }
            }
            ps = ancestor(parent, ps);
            // for(int p : ps) cout << p << ", "; cout << endl;
            int root = *ps.begin(); // the smallest prime factor of the group "a" belong to
            for(int p : ps) root = join(parent, count, root, p);
            ++count[root];
            // cout << "root = " << root << endl;
            // for(auto &p : count) cout << p.first << "(" << p.second << "), "; cout << endl;
        }
        int c = 1;
        for(auto &p : count) c = max(c, p.second);
        return c;
    }
    int find(unordered_map<int, int> &parent, int a) {
        if(parent[a] != a) parent[a] = find(parent, parent[a]);
        return parent[a];
    }
    int join(unordered_map<int, int> &parent, unordered_map<int, int> &count, int a, int b) {
        a = find(parent, a);
        b = find(parent, b);
        if(a > b) swap(a, b);
        if(a < b) {
            parent[b] = a;
            count[a] += count[b];
        }
        return a;
    }
    set<int> decompose(int n) {
        set<int> ps;
        for(auto p = primes.begin(); p != primes.end() && !isPrime[n]; ++p) {
            if(n % *p == 0) {
                ps.insert(*p);
                while(n % *p == 0) n /= *p;
            }
        }
        if(n > 1 && isPrime[n]) ps.insert(n);
        return ps;
    }
    set<int> ancestor(unordered_map<int, int> &parent, set<int> &primes) {
        set<int> ans;
        for(int p : primes) ans.insert(parent[p]);
        return ans;
    }
    int UB; // upperbound
    vector<bool> isPrime;
    set<int> primes;
    void init() {
        UB = 100001;
        isPrime = vector<bool>(UB, true);
        for(int i = 2; i < UB; ++i) if(isPrime[i]) {
            primes.insert(i);
            for(int j = 2; j * i < UB; ++j) isPrime[j * i] = false;
        }
    }
};

TEST_CASE("union-find", "[largestComponentSize]") {
    Solution s;
    vector<int> nums1{65,35,43,76,15,11,81,22,55,92,31};
    CHECK(s.largestComponentSize(nums1) == 9);
    vector<int> nums2{2,3,6,7,4,12,21,39};
    CHECK(s.largestComponentSize(nums2) == 8);
    vector<int> nums3{1,2,3,4,5,6,7,8,9};
    CHECK(s.largestComponentSize(nums3) == 6);
    vector<int> nums4{32,69,28,9,44,86,14,15,54,23,57,27,60};
    CHECK(s.largestComponentSize(nums4) == 13);
}
