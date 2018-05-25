/*
 * use map to record indices pair and their sum, search appeared number
 */
#include <iostream>
// #include <algorithm>
#include <vector>
#include <map>
#include <set>

using std::vector;
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
        if(nums.size() < 3) { // insufficient nums
            return {};
        }
        sort(nums.begin(), nums.end()); // sort in ascending order
        if(nums[0] > 0 || nums[nums.size() - 1] < 0) { // too big / too small
            return {};
        }
        int prev = nums[0] + 1, count = 0; // remove unnecessary repeat
        for(auto it = nums.begin(); it != nums.end(); ) {
            if(*it != prev) {
                count = 1;
                prev = *it;
                ++it;
            }
            else if (count < 2 || (count < 3 && *it == 0)) {
                ++count;
                ++it;
            }
            else {
                nums.erase(it);
            }
        }
        vector<vector<int>> answers;
        size_t a = 0, b, c;
        while(a < nums.size() - 2 && nums[a] <= 0) {
            b = a + 1;
            c = nums.size() - 1;
            while(b < c) {
                int sum = nums[a] + nums[b] + nums[c];
                // cout << nums[a] << " + " << nums[b] << " + " << nums[c] << " = " << sum
                //      << (sum == 0 ? " ==" : (sum < 0 ? " <" : " >")) << " 0" << endl;
                if(sum == 0) {
                    answers.push_back({nums[a], nums[b], nums[c]});
                    do { ++b; } while(b < c && nums[b] == nums[b - 1]);
                    do { --c; } while(b < c && nums[c] == nums[c + 1]);
                }
                else if (sum < 0) { do { ++b; } while(b < c && nums[b] == nums[b - 1]); }
                else if (sum > 0) { do { --c; } while(b < c && nums[c] == nums[c + 1]); }
            }
            do { ++a; } while(a < nums.size() && nums[a] == nums[a - 1]);
        }
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
