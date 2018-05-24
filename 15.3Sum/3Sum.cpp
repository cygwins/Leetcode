/*
 * use map to record indices pair and their sum, search appeared number
 */
#include <iostream>
// #include <algorithm>
#include <vector>
#include <map>

using std::vector;
using std::multimap;
using std::pair;
using std::cin;
using std::cout;
using std::endl;

void input(vector<int> &nums) {
    int num;
    cout << "nums: ";
    while(cin >> num) {
        nums.push_back(num);
    }
}

void output(vector<vector<int>> &nums) {
    for(auto &v : nums) {
        for(auto &i : v) {
            cout << i << " ";
        }
        cout << endl;
    }
}

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) { // O(n^2 * log(n)) if search is log(n)
        if(nums.size() < 3) { return {}; } // no solution
        sort(nums.begin(), nums.end()); // sort in ascending order
        vector<vector<int>> answers;
        multimap<int, pair<int, int>> twoSum; // can be added up by two number
        for(size_t i = 0; i != nums.size(); ++i) { // consider nums[i] as third in triplet
            auto twoRange = twoSum.equal_range(0 - nums[i]); // all matched first two's
            for(auto two = twoRange.first; two != twoRange.second; ++two) {
                vector<int> ans{two->second.first, two->second.second, nums[i]};
                if(find(answers.begin(), answers.end(), ans) == answers.end()) {
                    answers.push_back(ans); // new answer
                    // output(answers);
                }
            }
            if(i > 1 && nums[i] == nums[i - 2]) { continue; } // no need to update pair
            if(i > 0 && nums[i] == nums[i - 1]) { // only update this pair
                twoSum.insert({nums[i]+nums[i], {nums[i], nums[i]}});
                continue;
            }
            for(size_t j = 0; j != i; ++j) { // update pair
                twoSum.insert({nums[j]+nums[i], {nums[j], nums[i]}});
            }
        }
        sort(answers.begin(), answers.end());
        return answers;
    }
};

int main() {
    vector<int> nums;
    input(nums);
    Solution mySolution;
    vector<vector<int>> ans = mySolution.threeSum(nums);
    output(ans);
    return 0;
}
