#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using std::vector;
using std::string;
using std::unordered_map;
using std::stoi;
using std::to_string;

class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> counts;
        for(string &s : cpdomains) {
            size_t space;
            int c = stoi(s, &space), dot1 = s.find("."), dot2 = s.rfind(".");
            inc(counts, s.substr(space + 1), c); // whole domain
            inc(counts, s.substr(dot1 + 1), c); // sub domain
            if(dot2 != dot1) inc(counts, s.substr(dot2 + 1), c); // sub sub domain
        }
        vector<string> answer;
        for(auto &p : counts) {
            answer.push_back(to_string(p.second) + " " + p.first);
        }
        return answer;
    }
    void inc(unordered_map<string, int> &m, string s, int &c) {
        if(m.find(s) == m.end()) m[s] = c;
        else m[s] += c;
    }
};

int main() {
    Solution s;
    vector<string> c{"900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"};
    vector<string> a = s.subdomainVisits(c);
    for(auto &s : a) std::cout << s << std::endl;
    return 0;
}
