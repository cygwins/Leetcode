/*
 * brief
 */
#include <iostream>
#include "catch.hpp"
#include "../List.hpp"
using namespace List;

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if( head == nullptr ) return nullptr;
        if( head -> next == nullptr ) return head;
        auto tail = head, tmp = head -> next;
        head = head -> next;
        // switch first two
        tail -> next = tmp -> next;
        tmp -> next = tail;
        while((tmp = tail -> next) && tmp -> next) {
            tail -> next = tmp -> next;
            tmp -> next = tmp -> next -> next;
            tail -> next -> next = tmp;
            tail = tmp;
        }
        return head;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    CHECK(printList(s.swapPairs(parseList("1->2->3->4"))) == "2->1->4->3");
}
