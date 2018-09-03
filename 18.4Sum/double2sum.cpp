/*
 * hash all pairs, use 2sum method on pairs
 */
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include "catch.hpp"
using std::vector;
using std::sort;
using std::map;
using std::set;
using std::pair;
using std::make_pair;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        if( nums.empty() ) return {};
        sort( nums.begin(), nums.end() );
        // erase any duplicant that has more than 4 copies
        for( int i = 4; i < nums.size(); ) {
            if( nums[i] == nums[i - 4] ) {
                nums.erase( nums.begin() + i );
            } else {
                ++i;
            }
        }
        // construct all possible pairs
        map<int, set<pair<int,int>>> pairs;
        for( int i = 0; i < nums.size() - 1; ++i ) {
            for( int j = i + 1; j < nums.size(); ++j ) {
                int sum = nums[i] + nums[j];
                auto p = make_pair( i, j );
                if( pairs.find( sum ) == pairs.end() ||
                    pairs[sum].find( p ) == pairs[sum].end() ) {
                    pairs[sum].insert( p );
                }
            }
        }
        // use 2 sum method (hash check) to pairs (rather than to numbers)
        set<vector<int>> ans;
        for( auto psum : pairs ) {
            int t = target - psum.first;
            if( psum.first > t ) break; // t already checked as first pair sum
            if( pairs.find( t ) != pairs.end() ) {
                for( auto p : psum.second ) {
                    int a = p.first, b = p.second;
                    for( auto com : pairs[t] ) { // complement pair
                        int c = com.first, d = com.second;
                        if( c != a && c != b && d != a && d != b ) {
                            auto quad = vector<int>{ nums[a], nums[b], nums[c], nums[d] };
                            sort( quad.begin(), quad.end() );
                            ans.insert( quad );
                        }
                    }
                }
            }
        }
        return vector<vector<int>>( ans.begin(), ans.end() );
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<int> nums1{1, 0, -1, 0, -2, 2};
    vector<vector<int>> ans1{ {-2, -1, 1, 2}, {-2,  0, 0, 2}, {-1,  0, 0, 1} };
    CHECK(s.fourSum(nums1, 0) == ans1);
    vector<int> nums2;
    vector<vector<int>> ans2;
    CHECK(s.fourSum(nums2, 0) == ans2);
}
