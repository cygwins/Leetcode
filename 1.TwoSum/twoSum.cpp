#include <iostream>
#include <vector>
#include <map>

using std::vector;
using std::multimap;
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> answer;
        multimap<int, int> indices;
        int count = 0;
        for(auto &n : nums) {
            indices.insert({n, count++}); // {num, index}, auto sorted by num
        }
        auto head = indices.begin(); // smallest num
        auto tail = indices.end();
        --tail; // biggest num
        while(head != tail) {
            if(head -> first + tail -> first == target) { // match!
                answer.push_back(head -> second); // return indices
                answer.push_back(tail -> second);
                break;
            }
            if(head -> first + tail -> first < target) { // more!
                ++head;
                continue;
            }
            if(head -> first + tail -> first > target) { // less!
                --tail;
                continue;
            }
        }
        return answer;
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
