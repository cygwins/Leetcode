/*
 * use map to record indices pair and their sum, search appeared number
 */
#include <iostream>
// #include <algorithm>
#include <vector>
#include <map>
#include <set>

using std::vector;
using std::set;
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
        if(nums.size() < 3) {
            return vector<vector<int>>{};
        } // no solution
        sort(nums.begin(), nums.end()); // sort in ascending order
        if(nums[0] > 0 || nums[nums.size() - 1] < 0) {
            return vector<vector<int>>{};
        } // no solution
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
        set<vector<int>> answers;
        for(size_t a = 0; a < nums.size() - 2 && nums[a] <= 0; ++a) {
            size_t b = a + 1;
            size_t c = nums.size() - 1;
            while(b < c) {
                int sum = nums[a] + nums[b] + nums[c];
                /*
                cout << "   nums[" << a << "] = " << nums[a]
                     << " + nums[" << b << "] = " << nums[b]
                     << " + nums[" << c << "] = " << nums[c]
                     << " = " << sum << (sum == 0 ? " == " :
                         (sum < 0 ? " < " : " > ")) << "0" << endl;
                */
                if(sum == 0) {
                    answers.insert({nums[a], nums[b], nums[c]});
                    ++b;
                    --c;
                }
                else if (sum < 0) { ++b; }
                else if (sum > 0) { --c; }
            }
        }
        return vector<vector<int>>(answers.begin(), answers.end());
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
