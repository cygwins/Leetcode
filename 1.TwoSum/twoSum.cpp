/*
 * use map to record index and search appeared number
 */
#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::map;
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) { // O(n * log(n)) if search is log(n)
        if(nums.size() == 2) { return {0, 1}; } // solution existence guaranteed
        map<int, int> indices; // exactly one solution -> duplicates are useless or answer
        for(int i = 0; i != nums.size(); ++i) {
            auto it = indices.find(target - nums[i]);
            if(it != indices.end()) { // found
                return {indices[target - nums[i]], i};
            }
            indices.insert({nums[i], i}); // will not insert duplicate
        }
        // will not reach here
    }
};

int main() {
    int target, num;
    std::vector<int> nums;
    cout << "target: ";
    cin >> target;
    cout << "nums: ";
    while(cin >> num) {
        nums.push_back(num);
    }
    Solution mySolution;
    for(auto &i : mySolution.twoSum(nums, target)) { cout << i << " " << endl; }
    return 0;
}
