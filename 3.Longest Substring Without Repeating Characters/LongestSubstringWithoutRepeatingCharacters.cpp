/* 
 * greedy push tail of candidate substring, update head if repeat
 */
#include <iostream>
#include <map>
#include <string>
using std::string;

class Solution {
public:
    int lengthOfLongestSubstring(string &s) {
        size_t maxLen = 0, curLen;
        std::map<char, string::iterator> last; // record last position of the character
        for(auto head = s.begin(), tail = s.begin(); tail != s.end(); ++tail) {
            auto lastPos = last.find(*tail);
            if(lastPos == last.end() || lastPos -> second < head) { // *tail(character) not in current substring
                curLen = tail - head + 1; // only here could possibly beat maxLen
                maxLen = maxLen > curLen ? maxLen : curLen;
            }
            else { // *tail is repeated in current substring
                head = lastPos -> second; ++head; // restart after first repeated char
            }
            last[*tail] = tail; // update last appearance
        }
        return maxLen;
    }
};

int main() {
    Solution S;
    string s{"abcabcbb"};
    int m = S.lengthOfLongestSubstring(s);
    return 0;
}
