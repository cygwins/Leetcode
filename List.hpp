#ifndef LIST_H_
#define LIST_H_
#include <string>
#include <memory>

namespace List
{

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) { }
};

ListNode* parseNode(std::string &s) { // take out first node
    size_t delim = s.find('-');
    std::string n = s.substr(0, delim);
    if(delim == std::string::npos) s.erase(s.begin(), s.end());
    else s.erase(s.begin(), s.begin() + delim + 2); // erase '->' too
    if(n.empty()) return nullptr;
    return new ListNode(std::stoi(n));
}

ListNode* parseList(std::string s) {
    if(s.empty()) return nullptr;
    ListNode *head = parseNode(s), *tail = head;
    while(!s.empty()) {
        tail -> next = parseNode(s);
        tail = tail -> next;
    }
    return head;
}

std::string printList(ListNode* head) {
    std::string out;
    while(head) {
        out += std::to_string(head -> val);
        if(head -> next) out += "->";
        head = head -> next;
    }
    return out;
}

}
#endif
