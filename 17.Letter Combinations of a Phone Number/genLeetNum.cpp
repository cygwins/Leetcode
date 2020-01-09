/*
 * DFS
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "catch.hpp"
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string &digits) {
        ans.clear();
        dfs(digits, "", 0);
        return ans;
    }
    void dfs(string &digits, string s, int d) {
        if( d && d == digits.size() ) {
            ans.push_back( s );
            return;
        }
        for( auto c : dict[digits[d] - '2'] ) dfs(digits, s + c, d + 1);
    }
private:
    vector<string> ans;
    vector<string> dict{"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
};

string capital(string s) {
    s[0] += 'A' - 'a';
    return s;
}

int main() {
    Solution S;
    string s;
    cout << "Enter Number:" << endl;
    cin >> s;
    for(auto c : s) {
        if(c < '2' || c > '9') {
            cerr << "Error: only accept digits from 2 to 9" << endl;
            return 1;
        }
    }
    vector<string> comb = S.letterCombinations(s);
    // cout << "All possible combinations:" << endl;
    // for(auto w : comb) {
    //     cout << w << endl;
    // }
    vector<string> good; // find combinations that are actually english words
    string words = "/usr/share/dict/words";
    ifstream fin;
	fin.open(words);
	if(fin.fail()) {
		cout << "Unable to open " + words << endl;
        return 1;
	}
    cout << "Searching..." << endl;
	while(!fin.eof())
	{
		string temp = "";
		getline(fin,temp);
        for(auto w : comb) {
            if(w == temp || capital(w) == temp) {
                good.push_back(temp);
            }
        }
	}
    if(good.size()) {
        cout << endl << "Found " << good.size() << " useful word(s) out of " << comb.size() << " combinations:" << endl;
        for(auto g : good) {
            cout << "> " << g << endl;
        }
    } else {
        cout << "Unfortunately, all " << comb.size() << " combinations are not legit English words." << endl;
    }
	fin.close();
    return 0;
}
