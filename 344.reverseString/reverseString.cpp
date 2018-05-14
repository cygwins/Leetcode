#include <iostream>
#include <algorithm>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

class Solution {
public:
    inline string reverseString(string &s) {
        std::reverse(s.begin(), s.end()); // need #include <algorithm>
        return s;
    }
};

int main() {
    string str;
    cin >> str;
    Solution mySolution;
    cout << mySolution.reverseString(str) << endl;
    return 0;
}
