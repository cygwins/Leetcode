#ifndef TREE_H_
#define TREE_H_
#include <algorithm>
#include <string>
#include <queue>
#include <cctype>
#include <locale>
#include <memory>

namespace Tree
{

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
};

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

TreeNode* parseNode(std::string &s) { // take out first node
    trim(s);
    size_t delim = s.find(',');
    std::string n = s.substr(0, delim);
    if(delim == std::string::npos) s.erase(s.begin(), s.end());
    else s.erase(s.begin(), s.begin() + delim + 1); // erase ',' too
    trim(n);
    if(n.empty() || n == std::string{"null"}) return nullptr;
    return new TreeNode(std::stoi(n));
}

TreeNode* parseTree(std::string s) {
    trim(s);
    if(s.empty()) return nullptr;
    if(s.front() == '[') s.erase(s.begin());
    if(s.back() == ']') s.erase(s.end() - 1);
    trim(s);
    if(s.empty()) return nullptr;
    TreeNode *root = parseNode(s);
    std::queue<TreeNode*> q;
    q.push(root);
    while(!s.empty()) {
        auto now = q.front();
        q.pop();
        now -> left = parseNode(s);
        if(now -> left) q.push(now -> left);
        now -> right = parseNode(s);
        if(now -> right) q.push(now -> right);
    }
    return root;
}

std::string printTree(TreeNode* root) {
    if(!root) return std::string{"[]"};
    std::vector<std::string> out;
    std::queue<TreeNode*> q;
    q.push(root); out.push_back(std::to_string(root -> val));
    while(!q.empty()) {
        auto now = q.front();
        q.pop();
        if(now -> left) {
            out.push_back(std::to_string(now -> left -> val));
            q.push(now -> left);
        } else out.push_back(std::string{"null"});
        if(now -> right) {
            out.push_back(std::to_string(now -> right -> val));
            q.push(now -> right);
        } else out.push_back(std::string{"null"});
    }
    auto last = out.end();
    while(last != out.begin() && *(last - 1) == std::string{"null"}) --last;
    out.erase(last, out.end());
    std::string s{"[" + std::to_string(root -> val)};
    for(auto it = out.begin() + 1; it != out.end(); ++it) s += "," + *it;
    s += "]";
    return s;
}

}
#endif
